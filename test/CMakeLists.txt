include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(unittest ${SRC_FILES})
target_link_libraries(unittest PRIVATE gtest gtest_main)

target_include_directories(unittest PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(unittest PRIVATE -Wall)