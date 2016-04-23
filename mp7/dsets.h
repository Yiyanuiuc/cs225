/* Your code here! */

#include <vector>

using namespace std;

class DisjointSets {

public:

	/** 
	 * Creates n unconnected root nodes at the end of the vector. 
	 * Parameters num The number of nodes to create
	 */
	void addelements (int num);

	/** 
	 * This function should compress paths and works as described in lecture. 
	 * Returns the index of the root of the up-tree in which the parameter element resides.
	*/
	int find (int elem);

	/** 
	 * This function should be implemented as union-by-size. 
	 * Parameters 
	 * a Index of the first element to union
	 * b Index of the second element to union
	 */
	void setunion (int a, int b);
 	
private:

	/** 
	 * a vector storing indices
	 */
	vector<int> elems;
};