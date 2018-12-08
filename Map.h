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
public:
	int n; //number of nodes 
	int m; //number of edges
	vector<pair<ld, ld>>node; //node[id] {X, Y}
	vector<vector<pair<int, pair<ld, ld>>>>g; // g[id1] {id2, {Length, Time}}

	Map(string fileName); //read + create
	friend class Query;
	~Map();
};
