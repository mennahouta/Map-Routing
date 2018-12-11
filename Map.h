#pragma once
#include<iostream>
#include<vector>
#include<istream>
#include<ostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

typedef long double ld;
const int N = 2e5+5; //maximum # of nodes, not actually used anywhere

class Map
{
	//graph
	int n; //number of nodes 
	int m; //number of edges
	vector<pair<ld, ld>> nodes; //node[id] {X, Y}
	vector<vector<pair<int, pair<ld, ld>>>> g; // g[id1] {id2, {Length, Time}}

	vector<int> starts; //ids of possible start positions
	vector<int> ends; //ids of possible end positions

public:
	//query related data
	pair<double, double> source, destination;
	double maximumWalkingDist;

	Map(string fileName); //read input + create graph
	void viewMap();
	void solveQuery(pair<double, double>, pair<double, double>, double);
	void editMap();
	void restoreMap();
	//dijkstra (Eman)

	~Map();
};
