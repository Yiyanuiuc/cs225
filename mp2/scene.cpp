#include "scene.h"

#include <iostream>
using namespace std;

// Constructor & Destructor 

Scene::Scene (int max) { // done ?

	this->collection = new Image*[max];
	this->length = max;
	this->xCoord = new int[max];
	this->yCoord = new int[max];

	for (int n=0; n < this->length - 1; n++) {
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
		else {
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

		length = newmax;
		Image** newCollection = new Image*[newmax];
		int* newXCoord = new int[newmax];
		int* newYCoord = new int[newmax];

		for (int n=0; n<length; n++) {
			newCollection[n] = (Image*) new PNG(*collection[n]);
			newXCoord[n] = xCoord[n];
			newYCoord[n] = yCoord[n];
		}

		for (int n=length; n<newmax-1; n++) {
			newCollection[n] = NULL;
			newXCoord[n] = 0;
			newYCoord[n] = 0;
		}

		clear();

		collection = newCollection;
		xCoord = newXCoord;
		yCoord = newYCoord;

	}
}

void Scene::addpicture (const char *FileName, int index, int x, int y) { // done ?

	if (index>=length) cout << "index out of bounds" << endl;

	else {
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
		collection[newindex] = collection[index];
		xCoord[newindex] = xCoord[index];
		yCoord[newindex] = yCoord[index];
		collection[index] = NULL;
		xCoord[index] = 0;
		yCoord[index] = 0;
	}
	
}

void Scene::translate (int index, int xcoord, int ycoord) { // done ?

	if (index<0 || index>=length || collection[index]==NULL) 
		cout << "invalid index" << endl;
	
	else {
		xCoord[index] = xcoord;
		yCoord[index] = ycoord;
	}
}

void Scene::deletepicture (int index) { // done ?

	if (index<0 || index>=length || collection[index]==NULL) 
		cout << "invalid index" << endl;

	else {
		delete collection[index];
		collection[index] = NULL;
	}
}

Image * Scene::getpicture (int index) const { // done ?

	if (index<0 || index>=length || collection[index]==NULL) {
		cout << "invalid index" << endl;
		return NULL;
	}

	else {
		return collection[index];
	}
}


int Scene::maximum(int* array, int lo, int hi) const { // done ?
	if (lo>=hi) return array[lo];
	else {
		int maxOfNext = maximum(array, lo+1, hi);
		if (array[lo] > maxOfNext) return array[lo];
		else return maxOfNext;
	}
}

Image Scene::drawscene () const { // done ?

	int* newW = new int[length];
	int* newH = new int[length];
	for (int n=0; n<length; n++) {
		if (collection[n]!=NULL) {
			newW[n] = xCoord[n] + collection[n]->width();
			newH[n] = yCoord[n] + collection[n]->height();
		}
		else {
			newW[n] = 0;
			newH[n] = 0;
		}
	}

	int widthNeeded = maximum(newW, 0, length-1);
	int heightNeeded = maximum(newH, 0, length-1);

	PNG* resultPNG = new PNG(widthNeeded, heightNeeded);
	Image* result = (Image*) resultPNG;

	for (int n=0; n<length; n++) {
		if (collection[n]!=NULL) {
			for (size_t i=0; i<collection[n]->width(); i++) {
				for (size_t j=0; j<collection[n]->height(); j++) {
					*(*result)(xCoord[n]+i, yCoord[n]+j) = *(*collection[n])(i,j);
				}
			}
		}
	}
	delete [] newW;
	delete [] newH;
	newH = NULL;
	newW = NULL;
	
	return *result;
}
