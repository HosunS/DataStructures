#ifndef __PROJ_FOUR_LEVEL_BALANCED_TREE_HPP
#define __PROJ_FOUR_LEVEL_BALANCED_TREE_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>

class ElementNotFoundException : public RuntimeException 
{
public:
	ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};

template <typename Key, typename Value>
struct levelNode
{
	Key key;
	Value value;
	levelNode* left;
	levelNode* right;
	int level;
	levelNode(Key k , Value v): key(k), value(v), left(NULL), right(NULL),level(1){}
	bool operator >(const levelNode<Key,Value> &node) const
	{
		return key > node.key;
	}

	bool operator ==(const levelNode<Key,Value> &node) const
	{
		return key == node.key;
	}

	bool operator <(const levelNode<Key,Value> &node) const
	{
		return key < node.key;
	}
};

template<typename Key, typename Value>
class LevelBalancedTree
{
	typedef levelNode<Key,Value> Node;
private:
	// fill in private member data here
	// If you need to declare private functions, do so here too.
	Node* root2;
	int size2;
	bool deletetree(Node* R);

public:
	LevelBalancedTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	LevelBalancedTree(const LevelBalancedTree & st);
	//	LevelBalancedTree & operator=(const LevelBalancedTree & st);


	// The destructor is required. 
	~LevelBalancedTree();

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const noexcept; 

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const LevelBalancedTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the balancing operation(s) if needed
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);


	// Deletes the given key from the tree
	// and performs the balancing operation(s) if needed.
	// If the key does not exist in the tree, 
	// do not modify the tree.
	void remove(const Key &k);


	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;
	//helper functions
	void inOrder2(Node* root, std::vector<Key> &foo) const;
	void preOrder2(Node* root, std::vector<Key> &foo) const;
	void postOrder2(Node* root, std::vector<Key> &foo) const;
	void insert(Node* root, const Key & k, const Value & v);
	void balance(Node* root, Node* prev);
	int getdist(Node* parent, Node* child);
	void Rrotation(Node* root, Node* prev);
	void Lrotation(Node* root, Node* prev);
	void Mrotationright(Node* root, Node* prev);
	void Mrotationleft(Node* root, Node* prev);
	bool isBalanced(Node* root);
	void M2inrotationright(Node* root, Node* prev, Node* above);
	void M2inrotationleft(Node* root, Node* prev, Node* above);
	void remove(Node* root,const Key& k);
	void removebalance(Node* root, Node* prev);
};


template<typename Key, typename Value>
bool LevelBalancedTree<Key,Value>::deletetree(Node* R)
{
	if(!root2)
	return false;
	delete(R->left);
	delete(R->right);
	delete root2;
	return true;
}



template<typename Key, typename Value>
LevelBalancedTree<Key,Value>::LevelBalancedTree()
{
	root2 = nullptr;
	size2 = 0;
}

template<typename Key, typename Value>
LevelBalancedTree<Key,Value>::~LevelBalancedTree()
{
	delete(root2);
	size2 = 0;
	root2 = nullptr;
}

template<typename Key, typename Value>
size_t LevelBalancedTree<Key, Value>::size() const noexcept
{
	return size2;
}

template<typename Key, typename Value>
bool LevelBalancedTree<Key, Value>::isEmpty() const noexcept
{
	return (root2 == nullptr);
}


template<typename Key, typename Value>
bool LevelBalancedTree<Key, Value>::contains(const Key &k) const noexcept
{
	Node* curr = root2;
	while(curr != nullptr)
	{
		if(k < curr->key)
		{
			curr = curr->left;
		}
		else
		{
			if(k == curr->key)
			{
				return true;
			}
			else{
				curr = curr->right;
			}
		}
	}
	return false;
}



template<typename Key, typename Value>
Value & LevelBalancedTree<Key, Value>::find(const Key & k)
{
	Node* curr = root2;
	while(curr != nullptr)
	{
		if( k < curr->key)
		{
			curr = curr->left;
		}
		else if(k > curr->key)
		{
			curr = curr->right;
		}
		else
		{
			return curr->value;
		}
	}
	throw ElementNotFoundException("Value does not exist.");
}

