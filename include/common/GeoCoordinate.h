#pragma once

#include <Id.h>

#include <functional>
#include <limits>

class GeoCoordinate : public Id {
  using value_type = double;
  constexpr static value_type INVALID_COORD =
      std::numeric_limits<value_type>::min();

 public:
  GeoCoordinate() {}
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
    return m_latitude == other.m_latitude && m_longitude == other.m_longitude;
  }

 private:
  friend class GeoCoordinateBuilder;
};

template <>
struct std::hash<GeoCoordinate> {
  std::size_t operator()(GeoCoordinate const& coord) const noexcept {
    std::size_t h1 = std::hash<double>{}(coord.get_latitude());
    std::size_t h2 = std::hash<double>{}(coord.get_longitude());
    std::size_t h3 = std::hash<uint32_t>{}(coord.get_id());
    return h1 ^ (h2 << 1) ^ (h3 << 2);
  }
};