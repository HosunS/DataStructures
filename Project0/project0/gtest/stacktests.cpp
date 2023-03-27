#include "gtest/gtest.h"
#include "postfixCalc.hpp"
#include "LLStack.hpp"
#include <unordered_map>
#include <string>

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.
// However, be aware that if ANY test marked "Required" fails, 
// your score for the portion will be zero, regardless of other considerations.


namespace{


// And some tests for the linked list based stack and the associated calculator.
    // VERY IMPORTANT:  if your LLStack is not templated, or if 
    //      it is not linked-list based, your score for this project
    //      will be zero.  Be sure your LLStack compiles and runs 
    //      with non-numeric data types.  A char is a numeric type.
    // 

TEST(Required, RequiredStackTest1)
{
    LLStack<int> a;
    a.push(5);
    EXPECT_EQ( a.top(), 5 );
}

TEST(Required, RequiredStackTest2)
{
    LLStack<int> a;
    a.push(5);
    a.push(3);
    EXPECT_EQ( a.top(), 3 );
}


TEST(Required, RequiredStackTest3)
{
    LLStack<int> a;
    a.push(5);
    a.push(3);
    a.pop();
    EXPECT_EQ( a.top(), 5 );
}


TEST(Required, RequiredStackTest4)
{
    LLStack<int> a;
    EXPECT_THROW( a.top(), StackEmptyException );
}

TEST(Required, RequiredStackTest5) // testing asignment operator for class
{
    LLStack <int> myStack;
    LLStack <int> newStack;
    myStack.push(3);
    myStack.push(5);
    newStack = myStack;

    EXPECT_EQ( newStack.top(), 5);
}

TEST(Required, RequiredStackTest6) // testing copy constructor for class
{
    LLStack <int> myStack;
    myStack.push(3);
    myStack.push(5);

    LLStack <int> newStack = myStack;
    newStack.push(10);

    EXPECT_EQ( myStack.top(), 5);
}

TEST(Required, RequiredStackTest7) // testing const top function
{
    LLStack<int> myStack;
    myStack.push(5);
    const LLStack<int>& newConstStack = myStack;
    EXPECT_EQ( newConstStack.top(), 5 );
}




// YOU SHOULD ADD ADDITIONAL TEST CASES HERE!! 



TEST(Required, RequiredCalcTest1)
{
    const std::vector<std::string> EXPRESSION = {
        "5", "3", "*"
    };
    EXPECT_EQ( postfixCalculator(EXPRESSION), 15);
}

TEST(Required, RequiredCalcTest2)
{
    const std::vector<std::string> EXPRESSION = {
        "5", "3", "2", "-", "*"
    };
    EXPECT_EQ( postfixCalculator(EXPRESSION), 5);
    
}

TEST(Required, RequiredCalcTest3)
{
    const std::vector<std::string> EXPRESSION = {
        "5", "3", "2", "-"
    };
    EXPECT_ANY_THROW( postfixCalculator(EXPRESSION) );
    
}

// You can fail this test and still get partial credit from others that pass. 
// Of course, I would recommend you get this one to pass, too...
// Note that the group name is "CalcTest" and not "Required."
TEST(CalcTest, AdditionalTest4)
{
    const std::vector<std::string> EXPRESSION = {
        "5", "3", "*", "20", "*"
    };
    EXPECT_EQ( postfixCalculator(EXPRESSION), 300);
    
}







} // end namespace
