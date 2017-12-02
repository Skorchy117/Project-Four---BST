/*  Program: Project 4 - BST
 Author: Anthony Esmeralda, Kevin Ngo
 Class: CSCI 220
 Date:  Novemember 14, 2017
 Description: Binary Search Tree that uses an AVL tree search through records
 of county/state, population, and county/state name
 
 I certify that the code below is my own work.
 
 Exception(s): N/A
 */
#include "SearchTree.h"
SearchTree::SearchTree()
{
	T.addRoot();
	tSize = 0;
	T.expandExternal(T.root());
}

int SearchTree::size() const
{
	return tSize;
}

bool SearchTree::empty() const
{
	return tSize == 0;
}

void SearchTree::erase(int key)
{
	BinaryTree::Position v = finder(key, root());
	if (v.isExternal())
	{
		cout << "data was not found on " << key;
	}
	else eraser(v);
}

void SearchTree::erase(const Iterator & p)
{
	eraser(p.data);
}

SearchTree::Iterator SearchTree::find(int key)
{
	BinaryTree::Position dummy;
	BinaryTree::Position value = finder(key, root());		// use the finder function to find our position
	if (!value.isExternal())								// if our value function is internal
	{
		return SearchTree::Iterator(value);					// return the iterator
	}
	else return NULL;				// else return NULL.
}

SearchTree::Iterator SearchTree::insert(Entry data)
{
	BinaryTree::Position value = inserter(data);			// use our inserter function to input our data
	return SearchTree::Iterator(value);						// return our iterator.
}

SearchTree::Iterator SearchTree::begin()
{
	BinaryTree::Position v = root();
	while (!v.isExternal())
	{
		v = v.left();
	}
	return Iterator(v.parent());
}

SearchTree::Iterator SearchTree::end()
{
	return Iterator(T.root());
}

BinaryTree::Position SearchTree::root() const
{
	return T.root().left();									// since T.root() is our superroot, we go to the left to get our root.
}

BinaryTree::Position SearchTree::finder(int key,BinaryTree::Position  &data)
{
	Entry dataEntry = *data;						// grab the data's position entry data.
	if (data.isExternal())							// check if the data's position is external
	{
		return data;								// then it was not found and return data position
	}
	if (key < dataEntry.county_state_code)			// if the key is less than the data position key
	{
		return finder(key, data.left());			// recursively go to the left until the position key == key
	}
	else if (dataEntry.county_state_code < key)		// if the key is greater than the position key
	{
		return finder(key, data.right());			// then recursively  go to the right until the position key == key
	}
	else return data;
}

BinaryTree::Position SearchTree::inserter(Entry data)
{
	int key = data.county_state_code;						// obtain the key from our Entry variable data
	BinaryTree::Position value = finder(key, root());		
	while (!value.isExternal())								// while value is internal
	{
		value = finder(key, value.right());					// find a position to place our Entry variable data
	}
	Entry temp = *value;

	T.expandExternal(value);								// expand that position 
	value.addElement(data);									// and add the data into that position
	tSize++;												// increase our size
	return value;
}

BinaryTree::Position SearchTree::eraser(BinaryTree::Position data)
{
	BinaryTree::Position w;									// create a position holder (we named it w)
	if (data.left().isExternal())							// check if our data position left is external
	{
		w = data.left();									// if it is, then w = data.left
	}
	else if (data.right().isExternal())						// check if our data position right is external if left is not ex
	{
		w = data.right();									// if it is, then w = data.right
	}
	else                                                    // if none of the above
	{
		w = data.right();									// set w to data.right		
		do
		{
			w = w.left();									// keep looping left until we are at an external root (smallest right)
		} while (!w.isExternal());
		BinaryTree::Position u = w.parent();				// set u to be w's parent
		data.addElement(*u);								// set the position u's data to be added into data's position's data to save 
	}
	tSize--;
	return T.removeAboveExternal(w);
}

