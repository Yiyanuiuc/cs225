#include "scene.h"

#include <iostream>
using namespace std;

// Constructor & Destructor 

Scene::Scene (int max) { // done ?

	this->collection = new Image*[max];
	this->length = max;
	this->xCoord = new int[max];
	this->yCoord = new int[max];

	for (int i=0; i < this->length - 1; i++) {
		this->collection[i] = NULL;
		this->xCoord[i] = 0;
		this->yCoord[i] = 0;
	}
	cout << "Finish Scene" << endl;
}

void Scene::clear() {

	for (int i=0; i<length; i++) {
		delete collection[i];
		collection[i] = NULL;
	}
	delete [] collection;
	delete [] xCoord;
	delete [] yCoord;

	collection = NULL;
	xCoord = NULL;
	yCoord = NULL;

	cout << "Finish clear()" << endl;
}

Scene::~Scene() {
	clear();
	cout << "Finish ~Scene()" << endl;
};

void Scene::copy(const Scene &source) {

	collection = new Image*[source.length];
	length = source.length;
	xCoord = new int[source.length];
	yCoord = new int[source.length];

	for (int n=0; n<source.length-1; n++) {
		if (collection[n]!=NULL) {
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

	cout << "FInish copy" << endl;
}

Scene::Scene (const Scene &source) {
	copy(source);
	cout << "Finish copy Scene()" << endl;
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
	cout << "Finish addpi()" << endl;
}

void Scene::changelayer (int index, int newindex) { // done ?

	if (index<0 || index>=length || newindex<0 || newindex>=length) 
		cout << "invalid index" << endl;
	else if (index==newindex) return;

	else {
		if (collection[newindex]!=NULL) 
			delete collection[newindex];
		collection[newindex] = collection[index];
		xCoord[newindex] = xCoord[index];
		yCoord[newindex] = yCoord[index];
		collection[index] = NULL;
		xCoord[index] = 0;
		yCoord[index] = 0;
	}
	
	cout << "FInish changelayer" << endl;
}

void Scene::translate (int index, int xcoord, int ycoord) { // done ?

	if (index<0 || index>=length || collection[index]==NULL) 
		cout << "invalid index" << endl;
	
	else {
		xCoord[index] = xcoord;
		yCoord[index] = ycoord;
	}
	cout << "FInish translate" << endl;
}

void Scene::deletepicture (int index) { // done ?

	if (index<0 || index>=length || collection[index]==NULL) 
		cout << "invalid index" << endl;

	else {
		delete collection[index];
		collection[index] = NULL;
	}
	cout << "FInish delete" << endl;
}

Image * Scene::getpicture (int index) const { // done ?

	if (index<0 || index>=length || collection[index]==NULL) {
		cout << "invalid index" << endl;
		cout << "FInish get" << endl;
		return NULL;
	}

	else {
		cout << "FInish get" << endl;
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
	for (int i=0; i<length; i++) {
		if (collection[i]!=NULL) {
			newW[i] = xCoord[i] + collection[i]->width();
			newH[i] = yCoord[i] + collection[i]->height();
		}
		else {
			newW[i] = 0;
			newH[i] = 0;
		}
	}

	int widthNeeded = maximum(newW, 0, length-1);
	int heightNeeded = maximum(newH, 0, length-1);

	PNG* resultPNG = new PNG(widthNeeded, heightNeeded);
	Image* result = (Image*) resultPNG;

	for (int n=0; n<length; n++) {
		if (collection[n]!=NULL) {
			for (int i=0; i<collection[n]->width(); i++) {
				for (int j=0; j<collection[n]->height(); j++) {
					*(*result)(xCoord[n]+i, yCoord[n]+j) = *(*collection[n])(i,j);
				}
			}
		}
	}
	delete [] newW;
	delete [] newH;
	newH = NULL;
	newW = NULL;

	cout << "Finish draw()" << endl;
	return *result;
}
