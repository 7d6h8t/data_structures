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

add_executable(ds_test ${SRC_FILES})
target_link_libraries(ds_test PRIVATE gtest gtest_main)

target_include_directories(ds_test PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(ds_test PRIVATE -Wall)