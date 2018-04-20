project(test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

#add_executable(test_main_cli test_main.cpp ../src/filter.cpp)
add_executable(test_main_cli test_main.cpp)

target_include_directories(test_main_cli PRIVATE ../include)
target_include_directories(test_main_cli PRIVATE ${Boost_INCLUDE_DIR})

set_target_properties(test_main_cli PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(test_main_cli
  ${Boost_LIBRARIES}
  version
)

#--log_level=all
enable_testing()

add_test(test_version_valid  test_main_cli -t test_suite_main/test_version_valid)

add_test(test_std_map_def_allocator      test_main_cli -t test_suite_allocator/std_map_def_allocator)
add_test(test_std_map_cust_allocator     test_main_cli -t test_suite_allocator/std_map_cust_allocator)
add_test(test_simple_list_def_allocator  test_main_cli -t test_suite_allocator/simple_list_def_allocator)
add_test(test_simple_list_cust_allocator test_main_cli -t test_suite_allocator/simple_list_cust_allocator)
add_test(test_memory_leak                test_main_cli -t test_suite_allocator/memory_leak)

