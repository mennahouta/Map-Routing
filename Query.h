#pragma once
#include<iostream>

using namespace std;

class Query
{
	pair<double, double> source, destination;
	double maximumWalkingDist;

public:
	Query(pair<double, double> s, pair<double, double> d, double R) : source(s), destination(d), maximumWalkingDist(R) {}
	void solveQuery() {

	}
	~Query();
};
