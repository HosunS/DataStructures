#ifndef __PROJ1__VERIFIER__HPP
#define __PROJ1__VERIFIER__HPP

#include <string>
#include <unordered_map>

// This verifies that s1 + s2 = s3 is valid under the giving mapping.
// It also verifies that each char maps to a distinct digit.
// Specifically, everything in the map can only map to a digit, and cannot repeat a digit, or it returns false.
bool gradeYesAnswer(std::string s1, std::string s2, std::string s3, const std::unordered_map<char, unsigned> & mapping);


#endif
