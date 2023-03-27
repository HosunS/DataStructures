#include "postfixCalc.hpp"
#include "LLStack.hpp"

unsigned postfixCalculator(const std::vector<std::string> & entries)
{
	LLStack <std::string> stack; //creating an empty stack
	int ans = 0; // used to keep track of values
	int opCounter = 0; // keeps track of how many operators in the vector
	int numCounter = 0; // keeps track of how many integer entries are in the vector

	for(int i = 0; i < entries.size(); i++) //loop through the given vector
	{
		// once we hit a operator we can  set the varialbe ans to equal the value at stack's top
		// we will just stoi to convert strings to int
		// and use to_string() to convert it back to a string to push back onto stack when we finish the current operation
		if(entries.at(i) == "+" or entries.at(i) == "-" or entries.at(i) == "*" or entries.at(i) == "/")
		{
			opCounter++;
			ans = stoi(stack.top());
			stack.pop();

			if(entries.at(i) == "+")
			{
				ans = stoi(stack.top()) + ans;
				stack.pop();
				stack.push(std::to_string(ans));
			}
			else if(entries.at(i) == "-")
			{
				ans = stoi(stack.top()) - ans;
				stack.pop();
				stack.push(std::to_string(ans));
			}
			else if(entries.at(i) == "*")
			{
				ans = stoi(stack.top()) * ans;
				stack.pop();
				stack.push(std::to_string(ans));
			}
			else if(entries.at(i) == "/")
			{
				ans = stoi(stack.top())/ ans;
				stack.pop();
				stack.push(std::to_string(ans));
			}
		}
		else // if current entry is a number , push onto stack
		{
			numCounter++;
			stack.push(entries.at(i));
		}
	}

	if(numCounter - 1 == opCounter) //if this is true, it means we have to right amount of operators to num
	{
		return stoi(stack.top());
	}
	else
	{
		throw CannotEvaluateException("Cant do it");
	}
}

