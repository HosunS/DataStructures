


#ifndef ___SKIP_LIST_HPP
#define ___SKIP_LIST_HPP

#include <cmath> // for log2
#include <string>
#include <vector>
#include "runtimeexcept.hpp"
#include <iostream>
/**
 * flipCoin -- NOTE: Only read if you are interested in how the
 * coin flipping works.
 * 
 * @brief Uses the bitwise representation of the key to simulate
 * the flipping of a deterministic coin.
 * 
 * This function looks at the bitwise representation to determine
 * how many layers it occupies in the skip list. It takes the bitwise
 * XOR of each byte in a 32-bit unsigned number and uses the index `previousFlips`
 * to determine the truth value. It's best to look at an example and
 * to start with values that fit into one byte.
 * 
 * Let's start with the function call `flipCoin(0, 0)`. This call is
 * asking whether or not we should insert the key `0` into layer `1`
 * (because `previousFlips` represents the number of previous flips).
 * 
 * This function will get the bitwise representation of 0: 
 * 
 *        00000000 00000000 00000000 00000000
 * 
 * All bytes are XOR'd together: 
 * 
 * 
 *  c = 0 ^ 0 ^ 0 ^ 0
 * 
 * Then the index `previousFlips` is used to obtain the bit in the `previousFlips % 8` position.
 * 
 * So the return value is `0 & 1 = 0`, since the value in the zeroth position 
 * (obtained by bitmasking the value (1 << 0) at the bottom of the function
 * is 0.
 * Thus, this value `0` should never get added beyond the bottom-most layer.
 * 
 * Before:
 * 
 * S_1: -inf ----> inf
 * S_0: -inf ----> inf
 * 
 * And after 0 is inserted
 * 
 * S_1: -inf --------> inf
 * S_0: -inf --> 0 --> inf
 * 
 * Let's look at something more interesting, like the call `flipCoin(5, 0)`.
 * Remember the binary representation for 5 is 00000101.
 * 
 * c = 0 ^ 0 ^ 0 ^ 00000101 = 00000101
 * 
 * Now we get the bit at 0th position (from `previousFlips`).
 * 
 * 00000101 & 1 = 1. Thus, `5` DOES get inserted into the next layer,
 * layer 1.
 * 
 * So the skip list before this insertion might look like:
 * 
 * S_1: -inf ----> inf
 * S_0: -inf ----> inf
 * 
 * And after it would look like:
 * 
 * S_2: -inf --------> inf
 * S_1: -inf --> 5 --> inf
 * S_0: -inf --> 5 --> inf
 * 
 * Observe that a new layer had to get created, because there should always
 * be an empty layer at the top.
 * 
 * Since 5 got inserted into the next layer, we need to flip again to see if
 * it should get propagated once more.
 * 
 * `flipCoin(5, 1)` this will produce a result of `0`, since 00000101 & (1 << 1) = 0.
 * 
 * Thus, `5` will not be pushed up to the next layer.
 * 
 * @param key The integer key which will be added to the skip list
 * @param previousFlips The number of previous flips for this key
 * @return true simulates a "heads" from a coin flip
 * @return false simulates a "tails" from a coin flip
 */
inline bool flipCoin(unsigned key, unsigned previousFlips)
{
	char c;
	unsigned first8Bits = (key & 0xFF000000) / 0x01000000 ; 
	unsigned next8Bits =  (key & 0x00FF0000) / 0x00010000;
	unsigned andThen =	 (key & 0x0000FF00) / 0x00000100;
	unsigned lastBits =   (key & 0x000000FF);
	c = first8Bits ^ next8Bits ^ andThen ^ lastBits;
	previousFlips = previousFlips % 8;
	return ( c & (1 << previousFlips) ) != 0;
}

/**
 * @brief Works the same as the integer version above, except
 * it XORs chars in a string instead of the first four
 * bytes of an integer.
 * 
 * @param key key that will be inserted into the skip list
 * @param previousFlips number of previous flips for this key 
 * @return true simulates a "heads" from a coin flip
 * @return false simulates a "tails" from a coin flip
 */
