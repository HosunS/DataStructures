#ifndef __PUZZLE_SOLVER__HPP
#define __PUZZLE_SOLVER__HPP

#include <unordered_map>
#include <string>
#include <iostream>// used cout to check the specific values that were mapped
/* 
 * Project 1:  you need to implement this function.
 I promise that any of my test cases will have an empty 
 	map as the fourth parameter when called.
 If the puzzle IS solvable, return true AND make the mapping indicate the solution.
 If the puzzle is NOT solvable, it is enough to return false.

 See the project 1 write-up for a more complete description. 
 */


bool puzzleSolver(const std::string& s1, const std::string& s2, const std::string& s3, std::unordered_map<char, unsigned> & mapping);


#endif