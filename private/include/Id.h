#pragma once

#include <algorithm>
#include <array>
#include <boost/container_hash/hash.hpp>
#include <cstdint>
#include <iterator>
#include <set>
#include <utility>

template <uint8_t ids_size = 1>
struct Id {
  const Id& get_id() const { return *this; }
  bool operator==(const Id<ids_size>& other) const {
    if (m_id.size() != other.m_id.size()) {
      return false;
    }
    return std::all_of(
        m_id.begin(), m_id.end(),
        [&other](const std::pair<uint64_t, uint64_t>& item) {
          return std::any_of(
              other.m_id.begin(), other.m_id.end(),
              [&item](const std::pair<uint64_t, uint64_t>& other_item) {
                return other_item == item;
              });
        });
  }
  std::string to_str() const {
    std::stringstream str;
    std::for_each(m_id.begin(), m_id.end(),
                  [&str](const std::pair<uint64_t, uint64_t>& id) {
                    str << "{" << id.first << "," << id.second << "}";
                  });
    return str.str();
  }

 protected:
  std::array<std::pair<uint64_t, uint64_t>, ids_size> m_id;

 private:
  friend struct std::hash<Id<ids_size>>;
};

template <uint8_t ids_size>
struct std::hash<Id<ids_size>> {
  std::size_t operator()(Id<ids_size> const& coord) const noexcept {
    std::size_t result = 0;
    for (auto i : coord.m_id) {
      boost::hash_combine(result, i.first);
      boost::hash_combine(result, i.second);
    }
    return result;
  }
};