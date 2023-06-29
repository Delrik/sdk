#pragma once

#include <cstdint>

class Id {
 public:
  uint32_t get_id() const { return m_id; }

 protected:
  uint32_t m_id;
};