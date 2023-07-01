#include <MapData/OsmMapData.h>

OsmMapData::OsmMapData() {}

OsmMapData::~OsmMapData() {}

bool OsmMapData::load_data(const std::string& source) {
  if (!m_parser.init(source)) {
    return false;
  }

  auto res = m_parser.parse_source();

  return true;
}