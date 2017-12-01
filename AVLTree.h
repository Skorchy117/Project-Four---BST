#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_
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
#include <cmath>
#include <algorithm>
// AVL Tree Class Definition
class AVLTree : public SearchTree
{
protected:			
	typedef int county_state_code;	// a key
	typedef BinaryTree::Position TPos;			// a tree position

public:						// public functions
	AVLTree();						// constructor
	Iterator insert(Entry& entry); //Insert the entry based on the key (county_state_code)
	void erase(const county_state_code& key);	// remove country_state_code's entry
	void erase(const Iterator& it);			// remove entry at it

protected:						// utility functions 
	int height(const TPos& pos) const;			// node height utility
	void setHeight(TPos pos);				// set height utility
	bool isBalanced(const TPos& pos) const;		// is the position balanced?
	TPos tallGrandchild(const TPos& pos) const;		// get tallest grandchild
	void rebalance(const TPos& pos);			// rebalance utility
};

#endif // !_AVL_TREE_H_
