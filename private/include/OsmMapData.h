#pragma once

#include <AbstractMapData.h>

class OsmMapData : public AbstractMapData {
 public:
  OsmMapData();
  ~OsmMapData();

  bool load_data(const std::string& source) override;
};