/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <vector>
#include <iostream>
using namespace std;
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    // your code here
    // Call recursive helper function on the root
    mirror(root);
}

/**
 * Private helper function for the public mirror function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::mirror(Node* subRoot) 
{
    // Base case - null node
    if (subRoot == NULL)
        return;
    // Swap
    Node * temp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = temp;

    mirror(subRoot->left);
    mirror(subRoot->right);
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
    // Call recursive helper function on the root
    return isOrdered(root);
}

/**
 * Private helper function for the public isOrdered function.
 * @param subRoot
 * @return True if an in-order traversal of the subtree would produce a
 *  nondecreasing list output values, and false otherwise. 
 */
template <typename T>
bool BinaryTree<T>::isOrdered(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot==NULL || (subRoot->left==NULL && subRoot->right==NULL))
        return true;

    // left!=NULL
    else if (subRoot->left!=NULL && subRoot->right==NULL) {
        if (subRoot->elem < findRightMost(subRoot->left)->elem) return false;
        else return isOrdered(subRoot->left);
    }
    // right!=NULL
    else if (subRoot->left==NULL && subRoot->right!=NULL) {
        if (findLeftMost(subRoot->right)->elem < subRoot->elem) return false;
        else return isOrdered(subRoot->right);
    }
    // subRoot!=NULL && left!=NULL && right!=NULL
    else {
        if (subRoot->elem < findRightMost(subRoot->left)->elem 
            || findLeftMost(subRoot->right)->elem < subRoot->elem) return false;
        else return isOrdered(subRoot->left) && isOrdered(subRoot->right);
    }
}

/**
 * Private helper function for the public isOrdered function.
 * @param subRoot
 * @return the right most Node
 */
template <typename T>
typename BinaryTree<T>::Node * BinaryTree<T>::findRightMost(Node* subRoot) const
{
    // Base case
    if (subRoot == NULL || subRoot->right == NULL) return subRoot;
    else return findRightMost(subRoot->right);
}

/**
 * Private helper function for the public isOrdered function.
 * @param subRoot
 * @return the left most Node
 */
template <typename T>
typename BinaryTree<T>::Node * BinaryTree<T>::findLeftMost(Node* subRoot) const
{
    // Base case
    if (subRoot == NULL || subRoot->left == NULL) return subRoot;
    else return findLeftMost(subRoot->left);
}

/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards,
 * ending at a leaf node. Paths ending in a left node should be printed before
 * paths ending in a node further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
    // your code here
    // Call recursive helper function on the root
    vector<T> v = {};
    // use rightMost to track whether the path is the last one. 
    // if so, we don't need "cout << endl"
    // Node * rightMostPathLeaf = findRightMostPathLeaf(root);
    printPaths(root, v);
}

/**
 * Private helper function for the public printPaths function.
 * @param subRoot
 * @param v a vector storing vectices in a path
 */
template <typename T>
void BinaryTree<T>::printPaths(const Node* subRoot, vector<T> v) const
{
    // Base case - null node
    if (subRoot==NULL)
        cout << "Path:" << endl;

    else {
        // add to the vector
        v.push_back(subRoot->elem);

        // leaf node, print the vector
        if (subRoot->left==NULL && subRoot->right==NULL) {
            cout << "Path:";
            for (typename vector<T>::iterator it = v.begin() ; it != v.end(); ++it) 
                cout << " " << *it;
            cout << endl;
        }

        else if (subRoot->left!=NULL && subRoot->right==NULL) {
            printPaths(subRoot->left, v);
        }

        else if (subRoot->left==NULL && subRoot->right!=NULL) {
            printPaths(subRoot->right, v);
        }

        else {
            printPaths(subRoot->left, v);
            printPaths(subRoot->right, v);
        }
    }
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    // Call recursive helper function on the root
    return sumDistances(root,0);
}

/**
 * Private helper function for the public sumDistances function.
 * @param subRoot 
 * @param accumulated The current distance
 * @return The sum of the distances of all nodes to the subroot
 */
template <typename T>
int BinaryTree<T>::sumDistances(const Node* subRoot, int accumulated) const
{
    // Base case - null node
    if (subRoot==NULL) 
        return accumulated;

    // leaf node
    if (subRoot->left==NULL && subRoot->right==NULL) 
        return accumulated;
    
    else if (subRoot->left!=NULL && subRoot->right==NULL) 
        return accumulated + sumDistances(subRoot->left, accumulated+1);
    else if (subRoot->left==NULL && subRoot->right!=NULL) 
        return accumulated + sumDistances(subRoot->right, accumulated+1);
    else 
        return accumulated + sumDistances(subRoot->left, accumulated+1)
                           + sumDistances(subRoot->right, accumulated+1);
}