#pragma once

#include <boost/container_hash/hash.hpp>
#include <functional>
#include <limits>

class GeoCoordinate {
  using value_type = double;
  constexpr static value_type INVALID_COORD =
      std::numeric_limits<value_type>::min();

 public:
  GeoCoordinate() : m_latitude(INVALID_COORD), m_longitude(INVALID_COORD) {}
  GeoCoordinate(value_type lat, value_type lon)
      : m_latitude(lat), m_longitude(lon) {}

  const value_type& get_latitude() const { return m_latitude; }
  const value_type& get_longitude() const { return m_longitude; }
  bool is_valid() const {
    return m_latitude != INVALID_COORD && m_longitude != INVALID_COORD;
  }

 private:
  value_type m_latitude;
  value_type m_longitude;

 public:
  bool operator==(const GeoCoordinate& other) const {
    return fabs(m_latitude - other.m_latitude) <
               std::numeric_limits<value_type>::epsilon() &&
           fabs(m_longitude - other.m_longitude) <
               std::numeric_limits<value_type>::epsilon();
  }

 private:
  friend class GeoCoordinateBuilder;

  friend struct std::hash<GeoCoordinate>;
};

template <>
struct std::hash<GeoCoordinate> {
  std::size_t operator()(GeoCoordinate const& coord) const noexcept {
    std::size_t hash_1 = std::hash<double>{}(coord.m_latitude);
    std::size_t hash_2 = std::hash<double>{}(coord.m_longitude);
    boost::hash_combine(hash_1, hash_2);
    return hash_1;
  }
};