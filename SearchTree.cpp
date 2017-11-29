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
	BinaryTree::Position value = finder(key, root());		// use the finder function to find our position
	if (!value.isExternal())								// if our value function is internal
	{
		return SearchTree::Iterator(value);					// return the iterator
	}
	else return NULL;										// else return NULL.
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

BinaryTree::Position SearchTree::restructure(BinaryTree::Position data)
{
	BinaryTree::Position parent = data.parent();
	BinaryTree::Position gParent = parent.parent();
	if ((data == parent.right()) == (parent == gParent.right()))
	{
		rotate(parent);
		return parent;
	}
	else
	{
		rotate(data);
		rotate(data);
		return data;
	}
	
}

void SearchTree::rotate(BinaryTree::Position p)
{
	BinaryTree::Position x = p;
	BinaryTree::Position y = x.parent();
	BinaryTree::Position z = y.parent();
	if (z == NULL)
	{
		root().addElement(*x);
		x.parent() = NULL;
	}
	else
	{
		relink(z, x, y == z.left());
	}
	if (x == y.right())
	{
		relink(y,x.right(),true);
		relink(x,y,false);
	}
	else
	{
		relink(y,x.left(),false);
		relink(x,y,true);
	}
}

void SearchTree::relink(BinaryTree::Position parent, BinaryTree::Position child, bool makeLeftChild)
{
	child.parent() = parent;
	if (makeLeftChild)
	{
		parent.left() = child;
	}
	else
		parent.right() = child;
}
