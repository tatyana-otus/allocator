#include "lib.h"
#include <sstream>
#include <allocator.h>
#include <sstream>

#define BOOST_TEST_MODULE test_main

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp> 
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;


BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_version_valid)
{
    BOOST_CHECK( (major_version() >= 0) &&  (minor_version() >= 0) && (patch_version() >= 0) );
    BOOST_CHECK( (major_version() >  0) ||  (minor_version() >  0) || (patch_version() >  0) );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(test_suite_allocator)

BOOST_AUTO_TEST_CASE(std_map_def_allocator)
{
     BOOST_CHECK_NO_THROW(std_map_def_alloc(0));
     BOOST_CHECK_NO_THROW(std_map_def_alloc(1));
     BOOST_CHECK_NO_THROW(std_map_def_alloc(10));
     BOOST_CHECK_NO_THROW(std_map_def_alloc(1000));
}

BOOST_AUTO_TEST_CASE(std_map_cust_allocator)
{
    BOOST_CHECK_NO_THROW(std_map_custom_alloc(0));
    BOOST_CHECK_NO_THROW(std_map_custom_alloc(1));
    BOOST_CHECK_NO_THROW(std_map_custom_alloc(1000));

    std::stringstream oss;
    std::string out_data =
    "0 1\n"
    "1 1\n"
    "2 2\n"
    "3 6\n"
    "4 24\n"
    "5 120\n"
    "6 720\n"
    "7 5040\n"
    "8 40320\n"
    "9 362880\n";

    std_map_custom_alloc(10, oss);
    BOOST_CHECK( oss.str() == out_data );
}

BOOST_AUTO_TEST_CASE(simple_list_def_allocator)
{
     BOOST_CHECK_NO_THROW(simple_list_def_alloc(0));
     BOOST_CHECK_NO_THROW(simple_list_def_alloc(1));
     BOOST_CHECK_NO_THROW(simple_list_def_alloc(10));
     BOOST_CHECK_NO_THROW(simple_list_def_alloc(1000));
     
}

BOOST_AUTO_TEST_CASE(simple_list_cust_allocator)
{
    BOOST_CHECK_NO_THROW(simple_list_custom_alloc(0));
    BOOST_CHECK_NO_THROW(simple_list_custom_alloc(1));
    BOOST_CHECK_NO_THROW(simple_list_custom_alloc(10));
    BOOST_CHECK_NO_THROW(simple_list_custom_alloc(1000));  

    std::stringstream oss;
    std::string out_data =
    "0\n"
    "1\n"
    "2\n"
    "3\n"
    "4\n"
    "5\n"
    "6\n"
    "7\n"
    "8\n"
    "9\n";
    
    simple_list_custom_alloc(10, oss);
    BOOST_CHECK( oss.str() == out_data ); 
}

BOOST_AUTO_TEST_SUITE_END()