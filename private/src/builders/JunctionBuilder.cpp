#include <builders/JunctionBuilder.h>

#include <algorithm>
#include <unordered_map>
#include <utility>

void JunctionBuilder::add_link(const Link& link) {
  if (std::find_if(m_result.m_links.begin(), m_result.m_links.end(),
                   [&link](const Link& link_internal) {
                     return link.get_id() == link_internal.get_id();
                   }) == m_result.m_links.end()) {
    m_result.m_links.emplace_back(link);
  }
}

void JunctionBuilder::add_links(const std::vector<Link>& links) {
  std::for_each(links.begin(), links.end(),
                [this](const Link& link) { add_link(link); });
}

void JunctionBuilder::set_coordinate(const GeoCoordinate& coord) {
  m_result.m_coordinate = coord;
}

Junction JunctionBuilder::build() {
  auto res = m_result;
  m_result = {};
  if (res.m_links.empty()) {
    return {};
  }
  if (!res.m_coordinate.is_valid()) {
    std::unordered_map<GeoCoordinate, int> common_points;
    common_points[res.m_links[0].get_geometry().front()]++;
    common_points[res.m_links[0].get_geometry().back()]++;
    common_points[res.m_links[1].get_geometry().front()]++;
    common_points[res.m_links[1].get_geometry().back()]++;
    auto it = std::find_if(std::begin(common_points), std::end(common_points),
                           [](const auto& item) { return item.second == 2; });
    if (it == std::end(common_points)) {
      return {};
    }
    const GeoCoordinate& common_point = it->first;
    if (std::any_of(std::begin(res.m_links), std::end(res.m_links),
                    [&common_point](const Link& link) {
                      return std::none_of(
                          std::begin(link.get_geometry()),
                          std::end(link.get_geometry()),
                          [&common_point](const GeoCoordinate& coord) {
                            return coord == common_point;
                          });
                    })) {
      return {};
    }
    res.m_coordinate = common_point;
  }
  std::array<std::pair<uint64_t, uint64_t>, 1> id = {std::make_pair(
      *reinterpret_cast<const uint64_t*>(&res.m_coordinate.get_latitude()),
      *reinterpret_cast<const uint64_t*>(&res.m_coordinate.get_longitude()))};
  res.m_id = id;

  return res;
}