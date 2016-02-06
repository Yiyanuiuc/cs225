#include "scene.h"

#include <iostream>

using namespace std;

// Constructor & Destructor 

Scene::Scene (int max) { 

	this->collection = new Image*[max];
	this->length = max;
	this->xCoord = new int[max];
	this->yCoord = new int[max];

	// Initialize
	for (int n=0; n < this->length; n++) { 
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

	if (this != &source) {
		clear();
		copy(source);
	}
	return *this;
}

void Scene::changemaxlayers (int newmax) { 

	if (this->length > newmax) cout << "invalid newmax" << endl;

	else {

		Image** newCollection = new Image*[newmax];
		int* newXCoord = new int[newmax];
		int* newYCoord = new int[newmax];

		// [modified the whole for loop]
		for (int n=0; n<newmax; n++) {
			if (n<length && collection[n]!=NULL) {
				// delete "new"
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

		length = newmax; // [Change length at the end]

		// clear(); 
		// Big change here
		delete [] collection;
		delete [] xCoord;
		delete [] yCoord;
		collection = newCollection;
		xCoord = newXCoord;
		yCoord = newYCoord;
	}
}

void Scene::addpicture (const char *FileName, int index, int x, int y) { 

	if (index<0 || index>=length) cout << "index out of bounds" << endl; // [Invalid]

	else {
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

	if (index<0 || index>=length || newindex<0 || newindex>=length) 
		cout << "invalid index" << endl;
	else if (index==newindex) return;

	else {
		if (collection[newindex]!=NULL) {
			delete collection[newindex];
			collection[newindex] = NULL;
		}
		if (collection[index]==NULL) {
			xCoord[newindex] = 0;
			yCoord[newindex] = 0;	
			return;		
		}
		collection[newindex] = collection[index];
		xCoord[newindex] = xCoord[index];
		yCoord[newindex] = yCoord[index];
		collection[index] = NULL;
		xCoord[index] = 0;
		yCoord[index] = 0;
	}
	
}

void Scene::translate (int index, int xcoord, int ycoord) { 

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

	if (index<0 || index>=length || collection[index]==NULL) {
		cout << "invalid index" << endl;
		return NULL;
	}

	else {
		return collection[index];
	}
}

Image Scene::drawscene () const { 

	size_t newW = 1;
	size_t newH = 1;
	for (int n=0; n<length; n++) {
		//cout<<collection[n]<<endl;
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
					*(result(xCoord[n]+i, yCoord[n]+j)) = *((*collection[n])(i,j)); // [change]
				}
			}
		}
	}

	return result;
}
