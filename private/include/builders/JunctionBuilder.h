#pragma once
#include <common/Junction.h>

class JunctionBuilder {
 public:
  void add_link(const Link& link);
  void add_links(const std::vector<Link>& links);
  void set_coordinate(const GeoCoordinate& coord);
  Junction build();

 private:
  Junction m_result;
};