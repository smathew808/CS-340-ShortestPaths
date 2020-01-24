#pragma once
#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

using namespace std;




struct Vertex {

	int parentId; //the Id for the parent of the vertex, could have multiple parents since there could be multiple arrows
	int id; //The id for the vertex

	//dfs attributes
	string color; //color of a vertex
	int disc; //the discovery time for a vertex
	int fin; //the finished time for the vertex

	//bellmanford attributes
	int distance;

	vector <int> adjacencyList; //adjacencyList

};

struct Edge {

	int startingVertex; //vertexList
	int endingVertex;
	int edgeWeight;

};

struct Node {
	Vertex vertex;
	Node *next;
};

class Graph {
private:

	//***//
	//DFS//
	//***//

	int time;
	
	

	

	int weight; //the weight of an edge
	char root; //the root of one tree
	vector <Vertex> verticesSet; //the array(vector) that will hold 

public:
	Node *head, *tail, *traverse = nullptr;

	vector <Edge> edgeList;  //dynamic array(vector) of edges
	vector <Vertex> verticesList; //dynamic array(vector) of vertices

	int shortestPathListCounter = 0;

	vector<Vertex> shortestPathList;
	vector <Vertex> emptyList;

	vector<Vertex> queue;

	vector<Vertex> topoSortList;

	int negativeEdgeWeightDetector = 0;
	int cycleDetector = 0;

	//no args ctr
	Graph();

	//loads file
	void loadList(string fileName);

	//creates a new Vertex
	Vertex getNewVertice(int data);

	//relax
	void relax(int startingVertex, int endingVertex, int edgeWeight, vector <Vertex> &verticesList);

	//determining cycles
	//for bellman
	int DFS();
	int DFSVisit(vector <Vertex> &verticesList, Vertex &currVertex);

	vector<Vertex> TopoSort(vector <Vertex> &verticesList);


	void createnode(Vertex currVertex);

	//for topo
	vector<Vertex> topoDFS();
	vector <Vertex> topoDFSVisit(vector <Vertex> &verticesList, Vertex &currVertex);

	//bellmanFord
	vector <Vertex> BellmanFord(vector <Vertex> &verticesList, vector <Edge> edgeList, int sourceNode, int destinationNode);

	vector <Vertex> dagSP(vector <Vertex> &verticesList, vector <Edge> edgeList, int sourceNode, int destinationNode);

	vector <Edge> dijkstras(vector <Vertex> &verticesList, vector <Edge> edgeList, int sourceNode, int destinationNode);
};