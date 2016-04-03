/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */

#include "quadtree.h"
#include <math.h>
#include <iostream>
using namespace std;

/*
================================
Constructors & Big Three
================================
*/

/*
 * default constructor for QuadtreeNode
 */
Quadtree::QuadtreeNode::QuadtreeNode() {
	element = RGBAPixel();
	nwChild = neChild = swChild = seChild = NULL;
}

/*
 * default constructor 
 * The first takes no arguments, and produces an empty Quadtree object, 
 * i.e., one which has no associated QuadtreeNode objects, and in which root is NULL. 
 */
Quadtree::Quadtree () {
	root = NULL;
	resolution = 0;
}

/* 
 * This constructor's purpose is to build a Quadtree representing the upper-left d by d block of the source image.
 * This effectively crops the source image into a d by d square.
 * You may assume that d is a power of two, and that the width and height of source are each at least d.
 * Perhaps, to implement this, you could leverage the functionality of another function you have written in 5.1...
 * @param source The source image to base this Quadtree on
 * @param solution The width and height of the sides of the image to be represented
 */
Quadtree::Quadtree (PNG const & source, int resolution) {
	// initialize
	if ((int)source.width()>=resolution && (int)source.height()>=resolution) {
		root = NULL;
		this->resolution = resolution;
		buildTree (source, resolution);
	}
}	

/*
 * Copy constructor.
 * Simply sets this Quadtree to be a copy of the parameter.
 * @param other The Quadtree to make a copy of
 */
Quadtree::Quadtree (const Quadtree & other) {
	// base case: nothing to copy
	if (other.root==NULL) root = NULL;
	else {
		// initialize root
		root = new QuadtreeNode;
		resolution = other.resolution;
		copy(root,other.root);
	}
} 

/*
 * a helper function for copy
 * assume the input subRoot!=NULL;
 * @param subRoot 
 * @param sourceRoot the QuadtreeNOde * to make a copy of
 */
void Quadtree::copy (QuadtreeNode * & subRoot, QuadtreeNode * sourceRoot) {
	if (sourceRoot==NULL||subRoot==NULL) return;
	subRoot->element = sourceRoot->element;
	// base case: no children, four points are NULL by default;
	if (sourceRoot->nwChild==NULL);
	// recursive case
	else {
		subRoot->nwChild = new QuadtreeNode;
		copy(subRoot->nwChild, sourceRoot->nwChild);
		subRoot->neChild = new QuadtreeNode;
		copy(subRoot->neChild, sourceRoot->neChild);
		subRoot->swChild = new QuadtreeNode;
		copy(subRoot->swChild, sourceRoot->swChild);
		subRoot->seChild = new QuadtreeNode;
		copy(subRoot->seChild, sourceRoot->seChild);
	}
} 

/*
 * Destructor; frees all memory associated with this Quadtree.
 */
Quadtree::~Quadtree () {
	clear(root);
} 

/*
 * clear helper function
 * @param subRoot
 */
void Quadtree::clear(QuadtreeNode * & subRoot) {
	// base case: null node
	if (subRoot==NULL) return;
	// recursive case
	else {
		clear(subRoot->nwChild); 
		clear(subRoot->neChild); 
		clear(subRoot->swChild); 
		clear(subRoot->seChild); 
		delete subRoot;
		subRoot = NULL;
	}
}

/* 
 * Assignment operator
 * Frees memory associated with this Quadtree and sets its contents to be equal to the parameter's.
 * @param other The Quadtree to make a copy of
 * @return A constant reference to the Quadtree value that was copied
 */
const Quadtree & Quadtree::operator = (const Quadtree & other) { 
	// base case: nothing to copy
	if (other.root==NULL) {
		clear(root);
		root = NULL;
	}
	else if (this != &other) { 
		clear(root); 
		root = new QuadtreeNode;
		copy(root, other.root); 
		resolution = other.resolution;
	} 
	return *this; 
}

/*
=======================
Other Functions
=======================
*/

