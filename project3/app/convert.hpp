#ifndef ___PROJECT_3_CONVERT_HPP
#define ___PROJECT_3_CONVERT_HPP

#include <string>
#include <vector>
#include "Wordset.hpp"

void loadWordsIntoTable(WordSet & words, std::istream & in);

// bool BFS(std::string s1, std::string s2, std::map<std::string,std::set<std::string>> graph, std::map<std::string,std::string> &prev,std::map<std::string,int> &dist
// 		, std::set<std::string> &visited,std::queue<std::string> & frontier);
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const WordSet & words);



#endif
