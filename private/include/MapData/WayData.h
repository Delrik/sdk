#pragma once

#include <cstdint>
#include <vector>

struct WayData {
  uint32_t id;
  std::vector<uint32_t> nodes;
};