cmake_minimum_required(VERSION 3.22)
project(nav-sdk)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES 
    include/NavApp.h src/NavApp.cpp

    include/common/GeoCoordinate.h
    include/common/Junction.h
    include/common/Link.h

    private/include/NavAppImpl.h private/src/NavAppImpl.cpp
    private/include/Id.h

    private/include/MapData/AbstractMapData.h
    private/include/MapData/OsmMapData.h private/src/MapData/OsmMapData.cpp
    private/include/MapData/OsmXmlParser.h private/src/MapData/OsmXmlParser.cpp
    private/include/MapData/OsmMapDataStatistics.h private/src/MapData/OsmMapDataStatistics.cpp
    private/include/MapData/NodeData.h
    private/include/MapData/WayData.h
    
    private/include/Builders.h
    private/include/builders/GeoCoordinateBuilder.h private/src/builders/GeoCoordinateBuilder.cpp
    private/include/builders/LinkBuilder.h private/src/builders/LinkBuilder.cpp
    private/include/builders/JunctionBuilder.h private/src/builders/JunctionBuilder.cpp)

add_library(nav-sdk ${SOURCES})

target_include_directories(nav-sdk PUBLIC include)
target_include_directories(nav-sdk PRIVATE private/include)

#target_link_libraries(nav-sdk PRIVATE tinyxml2)

add_subdirectory(tests)