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

// Will simply set h equal to the highest height of the left or right node
void AVLTree::setHeight(TPos pos)
{
    int heightL = height(pos.left()); // Get the left node's height
    int heightR = height(pos.right()); // Get the right node's height
    pos.setHeight(1 + std::max(heightL,heightR)); // set the position as the max of the two
}

// Returns true if the position's height is balanced
bool AVLTree::isBalanced(const TPos& pos) const
{
    int bal = height(pos.left()) - height(pos.right());
    if ((bal >= 0) && (bal <= 1))
        return true;
    else
        return false;
}

TPos AVLTree::tallGrandchild(const TPos& pos) const
{
    TPos posL = pos.left();
    TPos posR = pos.right();
    if (height(posL) >= height(posR))
    {
        if (
    }
}


template <typename E>                    // get tallest grandchild
typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const
{
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))            // left child taller
        if (height(zl.left()) >= height(zl.right()))
            return zl.left();
        else
            return zl.right();
        else                         // right child taller
            if (height(zr.right()) >= height(zr.left()))
                return zr.right();
            else
                return zr.left();
}

// Will call the constructor of SearchTree since, there is no new data type (compared to the BST), but rather just functions in the AVLTree class
AVLTree::AVLTree() : SearchTree() {};
