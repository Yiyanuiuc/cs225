/* Your code here! */

#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>
#include "maze.h"
#include "dsets.h"

#include <ctime>
#include <iostream>

/**
 * No-parameter constructor.
 * Creates an empty maze.
 */
SquareMaze::SquareMaze () {
	width = 0;
	height = 0;
}

/** 
 * Makes a new SquareMaze of the given height and width.
 * If this object already represents a maze it will clear all the existing data before doing so. 
 * You will start with a square grid (like graph paper) with the specified height and width. 
 * You will select random walls to delete without creating a cycle, 
 * until there are no more walls that could be deleted without creating a cycle. 
 * Do not delete walls on the perimeter of the grid.
 * Hints: You only need to store 2 bits per square: the "down" and "right" walls. 
 * 	The finished maze is always a tree of corridors.
 * Parameters
 * 	width The width of the SquareMaze (number of cells)
 * 	height The height of the SquareMaze (number of cells)
 */
void SquareMaze::makeMaze (int width, int height) {
	// If this object already represents a maze it will clear all the existing data
	if (!right.empty())
		right.clear();
	if (!down.empty())
		down.clear();
	// Makes a new SquareMaze of the given height and width with all walls
	for (int i=0; i<width; i++) {
		vector<bool> temp;
		// false represents walls
		right.push_back(temp);
		down.push_back(temp);
		for (int j=0; j<height; j++) {
			right[i].push_back(false);
			down[i].push_back(false);
		}
	}
	this->width = width;
	this->height = height;
	s.addelements(width*height);
	// generate random numbers
	srand(time(NULL));
	int x, y, dir;
	// bool satisfied = false;
	// while (!satisfied) {
	// 	while (true) {
	// 		// You will select random walls to delete without creating a cycle
	// 		x = rand()%width;
	// 		y = rand()%height;
	// 		int curr = y*width+x;
	// 		dir = rand()%2;
	// 		// if the wall exist
	// 		if (!canTravel(x,y,dir)) {
	// 			// if a cycle will generated
	// 			if (dir==0 && s.find(curr)==s.find(curr+1)) 
	// 				break;
	// 			else if (dir==1 && s.find(curr)==s.find(curr+width)) 
	// 				break;
	// 			// if not, delete the wall
	// 			setWall (x, y, dir, false);
	// 		}
	// 	}
	// 	// check connection
	// 	satisfied = true;
	// 	for (int i=0; i<width*height; i++) {
	// 		// if there is a square not connected to 0,0
	// 		if (s.find(0)!=s.find(i)) {
	// 			satisfied = false;
	// 			break;
	// 		}
	// 	}
	// }
	int count = width*height-1;
	while (count>0) {
		// You will select random walls to delete without creating a cycle
		x = rand()%width;
		y = rand()%height;
		int curr = y*width+x;
		dir = rand()%2;
		// if the wall exist
		if (!canTravel(x,y,dir)) {
			// if a cycle will generated
			if (dir==0) {
				if (x==width-1) ;
				else if (s.find(curr)==s.find(curr+1));
				else {
					setWall (x, y, dir, false);
					count -= 1;
				}
			}
			else {
				if (y==height-1);
				else if (s.find(curr)==s.find(curr+width));
				else {
					setWall (x, y, dir, false);
					count -= 1;
				}
			}
		}
	}
} 

/**
 * This uses your representation of the maze to determine 
 * whether it is possible to travel in the given direction from the square at coordinates (x,y).
 * For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).
 * 	dir = 0 represents a rightward step (+1 to the x coordinate)
 * 	dir = 1 represents a downward step (+1 to the y coordinate)
 * 	dir = 2 represents a leftward step (-1 to the x coordinate)
 * 	dir = 3 represents an upward step (-1 to the y coordinate)
 * You can not step off of the maze or through a wall.
 * This function will be very helpful in solving the maze. 
 * It will also be used by the grading program to verify that your maze is a tree that occupies the whole grid, 
 * and to verify your maze solution. 
 * So make sure that this function works!
 * Parameters
 * 	x The x coordinate of the current cell
 * 	y The y coordinate of the current cell
 * 	dir The desired direction to move from the current cell
 */
