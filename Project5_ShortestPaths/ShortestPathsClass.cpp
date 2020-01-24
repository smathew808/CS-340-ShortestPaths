#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "ShortestPaths.h"
using namespace std;

Graph::Graph() {


}

Vertex Graph::getNewVertice(int data) {

	//create the vertex

	Vertex newVertex;
	//newVertex->color = "grey";
	newVertex.id = data; //sentinel value
						 //newVertex->disc = 0;//temp value
						 //newVertex->fin = 0; //temp value
	newVertex.parentId = data;

	return newVertex;
}



int Graph::DFS() {

	//**************************************************************************************************************************//
	//This checks whether there are ANY negative edgeWeights because if there is, then can only run either DAG SP or BellmanFord//
	//**************************************************************************************************************************//

	//check if theres any negative edgeWeights
	for (int i = 0; i < edgeList.size(); i++)
	{
		//if the edgeWeight is negative once, then break out
		if (edgeList[i].edgeWeight < 0)
		{
			negativeEdgeWeightDetector = 2;
			break;
		}

	}
	


	//this loop can also be said that it's prepping the graph, getting ready to be searched?
	for (int u = 0; u < verticesList.size(); u++) {

		verticesList[u].color = "white"; //color is set to white, meaning it's undiscovered

		//null value will be 420
		verticesList[u].parentId = 420; //do i need to create a nil object? like a nil vertex???

		time = 0; //timestamp for all the vertexes since they are undiscoverred
	}


	//At this point the graph is made with an empty graphg


	for (int u = 0; u < verticesList.size(); u++)
	{


		if (verticesList[u].color == "white") {
			cycleDetector = DFSVisit(verticesList, verticesList[u]);
		}
	}

	

	return (negativeEdgeWeightDetector + cycleDetector);

}

int Graph::DFSVisit(vector <Vertex> &verticesList, Vertex &currVertex) {

	Vertex newVertexSelected;

	time = time + 1; //when a vertex visits another vertex, it adds the current timestamp to 1, then 2, etc, for each visit

	currVertex.disc = time; //this sets the discovery stamp to 1, 2, etc

	currVertex.color = "gray"; //sets the color to gray to the vertex discovered


							   //for each vertex in the adj list...do stuff
	for (int i = 0; i < verticesList[currVertex.id - 1].adjacencyList.size(); i++) {

		//if the ajd vertex is undiscovered

		if (verticesList[currVertex.adjacencyList[i] - 1].color == "white") {

			//set the parent of the adj to the currVertex
		verticesList[currVertex.adjacencyList[i] - 1].parentId = currVertex.id;

			DFSVisit(verticesList, verticesList[currVertex.adjacencyList[i] - 1]); //explore again
		}


		//
		//If a back Edge has been detected then can only either pick 
		//
		if (verticesList[currVertex.adjacencyList[i] - 1].color == "gray")
		{
			//backedge 
			cycleDetector = 1;
			break;
		}
	}
								   
							   	
							   
							  // at this point all vertexes are grey
	currVertex.color = "black"; //labels the grey vertex to black
	time = time + 1; //increases time by 1 so the timestamping for the finished times can begin
	currVertex.fin = time; //sets the finished time to the correct time

	return cycleDetector;
}

vector <Vertex> Graph::BellmanFord(vector <Vertex> &verticesList, vector <Edge> edgeList, int sourceNode, int destinationNode)
{
	int infinite = 420420;
	int nil = 6969;

	//initalize the graph with pre-set values
	for (int i = 0; i < verticesList.size(); i++)
	{
		
		verticesList[i].distance = infinite;
		verticesList[i].parentId = nil;
	}
	verticesList[sourceNode - 1].distance = 0;

	//start the ctr at 0 for edgeList
	int edgeListCtr = 0;

	//for each vertex in the graph
	for (int i = 0; i < verticesList.size(); i++)
	{
		//for each edge thats connected to vertex i
		for (int j = 0; j < verticesList[i].adjacencyList.size(); j++)
		{
			//relax through that edge
			//minus 1 (x - 1) is needed because the index returned will be 1 index off

			relax( (edgeList[edgeListCtr].startingVertex - 1), (edgeList[edgeListCtr].endingVertex - 1), edgeList[edgeListCtr].edgeWeight, verticesList);
			edgeListCtr++;
		}

	}



	//output the last edge in the list


	for (int i = 0; i < edgeList.size(); i++)
	{

		//					//endingVertex//								//startingVertex//										//edgeWeight//
		if ( (verticesList[edgeList[i].endingVertex - 1].distance) > ( (verticesList[edgeList[i].startingVertex - 1].distance) + (edgeList[i].edgeWeight) ) )
		{
			return emptyList;
		}
	}

	return shortestPathList;
	
}




