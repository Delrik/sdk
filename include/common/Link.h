#pragma once

#include <common/GeoCoordinate.h>

#include <vector>

class Link : public Id {
 public:
  const std::vector<GeoCoordinate>& get_geometry() const { return m_geometry; }

 private:
  std::vector<GeoCoordinate> m_geometry;

 private:
  friend class LinkBuilder;
};