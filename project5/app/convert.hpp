#ifndef __PROJECT5_HPP
#define __PROJECT5_HPP

#include <vector>
#include <unordered_set>

void loadWordsIntoTable(std::unordered_set<std::string> & words, std::istream & in);


std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words);



#endif 
