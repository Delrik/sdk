#include <builders/LinkBuilder.h>

void LinkBuilder::set_id(uint32_t id) { m_result.m_id = id; }

void LinkBuilder::add_geom_point(const GeoCoordinate& point) {
  m_result.m_geometry.emplace_back(point);
}

Link LinkBuilder::build() {
  auto res = m_result;
  m_result = {};
  return res;
}