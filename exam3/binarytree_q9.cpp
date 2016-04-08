#include "binarytree.h"

bool BinaryTree::isFullBinaryTree() const {
    /* Your code here! */
    return isFullBinaryTree(root);
}


bool BinaryTree::isFullBinaryTree (BinaryTree::Node * subRoot) const {
	if (subRoot==NULL) 
		return true;
	else if (subRoot->left==NULL && subRoot->right==NULL) 
		return true;
	else if (subRoot->left!=NULL && subRoot->right!=NULL)
		return isFullBinaryTree(subRoot->left) && isFullBinaryTree(subRoot->right);
	else 
		return false;
}
