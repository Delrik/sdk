#pragma once

#include <common/Link.h>

class Junction : public Id {
 private:
  std::vector<Link> m_links;
  GeoCoordinate m_coordinate;

 public:
  bool operator==(const Junction& other) const {
    if (m_coordinate != other.m_coordinate) {
      return false;
    }
    if (m_links.size() != other.m_links.size()) {
      return false;
    }
    for (auto i = 0; i < m_links.size(); ++i) {
      if (m_links[i] != other.m_links[i]) {
        return false;
      }
    }
    return true;
  }

 private:
  friend class JunctionBuilder;
};