void Graph::relax(int startingVertex, int endingVertex, int edgeWeight, vector <Vertex> &verticesList)
{
	//if the currently labeled distance for x vertex is bigger than the path that is currently selected, then travel the path
	if (verticesList[endingVertex].distance > (verticesList[startingVertex].distance + edgeWeight) )
	{
		//travel the path and label the new reduced distance
		verticesList[endingVertex].distance = verticesList[startingVertex].distance + edgeWeight;

		//set the endingVertex's parent to the starting vertex
		verticesList[endingVertex].parentId = verticesList[startingVertex].id;

		shortestPathListCounter++;
		shortestPathList.resize(shortestPathListCounter);

		shortestPathList[shortestPathListCounter - 1] = verticesList[startingVertex];
	}
}



vector<Vertex> Graph::dagSP(vector<Vertex>& verticesList, vector<Edge> edgeList, int sourceNode, int destinationNode)
{
	 topoSortList = TopoSort(verticesList);

	int infinite = 420420;
	int nil = 6969;

	//initalize the graph with pre-set values
	for (int i = 0; i < verticesList.size(); i++)
	{

		topoSortList[i].distance = infinite;
		topoSortList[i].parentId = nil;
	}
	topoSortList[sourceNode - 1].distance = 0;

	//start the ctr at 0 for edgeList
	int edgeListCtr = 0;

	for (int i = 0; i < topoSortList.size(); i++)
	{

		for (int j = 0; j < verticesList[i].adjacencyList.size(); j++)
		{
			relax((edgeList[edgeListCtr].startingVertex - 1), (edgeList[edgeListCtr].endingVertex - 1), edgeList[edgeListCtr].edgeWeight, topoSortList);
			edgeListCtr++;
		}

		
	}

	return shortestPathList;
}


vector <Vertex> Graph::TopoSort(vector <Vertex> &verticesList) {
	topoDFS();
	
	vector <Vertex> topoSortedList;
	for (int i = 1; i <= verticesList.size(); i++)
	{
		topoSortedList.resize(i);
		
		topoSortedList[i - 1] = traverse->vertex;
		traverse = traverse->next;

	}

	return topoSortedList;

}

vector<Vertex> Graph::topoDFS() {

	//**************************************************************************************************************************//
	//This checks whether there are ANY negative edgeWeights because if there is, then can only run either DAG SP or BellmanFord//
	//**************************************************************************************************************************//

	//check if theres any negative edgeWeights
	for (int i = 0; i < edgeList.size(); i++)
	{
		//if the edgeWeight is negative once, then break out
		if (edgeList[i].edgeWeight < 0)
		{
			negativeEdgeWeightDetector = 2;
			break;
		}

	}

	//this loop can also be said that it's prepping the graph, getting ready to be searched?
	for (int u = 0; u < verticesList.size(); u++) {

		verticesList[u].color = "white"; //color is set to white, meaning it's undiscovered

										 //null value will be 420
		verticesList[u].parentId = 420; //do i need to create a nil object? like a nil vertex???

		time = 0; //timestamp for all the vertexes since they are undiscoverred
	}


	//At this point the graph is made with an empty graphg


	for (int u = 0; u < verticesList.size(); u++)
	{
		topoSortList.resize(u + 1);

		if (verticesList[u].color == "white") {
			 topoSortList = topoDFSVisit(verticesList, verticesList[u]);
		}
		
	}



	return verticesList;

}

