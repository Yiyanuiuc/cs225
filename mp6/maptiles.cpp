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
    MosaicCanvas * result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    for (int i=0; i<theSource.getRows(); i++) {
    	for (int j=0; j<theSource.getColumns(); j++) {
    		vector<Point<3>> pointsVector;
    		for (size_t k=0; k<theTiles.size(); k++) {
    			Point<3> temp(theTiles[k].getAverageColor().red,theTiles[k].getAverageColor().green,theTiles[k].getAverageColor().blue);
    			pointsVector.push_back(temp);
    		}
    		KDTree<3> tree(pointsVector);
		Point<3> color (theSource.getRegionColor(i,j).red,theSource.getRegionColor(i,j).green,theSource.getRegionColor(i,j).blue);
    		Point<3> nearest = tree.findNearestNeighbor(color);
    		int position = 0;
    		for (size_t k=0; k<theTiles.size(); k++) {
    			Point<3> temp(theTiles[k].getAverageColor().red,theTiles[k].getAverageColor().green,theTiles[k].getAverageColor().blue);
    			if (temp==nearest) 
    				position=k;
    		}
    		result->setTile(i, j, theTiles[position]);
	}
    }
    return result;
}

