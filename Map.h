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
#include<functional> //for greater<> in priority queue defintion 
using namespace std;

typedef long double ld;

class Map
{
	//graph
	int n; //number of nodes
	int m; //number of edges
	vector<pair<ld, ld>> nodes; //node[id] {X, Y}
	vector<vector<pair<int, pair<ld, ld>>>> g; // g[id1] {id2, {Length, Time}}

	vector<pair<int, ld>> starts; //ids of possible start positions + walking distance to them
	vector<pair<int, ld>> ends;   //ids of possible end positions + walking distance from them

	deque<int>nodes_path; // path of one destination node per query

	ld walkingToStartDist;
	ld walkingToEndDist;

	ld time;	 //final time from source to all other vertices after performing Dijkstra
	ld distance; //final distance from source to all other vertices after performing Dijkstra 
	ld vehicleDist;
public:
	//query related data
	pair<ld, ld> source, destination;
	ld maximumWalkingDist;

	Map(string fileName); //read input + create graph
	void viewMap();
	void solveQuery(pair<ld, ld>, pair<ld, ld>, ld);
	void editMap();
	void restoreMap();
	void dijkstra(int, int);
	void build_path(vector<int>, int);
	void writeOutput(); //view output on console
	void writeOutputFile(ofstream&);
	~Map();
};
