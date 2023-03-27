#include "Wordset.hpp"
#include <string>
#include <cmath>

// returns s, as a number in the given base, mod the given modulus
unsigned polynomialHashFunction(const std::string & s, unsigned base, unsigned mod)
{
	unsigned ans = 0;
	// use i for indicating the power for polyhashfunction base^(power), starts at size-1 and goes down to 0
	for(int i = s.size()-1 ;i >= 0; i--)
	{	// sets value at strings index 0, to the most 'significant' digit
		unsigned sigdig = s.at(s.size() - i - 1) - 'a' + 1;
		for(int j = 0; j < i; j++) 
		{
			sigdig = sigdig *  base; // multiply the significant digit we found to the base by the index it is currently at in the string
		}
		ans += sigdig;
		ans %= mod; // mod each significant number after multiplying it with the base ^ power
	}
	return ans;
}





WordSet::WordSet(unsigned initialCapacity, unsigned evictionThreshold)
{
// two dynamic arrays that need to be resized if needed later
hasharr1 = new std::string[initialCapacity];
hasharr2 = new std::string[initialCapacity];
this->arrSize = initialCapacity;
this->count = 0;
// populate new arrays with empty strings
for(int i = 0; i < arrSize; i++)
{
	hasharr1[i] = "";
	hasharr2[i] = "";
}
}


WordSet::~WordSet()
{
	// delete hasharr1;
}


void WordSet::insert(const std::string & s)
{
	unsigned threshCount = 0; // keeps track of how many times we've evicted a word from the array
	// use these string to keep a rotation and keep track of the string we kicked out
	std::string s1 = s;

	while(threshCount <= this->DEFAULT_EVICT_THRESHOLD) // will keep runnign as long as we are below the amount of evicts allowed
	{	
		if(contains(s1) == true)
		{
			break;
		}

		unsigned indexH1 = polynomialHashFunction(s1,WordSet::BASE_H1,arrSize); // uses poly hash to set the value of first index of the input string
		if(hasharr1[indexH1] == "") // if empty enter the word
		{
			hasharr1[indexH1] = s1;
			this->count++;
			break;
		}
		else
		{
			std::string s2 = hasharr1[indexH1];
			hasharr1[indexH1] = s1;
			unsigned indexH2 = polynomialHashFunction(s2,WordSet::BASE_H2,arrSize); // use hash function to find key

			if(hasharr2[indexH2] == "") // if empty place it in
			{
				hasharr2[indexH2] = s2;
				this->count++; // used to return amount of elements in arrays
				break;
			}
			else
			{
				s1 = hasharr2[indexH2];
				hasharr2[indexH2] = s2;
			}
		}
		threshCount++;
	}

	if(threshCount >= this->DEFAULT_EVICT_THRESHOLD)
	{
		bool prime = false;
		//guarantees new size to be more than twice the size of the current hash
		unsigned newSize = this->arrSize * 2;
		while(prime == false)
		{
			for(int i = 2; i < newSize ; i++)
			{
				if( newSize % i == 0)
				{
					prime = false;
					newSize++;
					break;
				}
				prime = true;
			}
		} // continue adding the the size of the array until we get a prime number

		WordSet resize = WordSet(newSize,this->DEFAULT_EVICT_THRESHOLD); //create new wordset, will create new empty arrays hasharr1 and hasharr2 with new prime size

		resize.insert(s1); // this part repopulates the new wordset by inserting again
		for(int i = 0; i < arrSize; i++)
		{
			if(hasharr1[i] != "")
			{
				resize.insert(hasharr1[i]);
			}
		}

		for(int i = 0; i < arrSize; i++)
		{
			if(hasharr2[i] != "")
			{
				resize.insert(hasharr2[i]);
			}
		}
	
		*this = resize;
	}
}


//finds the key given from polynomal hashfunction to go through both arrays, and see if the string exists // can only be in one array or the other
bool WordSet::contains(const std::string & s) const
{
	unsigned indexH1 = polynomialHashFunction(s,WordSet::BASE_H1,arrSize);
	unsigned indexH2 = polynomialHashFunction(s,WordSet::BASE_H2,arrSize);
	bool contains = false;
	if(hasharr1[indexH1] == s or hasharr2[indexH2] == s)
	{
		contains = true;
	}
	return contains;
}

// return how many distinct strings are in the set
unsigned WordSet::getCount() const
{

	return this->count; // this is not the right answer. 
}

// return how large the underlying array is.
unsigned WordSet::getCapacity() const
{
	return this->arrSize; // that isn't even a prime number!
}