template<typename Key, typename Value>
const Value & LevelBalancedTree<Key, Value>::find(const Key & k) const
{
	Node* curr = root2;
	while(curr != nullptr)
	{
		if( k < curr->key)
		{
			curr = curr->left;
		}
		else if(k > curr->key)
		{
			curr = curr->right;
		}
		else
		{
			return curr->value;
		}
	}
	throw ElementNotFoundException("Value does not exist.");
}

template<typename Key, typename Value>
int LevelBalancedTree<Key,Value>::getdist(Node* parent, Node* child)
{
	if(parent != nullptr and child != nullptr)
	{
		return (parent->level - child->level);
	}
	else
		return parent->level;
}						

template<typename Key, typename Value>
void LevelBalancedTree<Key,Value>::Rrotation(Node* root, Node* prev)
{
	// prev->level--;
	// prev->left = root->left;
	// root->left = root->left->right;
	// prev->left->right = root;
	if(prev->key == root2->key)
	{
		prev->level--;
		prev->left = root->right;
		root->right = prev;
		this->root2 = root;
	}
	else
	{
		// root->level--;
		// // prev->left = root->left;
		// // root->left = root->left->right;
		// // prev->left->right = root;
		// Node* temp = root->left;
		// root->left = temp->right;
		// temp->right = root;
		// prev->left = temp;
		prev->level--;
		prev->left = root->right;
		root->right = prev;


	}
}

template<typename Key, typename Value>
void LevelBalancedTree<Key,Value>::Lrotation(Node* root, Node* prev)
{
	// root->level--;
	// prev->right = root->right;
	// root->right = root->right->left;
	// prev->right->left = root;
	if(prev == root2)
	{
		root->level--;
		prev->right = root->left;
		root->left = prev;
		this->root2 = root;
	}
	else
	{
		prev->level--;
		prev->right = root->left;
		root->left = prev;
	}
}

template<typename Key, typename Value>
void LevelBalancedTree<Key,Value>::Mrotationright(Node* root, Node* prev)
{
	root->level--;
	prev->level--;
	root->right->level++;
	root->right = root2->left;
	root2->left = root;
	prev->left = root2->right;
	root2->right = prev;
}

template<typename Key, typename Value>
void LevelBalancedTree<Key,Value>::Mrotationleft(Node* root, Node* prev)
{
	root->level--;
	prev->level--;
	root->left->level++;
	root->left = root2->right;
	root2->right = root;
	prev->left = root2->left;
	root2->left = prev;
}

template<typename Key,typename Value> 
void LevelBalancedTree<Key,Value>::M2inrotationright(Node* root, Node* prev, Node* above)
{
	root->level--;
	prev->level--;
	root->right->level++;
	prev->left = above->right->right;
	root->right = above->right->left;
	above->right->left = root;
	above->right->right = prev;
}

template<typename Key,typename Value> 
void LevelBalancedTree<Key,Value>::M2inrotationleft(Node* root, Node* prev, Node* above)
{
	root->level--;
	prev->level--;
	root->left->level++;
	prev->right = above->left->left;
	root->left = above->left->right;
	above->left->right = root;
	above->left->left = prev;
}


template<typename Key, typename Value>
bool LevelBalancedTree<Key,Value>::isBalanced(Node* root)
{
	int leftdist = getdist(root,root->left);
	int rightdist = getdist(root,root->right);
	if((leftdist != 0 and leftdist <= 2) and (rightdist != 0 and rightdist <= 2)){
		return true;
	}
	else
	{
		return false;
	}
}



