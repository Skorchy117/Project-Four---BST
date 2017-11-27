#include "AVLTree.h"

/*
	Starting by defining the utilities
*/

// NOT DONE
int AVLTree::height(const TPos& pos) const
{
	if (pos.isExternal()) // If the node is equal to null, then return 0 because you are at the end.
		return 0;
		
}

// Will simply set h equal to the height of the node (calculated in the height() function above) then it will set the position's height to that value
void AVLTree::setHeight(TPos pos)
{
	int h = height(pos);
	pos.setHeight(h);
}


// Will call the constructor of SearchTree since, there is no new data type (compared to the BST), but rather just functions in the AVLTree class
AVLTree::AVLTree() : SearchTree() {};

