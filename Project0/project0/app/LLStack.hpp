#ifndef __ICS46_LL_STACK_HPP
#define __ICS46_LL_STACK_HPP

#include "runtimeexcept.hpp"

class StackEmptyException : public RuntimeException 
{
public:
	StackEmptyException(const std::string & err) : RuntimeException(err) {};
};

// This is the LLStack class you will be implementing for this project.
// Remember to see the write-up for more details!

template<typename Object>
class LLStack
{
public:
	struct node // node struct holds value and a pointer to the next node.
	{
		public:
		Object value;
		node *next;
	};
	

	// constructor
	LLStack();

	// copy constructor (remember, deep copy!)
	LLStack(const LLStack & st);

	// assignment operator (remember, deep copy!)
	LLStack & operator=(const LLStack & st);

	// destructor
	~LLStack();

	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	// We have two top() functions.  The first gets called if your LLStack is not
	// a const, while the latter gets called on a const LLStack
	// (the latter might occur via const reference parameter, for instance).
	// Be sure to test both!  It is important when testing to ensure that
	// EVERY funtion gets called and tested!
	Object & top();
	const Object & top() const;

	void push(const Object & elem) noexcept;
	void pop();
	private:
	// fill in private member data here
	node* hd;

};

template <typename Object>
LLStack<Object>::LLStack()
{
	// TODO: Fill in your constructor implementation here.
	this->hd = nullptr;

}

template <typename Object>
LLStack<Object>::LLStack(const LLStack & st)
{
	// TODO: Fill in your copy constructor implementation here.
	hd = st.hd;

}

template <typename Object>
LLStack<Object> & LLStack<Object>::operator=(const LLStack & st)
{
	// TODO: Fill in your assignment operator implementation here.
	this->hd = st.hd;
	return *this;
	// return *this; // Stub so this function compiles without implementation.
}

template <typename Object>
LLStack<Object>::~LLStack()
{
	// TODO: Fill in your destructor implementation here.
}

template <typename Object>
size_t LLStack<Object>::size() const noexcept
{
	// TODO: Fill in your size() implementation here.
	// return 0; // Stub so this function compiles without an implementation.
	int size = 0;
	 node *curNode = new node;  //create a pointer node that points to the head node
	 curNode = this->hd;
	while(curNode != nullptr) // runs this loop until we reach the end
	{
		size++; //increments size for every node we visit
		curNode = curNode->next; //sets curNode to go the node its pointing at 
	}
	delete curNode;
	return size;
}

template <typename Object>
bool LLStack<Object>::isEmpty() const noexcept
{
	if(this->hd == nullptr) //if the head is nullptr means our stack is empty
	{
		return true;
	}
	else //or stack has atleast one node
	{
		return false;
	}
	// TODO: Fill in your isEmpty() implementation here.
	// return true; // Stub so this function compiles without an implementation.
}

template <typename Object>
Object& LLStack<Object>::top()
{
	// TODO: Fill in your top() implementation here.
	// The following is a stub just to get the template project to compile.
	// You should delete it for your implementation.
	// Object * o = new Object();
	// return *o;
	if(this->hd != nullptr) //as long as the stack is not empty
	{
		return this->hd->value;
	}
	else
	{
		throw StackEmptyException("error");
	}

}

template <typename Object>
const Object& LLStack<Object>::top() const
{
	// TODO: Fill in your const top() implementation here.
	// The following is a stub just to get the template project to compile.
	// You should delete it for your implementation.
	// const Object * o = new Object();
	// return *o;
	if(this->hd != nullptr) 
	{
		Object &ref = this->hd->value;
		return ref;
	}
	else
	{
		throw StackEmptyException("error");
	}
}

template <typename Object>
void LLStack<Object>::push(const Object& elem) noexcept
{
	node* temp = new node;
	temp->value = elem;
	
	if(this->hd == nullptr)
	{
		this->hd = temp;
	}
	else
	{
		temp->next = this->hd;
		this->hd = temp;
	}
	
	// TODO: Fill in your push() implementation here.
}

template <typename Object>
void LLStack<Object>::pop()
{
	if(this->isEmpty() == false)
	{
		node* temp = new node;
		temp = this->hd->next;
		// delete hd;
		this->hd = temp;
		
	}
	// TODO: Fill in your pop() implementation here.
}









#endif 
