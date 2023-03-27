#ifndef __PROJ_0_POSTFIX_CALCULATOR
#define __PROJ_0_POSTFIX_CALCULATOR

#include "runtimeexcept.hpp"
#include <string>
#include <vector>

// This exception should be thrown whenever the postfix equation
// cannot be evaluated.
class CannotEvaluateException : public RuntimeException 
{
public:
	CannotEvaluateException(const std::string & err) : RuntimeException(err) {}
};

// For project 0, you should not need to do anything with this file.
// If you choose to create a helper function AND you want to add 
// separate Google Tests for it, you should declare it in this header.
// You are not required to do that for the assignment.

unsigned postfixCalculator(const std::vector<std::string> & entries);

#endif

