#include <math.h>
#include <cmath>

/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

/**
 * Determines if Point a is smaller than Point b in a given dimension d.
 * If there is a tie, break it with Point::operator<().
 */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    // if curDim is out of range
    if (curDim<0 || curDim>=Dim) return false;
    // if curDim is in the range
    else {
        /** "if there is a tie, use Point’s operator<" */
        if (first[curDim]==second[curDim]) return first < second;
        else return first[curDim]<second[curDim];
    }
}

template <int Dim>
int KDTree<Dim>::distance (const Point<Dim> & first, const Point<Dim> & second) const{
    int sum = 0;
    // calculate the total distance's square
    for (int i=0; i<Dim; i++) {
        sum += pow(first[i]-second[i],2);
    }
    return sum;
}

/**
 * Determines if a Point is closer to the target Point than another
 * reference Point. Takes three points: target, currentBest, and
 * potential, and returns whether or not potential is closer to
 * target than currentBest.
 */
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    /** "with a tie being broken by the operator< in the Point class: potential < currentBest" */
    if (distance (target, potential)==distance (target, currentBest))
        return potential < currentBest;
    else 
        return distance (target, potential) < distance (target, currentBest);
}

/**
 * Constructs a KDTree from a vector of Points, each having dimension Dim.
 */
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    // add all elements into points
    for (size_t i=0; i<newPoints.size(); i++) points.push_back(newPoints[i]);
    if (points.empty()) return;
    // ensure that points is not empty
    else sortPoints (points, 0, points.size()-1, 0);
}

template <int Dim>
int KDTree<Dim>::medianLocation (vector<Point<Dim>> & points, int a, int b, int c, int dimension) {
    // assume points is not empty and a,b,c are within the range
    if (smallerDimVal(points[a],points[b],dimension)) {
        // if a<b<c
        if (smallerDimVal(points[b],points[c],dimension)) return b;
        // if c<a<b
        else if (smallerDimVal(points[c],points[a],dimension)) return a;
        else return c;
    }
    else {
        // if b<a<c
        if (smallerDimVal(points[a],points[c],dimension)) return a;
        // if c<b<a
        else if (smallerDimVal(points[c],points[b],dimension)) return b;
        else return c;
    }
}

template <int Dim>
void KDTree<Dim>::swap (std::vector<Point<Dim>> & points, int a, int b) {
    // assume points is not empty and indices are within the range
    Point<Dim> temp = points[a];
    points[a] = points[b];
    points[b] = temp;
}

template <int Dim>
int KDTree<Dim>::partition (vector<Point<Dim>> & points, int startPoint, int endPoint, int pivotIndex, int dimension) {
    // assume points is not empty and indices are within the range
    Point<Dim> pivotPoint = points[pivotIndex];
    // move it to the back
    swap (points, pivotIndex, endPoint);
    int storeIndex = startPoint;
    for (int i=startPoint; i<endPoint; i++) {
        if (smallerDimVal(points[i], pivotPoint, dimension)) {
            swap (points, storeIndex, i);
            // update storeIndex
            storeIndex++;
        }
    }
    // move to the final position
    swap (points, endPoint, storeIndex);
    return storeIndex;
}

template <int Dim>
void KDTree<Dim>::sortPointsFixDim (std::vector<Point<Dim>> & points, int startPoint, int endPoint, int dimension) {
    // assume points is not empty and indices are within the range
    // base case
    if (startPoint>=endPoint) return;
    else {
        int pivotPoint = medianLocation (points, startPoint, endPoint, (startPoint+endPoint)/2, dimension);
        pivotPoint = partition (points, startPoint, endPoint, pivotPoint, dimension);
        // sort sublist recursively
        sortPointsFixDim (points, startPoint, pivotPoint-1, dimension);
        sortPointsFixDim (points, pivotPoint+1, endPoint, dimension);
    }
}

template <int Dim>
void KDTree<Dim>::sortPoints (std::vector<Point<Dim>> & points, int startPoint, int endPoint, int dimension) {
    // assume points is not empty and indices are within the range
    // base case
    if (startPoint>=endPoint) return;
    else {
        /** "Find the median of points with respect to dimension d/" */
        sortPointsFixDim (points, startPoint, endPoint, dimension);
        int midPoint = (startPoint+endPoint)/2;
        dimension++;
        /** "Recurse on the indices between aa though m−1m−1, and m+1m+1 through bb using splitting dimension (d+1)modk(d+1)modk." */
        sortPoints (points, startPoint, midPoint-1, dimension%Dim);
        sortPoints (points, midPoint+1, endPoint, dimension%Dim);
    }
}

/* 
 * findNearestNeighbor
 */

/**
 * Finds the closest point to the parameter point in the KDTree.
 */
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    int result = findNearest (query, points, 0, points.size()-1, 0);
    return points[result];
}

template <int Dim>
int KDTree<Dim>::findNearest (const Point<Dim> & query, 
        const std::vector<Point<Dim>> & points, int startPoint, int endPoint, int dimension) const{

    /** Step ONE "a search to find the smallest hyperrectangle that contains the target element" */

    // base case
    if (startPoint>=endPoint) return startPoint;
    /** binary search: "choosing the subtree which represents the region containing the search element." */
    int midPoint = (startPoint+endPoint)/2;
    int temp;
    if (smallerDimVal(query, points[midPoint], dimension))
        temp = findNearest (query, points, startPoint, midPoint-1, (dimension+1)%Dim);
    else 
        temp = findNearest (query, points, midPoint+1, endPoint, (dimension+1)%Dim);

    /** Step TWO "start traversing back up the k-d tree to the parent node" */

    /** "first check if the distance to the parent node is less than the current radius" */
    if (shouldReplace(query, points[temp], points[midPoint])) {
        // update temp
        temp = midPoint;
    }
    /** "that distance now defines the radius, and we replace the 'current best' match." */
    int radius = distance(points[temp], query);
    /** "check to see if the current splitting plane’s distance from search node is within the current radius" */
    /** "If so, then the opposite subtree could contain a closer node, and must also be searched recursively." */
    if ( pow(points[midPoint][dimension]-query[dimension],2) <= radius) {
        if (smallerDimVal(query,points[midPoint],dimension)) {
            int temp1 = findNearest (query, points, midPoint+1, endPoint, (dimension+1)%Dim);
            // update temp, if needed
            if (shouldReplace(query, points[temp], points[temp1])) 
                temp = temp1;
        }
        else {
            int temp2 = findNearest (query, points, startPoint, midPoint-1, (dimension+1)%Dim);
            // update temp, if needed
            if (shouldReplace(query, points[temp], points[temp2])) 
                temp = temp2;
        }
    }
    return temp;
}