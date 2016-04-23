/* Your code here! */

#include <vector>
#include "dsets.h"

using namespace std;

/** 
 * Creates n unconnected root nodes at the end of the vector. 
 * Parameters num The number of nodes to create
 */
void DisjointSets::addelements (int num) {
	// set all indices to -1
	for (size_t i=0; i<(size_t)num; i++) {
		elems.push_back(-1);
	}
}

/** 
 * This function should compress paths and works as described in lecture. 
 * Returns the index of the root of the up-tree in which the parameter element resides.
*/
int DisjointSets::find (int elem) {
	if (elem<0 || elem>=(int)elems.size()) return -1;
	// base case: reach root
	else if (elems[elem]<0) return elem;
	// recursive case: find & path compression
	else return elems[elem] = find(elems[elem]);
}

/** 
 * This function should be implemented as union-by-size. 
 * Parameters 
 * a Index of the first element to union
 * b Index of the second element to union
 */
void DisjointSets::setunion (int a, int b) {
	int root1 = find(a);
	int root2 = find(b);
	// if they are already in a union, do nothing
	if (root1==root2) return;
	//  count the sizes
	int sizeA = 0;
	int sizeB = 0;
	for (size_t i=0; i<elems.size(); i++) {
		if (find(i)==root1) sizeA++;
		else if (find(i)==root2) sizeB++;
	}
	if (sizeA<sizeB) elems[root1] = root2;
	else elems[root2] = root1;
}