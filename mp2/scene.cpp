#include "scene.h"

#include <iostream>

using namespace std;

// Constructor & Destructor 

Scene::Scene (int max) { 
	// "You may assume that max > 0."

	// "dynamically allocating an array of Image pointers of size "max""
	this->collection = new Image*[max];
	// "storing "max" as a member variable"
	this->length = max;
	// "creating storage for the coordinates"
	this->xCoord = new int[max];
	this->yCoord = new int[max];

	// Initialize all variables
	for (int n=0; n < this->length; n++) { 
		// "initializing all of them to NULL"
		this->collection[n] = NULL;
		this->xCoord[n] = 0;
		this->yCoord[n] = 0;
	}
}

void Scene::clear() {

	for (int n=0; n<length; n++) {
		delete collection[n];
		collection[n] = NULL;
	}

	delete [] collection;
	delete [] xCoord;
	delete [] yCoord;
	collection = NULL;
	xCoord = NULL;
	yCoord = NULL;
}

Scene::~Scene() {
	// "Frees all space that was dynamically allocated by this Scene"
	clear();
};

void Scene::copy(const Scene &source) {

	collection = new Image*[source.length];
	length = source.length;
	xCoord = new int[source.length];
	yCoord = new int[source.length];

	for (int n=0; n<source.length; n++) {
		if (source.collection[n] != NULL) {
			collection[n] = (Image*) new PNG(*source.collection[n]);
			xCoord[n] = source.xCoord[n];
			yCoord[n] = source.yCoord[n];
		}
		else { // if source.collection[n] == NULL
			collection[n] = NULL;
			xCoord[n] = 0;
			yCoord[n] = 0;
		}		
	}
}

Scene::Scene (const Scene &source) {
	copy(source);
}

// Member Function

const Scene & Scene::operator = (const Scene & source){

	// "checks for self assignment"
	if (this != &source) {
		// "deletes everything this Scene has allocated, "
		clear();
		// "makes this Scene an independent copy of the source"
		copy(source);
	}
	// "returns a reference to the current instance"
	return *this;
}

void Scene::changemaxlayers (int newmax) { 
	// "You may assume newmax is greater than zero."

	// "this cannot be done because there are non-null pointers outside the range [0, newmax-1]
	if (this->length > newmax) {
		for (int n=newmax; n<length; n++) {
			if (collection[n]!=NULL) {
				cout << "invalid newmax" << endl;
				return;
			}
		}
	}

	// "A new array of Image pointers of size newmax will be allocated"
	Image** newCollection = new Image*[newmax];
	int* newXCoord = new int[newmax];
	int* newYCoord = new int[newmax];

	for (int n=0; n<newmax; n++) {
		if (n<length && collection[n]!=NULL) {
			// "the non-null pointers in the old array will be copied over" 
			newCollection[n] = collection[n]; 
			newXCoord[n] = xCoord[n];
			newYCoord[n] = yCoord[n];
		}
		else {
			newCollection[n] = NULL;
			newXCoord[n] = 0;
			newYCoord[n] = 0;
		}
	}

	length = newmax; // * Change length at the end

	// * Delete clear(); 
	delete [] collection;
	delete [] xCoord;
	delete [] yCoord;
	collection = newCollection;
	xCoord = newXCoord;
	yCoord = newYCoord;
	
}

void Scene::addpicture (const char *FileName, int index, int x, int y) { 
	// "You may assume that x and y are integers in the range [0, MAXINT]."

	// * Invalid input
	// "If the index is not within the range"
	if (index<0 || index>=length) cout << "index out of bounds" << endl; 

	else {

		// * 
		// "If there is already an Image in cell location index it should be replaced by the new Image"
		if (collection[index] != NULL) {
			delete collection[index];
			collection[index] = NULL;
		}

		Image* newImage = new Image();
		newImage->readFromFile(FileName);

		collection[index] = newImage;
		xCoord[index] = x;
		yCoord[index] = y;
	}
}

void Scene::changelayer (int index, int newindex) { 

	// "If either index is invalid, do nothing and use the following code to print an error message"
	if (index<0 || index>=length || newindex<0 || newindex>=length) 
		cout << "invalid index" << endl;

	// "If the new index is the same as the old index, do nothing and return."
	else if (index==newindex) return;

	else { // * have to move

		// "If the destination is already occupied, delete the image there."
		if (collection[newindex]!=NULL) {
			delete collection[newindex];
			collection[newindex] = NULL;
		}

		// * newindex has been set to NULL
		// * If index==NULL unchanged. change newX newY
		// "do not prevent the user from requesting that a NULL Image pointer be moved to an occupied spot."
		if (collection[index]==NULL) {
			xCoord[newindex] = 0;
			yCoord[newindex] = 0;	
			return;		
		}
		// "Rather, just move the pointer."
		collection[newindex] = collection[index];
		xCoord[newindex] = xCoord[index];
		yCoord[newindex] = yCoord[index];
		// "The source index should be marked vacant by making it value NULL."
		collection[index] = NULL;
		xCoord[index] = 0;
		yCoord[index] = 0;
	}
	
}

void Scene::translate (int index, int xcoord, int ycoord) { 

	// "If the index is invalid or if it contains a NULL pointer, do nothing "
	if (index<0 || index>=length || collection[index]==NULL) 
		cout << "invalid index" << endl;
	
	else {
		xCoord[index] = xcoord;
		yCoord[index] = ycoord;
	}
}

void Scene::deletepicture (int index) { 

	if (index<0 || index>=length || collection[index]==NULL) 
		cout << "invalid index" << endl;

	else {
		delete collection[index];
		collection[index] = NULL;
	}
}

Image * Scene::getpicture (int index) const { 

	// "If the index is invalid, return NULL"
	if (index<0 || index>=length || collection[index]==NULL) {
		cout << "invalid index" << endl;
		return NULL;
	}

	else {
		return collection[index];
	}
}

Image Scene::drawscene () const { 

	// "determine the minimum width and height necessary to ensure"
	size_t newW = 1;
	size_t newH = 1;
	for (int n=0; n<length; n++) {
		if (collection[n] != NULL) {
			if (newW < xCoord[n] + collection[n]->width()) 
				newW = xCoord[n] + collection[n]->width();
			if (newH < yCoord[n] + collection[n]->height()) 
				newH = yCoord[n] + collection[n]->height();
		}
	}

	Image result = Image();
	result.resize(newW, newH);

	for (int n=0; n<length; n++) {
		if (collection[n]!=NULL) {
			for (size_t i=0; i<collection[n]->width(); i++) {
				for (size_t j=0; j<collection[n]->height(); j++) {
					*(result(xCoord[n]+i, yCoord[n]+j)) = *((*collection[n])(i,j)); // * delete operator
				}
			}
		}
	}

	return result;
}
