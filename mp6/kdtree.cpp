#include <math.h>
#include <cmath>

/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
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
        // if there is a tie, use Point’s operator<
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

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    return distance (target, currentBest)  > distance (target, potential);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    // add all elements into points
    for (size_t i=0; i<newPoints.size(); i++) points.push_back(newPoints[i]);
    if (points.empty());
    // ensure that points is not empty
    else sortPoints (points, 0, points.size()-1, 0);
}

template <int Dim>
int KDTree<Dim>::medianLocation (vector<Point<Dim>> & points, int a, int b, int c, int dimension) {
    // assume points is not empty and a,b,c are within the range
    if (dimension>=Dim) return 0;
    else if (smallerDimVal(points[a],points[b],dimension)) {
        if (smallerDimVal(points[b],points[c],dimension)) return b;
        else if (smallerDimVal(points[c],points[a],dimension)) return a;
        else return c;
    }
    else {
        if (smallerDimVal(points[a],points[c],dimension)) return a;
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
    if (dimension>=Dim) return 0;
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
    if (dimension>=Dim) return;
    else if (startPoint>=endPoint) return;
    else {
        // find a "median" location
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
    if (dimension>=Dim) return;
    else if (startPoint>=endPoint) return;
    else {
        // sort the vector about given dimention
        sortPointsFixDim (points, startPoint, endPoint, dimension);
        int midPoint = (startPoint+endPoint)/2;
        dimension++;
        // sort the vector recursively
        sortPoints (points, startPoint, midPoint-1, dimension%Dim);
        sortPoints (points, midPoint+1, endPoint, dimension%Dim);
    }
}

/* 
 * findNearestNeighbor
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

// template <int Dim>
// int KDTree<Dim>::findMatch (const Point<Dim>& query, 
//         const std::vector<Point<Dim>> & points, int startPoint, int endPoint, int dimension) const{
//     // assume points is not empty and indices are within the range
//     // base case
//     if (startPoint>=endPoint) return startPoint;
//     else {
//         int midPoint = (startPoint+endPoint)/2;
//         if (points[midPoint][dimension]==query[dimension]) return midPoint;
//         else if (points[midPoint][dimension]<query[dimension]) 
//             return findMatch (query, points, startPoint, midPoint-1, (dimension+1)%Dim);
//         else 
//             return findMatch (query, points, midPoint+1, endPoint, (dimension+1)%Dim);
//     }
// }

// template <int Dim>
// int KDTree<Dim>::findNearest (const Point<Dim> & query, 
//         const std::vector<Point<Dim>> & points, int startPoint, int endPoint, int dimension) const{
//     if (startPoint>=endPoint) return startPoint;
//     int temp = findMatch (query, points, startPoint, endPoint, dimension);
//     // find the parent
//     int midPoint = (startPoint+endPoint)/2;
//     if (shouldReplace(query, points[temp], points[midPoint])) {
//         temp = midPoint;
//     }
//     else {
//         int radius = distance(points[temp], query);
//         // if within radius
//         if (std::abs(points[midPoint][dimension]-points[temp][dimension])<radius) {
//             if (temp<=midPoint) {
//                 int temp1 =  findNearest (query, points, midPoint+1, endPoint, (dimension+1)%Dim);
//                 // update temp, if needed
//                 if (shouldReplace(query, points[temp], points[temp1])) 
//                     temp = temp1;
//             }
//             if (temp>=midPoint) {
//                 int temp2 = findNearest (query, points, startPoint, midPoint-1, (dimension+1)%Dim);
//                 // update temp, if needed
//                 if (shouldReplace(query, points[temp], points[temp2])) 
//                     temp = temp2;
//             }
//         }
//     }
//     return temp;
// }

template <int Dim>
int KDTree<Dim>::findNearest (const Point<Dim> & query, 
        const std::vector<Point<Dim>> & points, int startPoint, int endPoint, int dimension) const{
    // base case
    if (startPoint>=endPoint) return startPoint;
    /** binary search: "choosing the subtree which represents the region containing the search element." */
    int midPoint = (startPoint+endPoint)/2;
    int temp;
    /** special case: "a tie across a level’s splitting dimension" */
    if (points[midPoint][dimension]==query[dimension]) {
        if (points[midPoint] > query) 
            temp = findNearest (query, points, startPoint, midPoint, (dimension+1)%Dim);
        else 
            temp = findNearest (query, points, midPoint, endPoint, (dimension+1)%Dim);
    }
    else if (points[midPoint][dimension]>query[dimension]) 
        temp = findNearest (query, points, startPoint, midPoint-1, (dimension+1)%Dim);
    else 
        temp = findNearest (query, points, midPoint+1, endPoint, (dimension+1)%Dim);

    /** "start traversing back up the k-d tree to the parent node" */

    /** "first check if the distance to the parent node is less than the current radius" */
    if (shouldReplace(query, points[temp], points[midPoint])) {
        /** "that distance now defines the radius, and we replace the 'current best' match." */
        int radius = distance(points[midPoint], query);
        /** "check to see if the current splitting plane’s distance from search node is within the current radius" */
        /** "If so, then the opposite subtree could contain a closer node, and must also be searched recursively." */
        if (std::abs(points[midPoint][dimension]-points[temp][dimension])<radius) {
            if (temp<=midPoint) {
                int temp1 =  findNearest (query, points, midPoint+1, endPoint, (dimension+1)%Dim);
                // update temp, if needed
                if (shouldReplace(query, points[temp], points[temp1])) 
                    temp = temp1;
            }
            if (temp>=midPoint) {
                int temp2 = findNearest (query, points, startPoint, midPoint-1, (dimension+1)%Dim);
                // update temp, if needed
                if (shouldReplace(query, points[temp], points[temp2])) 
                    temp = temp2;
            }
        }
    }
    return temp;
}