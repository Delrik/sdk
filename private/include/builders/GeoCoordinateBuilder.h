#pragma once
#include <common/GeoCoordinate.h>

class GeoCoordinateBuilder {
 public:
  void set_id(uint32_t id);
  void set_coordinates(double lat, double lon);
  GeoCoordinate build();

 private:
  GeoCoordinate m_result;
};