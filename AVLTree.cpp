#include "AVLTree.h"

/******************************************/
//	Starting by defining the utilities    //
/*******************************************/

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
    pos.setHeight(1 + max(heightL,heightR)); // set the position as the max of the two
}

// Returns true if the position's height is balanced
bool AVLTree::isBalanced(const TPos& pos) const
{
	TPos left = pos.left();
	TPos right = pos.right();
    int bal = height(left) - height(right); // Checks if the balance is over 1
	return ((bal >= -1) && (bal <= 1)); // If it is over 1 or less than 1
  
}

// Returns the tallest grandchild
AVLTree::TPos AVLTree::tallGrandchild(const TPos& pos) const
{
    TPos posL = pos.left();
    TPos posR = pos.right();
    if (height(posL) >= height(posR)) // If the height of the left position is greater than the height of the right's
    {
        if (height(posL.left()) >= height(posL.right())) // Check the height of the left position's children, if the left position's left child is greater than its right return the left that position
            return posL.left();
        else
            return posL.right(); // Since the right child's height is greater, return the right
    }
    else // The height of the right position is greater than the height of the left's
    {
        if (height(posR.right()) >= height(posR.left())) // If the right position's height of the right child is greater than the left child return the right
            return posR.right();
        else // Return the left one since its greater
            return posR.left();
    }
}

// Rebalances the tree
void AVLTree::rebalance(const TPos& pos) // Will rebalance whatever position passed
{
    TPos temp = pos; // Assigns a temporary position to the passed position
	TPos whatRoot = root();
    while (temp != root()) // While temp is not the root
    {
		whatRoot = root();
        temp = temp.parent(); // Assign temp to be its parent
        setHeight(temp); // set the height of the parent
        if (!isBalanced(temp)) // If the node is unbalanced will balance it
        {
            TPos otherTemp = tallGrandchild(temp); // Sets another position as the tallest grandchild
            temp = restructure(otherTemp); // Restructures that grandchild then assigns the rebalanced section to temp
            setHeight(temp.left()); // Corrects the height
            setHeight(temp.right());
            setHeight(temp); // Sets temp's height
        }
    }
}

/************
 Starting by defining the public
 ************/

// Will call the constructor of SearchTree since, there is no new data type (compared to the BST), but rather just functions in the AVLTree class
AVLTree::AVLTree() : SearchTree() {};

// Will insert an entry, then return an iterator at that position
AVLTree::Iterator AVLTree::insert(Entry& entry)
{
    TPos temp = inserter(entry); // Inserts the entry then returns that position
    setHeight(temp); // Sets the height at that position so it can be used before rebalancing
    rebalance(temp);
    return Iterator(temp);
}

// Erases a position in the AVLTree (parameter is a key which should be a county_state_code
void AVLTree::erase(const county_state_code& key)// Erase a key
{
    TPos temp = finder(key, root());
	if (Iterator(temp) == end()) // If the item is a external
	{
	}
    TPos otherTemp = eraser(temp); // Erases the temp and returns the position of the position for rebalance
    rebalance(otherTemp);
}