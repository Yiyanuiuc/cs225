/* Your code here! */

#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>
#include "maze.h"
#include "dsets.h"

#include <stdlib.h>  

/**
 * No-parameter constructor.
 * Creates an empty maze.
 */
SquareMaze::SquareMaze () {
	width = 0;
	height = 0;
	right = vector<int>();
	height = vector<int>();
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
 * width The width of the SquareMaze (number of cells)
 * height The height of the SquareMaze (number of cells)
 */
void SquareMaze::makeMaze (int width, int height) {
	// If this object already represents a maze it will clear all the existing data
	while (!right.empty())
		right.pop();
	while (!height.empty())
		height.pop();
	// Makes a new SquareMaze of the given height and width with all walls
	for (int i=0; i<width*height; i++) {
		right.push_back(-1);
		down.push_back(-1);
	}
	this.width = width;
	this.height = height;
	bool pathDNE = true;
	while (keep) {
		int x = rand()%width;
		int y = rand()%height;
		int dir = rand()%4;
		setWall (x, y, dir, false);
		pathDNE = true;
		for (int i=0; i<width; i++) {
			for (int j=0; j<height; j++) {
				if (pathExist(i,j,i,j)) pathDNE = true;
				break;
			}
		}
	}

} 

bool SquareMaze::pathExist (int x, int y, int finalX, int finalY) {
	if (x<0||x>width-1 || y<0||y>height-1 || finalX<0||finalX>width-1 || finalY<0||finalY>height-1) 
		return false;
	if (x==finalX && y==finalY) return false;
	vector<vector<bool>> processed;
	for (int i=0; i<width; i++) {
		processed.push_back(vector<bool>());
		for (int j=0; j<height; j++)
			processed[i].push_back(false);
	}
	queue<int> xCoord;
	queue<int> yCoord;
	xCoord.push(x);
	yCoord.push(y);
	while (!xCoord.empty()) {
		int tempX = xCoord.front();
		xCoord.pop();
		int tempY = yCoord.front();
		yCoord.pop();
		if (tempX==finalX-1 && tempY==finalY && canTravel(tempX,tempY,0)) return true;
		else if (tempX==finalX && tempY==finalY-1 && canTravel(tempX,tempY,1)) return true;
		else if (tempX==finalX+1 && tempY==finalY && canTravel(tempX,tempY,2)) return true;
		else if (tempX==finalX && tempY==finalY+1 && canTravel(tempX,tempY,3)) return true;
		else if (!processed[tempX][tempY]) {
			processed[tempX][tempY] = true;
			if (canTravel(tempX, tempY, 0)) {
				xCoord.push(tempX+1);
				yCoord.push(tempY);
			}
			if (canTravel(tempX, tempY, 1)) {
				xCoord.push(tempX);
				yCoord.push(tempY+1);
			}
			if (canTravel(tempX, tempY, 2)) {
				xCoord.push(tempX-1);
				yCoord.push(tempY);
			}
			if (canTravel(tempX, tempY, 3)) {
				xCoord.push(tempX);
				yCoord.push(tempY-1);
			}
		}
	}
	return false;
}

/**
 * This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).
 * For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).
 * 	dir = 0 represents a rightward step (+1 to the x coordinate)
 * 	dir = 1 represents a downward step (+1 to the y coordinate)
 * 	dir = 2 represents a leftward step (-1 to the x coordinate)
 * 	dir = 3 represents an upward step (-1 to the y coordinate)
 * You can not step off of the maze or through a wall.
 * This function will be very helpful in solving the maze. 
 * It will also be used by the grading program to verify that your maze is a tree that occupies the whole grid, and to verify your maze solution. 
 * So make sure that this function works!
 * Parameters
 * 	x The x coordinate of the current cell
 * 	y The y coordinate of the current cell
 * 	dir The desired direction to move from the current cell
 */
bool SquareMaze::canTravel (int x, int y, int dir) const {
	if (dir<0||dir>3 || x<0||x>width-1 || y<0||y>height-1) return false;
	if (d==0) {
		if (x==width-1) return false;
		else return right[y*width+x]==y*width+(x+1);
	}
	else if (d==1) {
		if (y==height-1) return false;
		else return down[y*width+x]==(y+1)*width+x;
	}
	else if (d==2) {
		if (x==0) return false;
		else return right[y*width+(x-1)]==y*width+x;
	}
	else {
		if (y==0) return false;
		else return down[(y-1)*width+x]==y*width+x;
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
	if (dir==0 && x==width-1) return;
	if (dir==1 && y==height-1) return;
	if (exists) {
		if (dir==0) right[y*width+x] = -1;
		if (dir==1) down[y*width+x] = -1;
	}
	else {
		if (dir==0) right[y*width+x] = y*width+(x+1);
		if (dir==1) down[y*width+x] = (y+1)*width+x;
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
vector<int> solveMaze () 

void 
 
PNG * 	drawMaze () const
 	Draws the maze without the solution. More...
 
PNG * 	drawMazeWithSolution ()
 	This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit. More...