inline bool flipCoin(std::string key, unsigned previousFlips)
{
	char c = key[0];
	for(unsigned j = 1; j < key.length(); j++)
	{
		c = c ^ key[j];
	}
	previousFlips = previousFlips % 8;
	return ( c & (1 << previousFlips) ) != 0;	
}

template<typename Key, typename Value>
class SkipList
{
public:

struct node
{
	Key key;
	Value value;
	bool inf = false;
	struct node* next = nullptr;
	struct node* prev = nullptr;
	struct node* up = nullptr;
	struct node* down = nullptr; 
};

	SkipList();

	// You DO NOT need to implement a copy constructor or an assignment operator.

	~SkipList();
	
	// How many distinct keys are in the skip list?
	size_t size() const noexcept;

	// Does the Skip List contain zero keys?
	bool isEmpty() const noexcept;

	// How many layers are in the skip list?
	// Note that an empty Skip List has two layers by default,
	// the "base" layer S_0 and the top layer S_1.
	//
	// [S_1: Top layer]    -inf ------> inf
	// [S_0: Bottom layer] -inf ------> inf
	//
	// This "empty" Skip List has two layers and a height of one.
	unsigned numLayers() const noexcept;

	// What is the height of this key, assuming the "base" layer S_0
	// contains keys with a height of 1?
	// For example, "0" has a height of 1 in the following skip list.
	//
	// [S_1]  -inf --------> inf
	// [S_0]  -inf --> 0 --> inf
	//
	// Throw an exception if this key is not in the Skip List.
	unsigned height(const Key & k) const;

	// If this key is in the SkipList and there is a next largest key
	// return the next largest key.
	// This function should throw a RuntimeException if either the key doesn't exist
	// or there is no subsequent key. 
	// A consequence of this is that this function will
	// throw a RuntimeException if *k* is the *largest* key in the Skip List.
	Key nextKey(const Key & k) const;

	// If this key is in the SkipList and a next smallest key exists,
	// return the next smallest key.
	// This function should throw a RuntimeException if either the key doesn't exist
	// or there is no previous key. 
	// A consequence of this is that this function will
	// throw a RuntimeException if *k* is the *smallest* key in the Skip List.
	Key previousKey(const Key & k) const;

	// These return the value associated with the given key.
	// Throw a RuntimeException if the key does not exist.
	Value & find(const Key & k);
	const Value & find(Key k) const;

	// Return true if this key/value pair is successfully inserted, false otherwise.
	// See the project write-up for conditions under which the key should be "bubbled up"
	// to the next layer.
	// If the key already exists, do not insert one -- return false.
	bool insert(const Key & k, const Value & v);

	// Return a vector containing all inserted keys in increasing order.
	std::vector<Key> allKeysInOrder() const;

	// Is this the smallest key in the SkipList? Throw a RuntimeException
	// if the key *k* does not exist in the Skip List. 
	bool isSmallestKey(const Key & k) const;

	// Is this the largest key in the SkipList? Throw a RuntimeException
	// if the key *k* does not exist in the Skip List. 
	bool isLargestKey(const Key & k) const;

	// I am not requiring you to implement remove.
	
	node* insertafterabove(node *p, node *q,const Key & k,const Value & v) // will return the position has the largest key less than or equal to k
	{	
	node *newentry = new node;
	newentry->key = k;
	newentry->value = v;
	
	node *rightlink = new node;
	rightlink = q;
	while(rightlink->up == nullptr)
	{
		rightlink = rightlink->next;
	}
	rightlink = rightlink->up;


	p->next = newentry;
	newentry->prev = p;
	q->up = newentry;
	newentry->down = q;
	rightlink->prev = newentry;
	newentry->next = rightlink;
	return newentry;
	};

	node* search(const Key & k) // will return the position has the largest key less than or equal to k
	{
		node *start = new node;
		start = this->top;
		while(start->down != nullptr)
		{
			start = start->down;
			if(start->inf == true and isEmpty() == false)
			{
				start = start->next;
			}
			while(k >= start->next->key and start->next->inf != true)
			{
				start = start->next;
			}
		}
		return start;
	};

	private:
		// private variables go here.
	node* head = new node;
	node* tail = new node;
	node* top = new node;
	node* etop = new node;

