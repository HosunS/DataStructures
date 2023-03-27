#include "gtest/gtest.h"
#include "verifySol.hpp"
#include <unordered_map>
#include <string>

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.
// However, be aware that if ANY test marked "Required" fails, 
// your score for the portion will be zero, regardless of other considerations.


namespace{

TEST(Required, RequiredFirst){
    std::string s1 = "POT";
    std::string s2 = "PAN";
    std::string s3 = "BIB";

    std::unordered_map<char, unsigned> solution = { {'A', 7}, {'B', 5}, 
        {'I', 0}, {'N', 4}, {'O', 3}, {'P', 2}, {'T', 1}
    };

    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );
}

TEST(Required, RequiredSecond){

    std::string s1 = "CAT";
    std::string s2 = "DOG";
    std::string s3 = "PIG";

    std::unordered_map<char, unsigned> solution = { {'A', 5}, {'C', 2}, {'D', 1}, {'G', 6}, {'I', 9}, {'O', 4}, {'P', 3}, {'T', 0} };

    EXPECT_TRUE( verifySolution( s1, s2, s3, solution ) );
} // end test two


TEST(Required, RequiredThird){

    std::string s1 = "LARRY";
    std::string s2 = "CAREER";
    std::string s3 = "LEGEND";

    std::unordered_map<char, unsigned> solution = { {'L', 5}, {'A', 2}, {'R', 1}, {'Y', 6}, {'C', 9}, {'E', 4}, {'G', 3}, {'N', 0}, {'D', 7} };

    EXPECT_FALSE( verifySolution( s1, s2, s3, solution ) );
} 



// YOU SHOULD ADD ADDITIONAL TEST CASES HERE!! 



} // end namespace
