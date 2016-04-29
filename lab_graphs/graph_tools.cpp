/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <vector>
#include <map>

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
	/* Your code here! */

	// Initially label vertices and edges as unvisited.
	vector<Vertex> vertexList = graph.getVertices();
	for (size_t i=0; i<vertexList.size(); i++)
		graph.setVertexLabel(vertexList[i], "UNEXPLORED");
	queue<Vertex> q;
	Vertex v = graph.getStartingVertex();
	graph.setVertexLabel(v, "VISITED");
	q.push(v);
	while (!q.empty()) {
		Vertex nextV = q.front();
		q.pop();
		vector<Vertex> adj = graph.getAdjacent(nextV);
		for (size_t i=0; i<adj.size(); i++) {
			Vertex temp = adj[i];
			if (graph.getVertexLabel(temp)=="UNEXPLORED") {
				graph.setEdgeLabel(nextV, temp, "UNEXPLORED");
				graph.setVertexLabel(temp, "VISITED");
				q.push(temp);
			}
			else if (graph.getEdgeLabel(nextV, temp)!="UNEXPLORED") {
				graph.setEdgeLabel(nextV, temp, "UNEXPLORED");
			}
		}
	}
	for (size_t i=0; i<vertexList.size(); i++)
		graph.setVertexLabel(vertexList[i], "UNEXPLORED");
	while (!q.empty()) q.pop();

	graph.setVertexLabel(v, "VISITED");
	q.push(v);
	Vertex min1 = v;
	Vertex min2 = graph.getAdjacent(v)[0];
	while (!q.empty()) {
		Vertex nextV = q.front();
		q.pop();
		vector<Vertex> adj = graph.getAdjacent(nextV);
		for (size_t i=0; i<adj.size(); i++) {
			Vertex temp = adj[i];
			if (graph.getVertexLabel(temp)=="UNEXPLORED") {
				graph.setEdgeLabel(nextV, temp, "DISCOVERY");
				graph.setVertexLabel(temp, "VISITED");
				q.push(temp);
				if (graph.getEdgeWeight(nextV, temp) < graph.getEdgeWeight(min1, min2)) {
					min1 = nextV;
					min2 = temp;
				}
			}
			else if (graph.getEdgeLabel(nextV, temp)!="UNEXPLORED") {
				graph.setEdgeLabel(nextV, temp, "CROSS");
				if (graph.getEdgeWeight(nextV, temp) < graph.getEdgeWeight(min1, min2)) {
					min1 = nextV;
					min2 = temp;
				}
			}
		}
	}
	graph.setEdgeLabel(min1,min2,"MIN");
	return graph.getEdgeWeight(min1,min2);
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
	/* Your code here! */
	// Initially label vertices and edges as unvisited.
	vector<Vertex> vertexList = graph.getVertices();
	for (size_t i=0; i<vertexList.size(); i++)
		graph.setVertexLabel(vertexList[i], "UNEXPLORED");
	queue<Vertex> q;
	graph.setVertexLabel(start, "VISITED");
	q.push(start);
	while (!q.empty()) {
		Vertex nextV = q.front();
		q.pop();
		vector<Vertex> adj = graph.getAdjacent(nextV);
		for (size_t i=0; i<adj.size(); i++) {
			Vertex temp = adj[i];
			if (graph.getVertexLabel(temp)=="UNEXPLORED") {
				graph.setEdgeLabel(nextV, temp, "UNEXPLORED");
				graph.setVertexLabel(temp, "VISITED");
				q.push(temp);
			}
			else if (graph.getEdgeLabel(nextV, temp)!="UNEXPLORED") {
				graph.setEdgeLabel(nextV, temp, "UNEXPLORED");
			}
		}
	}
	for (size_t i=0; i<vertexList.size(); i++)
		graph.setVertexLabel(vertexList[i], "UNEXPLORED");
	while (!q.empty()) q.pop(); 


	graph.setVertexLabel(start, "VISITED");
	q.push(start);
	std::map<Vertex, int> dis;
	dis[start]=0;
	map<Vertex, Vertex> parent;
	Vertex nextV;	
	while (!q.empty()) {
		nextV = q.front(); 
		if (nextV==end) break;
		else {
			q.pop();
			vector<Vertex> adj = graph.getAdjacent(nextV);
			for (size_t i=0; i<adj.size(); i++) {
				Vertex temp = adj[i];
				if (graph.getVertexLabel(temp)=="UNEXPLORED") {
					graph.setVertexLabel(temp, "VISITED");
					q.push(temp);
					dis[temp] = dis[nextV]+1;
					parent[temp] = nextV;
				}
			}
		}
	}
	Vertex	temp = nextV;
	while (parent[temp]!=start) {
		graph.setEdgeLabel(parent[temp], temp, "MINPATH");
		temp = parent[temp];
	}
	graph.setEdgeLabel(start, temp, "MINPATH");
	return dis[nextV];
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
	/* Your code here! */
}

