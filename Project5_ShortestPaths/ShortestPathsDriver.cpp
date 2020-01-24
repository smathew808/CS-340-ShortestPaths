#include <iostream>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include "ShortestPaths.h"


//Name: Sean Mathews
//Class: CS340
//Instructor: Ercal
//Project: ShortestPaths
using namespace std;

char getFileName(); 
int getSourceNode();
int getDestinationNode();

int main() {

	string fileString; //this string will be the value to open the correct file
	char fileChoice;

	int sourceNodeChoice;
	int destinationNodeChoice;

	vector <Vertex> winningSet;
	
	Graph graph; //this creates the graph object that will store everything that is a graph 

	ifstream graphFile; //file to be opened

	ofstream outputFile; //this is the reference when creating the output file

	fileChoice = getFileName();

	if (fileChoice == '1') {
		fileString = "graphin_Fig1.txt";
	}

	else if (fileChoice == '2') {
		fileString = "graphin_Fig2.txt";
	}

	else if (fileChoice == '4') {
		fileString = "graphin_Fig4.txt";
	}
	else if (fileChoice == '5') {
		fileString = "graphin_Fig5.txt";
	}

	graph.loadList(fileString);


	int AlgDecider = graph.DFS();
	
	//dag sp
	if (AlgDecider == 2)
	{
		cout << "there are  no cycles, indicating a DAG" << endl;
		sourceNodeChoice = getSourceNode();
		destinationNodeChoice = getDestinationNode();

		winningSet = graph.dagSP(graph.verticesList, graph.edgeList, sourceNodeChoice, destinationNodeChoice);
	}
	
	//dijkstras
	if (AlgDecider == 1)
	{
		cout << "there is a cycle but no negative edgeWeights" << endl;
		sourceNodeChoice = getSourceNode();
		destinationNodeChoice = getDestinationNode();

		//winningSet = graph.dijkstras(graph.verticesList, graph.edgeList, sourceNodeChoice, destinationNodeChoice);
	}

	//bellmanford
	if (AlgDecider == 3)
	{
		cout << "There is a cycle and negative edgeWeights" << endl;
		sourceNodeChoice = getSourceNode();
		destinationNodeChoice = getDestinationNode();

		
		winningSet = graph.BellmanFord(graph.verticesList, graph.edgeList, sourceNodeChoice, destinationNodeChoice);

		//detects negativeWeight cycle
		if (winningSet.size() == 0)
		{
			//cout << "A negative weight cycle exists" << endl;
		}

		else
		{
			for (int i = winningSet.size() - 1; i >= 0; i--)
			{
				cout << "The shortest path is read from left to right, keep reading it from left to right until you hit the end of the list" << endl;
				cout << "The very first starting index is your source node and the last ending vertex is the destination\n\n" << endl;
				
				int pathLength = 0;

				for (int i = 0; i < winningSet.size(); i++)
				{
					pathLength =  pathLength;
				}

				cout << "The length of the path is: " << pathLength << endl;
			}
		}

	}

	


	system("pause");

	return 0;
}

char getFileName() {
	char fileChoice;
	cout << "please pick a file to run a shortestPaths Alg" << endl;
	cout << "1) graphin_Fig1" << endl;
	cout << "2) graphin_Fig2" << endl;
	cout << "4) graphin_Fig4" << endl;
	cout << "5) graphin_Fig5" << endl;


	cin >> fileChoice;
	return fileChoice;

}

int getSourceNode() {
	int sourceNodeChoice;

	cout << "\nplease pick a source node in the graph" << endl;

	cin >> sourceNodeChoice;
	return sourceNodeChoice;

}

int getDestinationNode() {
	int sourceNodeChoice;

	cout << "\nplease pick a destination node in the graph" << endl;

	cin >> sourceNodeChoice;
	return sourceNodeChoice;

}