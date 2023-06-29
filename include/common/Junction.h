#pragma once

#include <common/Link.h>

class Junction : public Id {
 private:
  std::vector<Link> m_links;
  GeoCoordinate m_coordinate;

 private:
  friend class JunctionBuilder;
};