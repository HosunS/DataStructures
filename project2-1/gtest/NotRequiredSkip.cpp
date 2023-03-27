#include "gtest/gtest.h"
#include <vector>
#include "SkipList.hpp"


/*
NOTE:  these are not intended as exhaustive tests.
	 You should make your own additional tests
	 VERY IMPORTANT:  if your SkipList is not templated, or if 
			it is not built as a linked structure, your score for this project
			will be zero.  Be sure your SkipList compiles and runs 
	 		with non-numeric data types. 


NOTE ALSO:  "Not Required" does not mean "optional" or "extra credit."  
"Not required" only means that we will still grade your project, even 
if these exact tests do not pass.  
*/

namespace{





	TEST(SampleTests, SimpleHeightsTest)
	{
		SkipList<unsigned, unsigned> sl;
		std::vector<unsigned> heights;
		for(unsigned i=0; i < 10; i++)
		{
			sl.insert(i,i);
			heights.push_back( sl.height(i) );
		}
		std::vector<unsigned> expectedHeights = {1, 2, 1, 3, 1, 2, 1, 4, 1, 2};
		EXPECT_TRUE( heights == expectedHeights );
	}

	TEST(SampleTests, SimpleFindTest)
	{
		SkipList<unsigned, unsigned> sl;
		for(unsigned i=0; i < 10; i++)
		{
			sl.insert(i, (100 + i) );
		}
		for(unsigned i=0; i < 10; i++)
		{
			EXPECT_TRUE((i+100) == sl.find(i));
		}
	}

	TEST(SampleTests, SimpleLargestAndSmallest)
	{
		SkipList<unsigned, unsigned> sl;
		for(unsigned i=0; i < 10; i++)
		{
			sl.insert(i, (100 + i) );
		}
		EXPECT_TRUE( sl.isSmallestKey( 0 ) and sl.isLargestKey( 9 ) );

	}

	TEST(SampleTests, InvolvedHeightsTest)
	{
		SkipList<unsigned, unsigned> sl;
		std::vector<unsigned> heights;
		for (unsigned i = 0; i < 10; i++)
		{
			sl.insert(i, i);
			heights.push_back(sl.height(i));
		}

		// The coinFlip function will always return heads
		// for 255 regardless of the current layer.
		// You can use this value to test your threshold for halting
		// the insertion procedure. If this results in an infinite loop inside
		// of your insert function you have not implemented a cutoff threshold.
		unsigned const MAGIC_VAL = 255;
		sl.insert(MAGIC_VAL, MAGIC_VAL);

		heights.push_back(sl.height(MAGIC_VAL));

		// The expected height for 255 is 12 because there are fewer than 16 nodes in
		// the skip list when 12 is added.
		std::vector<unsigned> expectedHeights = {1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 12};
		EXPECT_TRUE(heights == expectedHeights);

		// At this point there should be 13 layers
		// (because the fast lane is not included in the height calculation).
		EXPECT_TRUE(sl.numLayers() == 13);
	}

	TEST(SampleTests, Capacity17Test)
	{
		SkipList<unsigned, unsigned> sl;
		std::vector<unsigned> heights;

		// First insert 16 values into the skip list [0, 15].
		for (unsigned i = 0; i < 16; i++)
		{
			sl.insert(i, i);
			heights.push_back(sl.height(i));
		}

		// Same value used in SimpleHeightsTest for testing the threshold.
		unsigned const MAGIC_VAL = 255;
		sl.insert(MAGIC_VAL, MAGIC_VAL);

		heights.push_back(sl.height(MAGIC_VAL));

		// The expected height for 255 is 15 because 3 * ceil(log_2(17)) = 15
		// meaning the maximum height of any node should be 15 for a skip list with 17 nodes.
		std::vector<unsigned> expectedHeights = {1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, 15};
		EXPECT_TRUE(heights == expectedHeights);

		// At this point there should be 16 layers
		// (because the fast lane is not included in the height calculation).
		EXPECT_TRUE(sl.numLayers() == 16);
	}



}
