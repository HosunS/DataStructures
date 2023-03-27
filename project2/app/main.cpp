#include "SkipList.hpp"
#include <iostream>
using namespace std;

int main()
{
    SkipList<int,int> s1;
    s1.insert(0,0);
    s1.insert(1,2);

    return 0;
}

