#include "Map.h"

Map::Map(string fileName)
{
	//fileName += ".txt";

	// Open the filestream
	ifstream file;
	file.open(fileName);

	if(file.is_open()) {
		file >> n; // Read the first number in the file :: number of nodes
		nodes.resize(n + 5); // Set the nodes and the graph to have the the N nodes
		g.resize(n + 5);	// and extra nodes -needed when pushing extra nodes later
		int id;
		ld x, y;
		for(int i = 0; i < n; i++) {
			file >> id >> x >> y;
			// set the value of the cell to the pair the was read
			nodes[id] = {x, y};
		}

		file >> m; // Read the number of edges
		int u, v;
		ld length, speed, time;
		for(int i = 0; i < m; i++) {
			file >> u >> v >> length >> speed;

			// Calculate the time -> the weight needed in the problem
			time = length / speed;

			// Undirected graph, hence the pushing in both nodes
			g[u].push_back({v, {length, time}});
			g[v].push_back({u, {length, time}});
		}
		file.close();
	}
}

void Map::viewMap(){
	for (int i = 0; i < n; i++) {
		cout << "Node " << i << ": " << nodes[i].first << ' ' << nodes[i].second << '\n';
	}
	cout << "\nConnections between: \n";
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (int j = 0; j < g[i].size(); j++) {
			cout << g[i][j].first << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

void Map::solveQuery(pair<double, double> d, pair<double, double> s, double r) {
	destination = d;
	source = s;
	maximumWalkingDist = r * 1000; //r is in meters, and the program uses kilometers

	editMap();
	//call dijkstra
	restoreMap();
}

void Map::editMap() {
	nodes[n] = source; 
	nodes[n + 1] = destination;

	ld x1, y1, x2, y2, dist, time;
	for (int i = 0; i < n; i++) {
		x1 = nodes[i].first;
		y1 = nodes[i].second;

		//checking if nodes[i] is a possible start position
		x2 = source.first;
		y2 = source.second;
		dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
		dist = sqrt(dist);
		if (dist <= maximumWalkingDist) {
			time = dist / 5;
			g[n].push_back({i, {dist, time}});
			g[i].push_back({n, {dist, time}});
			starts.push_back(i);
		}

		//checking if nodes[i] is a possible end position
		x2 = destination.first;
		y2 = destination.second;
		dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
		dist = sqrt(dist);
		if (dist <= maximumWalkingDist) {
			time = dist / 5;
			g[n + 1].push_back({i, {dist, time}});
			g[i].push_back({n + 1, {dist, time}});
			ends.push_back(i);
		}
	}
}

void Map::restoreMap() {

	//removing edges from source to possible starts
	for (int nodeID : starts) {
		g[nodeID].pop_back();
	}


	//removing edges from possible ends to destination
	for (int nodeID : ends) {
		g[nodeID].pop_back();
	}

	//removing source and destination from the vector of nodes
	nodes.pop_back();
	nodes.pop_back();
}

Map::~Map() {}