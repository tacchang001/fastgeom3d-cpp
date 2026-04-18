include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_fastgeom3d
  test_fastgeom3d.cpp
)

target_link_libraries(test_fastgeom3d
  PRIVATE fastgeom3d GTest::gtest_main
)

target_include_directories(test_fastgeom3d
  PRIVATE ${PROJECT_SOURCE_DIR}/include
)

add_test(NAME fastgeom3d_test COMMAND test_fastgeom3d)
