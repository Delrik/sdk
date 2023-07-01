#pragma once

#include <MapData/AbstractMapData.h>
#include <MapData/OsmMapDataStatistics.h>
#include <MapData/OsmXmlParser.h>

class OsmMapData : public AbstractMapData {
 public:
  OsmMapData();
  ~OsmMapData();

  bool load_data(const std::string& source) override;

 private:
  OsmXmlParser m_parser;
  OsmMapDataStatistics m_statistics;
};