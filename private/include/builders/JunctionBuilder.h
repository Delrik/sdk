#pragma once
#include <common/Junction.h>

class JunctionBuilder {
 public:
  void set_id(uint32_t id);
  void add_link(const Link& link);
  void add_links(const std::vector<Link>& links);
  Junction build();

 private:
  Junction m_result;
};