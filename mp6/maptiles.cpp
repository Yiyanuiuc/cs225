/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
	/**
	* @todo Implement this function!
	*/
	// creates a new dynamically allocated MosaicCanvas
	MosaicCanvas * result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
	map<Point<3>, TileImage> newMap;
	vector<Point<3>> pointsVector;
	for (size_t k=0; k<theTiles.size(); k++) {
		RGBAPixel temp = theTiles[k].getAverageColor();
		Point<3> point(temp.red, temp.green, temp.blue);
		pointsVector.push_back(point);
		newMap[point] = theTiles[k];
	}	
	// construct a kdtree
	KDTree<3> tree(pointsVector);
	 // For every region in the SourceImage
	 for (int i=0; i<theSource.getRows(); i++) {
	    	for (int j=0; j<theSource.getColumns(); j++) {
			Point<3> color (theSource.getRegionColor(i,j).red,theSource.getRegionColor(i,j).green,theSource.getRegionColor(i,j).blue);
			// using a KDTree to find the Nearest Neighbor for each region
	    		Point<3> nearest = tree.findNearestNeighbor(color);
	    		result->setTile(i, j, newMap[nearest]);
		}
	}
	return result;
}

