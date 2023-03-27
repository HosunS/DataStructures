#include "convert.hpp"
#include <string>
#include <sstream>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <MyPriorityQueue.hpp>
#include <algorithm>
#include <iostream>
// You should not need to change this function.
void loadWordsIntoTable(std::unordered_set<std::string> & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}

int distanceBetweenWords(std::string s1,std::string s2)// use this to calculate how many letters away from the word
{
	int counter = 0;
	for(int i = 0; i < s1.size(); i++)
	{
		if(s1[i] != s2[i])
		{
			counter++;
		}
	}
	return counter;
}


// You probably want to change this function.
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words) 
{
	std::vector<std::string> ans;
	std::unordered_map<std::string,std::pair<int,std::string>> frontier; // word : <lcdistance + sum, prev> // will hold all the possible words that are linked together, as well as the sum between LC distance and how many words left to transform, and the word that will be its link to the previous word
	bool reachedEnd = false;
	if(s1.size() != s2.size() or s1 == s2) //return empty vector if the two words are the same or the size of the words are not equal
	{	
		return ans;
	}

	MyPriorityQueue<node> prio; // create a queue with nodes that keep track of the word at the node, the lewis carol distance, the sum of the distances, as well as the previous word it came from.
	prio.insert({s1,"",0,distanceBetweenWords(s1,s2)});

	while(prio.isEmpty() == false)
	{
		node curr = prio.min(); // get the current min which is the first element
		prio.extractMin(); // extract the first word which is our base word
		int sum = curr.dist + curr.dist; // 
		frontier.insert({curr.word,{sum + 1, ""}}); // we insert into the list that keep track of the words that can be used
		for(const auto &x : words) // loop through to find words from the dict that can compare to the word we are looking for 
		{
			if(x.size() == s1.size()) // only take into consideration words of the same size at s1, otherwise it would not be possible to convert
			{
				if(distanceBetweenWords(x,curr.word) == 1 and frontier.find(x) == frontier.end()) // if the distance is 1 and it is not in our word set 
				{
					prio.insert({x,curr.word, curr.dist + 1, distanceBetweenWords(x,s2)}); // insert into priority as a node with the new word, the current wordds
					frontier.insert({x,{(curr.dist + 1) + distanceBetweenWords(x,s2),curr.word}}); // insert into as the new word, and set the int to be the disttance between the current word dist + 1 and the distance between the new word and the last word
					if(x == s2){ // this means we found the word that we are looking for s2*
						reachedEnd = true; 
					}
				}
				else if(distanceBetweenWords(x,curr.word) == 1 and frontier.find(x) != frontier.end()) // if the distance between the new word and curr word are 1 and it is in our frontier word set
				{
					if(frontier.find(x)->second.first > ((curr.dist + 1) + distanceBetweenWords(x,s2))) // if the int distance in our frontier is greater than the distance between the current word + 1 and the distance between new word and last word
					{
						prio.insert({x,curr.word,curr.dist + 1, distanceBetweenWords(x,s2)}); // insert into prio, with new word, curr dist + 1, as well as the dist from the word to the last word
						frontier.find(x)->second = {(curr.dist + 1) + distanceBetweenWords(x,s2), curr.word}; // go into frontier set the int in the pair to be equal to the distance between the currdist + 1 + the distance from new word to last word, and curr word
						if(x == s2)
						{
							reachedEnd = true;
						}
					}
				}
			}
		}
	}
		if(reachedEnd == false)
		{
			return ans;
		}
		else // we found s2
		{
			ans.push_back(s2); // push back into ans reversed.
			std::string next = frontier.find(s2)->second.second; // next string we go into, will be the string that is in the pair within frontier

			while(next != "")
			{
				ans.push_back(next);
				next = frontier.find(next)->second.second;
			}
			std::reverse(ans.begin(),ans.end()); // need to reverse the string to get the correct answer
	// 	// prints mapping for prev vector
	// 	for(auto x: frontier)
	// 	{
	// 		std::cout << x.first << " : "<< "( " << x.second.first << "," << x.second.second << ")" << std::endl;
	// 	}

	// //shows final vector with the lewis carrol transformation
	// 	for(int i = 0; i < ans.size(); i++)
	// 	{
	// 		std::cout << ans[i] << std::endl;
	// 	}
			return ans;
		}
}

