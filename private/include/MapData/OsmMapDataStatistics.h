#pragma once

#include <MapData/NodeData.h>
#include <MapData/WayData.h>
#include <common/Junction.h>

#include <unordered_map>
#include <unordered_set>

class OsmMapDataStatistics {
  struct NodeStats {
    double lat;
    double lon;
    // Counts as junction in case counter>1;
    uint32_t counter;
    // Ways id related to this node
    std::unordered_set<uint32_t> ways;

    bool is_junction() const { return counter > 1; }
  };

 public:
  OsmMapDataStatistics();
  OsmMapDataStatistics(const OsmMapDataStatistics& other);
  OsmMapDataStatistics(OsmMapDataStatistics&& other);
  OsmMapDataStatistics& operator=(const OsmMapDataStatistics& other);
  OsmMapDataStatistics& operator=(OsmMapDataStatistics&& other);
  ~OsmMapDataStatistics();

  void init();
  void process(const NodeData& node);
  void process(const WayData& way);

  std::pair<std::vector<Link>, std::vector<Junction>> get_data();

 private:
  void to_junction(const std::pair<uint32_t, NodeStats>& item);
  std::vector<Link> get_links(uint32_t way_id, uint32_t node_id);

 private:
  // <node_id,NodeStats>
  std::unordered_map<uint32_t, NodeStats> m_stats;
  std::unordered_map<uint32_t, WayData> m_ways;

  std::unordered_set<Link> m_links;
  std::unordered_set<Junction> m_junctions;
};