#include "convert.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
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

// You probably want to change this function.
std::vector<string > convert(const string & s1, const string & s2, const WordSet & words)
{
	std::queue<std::string> frontier; // used for bfs
	std::set<std::string> visited; // used for bfs
	std::map<std::string,std::set<std::string>> graph; // placed into here for us to perform bfs to find the shortest distance
	std::map<std::string,std::string> prev; // key is the current string, element is previous string
	std::vector<std::string> path; // reverse of answer
	std::vector<std::string> ans; // return this to get the final vector of words
	std::vector<std::string> temp;
	bool BFS = false;
	// loop through wordset and push back all the words the same size as the s1
	for(int i = 0; i < words.arrSize; i++)
	{
		if(words.hasharr1[i].size() == s1.size())
		{
			temp.push_back(words.hasharr1[i]);
		}

		if(words.hasharr2[i].size() == s1.size())
		{
			temp.push_back(words.hasharr2[i]);
		}
	}

	for(int i = 0;i < temp.size(); i++) // places values with key and set of stringsinto graph map
	{
		std::set<std::string> ins;
		std::string key = temp[i];
		for(int j = 0; j < temp.size(); j++)
		{
			std::string value = temp[j];
			if(key != value)
			{
				unsigned counter = 0;
				for(int m = 0; m < key.size(); m++)
				{
					if(key[m] != value[m])
					{
						counter++;
					}
				}
				if(counter == 1)
				{
					ins.insert(value);
				}
			}
		}
		graph[key] = ins;
	}

	for(auto x : graph) //initializes values for  prev vector , prev holds the string and the previous string
	{
		prev[x.first] = "";
	}
	//bfs starts here
	visited.insert(s1);
	frontier.push(s1);
	
	while(frontier.empty() == false)
	{
		std::string p = frontier.front();
		frontier.pop();
		for(auto x : graph[p])
		{
			if(visited.find(x) == visited.end())
			{
				visited.insert(x);
				prev[x] = p;
				frontier.push(x);

				if(x == s2)
				{
					BFS = true;
					break;
				}
			}
		}
	}
	if(BFS == false) // if search does not work return empty vector
	{
		std::vector<std::string> nothing;
		return nothing;
	}

	//go into prev and find the shortest path available to us
	std::string s = s2;
	path.push_back(s);

	// start at the last word in prev, we then iterate to its previous word until there is no more previous words to find the answer
	while(prev[s] != "")
	{
		path.push_back(prev[s]);
		s = prev[s]; // alllows us to loop through prev to create a path
	}

	for(int i = path.size() -1 ; i >= 0; i--) //iterate backwards through path to insert into ans
	{
		ans.push_back(path[i]);
	}

//shows mapping for basically the whole wordset in graph
	// for(auto x: graph)
	// {
	// 	for(auto y: x.second)
	// 	{
	// 		cout << x.first << " : " << y << endl;
	// 	}
	// }
// prints mapping for prev vector
	// for(auto x: prev)
	// {
	// 	cout << x.first << " : " << x.second << endl;
	// }

// shows final vector with the lewis carrol transformation
	// for(int i = 0; i < ans.size(); i++)
	// {
	// 	cout << ans[i] << endl;
	// }

	return ans;
}
