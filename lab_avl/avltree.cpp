#include <algorithm>

/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node * & t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    if (t==NULL) return;
    Node * newRoot = t->right;
    t->right = newRoot->left;
    newRoot->left = t;
    t = newRoot;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    if (t==NULL) return;
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node * & t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    if (t==NULL) return;
    Node * newRoot = t->left;
    t->left = newRoot->right;
    newRoot->right = t;
    t = newRoot;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    if (t==NULL) return;
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node * & subtree)
{
    // your code here
    if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left)==2) {
        if (subtree->right==NULL);
        // if == 1
        else if (heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left)==1) 
            rotateLeft (subtree);
        // if == -1
        else 
            rotateRightLeft (subtree);
    }
    else if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left)==-2) {
        if (subtree->left==NULL);
        // if == -1
        else if (heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left)==-1) 
            rotateRight (subtree);
        // if == 1
        else 
            rotateLeftRight (subtree);
    }
    resetHeight (subtree);
}

template <class K, class V>
void AVLTree<K, V>::resetHeight(Node * & subtree) {
    if (subtree==NULL);
    else if (subtree->left==NULL && subtree->right==NULL)
        subtree->height = 0;
    else if (subtree->left!=NULL && subtree->right==NULL) {
        resetHeight(subtree->left);
        subtree->height = 1 + subtree->left->height;
    }
    else if (subtree->left==NULL && subtree->right!=NULL) {
        resetHeight(subtree->right);
        subtree->height = 1 + subtree->right->height;
    }
    else {
        resetHeight(subtree->left);
        resetHeight(subtree->right);
        subtree->height = 1 + max(subtree->left->height, subtree->right->height);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree==NULL) {
        subtree = new Node(key,value);
        subtree->height = 0;
    }
    else if (subtree->key==key);
    else {
        if (subtree->key > key) 
            insert(subtree->left, key, value);
        else
            insert(subtree->right, key, value);
        rebalance (subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    // base case
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } 
    else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } 
    // if key==subtree->key
    else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } 
        else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            // iop does exist
            Node * & iop = rightMostNode (subtree->left);
            swap (iop, subtree);
            remove (subtree->left, key);
        } 
        else {
            /* one-child remove */
            // your code here
            Node * temp = subtree;
            if (subtree->left!=NULL) 
                subtree = subtree->left;
            else 
                subtree = subtree->right;
            delete temp;
            temp = NULL;
        }
        // your code here
        rebalance (subtree);
    }
}

template <class K, class V>
typename AVLTree<K, V>::Node * & AVLTree<K, V>::rightMostNode(Node * & subtree) {
    if (subtree==NULL || subtree->right==NULL) 
        return subtree;
    else 
        return rightMostNode(subtree->right);
}