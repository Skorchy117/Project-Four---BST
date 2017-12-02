/*  Program: Project 4 - BST
 Author: Anthony Esmeralda, Kevin Ngo
 Class: CSCI 220
 Date:  Novemember 14, 2017
 Description: Binary Search Tree that uses an AVL tree search through records
 of county/state, population, and county/state name
 
 I certify that the code below is my own work.
 
 Exception(s): N/A
 */
#ifndef _SEARCH_TREE_H_
#define _SEARCH_TREE_H_
#include "BinaryTree.h"

class SearchTree {
private:
	BinaryTree T;
	int tSize;

///////////////////////////////////////
//	 Functions that we will be able	 //
//		 to use outside of			 //
//		     SearchTree				 //
//			  Class					 //
//////////////////////////////////////

public:
	class Iterator;
	SearchTree();
	int size() const;
	bool empty() const;
	void erase(int key);
	void erase(const Iterator &p);
	Iterator find(int key);
	Iterator insert(Entry data);
	Iterator begin();
	Iterator end();

protected:
	BinaryTree::Position root() const;
	BinaryTree::Position finder(int key,BinaryTree::Position &data);
	BinaryTree::Position inserter(Entry data);
	BinaryTree::Position eraser(BinaryTree::Position data);
	BinaryTree::Position restructure(BinaryTree::Position x);
	void newRoot(BinaryTree::Position x);
///////////////////////////////////
//		 Iterator SubClass	    //
/////////////////////////////////

public:
	class Iterator {
	private:
		BinaryTree::Position data;
	public:
		Iterator(const BinaryTree::Position input)
		{
			data = input;
		}
		const Entry operator*()
		{
			return *data;
		}
		bool operator==(const Iterator&p)
		{
			return data == p.data;
		}
		bool operator!=(const Iterator&p)
		{
			return data != p.data;
		}
		Iterator& operator++()						// use inorder.
		{
			BinaryTree::Position w = data.right();
			if (!w.isExternal())
			{
				do
				{
					data = w;
					w = w.left();
				} while (!w.isExternal());
			}
			else
			{
				w = data.parent();
				while (data == w.right())
				{
					data = w;
					w = w.parent();
				}
				data = w;
			}
			return *this;
		}
		friend class SearchTree;
	};
};
#endif // !_SEARCH_TREE_H_
