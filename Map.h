#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<istream>
#include<ostream>
#include<sstream>
#include<fstream>
#include<string>
#include<queue>
#include<functional> //for max priority queue
using namespace std;

typedef long double ld;

class Map
{
	//graph
	int n; //number of nodes
	int m; //number of edges
	vector<pair<ld, ld>> nodes; //node[id] {X, Y}
	vector<vector<pair<int, pair<ld, ld>>>> g; // g[id1] {id2, {Length, Time}}

	vector<int> starts; //ids of possible start positions
	vector<int> ends; //ids of possible end positions

	deque<int>nodes_path; // path of one destination node per query

public:
	//query related data
	pair<ld, ld> source, destination;
	ld maximumWalkingDist;

	Map(string fileName); //read input + create graph
	void viewMap();
	void solveQuery(pair<ld, ld>, pair<ld, ld>, ld);
	void editMap();
	void restoreMap();
	pair<ld, ld>dijkstra(int,int);
	void build_path(vector<int>, int);
	~Map();
};
