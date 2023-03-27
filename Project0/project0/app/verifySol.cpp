#include <unordered_map>
#include <string>
#include "verifySol.hpp"

bool verifySolution(std::string s1, std::string s2, std::string s3, const std::unordered_map<char, unsigned> & mapping)
{

    //need an int to hold the value of each addend after converting using map
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

    //return true if converted (s1 + s2 = s3) ~ if not return false
    if(cons1 + cons2 == cons3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

