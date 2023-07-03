#pragma once

#include <Id.h>
#include <common/GeoCoordinate.h>

#include <vector>

class Link : public Id<2> {
 public:
  const std::vector<GeoCoordinate>& get_geometry() const { return m_geometry; }

 private:
  std::vector<GeoCoordinate> m_geometry;

 public:
  bool operator==(const Link& other) const {
    if (m_geometry.size() != other.m_geometry.size()) {
      return false;
    }
    auto it = m_geometry.begin();
    if (*it == other.m_geometry.front()) {
      auto other_it = other.m_geometry.begin();
      while (it != m_geometry.end()) {
        if (*it != *other_it) {
          return false;
        }
        ++it;
        ++other_it;
      }
    } else if (*it == other.m_geometry.back()) {
      auto other_it = other.m_geometry.rbegin();
      while (it != m_geometry.end()) {
        if (*it != *other_it) {
          return false;
        }
        ++it;
        ++other_it;
      }
    } else {
      return false;
    }
    return true;
  }

 private:
  friend class LinkBuilder;
};

template <>
struct std::hash<Link> {
  std::size_t operator()(Link const& link) const noexcept {
    auto id = link.get_id();
    std::size_t res = std::hash<decltype(id)>{}(id);
    return res;
  }
};