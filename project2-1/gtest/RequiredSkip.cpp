#include "gtest/gtest.h"
#include <vector>
#include "SkipList.hpp"


namespace{

/*
NOTE:  these are not intended as exhaustive tests.
	 You should make your own additional tests
	 VERY IMPORTANT:  if your SkipList is not templated, or if 
			it is not built as a linked structure, your score for this project
			will be zero.  Be sure your SkipList compiles and runs 
	 		with non-numeric data types. 


IF YOUR CODE DOES NOT PASS EVERY TEST IN THIS FILE, YOUR SCORE WILL BE A ZERO.


*/

	TEST(Required, CreatedBasics)
	{
		SkipList<unsigned, unsigned> sl;
		EXPECT_EQ( 2, sl.numLayers());
		EXPECT_EQ( 0, sl.size() );
		EXPECT_TRUE( sl.isEmpty() );
	}

	TEST(Required, SkipListTest1)
	{
		SkipList<unsigned, unsigned> sl;
		sl.insert(3, 5);
		EXPECT_TRUE( sl.find(3) == 5 );
	}

	TEST(Required, SkipListTest2)
	{
		SkipList<std::string, std::string> sl;
		sl.insert("Shindler", "ICS 46");
		EXPECT_TRUE(sl.find("Shindler") == "ICS 46");
	}

	TEST(Required, SimpleNextAndPrev)
	{
		SkipList<unsigned, unsigned> sl;
		for(unsigned i=0; i < 10; i++)
		{
			sl.insert(i,i);
		}
		for(unsigned i=1; i < 9; i++)
		{
			EXPECT_TRUE(sl.previousKey(i) == (i-1) and sl.nextKey(i) == (i+1) );
		}
	}

	TEST(Required, SimpleAllKeysInOrder)
	{
		SkipList<unsigned, unsigned> sl;
		std::vector<unsigned> expected;
		for(unsigned i=0; i < 10; i++)
		{
			sl.insert(i, (100 + i) );
			expected.push_back( i );
		}
		EXPECT_TRUE( expected == sl.allKeysInOrder() );
	}

}
