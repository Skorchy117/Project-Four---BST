#include "BinaryTree.h"
BinaryTree::BinaryTree()
{
	_root = nullptr;
	counter = 0;
}

int BinaryTree::size() const
{
	return counter;
}

BinaryTree::Position BinaryTree::root() const
{
	return Position(_root);
}

BinaryTree::PositionList BinaryTree::positions() const
{
	PositionList pl;
	inorder(_root, pl);
	return PositionList(pl);
}

void BinaryTree::addRoot()
{
	_root = new Node;
	counter++;
}
void BinaryTree::setRoot(const Position & p)
{
	Node *temp = p.curNode;
	_root = temp;
}
BinaryTree::Position BinaryTree::removeAboveExternal(const Position & p)
{
	Node *temp = p.curNode;
	Node *par = temp->parent;
	Node *sibling;
	if (temp == par->left)
	{
		sibling = par->right;
	}
	else sibling = par->left;
	if (par == _root)
	{
		_root = sibling;
		sibling->parent = NULL;
	}
	else
	{
		Node *grandparent = par->parent;
		if (par == grandparent->left)
		{
			grandparent->left = sibling;
		}
		else grandparent->right = sibling;
		sibling->parent = grandparent;
	}
	delete temp;
	delete par;
	counter -= 2;
	return Position(sibling);
}

void BinaryTree::expandExternal(const Position &p)
{
	Node *curNode = p.curNode;
	curNode->left = new Node;
	curNode->right = new Node;
	curNode->left->parent = curNode;
	curNode->right->parent = curNode;
}

void BinaryTree::inorder(Node *curNode, PositionList &pl) const
{
	if (curNode->left != nullptr)
	{
		inorder(curNode->left, pl);
	}
	pl.push_back(Position(curNode));
	if (curNode->right != nullptr)
	{
		inorder(curNode->right, pl);
	}
}