template<typename Key,typename Value>
void LevelBalancedTree<Key,Value>::balance(Node* root, Node* prev)
{
	if(root == nullptr)
		return;
	if(prev == nullptr and (getdist(root,root->left) == 0 or getdist(root,root->right) == 0)){

		if((getdist(root,root->left) == 0 and getdist(root,root->right) < 2) or (getdist(root,root->right) == 0 and getdist(root,root->left) < 2 ))
		{
			root->level++;
		}
		else if((getdist(root,root->left) == 0 and getdist(root,root->right) >= 2) and (getdist(root->left,root->left->left) < 2))
		{
			// root->level--;
			// Node* temp = root;
			// root->right = root->right->left;
			// temp->left->right = root;
			Rrotation(root->left,root);
		}
		else if ((getdist(root,root->right) == 0 and getdist(root,root->left) >= 2) and (getdist(root->right,root->right->right) < 2))
		{
			// root->level--;
			// Node* temp = root;
			// root->left = root->left->right;
			// temp->left->right = root;
			Lrotation(root->right,root);
		}
		else if(getdist(root,root->right) >= 2 and getdist(root->left,root->left->left) >= 2 and getdist(root->left,root->left->right) == 1)
		{
			this->root2 = root->left->right;
			Mrotationright(root->left,root);
		}
		else if(getdist(root,root->left) >= 2 and getdist(root->right,root->right->right) >= 2 and getdist(root->right,root->right->left) == 1)
		{
			this->root2 = root->right->left;
			Mrotationleft(root->right,root);
		}
	}
	else // not at root of whole tree
	{	if((getdist(root,root->left) == 0 and getdist(root,root->right) < 2) or (getdist(root,root->right) == 0 and getdist(root,root->left) < 2 ))
		{
			root->level++;
			return;
		}
		else if(getdist(root,root->left) == 0 and getdist(root,root->right) >= 2 and getdist(root->left,root->left->left) < 2)
		{
			prev->left = root->left;
			Rrotation(root->left,root);
			return;
		}
		else if(getdist(root,root->right) == 0 and getdist(root,root->left) >= 2 and getdist(root->right,root->right->right) < 2 )
		{
				prev->right = root->right;
				Lrotation(root->right,root);
				return;
		}
		else if(getdist(root,root->left) == 0 and getdist(root,root->right) >= 2 and (getdist(root->left,root->left->left) >= 2 and getdist(root->left,root->left->right)== 1))
		{
			prev->right = root->left->right;
			M2inrotationright(root->left,root,prev);
			return;
		}
		else if(getdist(root,root->right) == 0 and getdist(root,root->left) >= 2 and (getdist(root->right,root->right->right) >= 2 and getdist(root->right,root->right->left)== 1))
		{
			prev->left = root->right->left;
			M2inrotationleft(root->right,root,prev);
			return;
		}
	}
}

//insert helper func
template<typename Key, typename Value>
void LevelBalancedTree<Key,Value>::insert(Node* root, const Key& k, const Value & v)
{
	if(k < root->key)
	{
		if(root->left == nullptr)
		{
			root->left = new Node(k,v);
			return;
		}
		insert(root->left,k,v);
		balance(root->left,root);
		return;
	}

	// key is greater than current nodes key
	if(root->right == nullptr)
	{
		root->right = new Node(k,v);
		return;
	}						
	insert(root->right,k,v);
	balance(root->right,root);
}

template<typename Key, typename Value>
void LevelBalancedTree<Key, Value>::insert(const Key & k, const Value & v)
{
	if(isEmpty())
	{
		root2 = new Node(k,v);
		size2++;
		root2->level = 1;
		return;
	}
	insert(root2,k,v);
	balance(root2, nullptr);
	size2++; 	
}

