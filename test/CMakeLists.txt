# set(PROGECT_NAME basic_tools_unit_test)
# project(${PROGET_NAME})

# # check gcov is existed
# if(ENABLE_COVERAGE)
#     find_package(PATH_GCOV gcov)
#     if(NOT PATH_GCOV)
#         message(FATAL_ERROR "Don't have Gcov, code coverage analysis requires this!")
#     endif()
# endif()

# # get gtest
# message(STATUS "fetch google test framework library")
# include(FetchContent)
# FetchContent_Declare(gtest
#   QUIET
#   URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
# )
# # configure build of googletest
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(gtest)

# basic tools sources
file(GLOB BASIC_TOOLS_SRCS "${CMAKE_SOURCE_DIR}/*.h" "${CMAKE_SOURCE_DIR}/*.cc")
file(GLOB BASIC_TOOLS_LOG_SRCS "${CMAKE_SOURCE_DIR}/log/*.h" "${CMAKE_SOURCE_DIR}/log/*.cc")

# test sources
file(GLOB TEST_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

# add_executable(${PROGETC_NAME} ${TEST_SRCS})
message(STATUS "fetch google test framework")
include(FetchContent)
FetchContent_Declare(gtest
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)
# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

include_directories(${PROJECT_SOURCE_DIR}) 

add_library(basic_tools_libraty STATIC
    ${BASIC_TOOLS_SRCS}
    ${BASIC_TOOLS_LOG_SRCS}
)

add_executable(
    unit_tests
    ${TEST_SRCS}
    # basic_any_unit_test.cc
    )

target_link_libraries(unit_tests
  PRIVATE
    gtest_main
    basic_tools_libraty
  )

# automatic discovery of unit tests
include(GoogleTest)
gtest_discover_tests(unit_tests
  PROPERTIES
    LABELS "unit"
  DISCOVERY_TIMEOUT  # how long to wait (in seconds) before crashing
    240
  )