vector <Vertex> Graph::topoDFSVisit(vector <Vertex> &verticesList, Vertex &currVertex) {

	Vertex newVertexSelected;

	time = time + 1; //when a vertex visits another vertex, it adds the current timestamp to 1, then 2, etc, for each visit

	currVertex.disc = time; //this sets the discovery stamp to 1, 2, etc

	currVertex.color = "gray"; //sets the color to gray to the vertex discovered


							   //for each vertex in the adj list...do stuff
	for (int i = 0; i < verticesList[currVertex.id - 1].adjacencyList.size(); i++) {

		//if the ajd vertex is undiscovered

		if (verticesList[currVertex.adjacencyList[i] - 1].color == "white") {

			//set the parent of the adj to the currVertex
			verticesList[currVertex.adjacencyList[i] - 1].parentId = currVertex.id;

			topoDFSVisit(verticesList, verticesList[currVertex.adjacencyList[i] - 1]); //explore again
		}
		
	}



	// at this point all vertexes are grey
	currVertex.color = "black"; //labels the grey vertex to black
	time = time + 1; //increases time by 1 so the timestamping for the finished times can begin
	currVertex.fin = time; //sets the finished time to the correct time

	createnode(currVertex);

	return verticesList;
}


void Graph::createnode(Vertex currVertex)
{
	Node *temp = new Node;
	temp->vertex = currVertex;
	temp->next = nullptr;
	if (head == nullptr)
	{
		traverse = temp;
		head = temp;
		tail = temp;
		temp->next = nullptr;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}


vector<Edge> Graph::dijkstras(vector<Vertex>& verticesList, vector<Edge> edgeList, int sourceNode, int destinationNode)
{
	int infinite = 420420;
	int nil = 6969;

	//initalize the graph with pre-set values
	for (int i = 0; i < verticesList.size(); i++)
	{
		
		verticesList[i].distance = infinite;
		verticesList[i].parentId = nil;
		queue[i] = verticesList[i];
	}
	verticesList[sourceNode - 1].distance = 0;

	//start the ctr at 0 for edgeList
	int edgeListCtr = 0;

	queue.resize(verticesList.size());

	while (queue.size() != 0)
	{

		/*for (int j = 0; j < verticesList[i].adjacencyList.size(); j++)
		{
			relax((edgeList[edgeListCtr].startingVertex - 1), (edgeList[edgeListCtr].endingVertex - 1), edgeList[edgeListCtr].edgeWeight, topoSortList);
			edgeListCtr++;
		}*/

	}

	return vector<Edge>();
}





void Graph::loadList(string fileName) {

	//first read in the first character in the line, that will be verticeList character
	// the : represents a delimiter to switch to reading in the characters to the adjList. 
	// the only issues would be to create some type of loops to see if you want to continue reading in more information froma  line until its done
	// spaces will need to be ignored, so reading in a line for example coud be " " + "8" as one part, and deleting the space from reading it in

	ifstream graphFile; //file object to read in file



	string vertexListInputString; //reference for reading in the input

	string adjEdgeInputString; //reference for the rest of the string that will be ready to get seperated

	int vertexListInput; //reference for reading in the input

	int adjEdgeInputInt;

	int vertexListCounter = 0; //a counter is used to increment the vertexList index, each vertex will have its own edge and vertice list. this allows the vertex to be incremented correctly

	int edgeListCounter = 0;



	//sentinel values//

	int infiniteValue = 9999;





	graphFile.open(fileName);

	if (graphFile.fail()) {
		cout << "Oops! file couldn't open." << endl;
	}

	while (!graphFile.eof())
	{
		int adjListCounter = 0;


		verticesList.resize(vertexListCounter + 1);

		getline(graphFile, vertexListInputString, ':');//keeps reading until it hits a colon, and stops

		vertexListInput = stoi(vertexListInputString); // converts the string value into an int 

		verticesList[vertexListCounter] = getNewVertice(vertexListInput); //adds the value into the vector

		getline(graphFile, adjEdgeInputString); //keeps reading until it hits the end of line character "\n

		adjEdgeInputString.erase(remove_if(adjEdgeInputString.begin(), adjEdgeInputString.end(), ::isspace), adjEdgeInputString.end()); // gets rid of white space in string

		if (adjEdgeInputString != "")
		{



			

			adjEdgeInputInt = stoi(adjEdgeInputString); // the adj and edge input into an int

			


																	  //while you are not at the end of line character, keep inserting into the edgeList and adjList
			for (int i = 0; i < adjEdgeInputString.length(); i++)
			{


				//if you are at an odd position, then read into the adj list, if you are at an even position, then read into the edgelist

				//even

				//Note, cannot use i for any insertion of data, have to use sepereate counters 
				if (((i + 1) % 2) == 0)
				{

					//need to createaa a new edge object
					//make one first, then add the weight to it

					Edge newEdge;

					//*******************************************************//
					//Determine whether or not there is a negative edgeWeight//
					//*******************************************************//


					//this finds if there is a '-' character in the string. if there is, then move by file reader by 1 to get the actual weight of the edge, then multiply it by -1, then remove the - from the string
					//deal with a negative edge
					if (adjEdgeInputString.at(i) == '-')
					{
						//attach the found negative number to a reference
						char negativeCharFinder = adjEdgeInputString.at(i + 1);

						// convert the char reference into an int
						int negativeIntFinder = negativeCharFinder - '0';

						//multiply it by -1
						negativeIntFinder = (negativeIntFinder * -1);

						//assign the -1 edgeWeight
						newEdge.edgeWeight = negativeIntFinder;

						newEdge.startingVertex = vertexListCounter + 1; //assigns the starting vertex which is the value in the vertexList at index vertexListCounter

						newEdge.endingVertex = verticesList[vertexListCounter].adjacencyList[adjListCounter - 1]; // assigns the ending vertex which is the value in the adjList at index adjListCounter

						//erases the - char
						adjEdgeInputString.erase(i, 1);

					}

					else {
						//deal with a positive edge
						newEdge.edgeWeight = adjEdgeInputString.at(i) - '0'; //grabs the edge and fills  edgeList[edgeListCounter
						newEdge.startingVertex = vertexListCounter + 1; //assigns the starting vertex which is the value in the vertexList at index vertexListCounter
																		//newEdge.endingVertex = adjEdgeInputString.at(i - 1) - '0';

						newEdge.endingVertex = verticesList[vertexListCounter].adjacencyList[adjListCounter - 1]; // assigns the ending vertex which is the value in the adjList at index adjListCounter
					}
					//purpose for counters to ensure that the entire list was checked twice 
					int checkSelfCounter = 0;
					int checkForDuplicateCounter = 0;

					//this for loop checks each edgeList[i] to see if edgeList[i] is the new edge, if it is then going to skip going through that edge
					for (int i = 0; i < edgeList.size(); i++)
					{
						if ((newEdge.edgeWeight == edgeList[i].edgeWeight) && (newEdge.startingVertex == edgeList[i].startingVertex) && (newEdge.endingVertex == edgeList[i].endingVertex))
						{
							checkSelfCounter++;
						}
						//iterate through the whole edgelist to see if itself is in there	
					}

					//this for loop checks each edgeList[i] to see if edgeList[i] is a duplicate, meaning that the starting vertex is == to the ending vertex, and the ending vertex is == to the starting vertex, which means its a duplicate 
					for (int i = 0; i < edgeList.size(); i++)
					{
						//itterate through whole edgelist to see if there is a duplcate in there
						if ((newEdge.edgeWeight == edgeList[i].edgeWeight) && (newEdge.startingVertex == edgeList[i].endingVertex) && (newEdge.endingVertex == edgeList[i].startingVertex))
						{
							checkForDuplicateCounter++;
						}
					}

					int isThereADuplcate = checkForDuplicateCounter + checkSelfCounter;

					if (isThereADuplcate == 0)
					{
						edgeList.resize(edgeListCounter + 1); //memory management 
						edgeList[edgeListCounter] = newEdge; //assign the new edge to edgeList[edgeListCounter]
						edgeListCounter++;
					}
				}
				//if both lists have been itterated and both conditions have been false the whole time, then add the new edge into the edgelist


				//even
				else
				{
					verticesList[vertexListCounter].adjacencyList.resize(adjListCounter + 1); //give the adjlist at the corresponding vertex a size of 20
					verticesList[vertexListCounter].adjacencyList[adjListCounter] = adjEdgeInputString.at(i) - '0';
					adjListCounter++;

				}


			}

		}

		vertexListCounter++;


	}
}