/*
 * Deletes the current contents of this Quadtree object, then turns it into a Quadtree object representing the upper-left d by d block of source.
 * You may assume that d is a power of two, and that the width and height of source are each at least d.
 * @param source The source image to base this Quadtree on
 * @param resolution The width and height of the sides of the image to be represented
 */
void Quadtree::buildTree (PNG const & source, int resolution) {
	// Deletes the current contents of this Quadtree object
	// if ((int)source.width()>=resolution && (int)source.height()>=resolution) {
	// 	if (root!=NULL) 
	// 		clear(root);
	// 	// initialize root
	// 	root = new QuadtreeNode;
	// 	this->resolution = resolution;
	// 	// build tree
	// 	assignPixel (source, root, 0, 0, resolution);
	// }
	if ((int)source.width()>=resolution && (int)source.height()>=resolution) {
		if (root!=NULL) 
			clear(root);
		root = NULL;
		this->resolution = resolution;
		// build tree
		assignPixel (source, root, 0, 0, resolution);
	}
}


/*
 * a helper function for buildTree
 * @param source The source image to base this Quadtree on
 * @param subRoot
 * @param xCoord
 * @param yCoord
 * @param resolution The remaining size
 */
void Quadtree::assignPixel (PNG const & source, QuadtreeNode * & subRoot, int xCoord, int yCoord, int resolution) {
	// // base case
	// if (subRoot==NULL) return;
	// // base case 2: reach the node before leaves
	// else if (resolution<=2) {
	// 	// allocate new memory for children and assign pixels
	// 	subRoot->nwChild = new QuadtreeNode;
	// 	subRoot->nwChild->element = *source(2*xCoord, 2*yCoord);
	// 	subRoot->neChild = new QuadtreeNode;
	// 	subRoot->neChild->element = *source(2*xCoord+1, 2*yCoord);
	// 	subRoot->swChild = new QuadtreeNode;
	// 	subRoot->swChild->element = *source(2*xCoord, 2*yCoord+1);
	// 	subRoot->seChild = new QuadtreeNode;
	// 	subRoot->seChild->element = *source(2*xCoord+1, 2*yCoord+1);
	// }
	// // recursive case: assignPixel to children
	// else {
	// 	subRoot->nwChild = new QuadtreeNode;
	// 	assignPixel (source, subRoot->nwChild, 2*xCoord, 2*yCoord, resolution/2);
	// 	subRoot->neChild = new QuadtreeNode;
	// 	assignPixel (source, subRoot->neChild, 2*xCoord+1, 2*yCoord, resolution/2);
	// 	subRoot->swChild = new QuadtreeNode;
	// 	assignPixel (source, subRoot->swChild, 2*xCoord, 2*yCoord+1, resolution/2);
	// 	subRoot->seChild = new QuadtreeNode;
	// 	assignPixel (source, subRoot->seChild, 2*xCoord+1, 2*yCoord+1, resolution/2);
	// }
	// // assign pixels for subRoot
	// // The element field of each interior node stores the average of its children’s elements.
	// subRoot->element.red = (subRoot->nwChild->element.red 
	// 				+ subRoot->neChild->element.red
	// 				+ subRoot->swChild->element.red
	// 				+ subRoot->seChild->element.red)/4;
	// subRoot->element.green = (subRoot->nwChild->element.green 
	// 				+ subRoot->neChild->element.green
	// 				+ subRoot->swChild->element.green 
	// 				+ subRoot->seChild->element.green)/4;
	// subRoot->element.blue = (subRoot->nwChild->element.blue 
	// 				+ subRoot->neChild->element.blue
	// 				+ subRoot->swChild->element.blue 
	// 				+ subRoot->seChild->element.blue)/4;
	if (subRoot==NULL) subRoot = new QuadtreeNode;
	// base case: reach leaves
	if (resolution<=1) {
		// assign pixels
		subRoot->element = *source(xCoord, yCoord);
	}
	// recursive case: assignPixel to children
	else {
		assignPixel (source, subRoot->nwChild, 2*xCoord, 2*yCoord, resolution/2);
		assignPixel (source, subRoot->neChild, 2*xCoord+1, 2*yCoord, resolution/2);
		assignPixel (source, subRoot->swChild, 2*xCoord, 2*yCoord+1, resolution/2);
		assignPixel (source, subRoot->seChild, 2*xCoord+1, 2*yCoord+1, resolution/2);
		// assign pixels for subRoot
		// The element field of each interior node stores the average of its children’s elements.
		subRoot->element.red = (subRoot->nwChild->element.red 
						+ subRoot->neChild->element.red
						+ subRoot->swChild->element.red
						+ subRoot->seChild->element.red)/4;
		subRoot->element.green = (subRoot->nwChild->element.green 
						+ subRoot->neChild->element.green
						+ subRoot->swChild->element.green 
						+ subRoot->seChild->element.green)/4;
		subRoot->element.blue = (subRoot->nwChild->element.blue 
						+ subRoot->neChild->element.blue
						+ subRoot->swChild->element.blue 
						+ subRoot->seChild->element.blue)/4;
	}
}

