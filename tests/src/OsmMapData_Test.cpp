#include <OsmMapData.h>
#include <builders/GeoCoordinateBuilder.h>
#include <builders/JunctionBuilder.h>
#include <builders/LinkBuilder.h>
#include <gtest/gtest.h>

#include <memory>
#include <tuple>

const static std::string res_dir = "res/OsmMapData_Test/";

namespace {
std::string get_res_path(const std::string& str) { return res_dir + str; }

std::vector<GeoCoordinate> create_points(
    const std::initializer_list<std::tuple<int, double, double>>& data) {
  std::vector<GeoCoordinate> result;
  for (const auto& item : data) {
    GeoCoordinateBuilder b;
    b.set_id(std::get<0>(item));
    b.set_coordinates(std::get<1>(item), std::get<2>(item));
    result.emplace_back(b.build());
  }
  return result;
}

std::vector<Link> create_links(
    const std::initializer_list<std::pair<int, std::vector<GeoCoordinate>>>&
        data) {
  std::vector<Link> result;
  for (auto& item : data) {
    LinkBuilder b;
    b.set_id(item.first);
    b.add_geom_points(item.second);
    result.emplace_back(b.build());
  }
  return result;
}

std::vector<Junction> create_junctions(
    const std::initializer_list<std::pair<int, std::vector<Link>>>& data) {
  std::vector<Junction> result;
  for (auto& item : data) {
    JunctionBuilder b;
    b.set_id(item.first);
    b.add_links(item.second);
    result.emplace_back(b.build());
  }
  return result;
}

}  // namespace

class BaseOsmMapDataTest : public ::testing::Test {
 public:
  void SetUp() override { m_map = std::make_shared<OsmMapData>(); }

  std::shared_ptr<AbstractMapData> m_map;
};

//--------------------------------------------------------------------------------------------------

TEST_F(BaseOsmMapDataTest, correct_points) {
  ASSERT_TRUE(m_map->load_data(get_res_path("initial_test.osm")));

  auto points = m_map->get_points();
  decltype(points) expected_points =
      create_points({{1658892715, 50.0484352, 19.9578585},
                     {1658892837, 50.0487473, 19.9575554},
                     {1658892870, 50.0488517, 19.9574385},
                     {8869531296, 50.0470099, 19.9560818},
                     {3308660443, 50.0487668, 19.9576425}});
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
  // First link
  decltype(points) expected_points_1 =
      create_points({{597815470, 50.0472115, 19.9576255},
                     {275424725, 50.0462107, 19.9577490},
                     {325632942, 50.0461162, 19.9577532}});
  // Second link
  decltype(points) expected_points_2 =
      create_points({{1658892773, 50.0485285, 19.9602894},
                     {5184148054, 50.0484834, 19.9602841},
                     {1360316280, 50.0484224, 19.9602599},
                     {3205862016, 50.0482731, 19.9601454}});
  for (const auto& point : expected_points_1) {
    EXPECT_NE(std::find_if(points.begin(), points.end(),
                           [&point](decltype(point) point_internal) {
                             return point_internal == point;
                           }),
              points.end())
        << "Expected point not found: " << point.get_latitude() << ", "
        << point.get_longitude();
  }
  for (const auto& point : expected_points_2) {
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
  decltype(links) expected_links = create_links(
      {{25944843, expected_points_1}, {34628589, expected_points_2}});
  for (const auto& link : expected_links) {
    EXPECT_NE(std::find_if(links.begin(), links.end(),
                           [&link](decltype(link) link_internal) {
                             return link_internal == link;
                           }),
              links.end())
        << "Expected link not found: " << link.get_id();
  }
}

//--------------------------------------------------------------------------------------------------

TEST_F(BaseOsmMapDataTest, correct_junction) {
  ASSERT_TRUE(m_map->load_data(get_res_path("initial_test.osm")));

  auto to_tuple = [](const GeoCoordinate& coords) {
    uint32_t id = coords.get_id();
    return std::tie(id, coords.get_latitude(), coords.get_longitude());
  };

  // Points
  auto points = m_map->get_points();
  const GeoCoordinate common_point =
      create_points({{597815470, 50.0472115, 19.9576255}}).front();

  decltype(points) expected_points_1 =
      create_points({{597815472, 50.0472362, 19.9583434},
                     {5649671939, 50.0472333, 19.9582624},
                     {10965518031, 50.0472247, 19.9580216},
                     {3120647862, 50.0472128, 19.9576897},
                     to_tuple(common_point)});

  decltype(points) expected_points_2 = create_points(
      {{275424720, 50.0473291, 19.9576233}, to_tuple(common_point)});

  decltype(points) expected_points_3 =
      create_points({to_tuple(common_point),
                     {275424725, 50.0462107, 19.9577490},
                     {325632942, 50.0461162, 19.9577532}});

  for (const auto& point : expected_points_1) {
    EXPECT_NE(std::find_if(points.begin(), points.end(),
                           [&point](decltype(point) point_internal) {
                             return point_internal == point;
                           }),
              points.end())
        << "Expected point not found: " << point.get_latitude() << ", "
        << point.get_longitude();
  }
  for (const auto& point : expected_points_2) {
    EXPECT_NE(std::find_if(points.begin(), points.end(),
                           [&point](decltype(point) point_internal) {
                             return point_internal == point;
                           }),
              points.end())
        << "Expected point not found: " << point.get_latitude() << ", "
        << point.get_longitude();
  }
  for (const auto& point : expected_points_3) {
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
  decltype(links) expected_links =
      create_links({{46785409, expected_points_1},
                    {25944843, expected_points_2},
                    {25944843, expected_points_3}});
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
  auto expected_junction = create_junctions({{1, expected_links}}).front();
  auto it =
      std::find_if(junctions.begin(), junctions.end(),
                   [&expected_junction](const Junction& junction_internal) {
                     return junction_internal == expected_junction;
                   });
  ASSERT_NE(it, junctions.end())
      << "Expected junction not found: " << expected_junction.get_id();
  EXPECT_EQ(it->get_id(), expected_junction.get_id());
}