BinaryTree::Position SearchTree::restructure(BinaryTree::Position x)
{																		// data is our x variable
	BinaryTree::Position y = x.parent();								// parent is our y variable
	BinaryTree::Position z = y.parent();								// grandparent is our z variable
	BinaryTree::Position a, b, c, t0, t1, t2, t3, newNode;
	if (y == z.right() && x == y.right())								// if our tree is a single rotation case on the right side
	{
		a = z;															// set our a,b,c accordingly
		b = y;
		c = x;
		t0 = a.left();													// t0 is always a's left
		t1 = b.left();													// t1 is always b's left
		t2 = c.left();													// t2 is always c's left
		t3 = c.right();													// t3 is always c's right
		newNode = b;													// set b to be our new subtree root
		newNode.setParent(z.parent());									// set our newNode parents to be z's parent
		if (z != z.parent().left())						// if z is not the root and z does not equal the parent of z's left
		{
			z.parent().setRightChild(newNode);							// then newNode is the z's parent right child (since we are on the right side)
		}
		else z.parent().setLeftChild(newNode);							// else then we are the left child since z was a root and the superoot's child is on the left side
		t1.setParent(a);												// set t1 parents to be a
		a.setRightChild(t1);											// and a's right child to be t1
		a.setParent(newNode);											// a's parent is our new Node
		c.setParent(newNode);											// c's parents is our new Node
		newNode.setLeftChild(a);										// set new Nodes left child to be a
		newNode.setRightChild(c);
																		// we dont need to do newNodes right child to be c, since c was already on b's right side.
	}
	if (y == z.left() && x == y.left())									// if our a tree is a single rotation case on left side
	{
		a = z;															// set our a,b,c accordingly
		b = y;
		c = x;
		t0 = a.right();													// t0 is always a's right
		t1 = b.right();													// t1 is always b's right
		t2 = c.right();													// t2 is always c's right
		t3 = c.left();													// t3 is always c's left
		newNode = b;													// b will be the new subtree root
		newNode.setParent(z.parent());									// newNodes parent is z's parent
		if (z.parent().left() == z)
		{
			z.parent().setLeftChild(newNode);								// this one doesnt need a special case like in the right side case since we're always making z's parent child left.
		}
		else z.parent().setRightChild(newNode);
		t1.setParent(a);												// t1's parent is a
		a.setLeftChild(t1);												// a left child is t1
		a.setParent(newNode);											// a's parent is newNode
		c.setParent(newNode);											// c's parent is newNode
		newNode.setRightChild(a);										// newNode's right child is a
		newNode.setLeftChild(c);
																		// again, we do not need to set a left child since newNode's left child is already c.
	}
	if (y == z.right() && x == y.left())
	{
		a = z;															// set our a,b,c accordingly
		b = x;
		c = y;
		t0 = a.left();													// t0 is always a's left
		t1 = b.left();													// t1 is always b's right
		t2 = b.right();													// t2 is always b's left
		t3 = c.right();													// t3 is always c's right
		newNode = b;													// b will be the new subtree root
		newNode.setParent(z.parent());									// newNodes parent is z's parents
		if (z != z.parent().left())												// check if z is a root since we're doing a right left rotation
		{
			z.parent().setRightChild(newNode);							// if its not, newNode will be the right child of z's parent
		}
		else z.parent().setLeftChild(newNode);							// else it will be the new root
		t1.setParent(a);												// t1's parent is a
		a.setRightChild(t1);											// a's right child is t1
		t2.setParent(c);												// t2's parent is c
		c.setLeftChild(t2);												// c's left child is t2
		a.setParent(newNode);											// a's parent is newNode
		c.setParent(newNode);											// c's parent is newNode.
		newNode.setLeftChild(a);										// newNodes left child is a
		newNode.setRightChild(c);										// newNodes right child is b
	}

	if (y == z.left() && x == y.right())
	{
		c = z;															// set our a,b,c accordingly
		b = x;
		a = y;
		t0 = a.left();													// t0 is always a's left
		t1 = b.left();													// t1 is always b's left
		t2 = b.right();													// t2 is always b's right
		t3 = c.right();													// t3 is always c's right
		newNode = b;													// b will be the new subtree root
		newNode.setParent(z.parent());									// newNodes parent is z's parents
		if (z.parent().left() == z)
		{
			z.parent().setLeftChild(newNode);								// z's parent left child is our newNode
		}
		else z.parent().setRightChild(newNode);
		t1.setParent(a);												// t1's parent is a
		a.setRightChild(t1);											// a's right child is t1
		t2.setParent(c);												// t2's parent is c;
		c.setLeftChild(t2);												// c's left child is t2
		a.setParent(newNode);											// a's parent is newNode
		c.setParent(newNode);											// c's parent is newNode
		newNode.setLeftChild(a);										// newNodes left child is a
		newNode.setRightChild(c);										// newNodes right child is c
	}
	if (z == root())													// if z was the root, we need to make sure to change the root 
	{
		newRoot(newNode);													
	}
	return newNode;
}

void SearchTree::newRoot(BinaryTree::Position x)
{
	T.setRoot(x);
}
