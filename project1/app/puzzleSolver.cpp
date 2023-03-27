#include "puzzleSolver.hpp"
using namespace std;

//function to see if the current mapping works with the given strings.
bool verifySolution(std::string s1, std::string s2, std::string s3, const std::unordered_map<char, unsigned> &mapping)
{
    // need an int to hold the value of each addend after converting using map
    int cons1 = 0;
    int cons2 = 0;
    int cons3 = 0;
    // use for loops to scan each value at each mapping and convert the value into an int
    for(int i = 0; i < s1.size(); i++)
    {
        cons1 = mapping.at(s1[i]) + (cons1 * 10);
    }

    for(int i = 0; i < s2.size(); i++)
    {
        cons2 = mapping.at(s2[i]) + (cons2 * 10);
    }

    for(int i = 0; i < s3.size(); i++)
    {
        cons3 = mapping.at(s3[i]) + (cons3 * 10);
    }
    // return true if converted (s1 + s2 = s3) ~ if not return false
    if(cons1 + cons2 - cons3 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkmap(std::unordered_map <char,unsigned> mapping, int i)
{
    bool used = false;
    for(auto const &pair : mapping)
    {
        if(pair.second == i)
        {
            used =  true;
        }
    }
    return used;
}

//Use this helper function to run the recursion and use permutation to figure out the different values
bool perm(std::string s1, std::string s2, std::string s3, std::unordered_map<char, unsigned> &mapping, std::unordered_map<unsigned, char> &letters, int counter,std::unordered_map<int,bool> &usedNumbers, int k)
{
    if (k == counter - 1) // base case, means we hit the "last" unique character, so it will hit this part and test for map correctness
    {
        for (int i = 0; i < 10; i++) //loop through 0 - 9 to check if those numbers work in the "last" unique character
        {
            if (usedNumbers[i]== 0) //this is used to check if the current integer we are trying to get is already being used in another spot
            {

                mapping[letters[k]] = i; //this uses the letters map which wont change once assigned to return the char at the given "index" k, we assign the number i to change the value that the mapping is holding at the letter index
                
                
                if (verifySolution(s1, s2, s3, mapping))//We are in the last integer to change so we can check if the mapping we are checking is true.
                {
                     return true;
                }
            }
        }

        return false;
    }

    else // run this for every case we enter this function and k is not counter - 1
    {
        for (int i = 0; i < 10; i++) // run through each digit 1 - 9
        {
            if (usedNumbers[i]== 0)
            {
                mapping[letters[k]] = i; // assign the value to mapping
                usedNumbers[i] = 1; //this sets the value to true for the current integer we are checking in place

                if (perm(s1, s2, s3, mapping, letters, counter, usedNumbers, k + 1)) // call recursion here to check if we return the value true from the "last" Character we are checking
                {
                    return true; //will only return true if base case returns true.
                }
                usedNumbers[i] = 0; //this allows us to backtrack, by setting the value we just checked to false.

            }
        }
        return false;
    }
}



bool puzzleSolver(const std::string &s1, const std::string &s2, const std::string &s3, std::unordered_map<char, unsigned> &mapping)
{
	std::unordered_map<int, bool> usedNumbers = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}}; //essentially making an array that by making the key 0 - 9 like an array to keep track of whether the number is used or not
	std::unordered_map<unsigned, char> letters; // makes a map in the format of an array, we use this to keep track of what position/character we are currently working on in the recursion
	int counter = 0; //keeps count of how many unique numbers we have from the given strings
    // loops to split up unique letters from each of the strings to put into the letters map and mappings map
    
    //the code below allows us to loop into each value and set up the unique characters from every string
    for (int i = 0; i < s1.size(); i++) 
    {
        if (mapping.find(s1.at(i)) == mapping.end()) //checks if current mapping has the character in it already
        {
            letters[counter] = s1.at(i); // sets the letters map to hold the 'index'(key is the counter) and the character
            mapping[s1.at(i)] = 0; // sets up mapping with unique character set to 0;
			counter++;
        }
    }

    for (int i = 0; i < s2.size(); i++)
    {
        if (mapping.find(s2.at(i)) == mapping.end())
        {
            letters[counter] = s2.at(i);
            mapping[s2.at(i)] = 0;
			counter++;
        }
    }

    for (int i = 0; i < s3.size(); i++)
    {
        if (mapping.find(s3.at(i)) == mapping.end())
        {
            letters[counter] = s3.at(i);
            mapping[s3.at(i)] = 0;
			counter++;
        }
    }
 
	//set ans to call the perm function for the first time
	bool ans = perm(s1,s2,s3,mapping,letters,counter, usedNumbers,0);

    return ans;

}

