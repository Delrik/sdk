#pragma once
#include <common/Link.h>

class LinkBuilder {
 public:
  void set_id(uint32_t id);
  void add_geom_point(const GeoCoordinate& point);
  Link build();

 private:
  Link m_result;
};