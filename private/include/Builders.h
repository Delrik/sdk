#pragma once

#include <builders/GeoCoordinateBuilder.h>
#include <builders/JunctionBuilder.h>
#include <builders/LinkBuilder.h>

struct Builders {
  static GeoCoordinateBuilder GetGeoCoordinateBuilder() {
    return GeoCoordinateBuilder;
  }
  static LinkBuilder GetLinkBuilder() { return LinkBuilder; }
  static JunctionBuilder GetJunctionBuilder() { return JunctionBuilder; }
}