#include <MapData/OsmMapData.h>
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
    const std::initializer_list<std::pair<double, double>>& data) {
  std::vector<GeoCoordinate> result;
  for (const auto& item : data) {
    GeoCoordinateBuilder b;
    b.set_coordinates(item.first, item.second);
    result.emplace_back(b.build());
  }
  return result;
}

std::vector<Link> create_links(
    const std::initializer_list<std::vector<GeoCoordinate>>& data) {
  std::vector<Link> result;
  for (auto& item : data) {
    LinkBuilder b;
    b.add_geom_points(item);
    result.emplace_back(b.build());
  }
  return result;
}

std::vector<Junction> create_junctions(
    const std::initializer_list<std::vector<Link>>& data) {
  std::vector<Junction> result;
  for (auto& item : data) {
    JunctionBuilder b;
    b.add_links(item);
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

TEST_F(BaseOsmMapDataTest, correct_links) {
  ASSERT_TRUE(m_map->load_data(get_res_path("initial_test.osm")));

  // First link
  std::vector<GeoCoordinate> link_points_1 =
      create_points({{50.0472115, 19.9576255},
                     {50.0462107, 19.9577490},
                     {50.0461162, 19.9577532},
                     {50.0450740, 19.9578836},
                     {50.0450142, 19.9578885}});
  // Second link
  std::vector<GeoCoordinate> link_points_2 =
      create_points({{50.0485285, 19.9602894},
                     {50.0484834, 19.9602841},
                     {50.0484224, 19.9602599},
                     {50.0482731, 19.9601454},
                     {50.0478119, 19.9597596},
                     {50.0476706, 19.9596751},
                     {50.0475125, 19.9596358}});
  // Third link
  std::vector<GeoCoordinate> link_points_3 =
      create_points({{50.0473863, 19.9595179},
                     {50.0473643, 19.9594812},
                     {50.0473358, 19.9594574}});

  auto missing_link = create_links({create_points({
                                       {50.0472115, 19.9576255},
                                       {50.0462107, 19.9577490},
                                       {50.0461162, 19.9577532},
                                   })})
                          .front();

  // Links
  auto links = m_map->get_links();
  decltype(links) expected_links =
      create_links({link_points_1, link_points_2, link_points_3});
  for (const auto& link : expected_links) {
    EXPECT_NE(std::find_if(links.begin(), links.end(),
                           [&link](const Link& link_internal) {
                             return link_internal == link;
                           }),
              links.end())
        << "Expected link not found: " << link.get_id().to_str().c_str();
  }
  EXPECT_EQ(std::find_if(links.begin(), links.end(),
                         [&missing_link](const Link& link_internal) {
                           return link_internal == missing_link;
                         }),
            links.end())
      << "Unexpected link was found: "
      << missing_link.get_id().to_str().c_str();
}

//--------------------------------------------------------------------------------------------------

TEST_F(BaseOsmMapDataTest, correct_junction) {
  ASSERT_TRUE(m_map->load_data(get_res_path("initial_test.osm")));

  auto to_pair = [](const GeoCoordinate& coords) {
    return std::make_pair(coords.get_latitude(), coords.get_longitude());
  };

  const GeoCoordinate common_point =
      create_points({{50.0472115, 19.9576255}}).front();

  std::vector<GeoCoordinate> link_points_1 =
      create_points({{50.0472128, 19.9576897}, to_pair(common_point)});

  std::vector<GeoCoordinate> link_points_2 =
      create_points({{50.0473291, 19.9576233}, to_pair(common_point)});

  std::vector<GeoCoordinate> link_points_3 =
      create_points({to_pair(common_point),
                     {50.0462107, 19.9577490},
                     {50.0461162, 19.9577532},
                     {50.0450740, 19.9578836},
                     {50.0450142, 19.9578885}});

  std::vector<GeoCoordinate> link_points_4 =
      create_points({{50.0472090, 19.9574168}, to_pair(common_point)});

  // Links
  auto links = m_map->get_links();
  decltype(links) expected_links = create_links(
      {link_points_1, link_points_2, link_points_3, link_points_4});
  for (const auto& link : expected_links) {
    EXPECT_NE(std::find_if(links.begin(), links.end(),
                           [&link](const Link& link_internal) {
                             return link_internal == link;
                           }),
              links.end())
        << "Expected link not found: " << link.get_id().to_str();
  }
  // Junctions
  auto junctions = m_map->get_junctions();
  auto expected_junction = create_junctions({expected_links}).front();
  auto it =
      std::find_if(junctions.begin(), junctions.end(),
                   [&expected_junction](const Junction& junction_internal) {
                     return junction_internal == expected_junction;
                   });
  ASSERT_NE(it, junctions.end())
      << "Expected junction not found: " << expected_junction.get_id().to_str();
  EXPECT_EQ(it->get_id(), expected_junction.get_id());
}