#include <MapData/OsmXmlParser.h>

#include <fstream>

bool OsmXmlParser::init(const std::string& source) {
  std::ifstream f(source);
  if (!f.is_open()) {
    return false;
  }

  f.seekg(0, std::ios::end);
  m_file_data.resize(f.tellg());
  f.seekg(0);
  f.read(m_file_data.data(), m_file_data.size());

  return true;
}

std::vector<std::variant<NodeData, WayData>> OsmXmlParser::parse_source() {
  rapidxml::xml_document<> doc;
  doc.parse<0>(m_file_data.data());
  auto current_node = doc.first_node();

  m_result.clear();
  while (auto node = current_node->first_node("node")) {
    process_node(node);
    current_node->remove_node(node);
  }

  while (auto way = current_node->first_node("way")) {
    process_way(way);
    current_node->remove_node(way);
  }
  return m_result;
}

void OsmXmlParser::process_node(rapidxml::xml_node<>* node) {
  NodeData node_item;
  node_item.id = std::stoul(node->first_attribute("id")->value());
  node_item.lat = std::stod(node->first_attribute("lat")->value());
  node_item.lon = std::stod(node->first_attribute("lon")->value());
  m_result.emplace_back(node_item);
}

void OsmXmlParser::process_way(rapidxml::xml_node<>* node) {
  WayData way_item;
  way_item.id = std::stoul(node->first_attribute("id")->value());
  while (auto nd = node->first_node("nd")) {
    way_item.nodes.emplace_back(
        std::stoul(nd->first_attribute("ref")->value()));
    node->remove_node(nd);
  }
  m_result.emplace_back(way_item);
}