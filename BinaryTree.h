#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
/*  Program: Project 4 - BST
    Author: Anthony Esmeralda, Kevin Ngo
    Class: CSCI 220
    Date:  Novemember 14, 2017
    Description: Binary Search Tree that uses an AVL tree search through records 
				 of county/state, population, and county/state name

    I certify that the code below is my own work.
	
	Exception(s): N/A

*/
#include <iostream>
#include <list>
#include <iterator>
#include "Entry.h"

using namespace std;

class BinaryTree {
protected:
	struct Node {
		Entry element;
		Node *parent;
		Node *left;
		Node *right;
		Node()
		{
			parent = nullptr;
			left = nullptr;
			right = nullptr;
		}
	};
	// POSITION CLASS (NESTED CLASS)
public:		
	class Position {
	private:
		Node *curNode;
	public:
		Position()
		{
			curNode = nullptr;
		}
		Position(Node *passedNode)
		{
			curNode = passedNode;
		}
		void addElement(Entry data)
		{
			curNode->element = data;
		}
		Entry& operator*()
		{
			return curNode->element;
		}
		Position left() const
		{
			return Position(curNode->left);
		}
		Position right() const
		{
			return Position(curNode->right);
		}
		Position parent() const
		{
			return Position(curNode->parent);
		}
		bool isRoot()
		{
			return curNode->parent == NULL;
		}
		bool isExternal() const
		{
			return (curNode->left == nullptr && curNode->right == nullptr);
		}
		bool operator==(const Position &p)
		{
			return curNode == p.curNode;
		}
		bool operator!=(const Position &p)
		{
			return curNode != p.curNode;
		}

		friend class BinaryTree;
	};
	typedef list<Position> PositionList;		// CREATE A LIST NAMED POSITIONLIST TO HOLD OUR POSITIONS.

/////////////////////////////////////////////////////////
//	The Binary Tree's Public and Protected Functions   //
//		the list of prototypes for all the			   //
//			functions that is required                 // 
//			  while using the binary                   //
//					 tree							   //
/////////////////////////////////////////////////////////
public:
	BinaryTree();
	int size() const;
	Position root() const;
	PositionList positions() const;
	void addRoot();
	void expandExternal(const Position& p);
	Position removeAboveExternal(const Position &p);
protected:
	void inorder(Node *curNode, PositionList& pl) const;
private:
	Node *_root;
	int counter;
};
#endif // !_BINARY_TREE_H_