bool SquareMaze::canTravel (int x, int y, int dir) const {
	if (dir<0||dir>3 || x<0||x>width-1 || y<0||y>height-1) return false;
	int curr = y*width+x;
	// dir = 0 represents a rightward step (+1 to the x coordinate)
	if (dir==0) {
		if (x==width-1) return false;
 		else return right[x][y];
 	}
	// dir = 1 represents a downward step (+1 to the y coordinate)
	else if (dir==1) {
		if (y==height-1) return false;
		else return down[x][y];
	}
	// dir = 2 represents a leftward step (-1 to the x coordinate)
	else if (dir==2) {
		if (x==0) return false;
		else return right[x-1][y];
	}
	// dir = 3 represents an upward step (-1 to the y coordinate)
	else {
		if (y==0) return false;
		else return down[x][y-1];
	}
}

/** 
 * Sets whether or not the specified wall exists.
 * This function should be fast (constant time). 
 * You can assume that in grading we will not make your maze a non-tree and then call one of the other member functions. 
 * setWall should not prevent cycles from occurring, but should simply set a wall to be present or not present. 
 * Our tests will call setWall to copy a specific maze into your implementation.
 * Parameters
 * 	x The x coordinate of the current cell
 * 	y The y coordinate of the current cell
 * 	dir Either 0 (right) or 1 (down), which specifies which wall to set (same as the encoding explained in canTravel). 
 * 		You only need to support setting the bottom and right walls of every square in the grid.
 * 	exists	true if setting the wall to exist, false otherwise
 */
void SquareMaze::setWall (int x, int y, int dir, bool exists){
	if (x<0||x>width-1 || y<0||y>height-1) return;
	// reach the margin
	if (dir==0 && x==width-1) return;
	if (dir==1 && y==height-1) return;
	// if true, set the wall to exist
	int curr = y*width+x;
	if (exists) {
		if (dir==0) 
			right[x][y] = false;
		else if (dir==1) 
			down[x][y] = false;
	}
	// if false, delete the wall
	else {
		if (dir==0) {
			right[x][y] = true;
			s.setunion(curr, curr+1);
		}
		else if (dir==1) {
			down[x][y] = true;
			s.setunion(curr, curr+width);
		}
	}
}

/**  
 * Solves this SquareMaze.
 * For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell), 
 * which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.
 * Select the square in the bottom row with the largest distance from the origin as the destination of the maze. 
 * solveMaze() returns the winning path from the origin to the destination as a vector of integers, 
 * where each integer represents the direction of a step, using the same encoding as in canTravel().
 * If multiple paths of maximum length exist, use the one with the destination cell that has the smallest x value.
 * Hint: this function should run in time linear in the number of cells in the maze.
 * Returns a vector of directions taken to solve the maze
 */
vector<int> SquareMaze::solveMaze () {
	vector<int> path;
	for (int k=0; k<width; k++) {
		// if they are connected
		if (s.find(0) == s.find(width*(height-1)+k)) {
			vector<vector<bool>> processed;
			for (int i=0; i<width; i++) {
				processed.push_back(vector<bool>());
				for (int j=0; j<height; j++)
					processed[i].push_back(false);
			}
		 	vector<int> tempPath;
		 	findPath(0,0,k,height-1,tempPath,processed);
		 	// update the longest path
		 	if (path.size()<tempPath.size()) path = tempPath;
		}
	}
	return path;
}

