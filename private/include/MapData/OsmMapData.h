#pragma once

#include <MapData/AbstractMapData.h>
#include <MapData/OsmMapDataStatistics.h>
#include <MapData/OsmXmlParser.h>

class OsmMapData : public AbstractMapData {
 public:
  OsmMapData();
  OsmMapData(const OsmMapData& other);
  OsmMapData(OsmMapData&& other);
  OsmMapData& operator=(const OsmMapData& other);
  OsmMapData& operator=(OsmMapData&& other);
  ~OsmMapData();

  bool load_data(const std::string& source) override;

 private:
  OsmXmlParser m_parser;
  OsmMapDataStatistics m_statistics;
};