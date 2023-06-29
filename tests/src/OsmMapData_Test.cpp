#include <OsmMapData.h>
#include <gtest/gtest.h>

#include <memory>

const static std::string res_dir = "res/OsmMapData_Test/";

namespace {
std::string get_res_path(const std::string& str) { return res_dir + str; }
}  // namespace

class BaseOsmMapDataTest : public ::testing::Test {
 public:
  void SetUp() override { m_map = std::make_shared<OsmMapData>(); }

  std::shared_ptr<AbstractMapData> m_map;
};
/*
//--------------------------------------------------------------------------------------------------

TEST_F(BaseOsmMapDataTest, correct_points) {
  ASSERT_TRUE(m_map->load_data(get_res_path("initial_test.osm")));

  auto points = m_map->get_points();
  decltype(points) expected_points = {{1658892715, 50.0484352, 19.9578585},
                                      {1658892837, 50.0487473, 19.9575554},
                                      {1658892870, 50.0488517, 19.9574385},
                                      {8869531296, 50.0470099, 19.9560818},
                                      {3308660443, 50.0487668, 19.9576425}};
  for (const auto& point : expected_points) {
    EXPECT_NE(std::find_if(points.begin(), points.end(),
                           [&point](decltype(point) point_internal) {
                             return point_internal == point;
                           }),
              points.end())
        << "Expected point not found: " << point.get_latitude() << ", "
        << point.get_longitude();
  }
}

//--------------------------------------------------------------------------------------------------

TEST_F(BaseOsmMapDataTest, correct_links) {
  ASSERT_TRUE(m_map->load_data(get_res_path("initial_test.osm")));

  // Points
  auto points = m_map->get_points();
  decltype(points) expected_points = {{1658892715, 50.0484352, 19.9578585},
                                      {1658892837, 50.0487473, 19.9575554},
                                      {1658892870, 50.0488517, 19.9574385},
                                      {8869531296, 50.0470099, 19.9560818},
                                      {3308660443, 50.0487668, 19.9576425}};
  for (const auto& point : expected_points) {
    EXPECT_NE(std::find_if(points.begin(), points.end(),
                           [&point](decltype(point) point_internal) {
                             return point_internal == point;
                           }),
              points.end())
        << "Expected point not found: " << point.get_latitude() << ", "
        << point.get_longitude();
  }
  // Links
  auto links = m_map->get_links();
  decltype(links) expected_links = {};
  for (const auto& link : expected_links) {
    EXPECT_NE(std::find_if(links.begin(), links.end(),
                           [&link](decltype(link) link_internal) {
                             return link_internal == link;
                           }),
              links.end())
        << "Expected link not found: " << links.get_id();
  }
}

//--------------------------------------------------------------------------------------------------

TEST_F(BaseOsmMapDataTest, correct_junction) {
  ASSERT_TRUE(m_map->load_data(get_res_path("initial_test.osm")));

  // Points
  auto points = m_map->get_points();
  decltype(points) expected_points = {{1658892715, 50.0484352, 19.9578585},
                                      {1658892837, 50.0487473, 19.9575554},
                                      {1658892870, 50.0488517, 19.9574385},
                                      {8869531296, 50.0470099, 19.9560818},
                                      {3308660443, 50.0487668, 19.9576425}};
  for (const auto& point : expected_points) {
    EXPECT_NE(std::find_if(points.begin(), points.end(),
                           [&point](decltype(point) point_internal) {
                             return point_internal == point;
                           }),
              points.end())
        << "Expected point not found: " << point.get_latitude() << ", "
        << point.get_longitude();
  }
  // Links
  auto links = m_map->get_links();
  decltype(links) expected_links = {};
  for (const auto& link : expected_links) {
    EXPECT_NE(std::find_if(links.begin(), links.end(),
                           [&link](decltype(link) link_internal) {
                             return link_internal == link;
                           }),
              links.end())
        << "Expected link not found: " << link.get_id();
  }
  // Junctions
  auto junctions = m_map->get_junctions();
  decltype(junctions) expected_junctions = {};
  for (const auto& junction : expected_junctions) {
    EXPECT_NE(std::find_if(junctions.begin(), junctions.end(),
                           [&junction](decltype(junction) junction_internal) {
                             return junction_internal == junction;
                           }),
              junctions.end())
        << "Expected junction not found: " << junction.get_id();
  }
}*/