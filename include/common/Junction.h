#pragma once

#include <common/Link.h>

class Junction : public Id<1> {
 private:
  std::vector<Link> m_links;
  GeoCoordinate m_coordinate;

 public:
  const std::vector<Link>& get_links() const { return m_links; }

  bool operator==(const Junction& other) const {
    if (m_coordinate != other.m_coordinate) {
      return false;
    }
    if (m_links.size() != other.m_links.size()) {
      return false;
    }
    for (const auto& item : m_links) {
      if (std::none_of(other.m_links.begin(), other.m_links.end(),
                       [&item](const Link& link) { return item == link; })) {
        return false;
      }
    }
    return true;
  }

 private:
  friend class JunctionBuilder;
};

template <>
struct std::hash<Junction> {
  std::size_t operator()(Junction const& j) const noexcept {
    auto id = j.get_id();
    std::size_t res = std::hash<decltype(id)>{}(id);
    return res;
  }
};