/*
 * Gets the RGBAPixel corresponding to the pixel at coordinates (x, y) in the bitmap image which the Quadtree represents.
 * Note that the Quadtree may not contain a node specifically corresponding to this pixel (due, for instance, to pruning - see below). 
 * In this case, getPixel will retrieve the pixel (i.e. the color) of the square region within which the smaller query grid cell would lie. 
 * (That is, it will return the element of the nonexistent leaf's deepest surviving ancestor.) 
 * If the supplied coordinates fall outside of the bounds of the underlying bitmap, or if the current Quadtree is "empty" 
 * (i.e., it was created by the default constructor) 
 * then the returned RGBAPixel should be the one which is created by the default RGBAPixel constructor.
 * @param x	The x coordinate of the pixel to be retrieved
 * @param y	The y coordinate of the pixel to be retrieved
 * @return The pixel at the given (x, y) location
 */
RGBAPixel Quadtree::getPixel (int x, int y) const {
	if (x<0 || x>=resolution || y<0 || y>=resolution) return RGBAPixel();
	else return getPixel (root, x, y, resolution);
}

/* 
 * a helper function to get the pixel 
 * @param subRoot
 * @param xCoord
 * @param yCoord
 * @param resolution The remaining size
 */
RGBAPixel Quadtree::getPixel (QuadtreeNode * subRoot, int xCoord, int yCoord, int resolution) const {
	// // base case
	// if (subRoot==NULL) return RGBAPixel();
	// // base case 2: almost the node before leaves
	// else if (resolution<=2) {
	// 	if (xCoord==0 && yCoord==0) 
	// 		return subRoot->nwChild->element;
	// 	else if (xCoord==1 && yCoord==0) 
	// 		return subRoot->neChild->element;
	// 	else if (xCoord==0 && yCoord==1) 
	// 		return subRoot->swChild->element;
	// 	else if (xCoord==1 && yCoord==1) 
	// 		return subRoot->seChild->element;
	// 	else return RGBAPixel();
	// }
	// // recursive case: resolution>=4
	// else {
	// 	resolution/=2;
	// 	if (subRoot->nwChild==NULL) return subRoot->element;
	// 	if (xCoord<resolution && yCoord<resolution) 
	// 		return getPixel(subRoot->nwChild, xCoord, yCoord, resolution);
	// 	else if (xCoord>=resolution && yCoord<resolution) 
	// 		return getPixel(subRoot->neChild, xCoord-resolution, yCoord, resolution);
	// 	else if (xCoord<resolution && yCoord>=resolution) 
	// 		return getPixel(subRoot->swChild, xCoord, yCoord-resolution, resolution);
	// 	else 
	// 		return getPixel(subRoot->seChild, xCoord-resolution, yCoord-resolution, resolution);
	// }
	// base case
	if (subRoot==NULL) return RGBAPixel();
	// base case 2: leaves
	else if (resolution<=1) {
		if (xCoord==0 && yCoord==0) return subRoot->element;
		else return RGBAPixel();
	}
	// recursive case: resolution>=2
	else {
		resolution/=2;
		if (subRoot->nwChild==NULL) return subRoot->element;
		if (xCoord<resolution && yCoord<resolution) 
			return getPixel(subRoot->nwChild, xCoord, yCoord, resolution);
		else if (xCoord>=resolution && yCoord<resolution) 
			return getPixel(subRoot->neChild, xCoord-resolution, yCoord, resolution);
		else if (xCoord<resolution && yCoord>=resolution) 
			return getPixel(subRoot->swChild, xCoord, yCoord-resolution, resolution);
		else 
			return getPixel(subRoot->seChild, xCoord-resolution, yCoord-resolution, resolution);
	}
}

