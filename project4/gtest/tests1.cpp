#include "gtest/gtest.h"
#include "LevelBalancedTree.hpp"
#include <string>
#include <sstream>
#include <vector>

namespace{


// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.


// None of the "required" tests require you to have
// Level-Balanced functionality.
// Implementing your tree as a plain binary search
// tree is more than enough to pass these tests.

// Of course, you are expected to implement that functionality
// for the full project.

// BE SURE TO FULLY TEST YOUR CODE.
// This means making sure your templating is not hard-coding for 
// a specific type, that every function is called somewhere in 
// your test cases, etc. 


TEST(Required, FindTheRoot)
{
	LevelBalancedTree<int, std::string> tree;
	tree.insert(5, "foo");

	EXPECT_TRUE( tree.contains(5) );
}

TEST(Required, FindOneHop)
{
	LevelBalancedTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(10, "bar");

	EXPECT_TRUE( tree.contains(10) );
}

TEST(Required, FindTwoHops)
{
	LevelBalancedTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");

	EXPECT_TRUE( tree.contains(12) );
}



TEST(Required, CanAddAFew)
{
	LevelBalancedTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");
	tree.insert(15, "fifteen");
	tree.insert(2, "two");
	tree.insert(4, "four");
	tree.insert(1,"one");
	tree.insert(8,"eight");
	tree.insert(7,"seven");
	//insert example 20,19,18,12,9,17,7,5,13,15,6,16,14
	// tree.insert(20,"twenty");
	// tree.insert(19,"nineteen");
	// tree.insert(18,"eighteen");
	// tree.insert(12,"twelve");
	// tree.insert(9,"nine");
	// tree.insert(17,"seventeen");
	// tree.insert(7,"seven");
	// tree.insert(5,"five");
	// tree.insert(13,"thirteen");
	// tree.insert(15,"fifteen");
	// tree.insert(6,"six");
	// tree.insert(16,"sixteen");
	// tree.insert(14,"fourteen");

	EXPECT_EQ( tree.size(), 10);
}

TEST(Required, DoAPreOrder)
{
	LevelBalancedTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	auto trav = tree.postOrder();
	std::vector<int> expected = {3, 10, 5};
	EXPECT_EQ(trav, expected);

}


TEST(Required, RemoveDoesARemove)
{
	LevelBalancedTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	EXPECT_TRUE( tree.contains( 3 ) );
	tree.remove(3);

	// tree.insert(44, "fourtyfour");
	// tree.insert(17,"seventeen");
	// tree.insert(78,"seventyeight");
	// tree.insert(32,"thirtytwo");
	// tree.insert(50,"fifty");
	// tree.insert(87,"87");
	// tree.insert(48,"fourtyeight");
	// tree.insert(62,"sixtytwo");
	// tree.remove(48);
	// tree.remove(62);
	// tree.remove(87);
	// tree.remove(50);
	EXPECT_FALSE( tree.contains( 3 ) );
	EXPECT_TRUE( tree.contains( 5 ) );
}


TEST(PostCheckPoint, InOrderTraversal)
{
	LevelBalancedTree<int, std::string> tree;
	tree.insert(5, "foo");
	tree.insert(3, "sna");
	tree.insert(10, "bar");
	tree.insert(12, "twelve");
	tree.insert(15, "fifteen");

	std::vector<int> trav = tree.inOrder();
	std::vector<int> expected = {3, 5, 10, 12, 15};
	EXPECT_EQ( trav, expected );
}


}