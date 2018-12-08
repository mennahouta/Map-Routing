#include "Map.h"

Map::Map(string fileName)
{
	//fileName += ".txt";

	// Open the filestream
	ifstream file;
	file.open(fileName);

	if(file.is_open())
	{
		file >> n; // Read the first number in the file :: number of nodes
		node.resize(n + 5); // Set the nodes and the graph to have the the N nodes
		g.resize(n + 5);	// and extra nodes -needed when pushing extra nodes later
		for(int i = 0; i < n; i++)
		{
			int id;
			ld x, y;
			file >> id >> x >> y;
			// set the value of the cell to the pair the was read
			node[id] = make_pair(x, y);
		}

		file >> m; // Read the number of edges
		for(int i = 0; i < m; i++)
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

void Map::viewMap(){
	for (int i = 0; i < n; i++) {
		cout << "Node " << i << ": " << node[i].first << ' ' << node[i].second << '\n';
	}
	cout << "\nConnections between: \n";
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (int j = 0; j < g[i].size(); j++) {
			cout << g[i][j].first << ' ';
		}
		cout << '\n';
	}
}

void Map::solveQuery(pair<double, double> d, pair<double, double> s, double r) {
	destination = d;
	source = s;
	maximumWalkingDist = r;

	//CALL starts/ends + add nodes
	//CALL dijkstra
	//CALL remover nodes
}

Map::~Map()
{
}