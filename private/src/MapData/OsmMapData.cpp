#include <MapData/OsmMapData.h>

OsmMapData::OsmMapData() : m_statistics() {}
OsmMapData::OsmMapData(const OsmMapData& other) {}
OsmMapData::OsmMapData(OsmMapData&& other) {}
OsmMapData& OsmMapData::operator=(const OsmMapData& other) { return *this; }
OsmMapData& OsmMapData::operator=(OsmMapData&& other) { return *this; }

OsmMapData::~OsmMapData() {}

bool OsmMapData::load_data(const std::string& source) {
  if (!m_parser.init(source)) {
    return false;
  }

  std::vector<std::variant<NodeData, WayData>> xml_res =
      m_parser.parse_source();

  m_statistics.init();

  auto visitor = [this](const auto& item) { m_statistics.process(item); };

  for (const auto& item : xml_res) {
    std::visit(visitor, item);
  }

  std::tie(m_links, m_junctions) = m_statistics.get_data();

  return true;
}