#include <builders/JunctionBuilder.h>

#include <algorithm>
#include <unordered_map>
#include <utility>

void JunctionBuilder::set_id(uint32_t id) { m_result.m_id = id; }

void JunctionBuilder::add_link(const Link& link) {
  m_result.m_links.emplace_back(link);
}

void JunctionBuilder::add_links(const std::vector<Link>& links) {
  std::copy(links.begin(), links.end(), std::back_inserter(m_result.m_links));
}

Junction JunctionBuilder::build() {
  auto res = m_result;
  m_result = {};
  if (res.m_coordinate.is_valid()) {
    return res;
  }
  if (res.m_links.size() < 2) {
    return {};
  }
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
  return res;
}