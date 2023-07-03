#include <builders/GeoCoordinateBuilder.h>

void GeoCoordinateBuilder::set_coordinates(double lat, double lon) {
  m_result.m_latitude = lat;
  m_result.m_longitude = lon;
}

GeoCoordinate GeoCoordinateBuilder::build() {
  auto res = m_result;
  m_result = {};
  return res;
}