/*
 * Returns the underlying PNG object represented by the Quadtree.
 * If the current Quadtree is "empty" (i.e., it was created by the default constructor) 
 * then the returned PNG should be the one which is created by the default PNG constructor. 
 * @return The decompressed PNG image this Quadtree represents
 */
PNG Quadtree::decompress() const {
	if (root==NULL) return PNG();
	else {
		// declare a PNG
		PNG img(resolution, resolution);
		// set initialized coordinates to (0,0)
		decompress(img, root, 0, 0, resolution);
		return img;
	}
}

/* 
 * a helper function to get the pixel
 * @param img The reference of image to paint
 * @param subRoot
 * @param xCoord
 * @param yCoord
 * @param resolution The remaining size
 */
void Quadtree::decompress(PNG & img, QuadtreeNode * subRoot, int xCoord, int yCoord, int resolution) const {
	// base case
	if (subRoot==NULL);
	// base case 2. Here resolution>=1, and =1 shen nwChild==NULL
	else if (subRoot->nwChild==NULL || resolution<=1) {
		for (int i=0; i<resolution; i++)
			for (int j=0; j<resolution; j++) 
				*img(xCoord*resolution+i,yCoord*resolution+j) = subRoot->element;
	}
	// recursive case: decompress children
	else {
		decompress(img, subRoot->nwChild, 2*xCoord, 2*yCoord, resolution/2);
		decompress(img, subRoot->neChild, 2*xCoord+1, 2*yCoord, resolution/2);
		decompress(img, subRoot->swChild, 2*xCoord, 2*yCoord+1, resolution/2);
		decompress(img, subRoot->seChild, 2*xCoord+1, 2*yCoord+1, resolution/2);
	}
}

/*
=======================
Further Functions in 5.2
=======================
*/

/**
 * Rotates the Quadtree object's underlying image clockwise by 90 degrees.
 */
void Quadtree::clockwiseRotate () {
	clockwiseRotate(root);
}	

/**
 * helper function for clockwiseRotate
 * @param subRoot
 */
void Quadtree::clockwiseRotate (QuadtreeNode * subRoot) {
	if (subRoot==NULL || subRoot->nwChild==NULL) return;
	// swap children
	QuadtreeNode * tempNW = subRoot->nwChild;
	QuadtreeNode * tempNE = subRoot->neChild;
	QuadtreeNode * tempSW = subRoot->swChild;
	QuadtreeNode * tempSE = subRoot->seChild;
	subRoot->nwChild = tempSW;
	subRoot->neChild = tempNW;
	subRoot->swChild = tempSE;
	subRoot->seChild = tempNE;
	tempNW = tempNE = tempSW = tempSE = NULL;
	clockwiseRotate (subRoot->nwChild);
	clockwiseRotate (subRoot->neChild);
	clockwiseRotate (subRoot->swChild);
	clockwiseRotate (subRoot->seChild);
}

/**
 * Compresses the image this Quadtree represents.
 * @param tolerance The integer tolerance between two nodes that determines whether the subtree can be pruned.
 */
void Quadtree::prune (int tolerance) {
	prune(root, tolerance);
}	

/**
 * helper function for prune
 * @param subRoot
 * @param temp
 * @param tolerance The integer tolerance between two nodes that determines whether the subtree can be pruned.
 * @return bool whether the node should be pruned
 */
