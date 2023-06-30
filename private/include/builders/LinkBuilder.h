#pragma once
#include <common/Link.h>

class LinkBuilder {
 public:
  void set_id(uint32_t id);
  void add_geom_point(const GeoCoordinate& point);
  void add_geom_points(const std::vector<GeoCoordinate>& points);
  Link build();

 private:
  Link m_result;
};