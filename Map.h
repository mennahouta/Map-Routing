#pragma once
#include<iostream>
using namespace std;

class Map
{
	//graph
public:
	Map(string fileName);
	friend class Query;
	~Map();
};