bool Quadtree::toBePruned (QuadtreeNode * & subRoot, QuadtreeNode * & temp, int tolerance) const {
	if (subRoot==NULL||temp==NULL) return false;
	// reach leaves
	else if (temp->nwChild==NULL) {
		int diff = pow(subRoot->element.red - temp->element.red, 2) 
			+ pow(subRoot->element.green - temp->element.green, 2) 
			+ pow(subRoot->element.blue - temp->element.blue, 2);
		return diff<=tolerance;
	}
	// if temp has children
	else return toBePruned(subRoot,temp->nwChild,tolerance)
		&& toBePruned(subRoot,temp->neChild,tolerance)
		&& toBePruned(subRoot,temp->swChild,tolerance)
		&& toBePruned(subRoot,temp->seChild,tolerance);
}
 
/**
 * helper function for prune
 * @param subRoot
 * @param tolerance The integer tolerance between two nodes that determines whether the subtree can be pruned.
 */
void Quadtree::prune (QuadtreeNode * & subRoot, int tolerance) {
	if (subRoot==NULL || subRoot->nwChild==NULL) return;
	// if it has children
	if (toBePruned(subRoot, subRoot, tolerance)) {
		clear(subRoot->nwChild);
		clear(subRoot->neChild);
		clear(subRoot->swChild);
		clear(subRoot->seChild);
		subRoot->nwChild = subRoot->neChild = subRoot->swChild = subRoot->seChild = NULL;
	}
	else {
		prune (subRoot->nwChild, tolerance);
		prune (subRoot->neChild, tolerance);
		prune (subRoot->swChild, tolerance);
		prune (subRoot->seChild, tolerance);
	}
}

/**
 * This function is similar to prune; however, it does not actually prune the Quadtree.
 * Rather, it returns a count of the total number of leaves the Quadtree would have if it were pruned as in the prune function.
 * @param tolerance The integer tolerance between two nodes that determines whether the subtree can be pruned.
 * @return How many leaves this Quadtree would have if it were pruned with the given tolerance.
 */
int Quadtree::pruneSize (int tolerance) const {
	return pruneSize(root, tolerance);
}

/**
 * helper function for pruneSIze
 * @param subRoot
 * @param tolerance The integer tolerance between two nodes that determines whether the subtree can be pruned.
 * @return How many leaves this Quadtree would have if it were pruned with the given tolerance below the subRoot.
 */
int Quadtree::pruneSize (QuadtreeNode * subRoot, int tolerance) const {
	if (subRoot==NULL) return 0;
	if (subRoot->nwChild==NULL) return 1;
	// if it has children
	if (toBePruned(subRoot, subRoot, tolerance)) return 1;
	else 
		return pruneSize(subRoot->nwChild,tolerance) 
			+ pruneSize(subRoot->neChild,tolerance)
			+ pruneSize(subRoot->swChild,tolerance) 
			+ pruneSize(subRoot->seChild,tolerance);
}

/**
 * Calculates and returns the minimum tolerance necessary to guarantee that upon pruning the tree, no more than numLeaves leaves remain in the Quadtree.
 * @param numLeaves The number of leaves you want to remain in the tree after prune is called.
 * @returns The minimum tolerance needed to guarantee that there are no more than numLeaves remaining in the tree.
 */
int Quadtree::idealPrune (int numLeaves) const {
	return idealPrune(0, 3*pow(255,2), numLeaves);
}

/**
 * helper function for idealPrune
 * @param start
 * @param end 
 * @param numLeaves The number of leaves you want to remain in the tree after prune is called.
 * @returns The minimum tolerance needed to guarantee that there are no more than numLeaves remaining in the tree.
 */
int Quadtree::idealPrune (int startP, int endP, int numLeaves) const{
	if (startP>=endP-1) {
		if (pruneSize(startP)>numLeaves) 
			return idealPrune (startP+1, endP+1, numLeaves);
		else return startP;
 	}
	else {
		int midP = (startP + endP)/2;
		if (pruneSize(midP)>numLeaves) return idealPrune(midP, endP, numLeaves);
		else return idealPrune(startP, midP, numLeaves); 
	}
}
