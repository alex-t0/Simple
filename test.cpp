#include <catch2/catch_test_macros.hpp>

TEST_CASE( "Main test case", "[main]" ) {
    SECTION( "Section 1" ) {
        REQUIRE( 1 != 0 );
    }
    SECTION( "Section 2" ) {
        REQUIRE( true == true );
    }

}