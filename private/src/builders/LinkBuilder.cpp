#include <builders/LinkBuilder.h>

void LinkBuilder::add_geom_point(const GeoCoordinate& point) {
  m_result.m_geometry.emplace_back(point);
}

void LinkBuilder::add_geom_points(const std::vector<GeoCoordinate>& points) {
  std::copy(points.begin(), points.end(),
            std::back_inserter(m_result.m_geometry));
}

Link LinkBuilder::build() {
  auto res = m_result;
  if (res.m_geometry.size() < 2) {
    return {};
  }
  std::array<std::pair<uint64_t, uint64_t>, 2> id = {
      std::make_pair(*reinterpret_cast<const uint64_t*>(
                         &res.m_geometry.front().get_latitude()),
                     *reinterpret_cast<const uint64_t*>(
                         &res.m_geometry.front().get_longitude())),
      std::make_pair(*reinterpret_cast<const uint64_t*>(
                         &res.m_geometry.back().get_latitude()),
                     *reinterpret_cast<const uint64_t*>(
                         &res.m_geometry.back().get_longitude()))};
  res.m_id = id;
  m_result = {};
  return res;
}