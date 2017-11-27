#include "AVLTree.h"

/*
	Starting by defining the utilities
*/

int AVLTree::height(const TPos& pos) const
{
	if (pos.isExternal()) // If the node is equal to null, then return 0 because you are at the end.
		return 0;
    else
        return pos.getHeight(); // Else will return the node's current height
}

// Will simply set h equal to the height of the node (calculated in the height() function above) then it will set the position's height to that value
void AVLTree::setHeight(TPos pos)
{
    int heightL = height(pos.left()); // Get the left node's height
    int heightR = height(pos.right()); // Get the right node's height
    pos.setHeight(1 + std::max(heightL,heightR)); // set the position as the max of the two (recursively)
}



// Will call the constructor of SearchTree since, there is no new data type (compared to the BST), but rather just functions in the AVLTree class
AVLTree::AVLTree() : SearchTree() {};
