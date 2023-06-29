#pragma once

#include <common/GeoCoordinate.h>

#include <vector>

class Link : public Id {
 public:
  const std::vector<GeoCoordinate>& get_geometry() const { return m_geometry; }

 private:
  std::vector<GeoCoordinate> m_geometry;

 public:
  bool operator==(const Link& other) const {
    if (m_geometry.size() != other.m_geometry.size()) {
      return false;
    }
    for (auto i = 0; i < m_geometry.size(); ++i) {
      if (m_geometry[i] != other.m_geometry[i]) {
        return false;
      }
    }
    return true;
  }

 private:
  friend class LinkBuilder;
};