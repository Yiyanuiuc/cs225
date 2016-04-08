#include "binarytree.h"

void BinaryTree::makeNeighbors() {
    /* Your code here! */
	if (root==NULL) return;
	// else
	// make Queue
	std::queue<Node*> Q1;
	std::queue<Node*> Q2;
	Q1.push(root);
	while (!Q1.empty()){
		Node* temp = Q1.front();
		Q1.pop();
		if (temp->left!=NULL) Q1.push(temp->left);
		if (temp->right!=NULL) Q1.push(temp->right);
		Q2.push(temp);
	}
	// everything in q2 is level order
	while (!Q2.empty()) {
		Node * temp = Q2.front();
		Q2.pop();
		if (!Q2.empty()) temp->neighbor = Q2.front();
		else temp->neighbor = NULL;
	}

    return;
}