template<typename Key,typename Value>
void LevelBalancedTree<Key,Value>::removebalance(Node* root, Node* prev)
{

		if(isBalanced(root) == true and root->left != nullptr and root->right != nullptr)
		{
			return;
		}
		else if(root->right == nullptr and root->left == nullptr)
		{
			root->level = 1;
		}
		else if(root->right == nullptr and root->left == nullptr)
		{
			root->level = 1;
		}
		else if(getdist(root,root->left) == 2 and getdist(root,root->right) == 3)
		{
			root->level--;
		}
		else if(getdist(root,root->right) == 2 and getdist(root,root->left) == 3)
		{
			root->level--;
		}
		else if(getdist(root,root->right) > 2 and root->left->right != nullptr)
		{
			root->level--;
			root->left->level++;
			prev->right = root->left;
			root->left = root->left->right;
			prev->right->right = root;
		}
		else if(getdist(root,root->left) > 2 and root->right->left != nullptr)
		{
			root->level--;
			root->right->level++;
			prev->left = root->right;
			root->right = root->right->left;
			prev->left->left = root;
		}
		else if(getdist(root,root->right) > 2 and root->left->right == nullptr)
		{
			root->level = 1;
			prev->right = root->left;
			prev->right->right = root;
			root->left = nullptr;
		}
		else if(getdist(root,root->left) > 2 and root->right->left == nullptr)
		{
			root->level = 1;
			prev->left = root->right;
			prev->left->left = root;
			root->right = nullptr;
		}

}




template<typename Key, typename Value>
void LevelBalancedTree<Key,Value>::remove(Node* root,const Key& k)
{
	if(k < root->key)
	{
		if(root->left != nullptr)
		{
		if(root->left->key == k)
		{
			if(root->left->level == 1) //we are deleting leaf node
			{
				root->left = root->left->left;
				return;
			}
			else //deleting internal node, need to move into position to be leaf node.
			{
				if(root->left->left != nullptr and root->left->right != nullptr)
				{
					root->left->left->level = root->left->level;
					root->left->left->right = root->left->right;
					root->left = root->left->left;

				}
				else
				{
					root->left = root->left->left;
				}
			}
			return;
		}
		remove(root->left,k);
		removebalance(root->left,root);
		}
	}
	if(root->right != nullptr)
	{
	if(root->right->key == k)
	{
		if(root->right->level == 1) //we are deleting leaf node
		{
			root->right = root->right->right;
			return;
		}
		else //deleting internal node, need to move into position to be leaf node.
		{
			if(root->right->right != nullptr and root->right->left != nullptr)
			{
				root->right->right->level = root->right->level;
				root->right->right->left = root->right->left;
				root->right = root->right->right;
			}
			else
			{
				root->left = root->left->left;
			}
			return;
		}
	}
		remove(root->right,k);
		removebalance(root->right,root);
}
}

template<typename Key, typename Value>
void LevelBalancedTree<Key, Value>::remove(const Key &k)
{
	if(isEmpty())
	{
		return;
	}
	remove(root2,k);
	removebalance(root2,nullptr);
	size2--;

}












template<typename Key, typename Value>
void LevelBalancedTree<Key,Value>::inOrder2(Node* root, std::vector<Key> &foo) const
{
	if(root == nullptr) 
	{
		return;
	}
	inOrder2(root->left, foo);
	foo.push_back(root->key);
	inOrder2(root->right,foo);
}

template<typename Key, typename Value>
void LevelBalancedTree<Key,Value>::preOrder2(Node* root, std::vector<Key> &foo) const
{
	if(root == nullptr)
	{
		return;
	}
	foo.push_back(root->key);
	preOrder2(root->left,foo);
	preOrder2(root->right,foo);

}

template<typename Key, typename Value>
void LevelBalancedTree<Key,Value>::postOrder2(Node* root, std::vector<Key> &foo) const
{
	if(root == nullptr)
	{
		return;
	}
	preOrder2(root->left,foo);
	preOrder2(root->right,foo);
	foo.push_back(root->key);
}


template<typename Key, typename Value>
std::vector<Key> LevelBalancedTree<Key, Value>::inOrder() const
{
	std::vector<Key> foo;
	inOrder2(root2,foo);
	return foo;

}


template<typename Key, typename Value>
std::vector<Key> LevelBalancedTree<Key, Value>::preOrder() const
{
	std::vector<Key> foo;
	preOrder2(root2,foo);
	return foo; 
}


template<typename Key, typename Value>
std::vector<Key> LevelBalancedTree<Key, Value>::postOrder() const
{
	std::vector<Key> foo;
	postOrder2(root2,foo);
	return foo; 
};







#endif