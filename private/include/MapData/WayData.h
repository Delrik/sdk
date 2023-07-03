#pragma once

#include <cstdint>
#include <vector>

struct WayData {
  uint32_t id;
  std::vector<uint32_t> nodes;
};

template <>
struct std::hash<WayData> {
  std::size_t operator()(const WayData& way) const noexcept {
    return std::hash<uint32_t>{}(way.id);
  }
};

inline bool operator==(const WayData& l, const WayData& r) {
  return l.id == r.id && l.nodes.size() == r.nodes.size();
}