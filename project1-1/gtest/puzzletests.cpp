#include "gtest/gtest.h"
#include "puzzleSolver.hpp"
#include "ver.hpp" 
#include <unordered_map>
#include <string>


/*
 
Note that this IS NOT a comprehensive set of test cases.
You should still write additional test cases.

This is to get you started and serve as a sanity check.


Note that "gradeYesAnswer" is provided for use in your test cases, but 
you may NOT use it in any code you write otherwise for this project.

 */


namespace{

TEST(Required, PotPanBib){

    std::unordered_map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("POT", "PAN", "BIB", puzzle);
    EXPECT_TRUE( p1 and  gradeYesAnswer("POT", "PAN", "BIB", puzzle) ) ;
}

TEST(Required, NeatFind){

    std::unordered_map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("UCI", "ALEX", "MIKE", puzzle);
    EXPECT_TRUE( p1 and gradeYesAnswer("UCI", "ALEX", "MIKE", puzzle) );
} // end test two, "NeatFind"


TEST(Required, FirstNo){

    std::unordered_map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("LARRY", "CAREER", "LEGEND", puzzle);
    EXPECT_FALSE( p1 );
}

TEST(Required, secondNo){

    std::unordered_map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("LARRY", "CARTER", "LEGEND", puzzle);
    EXPECT_TRUE( p1 and gradeYesAnswer("LARRY", "CARTER", "LEGEND", puzzle));
}

TEST(Required, thirdNo){

    std::unordered_map<char, unsigned> puzzle;

    bool p1 = puzzleSolver("RTYWTTROPT", "OTRYERTQW", "TEPTPUIEPY", puzzle);

        // std::cout << "Correct Mapping: ";
        // for (auto const &pair : puzzle)
        // {
        //     std::cout << "{" << pair.first << ": " << pair.second << "}"
        //     << " ";
        // }
    EXPECT_TRUE( p1 /*and gradeYesAnswer("RTYWTTROPT", "OTRYERTQW", "TEPTPUIEPY", puzzle)*/);
}

} // end namespace
