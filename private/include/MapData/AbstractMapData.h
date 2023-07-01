#pragma once
#include <common/Junction.h>

#include <string>
#include <vector>

class AbstractMapData {
 public:
  virtual ~AbstractMapData() = default;

  virtual bool load_data(const std::string& source) = 0;
  std::vector<GeoCoordinate> get_points() { return m_points; }
  std::vector<Link> get_links() { return m_links; }
  std::vector<Junction> get_junctions() { return m_junctions; }

 protected:
  std::vector<GeoCoordinate> m_points;
  std::vector<Link> m_links;
  std::vector<Junction> m_junctions;
};