// return the y-coordinate of destination
void SquareMaze::findPath (int x, int y, int finalX, int finalY, vector<int> & path, vector<vector<bool>> processed) {
	// when reach the destination
	if (x==finalX && y==finalY) return;
	// if it is out of bound but not reach destination, it is not a good path
	if (x<0||x>width-1 || y<0||y>height-1 || finalX<0||finalX>width-1 || finalY<0||finalY>height-1) {
		path = vector<int>();
		return;
	}
	// if it has been processed but not reach destination, it is not a good path
	if (processed[x][y]) {
		path = vector<int>();
		return ;
	}
	// otherwise,
	processed[x][y] = true;
	vector<int> largest;
	if (canTravel(x, y, 0)) {
		vector<int> tempPath = path;
		tempPath.push_back(0);
		findPath (x+1,y,finalX,finalY,tempPath,processed);
		if (largest.size()<tempPath.size()) {
			largest = tempPath;
		}
	}
	if (canTravel(x, y, 1)) {
		vector<int> tempPath = path;
		tempPath.push_back(1);
		findPath (x,y+1,finalX,finalY,tempPath,processed);
		if (largest.size()<tempPath.size()) {
			largest = tempPath;
		}
	}
	if (canTravel(x, y, 2)) {
		vector<int> tempPath = path;
		tempPath.push_back(2);
		findPath (x-1,y,finalX,finalY,tempPath,processed);
		if (largest.size()<tempPath.size()) {
			largest = tempPath;
		}
	}
	if (canTravel(x, y, 3)) {
		vector<int> tempPath = path;
		tempPath.push_back(3);
		findPath (x,y-1,finalX,finalY,tempPath,processed);
		if (largest.size()<tempPath.size()) {
			largest = tempPath;
		}
	}
	path = largest;
}

/**  
 * Draws the maze without the solution.
 * First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). 
 * where height and width were the arguments to makeMaze. 
 * Blacken the entire topmost row and leftmost column of pixels, except the entrance (1,0) through (9,0). 
 * For each square in the maze, call its maze coordinates (x,y). 
 * If the right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10. 
 * If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
 * The resulting PNG will look like the sample image, except there will be no exit from the maze and the red line will be missing.
 * Returns a PNG of the unsolved SquareMaze
 */
PNG * SquareMaze::drawMaze () const {
	PNG * result = new PNG(width*10+1,height*10+1);
	// Blacken the entire topmost row and leftmost column of pixels, except the entrance (1,0) through (9,0). 
	*((*result)(0,0)) = RGBAPixel(0,0,0);
	*((*result)(width*10,height*10)) = RGBAPixel(0,0,0);
	for (int i=10; i<width*10+1; i++)
		*((*result)(i,0)) = RGBAPixel(0,0,0);
	for (int i=0; i<height*10+1; i++)
		*((*result)(0,i)) = RGBAPixel(0,0,0);
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			if (!canTravel(i,j,0)) 
				for (int k=0; k<=10; k++)
					*((*result)((i+1)*10,j*10+k)) = RGBAPixel(0,0,0);
			if (!canTravel(i,j,1)) 
				for (int k=0; k<=10; k++)
					*((*result)(i*10+k,(j+1)*10)) = RGBAPixel(0,0,0);
		}
	}
	return result;
}
 
/**
 *This function calls drawMaze, then solveMaze; 
 * it modifies the PNG from drawMaze to show the solution vector and the exit.
 * Start at pixel (5,5). Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction. 
 * If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 255,0,0 in RGB). 
 * Then if the second step is right, color pixels (5,15) through (15,15) red. 
 * Then if the third step is up, color pixels (15,15) through (15,5) red. 
 * Continue in this manner until you get to the end of the solution vector, so that your output looks analogous the above picture.
 * Make the exit by undoing the bottom wall of the destination square: 
 * call the destination maze coordinates (x,y), and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
 * Returns a PNG of the solved SquareMaze
 */
PNG * SquareMaze::drawMazeWithSolution () {
	PNG * result = drawMaze();
	vector<int> path = solveMaze();
	int currentX = 5;
	int currentY = 5;
	for (size_t i=0; i<path.size(); i++) {
		if (path[i]==0) {
			for (int j=0; j<=10; j++) 
				*((*result)(currentX+j, currentY)) = RGBAPixel(255,0,0);
			currentX += 10;
		}
		else if (path[i]==1) {
			for (int j=0; j<=10; j++) 
				*((*result)(currentX, currentY+j)) = RGBAPixel(255,0,0);
			currentY += 10;
		}
		else if (path[i]==2) {
			for (int j=0; j<=10; j++) 
				*((*result)(currentX-j, currentY)) = RGBAPixel(255,0,0);
			currentX -= 10;
		}		
		else {
			for (int j=0; j<=10; j++) 
				*((*result)(currentX, currentY-j)) = RGBAPixel(255,0,0);
			currentY -= 10;
		}	
	}
	// mark the exit
	for (int i=1; i<10; i++)
		*((*result)(currentX-5+i,height*10)) = RGBAPixel(255,255,255);
	return result;
}