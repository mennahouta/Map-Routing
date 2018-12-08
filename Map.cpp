#include "Map.h"

Map::Map(string fileName)
{
	fileName += ".txt";

	// Open the filestream
	ifstream file;
	file.open(fileName.c_str());

	if(file.is_open())
	{
		file >> n; // Read the first number in the file :: number of nodes
		node.resize(n + 5); // Set the nodes and the graph to have the the N nodes
		g.resize(n + 5);	// and extra nodes -needed when pushing extra nodes later
		for(int i=0 ; i < n ; i++)
		{
			int id; ld x, y;
			file >> id >> x >> y;
			// set the value of the cell to the pair the was read
			node[id] = make_pair(x, y);
		}

		file >> m; // Read the number of edges
		for(int i=0 ; i < m ; i++)
		{
			int u, v; ld length, speed;
			file >> u >> v >> length >> speed;
			// Calculate the time -> the weight needed in the problem
			ld time = length / speed;
			// Undirected graph, hence the pushing in both nodes
			g[u].push_back(make_pair(v, make_pair(length, time)));
			g[v].push_back(make_pair(u, make_pair(length, time)));
		}
		file.close();
	}
}

Map::~Map()
{
}