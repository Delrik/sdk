cmake_minimum_required(VERSION 3.22)
project(nav-sdk-tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

include(${CMAKE_SOURCE_DIR}/cmake/common/copy_dir_after_build.cmake)

function(add_gtest target)
    add_executable(${target} src/${target}.cpp)
    target_link_libraries(${target} GTest::gtest_main nav-sdk)
    target_include_directories(${target} PRIVATE ../private/include)
    copy_dir_after_build(res/${target} ${target})
endfunction()

add_gtest(OsmMapData_test)


include(GoogleTest)
gtest_discover_tests(OsmMapData_test)