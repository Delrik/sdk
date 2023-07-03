#include <Builders.h>
#include <MapData/OsmMapDataStatistics.h>

#include <cstdio>
#include <list>

OsmMapDataStatistics::OsmMapDataStatistics()
    : m_stats(), m_ways(), m_links(), m_junctions() {}

OsmMapDataStatistics::OsmMapDataStatistics(const OsmMapDataStatistics& other) {}
OsmMapDataStatistics::OsmMapDataStatistics(OsmMapDataStatistics&& other) {}
OsmMapDataStatistics& OsmMapDataStatistics::operator=(
    const OsmMapDataStatistics& other) {
  return *this;
}
OsmMapDataStatistics& OsmMapDataStatistics::operator=(
    OsmMapDataStatistics&& other) {
  return *this;
}
OsmMapDataStatistics::~OsmMapDataStatistics() {}

void OsmMapDataStatistics::init() {
  m_stats.clear();
  m_ways.clear();
}

void OsmMapDataStatistics::process(const NodeData& node) {
  m_stats[node.id].lat = node.lat;
  m_stats[node.id].lon = node.lon;
}

void OsmMapDataStatistics::process(const WayData& way) {
  for (auto i = 0; i < way.nodes.size(); ++i) {
    uint8_t incrementor = ((i == 0) || (i == way.nodes.size() - 1)) ? 2 : 1;
    auto node_id = way.nodes[i];
    m_stats[node_id].counter += incrementor;
    m_stats[node_id].ways.insert(way.id);
  }
  m_ways[way.id] = way;
}

std::pair<std::vector<Link>, std::vector<Junction>>
OsmMapDataStatistics::get_data() {
  for (const auto& item : m_stats) {
    if (item.second.is_junction()) {
      to_junction(item);
    }
  }

  std::vector<Junction> junctions_result(m_junctions.begin(),
                                         m_junctions.end());
  std::vector<Link> links_result(m_links.begin(), m_links.end());

  return std::make_pair(links_result, junctions_result);
}

void OsmMapDataStatistics::to_junction(
    const std::pair<uint32_t, NodeStats>& item) {
  if (item.first == 0 || !item.second.is_junction() ||
      item.second.ways.empty()) {
    return;
  }
  auto coord_builder = Builders::GetGeoCoordinateBuilder();
  auto junction_builder = Builders::GetJunctionBuilder();

  // Junction coordinates
  coord_builder.set_coordinates(item.second.lat, item.second.lon);
  junction_builder.set_coordinate(coord_builder.build());

  // Junction links
  for (const auto& way_id : item.second.ways) {
    auto links = get_links(way_id, item.first);
    junction_builder.add_links(links);
  }

  auto junction = junction_builder.build();

  const auto& links = junction.get_links();
  std::for_each(links.begin(), links.end(),
                [this](const Link& link) { m_links.insert(link); });
  m_junctions.insert(junction);
}

std::vector<Link> OsmMapDataStatistics::get_links(uint32_t way_id,
                                                  uint32_t node_id) {
  std::vector<Link> result;
  if (!m_ways.contains(way_id)) {
    return {};
  }

  const WayData& way = m_ways[way_id];

  // Check to the left
  std::list<uint32_t> l_node_ids = {node_id};
  {
    auto it = std::find(way.nodes.rbegin(), way.nodes.rend(), node_id);
    if (it == way.nodes.rend()) {
      return {};
    }
    for (it = it + 1; it != way.nodes.rend(); ++it) {
      l_node_ids.emplace_front(*it);
      if (m_stats[*it].is_junction()) {
        break;
      }
    }
  }

  // Check to the right
  std::list<uint32_t> r_node_ids = {node_id};
  {
    auto it = std::find(way.nodes.begin(), way.nodes.end(), node_id);
    if (it == way.nodes.end()) {
      return {};
    }
    for (it = it + 1; it != way.nodes.end(); ++it) {
      r_node_ids.emplace_front(*it);
      if (m_stats[*it].is_junction()) {
        break;
      }
    }
  }
  auto coord_builder = Builders::GetGeoCoordinateBuilder();
  auto link_builder = Builders::GetLinkBuilder();

  if (l_node_ids.size() > 1) {
    for (const auto& item : l_node_ids) {
      coord_builder.set_coordinates(m_stats[item].lat, m_stats[item].lon);
      link_builder.add_geom_point(coord_builder.build());
    }
    result.emplace_back(link_builder.build());
  }

  if (r_node_ids.size() > 1) {
    for (const auto& item : r_node_ids) {
      coord_builder.set_coordinates(m_stats[item].lat, m_stats[item].lon);
      link_builder.add_geom_point(coord_builder.build());
    }
    result.emplace_back(link_builder.build());
  }

  return result;
}