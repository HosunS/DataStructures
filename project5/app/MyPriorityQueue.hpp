#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"

class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};

struct node {
	std::string word;
	std::string prev;
	int dist;
	int sum;

	node()
	{
		word = "";
		prev = "";
		dist = -1; // declare -1 because index 0 is an actually the index for the min heap
		sum = -1;
	}
	
	node(std::string word, std::string prev, int distance, int summation)
	{
		this->word = word;
		this->prev = prev;
		this->dist = distance;
		this->sum = summation;
	}
	// ~node(){};
	// need these overloaded operators to be able to compare within extract min because we will be holding nodes and we need to make sure that the program knows we are comparing the dist + sum
	const bool operator < (const node & next) const
	{
		return (dist + sum < next.dist + next.sum);
	}

	const bool operator > (const node & next) const
	{
		return (dist + sum > next.dist + next.sum);
	}


};


template<typename Object>
class MyPriorityQueue
{
private:
	// fill in private member data here
	std::vector<Object> heap; // this is only here for use in a stub, you probably want to delete this.


public:

	// You also need a constructor and a destructor.
	MyPriorityQueue();
	~MyPriorityQueue();

 	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	void insert(const Object & elem);


	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, we will do this.
	// min and extractMin should throw PriorityQueueEmptyException if the queue is empty.
	const Object & min() const; 

	void extractMin(); 

};


template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{

}


template<typename Object>
MyPriorityQueue<Object>::~MyPriorityQueue()
{
}

template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return heap.size();
}



template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	return heap.empty();
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
	heap.push_back(elem);
	int index = heap.size() -1;
	while( index > 0)
	{
		int parent = (index-1)/2;
		if(heap[index] < heap[parent])
		{
			std::swap(heap[index],heap[parent]);
		}
		else{
			break;
		}
		index = parent;
	}
}




template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
		if(heap.empty())
		{
			throw RuntimeException("The heap is empty, so there is no min");
		}
	return heap[0];
}



template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{
	if(heap.empty() == true) // no elements
	{
		throw RuntimeException("The heap is empty, so we cannot extract.");
	}
	if(heap.size() == 1) // 1 element get rid of it
	{
		heap.pop_back();
	}
	else
	{
	heap[0] = heap[heap.size()-1]; // send to end of the heap to delete
	heap.pop_back();
	int i = 1; // start at the first child of the root ( left child)
	while((i * 2) > heap.size() == false) // continue until we reach an index where it is greater than the heaps size, which means we scanned through the whole thing
	{
		if((i*2) + 1 > heap.size() == true) // case in which we will only compare the left child, only when heap size is 2 
		{
			if(heap[i-1] > heap[i*2 -1] == true) // if the new root is greater than its left child we swap the two
			{
				std::swap(heap[i-1] , heap[i*2 -1]);
				i = i * 2;
			}
			else
			{
				break;
			}
		}
		else
		{
			if(heap[i*2 -1] < heap[i*2] == true) // if the left child is lower than the right
			{
				if(heap[i-1] > heap[i*2 -1] == true)  // if parent is greater than left child swap
				{
					std::swap(heap[i-1],heap[i*2 -1]);
					i = i * 2; // 
				}
				else
				{
					break;
				}
			}
			else // if right child is lower than left child
			{
				if(heap[i -1] > heap[i*2] == true) // if parent is greater than right child swap
				{
					std::swap(heap[i -1], heap[i*2]);
					i = i * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
	}
	}
}


#endif 
