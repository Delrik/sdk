#pragma once

#include <MapData/NodeData.h>
#include <MapData/WayData.h>

#include <rapidxml/rapidxml.hpp>
#include <string>
#include <variant>
#include <vector>

class OsmXmlParser {
 public:
  bool init(const std::string& source);
  std::vector<std::variant<NodeData, WayData>> parse_source();

 private:
  std::string m_file_data;

  std::vector<std::variant<NodeData, WayData>> m_result;

  void process_node(rapidxml::xml_node<>* node);
  void process_way(rapidxml::xml_node<>* node);
};