	int level; // keep track of how many level we have;
	float maxHeight = 1;


};

template<typename Key, typename Value>
SkipList<Key, Value>::SkipList() {
    // TODO - your implementation goes here!
	this->head->next = this->tail;
	this->tail->prev = this->head;
	this->head->down = nullptr;
	this->tail->down = nullptr;
	this->tail->next = nullptr;
	this->head->prev = nullptr;
	//create new nodes for second layer;
	top->next = etop;
	etop->prev = top;
	top->down = this->head;
	this->head->up = top;
	etop->down = this->tail;
	this->tail->up = etop;
	this->level = 2;
	//use these bools to keep track of tail nodes and head nodes
	this->tail->inf = true;
	etop->inf = true;
	this->head->inf = true;
	top->inf = true;
}

template<typename Key, typename Value>
SkipList<Key, Value>::~SkipList() {
	// node *currNode = head;
	// node * nextNode = nullptr;

	// while(currNode->next->inf == false)
	// {
	// 	nextNode = currNode->next;
	// 	delete currNode;
	// 	currNode = nextNode;
	// }
}

template<typename Key, typename Value>
size_t SkipList<Key, Value>::size() const noexcept {
	// TODO - your implementation goes here!
	if(head->next->inf == true)
	{
		return 0;
	}
	else
	{
		node* track = new node;
		track = head;
		int size = 0;
		while(track->next->inf == false)
		{
			size++;
			track = track->next;
		}
		return size;
	}
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::isEmpty() const noexcept {
	// TODO - your implementation goes here!
	if(head->next == tail)
	{
		return true;
	}
	return false;
}

template<typename Key, typename Value>
unsigned SkipList<Key, Value>::numLayers() const noexcept {
	// TODO - your implementation goes here!
	return this->level;
}

template<typename Key, typename Value>
unsigned SkipList<Key, Value>::height(const Key & k) const {
    // TODO - your implementation goes here!
	RuntimeException ex("Key does not exists\n");
	unsigned height = 1;
	node *track = new node;
	track = head;
	try{
	while(track->next != nullptr)
	{
		if(track->key == k and track->inf != true)
		{
			while(track->up != nullptr)
			{
			height++;
			track = track->up;
			}
			return height;
		}
		track = track->next;
	}
	
		if(track->inf == true)
		{
			throw ex;
		}
	}
	catch(const RuntimeException &exception)
	{
		std::cout << exception.getMessage();
	}
	// need an exception for if the key given is not found
	return height; 
}

template<typename Key, typename Value>
Key SkipList<Key, Value>::nextKey(const Key & k) const {
    // TODO - your implementation goes here!
	RuntimeException ex("Key does not exist\n");
	try{
	node *curNode = new node;
	curNode = this->head;
	while (curNode->next->inf != true)
	{
		curNode = curNode->next;
		if (curNode->key == k)
		{
			if (curNode->next != nullptr)
			{
				return curNode->next->key;
			}
		}
	}
	if(curNode->next->inf == true)
	{
		throw ex;
	}
	}
	catch(const RuntimeException &exception)
	{
		std::cout << exception.getMessage();
	}
	return k;
}

template<typename Key, typename Value>
Key SkipList<Key, Value>::previousKey(const Key & k) const {
     // TODO - your implementation goes here!
	 RuntimeException ex("Key does not exists\n");
	try{
	node *curNode = new node;
	curNode = this->head;
	while (curNode->next->inf != true)
	{
		curNode = curNode->next;
		if (curNode->key == k)
		{
			if (curNode->prev != nullptr)
			{
				return curNode->prev->key;
			}
		}
	}
	if(curNode->next->inf == true)
	{
		throw ex;
	}
	}
	catch(const RuntimeException &exception)
	{
		 std::cout << ex;
	}
	return k;
}

template<typename Key, typename Value>
const Value & SkipList<Key, Value>::find(Key k) const {
	RuntimeException ex("Key not found\n");
	node *curNode = new node;
	try{
	curNode = this->head;
	while(curNode->next->inf != true)
	{
		curNode = curNode->next;
		if(curNode->key == k)
		{
			return curNode->value;
		}
	}
	if(curNode->next->inf == true)
	{
		throw ex;
	}
	}
	catch(const RuntimeException &exception)
	{
		std::cout << exception.getMessage();
	}
	return curNode->value;
}

template<typename Key, typename Value>
Value & SkipList<Key, Value>::find(const Key & k) {
	// TODO - your implementation goes here!
	RuntimeException ex("Key not found\n");
	node *curNode = new node;
	try{
	curNode = this->head;
	while(curNode->next->inf != true)
	{
		curNode = curNode->next;
		if(curNode->key == k)
		{
			return curNode->value;
		}
	}
	if(curNode->next->inf == true)
	{
		throw ex;
	}
	}
	catch(const RuntimeException &exception)
	{
		std::cerr<< exception.getMessage();
	}
	return curNode->value;
}




template<typename Key, typename Value>
bool SkipList<Key, Value>::insert(const Key & k, const Value & v) {
	// TODO - your implementation goes here!
	node* p = new node;
	node* q = new node;
	node* entry = new node;
	
	p = search(k);
	entry->key = k;
	entry->value = v;
	if(p->key == k and p->inf != true)
	{
		return false;
	}
	//setting new entry into bottom level
	entry->next = p->next;
	entry->prev = p;
	p->next->prev = entry;
	p->next = entry;
	q = entry;
	unsigned counter = 0;
	
	if(this->size() >= 16)
	{
		maxHeight = 3*ceil(log2(this->size()));
	}
	else
	{
		maxHeight = 12;
	}

	while(flipCoin(k, counter) == true and height(k) < maxHeight)
	{
		counter++;
		if(counter >= level-1) // add new level
		{
			level++;
			node* ntop = new node; //new top
			node* netop = new node; // new end top
			// creates enviroment for a new inf node and as new tops
			ntop->inf = true;
			ntop->up = nullptr;
			ntop->prev = nullptr;
			// same as above but for tail-top
			netop->inf = true;
			netop->up = nullptr;
			netop->next = nullptr;
			//link vertically to previous top
			ntop->down = top;
			netop->down = top;
			top->up = ntop;
			etop->up = netop;
			//link horizontally
			ntop->next = netop;
			netop->prev = ntop;
			//set new values for top
			this->top = ntop;
			this->etop = netop;
		}
		while(p->up == nullptr)
		{
			p = p->prev;
		}
		p = p->up;
		q = insertafterabove(p,q,entry->key, entry->value);
	}
	
	return true;	

	
}
//here
template<typename Key, typename Value>
std::vector<Key> SkipList<Key, Value>::allKeysInOrder() const {
	// TODO - your implementation goes here!
	node *currnode = new node;
	currnode = head->next;
	std::vector<Key> keys;
	while(currnode->next != nullptr and currnode->inf != true)
	{
		keys.push_back(currnode->key);
		currnode = currnode->next;
	}
    return keys;
}
//here
template<typename Key, typename Value>
bool SkipList<Key, Value>::isSmallestKey(const Key & k) const {
	// TODO - your implementation goes here!
	RuntimeException ex("Key not found\n");
	node *curNode = new node;
	try{
	curNode = this->head;
	while(curNode->next->inf != true)
	{
		curNode = curNode->next;
		if(curNode->key == k)
		{
			if(curNode->prev->inf == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	if(curNode->next->inf == true)
	{
		throw ex;
	}
	}
	catch(const RuntimeException &exception)
	{
		std::cout << exception.getMessage();
	}
	return false;
}
//here
template<typename Key, typename Value>
bool SkipList<Key, Value>::isLargestKey(const Key & k) const {
	// TODO - your implementation goes here!
	RuntimeException ex("Key not found\n");
	node *curNode = new node;
	try{
	curNode = this->head;
	while(curNode->next->inf != true)
	{
		curNode = curNode->next;
		if(curNode->key == k)
		{
			if(curNode->next->inf == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	if(curNode->next->inf == true)
	{
		throw ex;
	}
	}
	catch(const RuntimeException &exception)
	{
		std::cout << exception.getMessage();
	}
	return false;
}

#endif

