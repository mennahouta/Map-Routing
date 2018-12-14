#include "Map.h"

#define precision setprecision(2) << fixed
typedef pair<pair<ld, ld>, int> pairr;

Map::Map(string fileName) {
	// Open the filestream
	ifstream file;
	file.open(fileName);

	if(file.is_open()) {
		file >> n;			 // Read the first number in the file :: number of nodes
		nodes.resize(n + 5); // Set the nodes and the graph to have the the N nodes
		g.resize(n + 5);	 // and extra nodes -needed when pushing extra nodes later

		int id;
		ld x, y;
		for(int i = 0; i < n; i++) {
			file >> id >> x >> y;
			// set the value of the cell to the pair the was read
			nodes[id] = make_pair(x, y);
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

void Map::viewMap() {
	for (int i = 0; i < n; i++)
		cout << "Node " << i << ": " << nodes[i].first << ' ' << nodes[i].second << '\n';

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

void Map::solveQuery(pair<ld, ld> s, pair<ld, ld> d, ld r) {
	source = s;
	destination = d;
	maximumWalkingDist = r / 1000; //r is in meters, and the program uses kilometers, "division not multiplication"

	starts.clear();
	ends.clear();
	nodes_path.clear();

	editMap();
	pair<ld, ld> answer  = dijkstra(n, n+1);
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
		dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		if (dist <= maximumWalkingDist) {
			time = dist / 5; //walking speed = 5 km/h
			g[n].push_back(make_pair(i, make_pair(dist, time)));
			g[i].push_back(make_pair(n, make_pair(dist, time)));
			starts.push_back(i);
		}

		//checking if nodes[i] is a possible end position
		x2 = destination.first;
		y2 = destination.second;
		dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		if (dist <= maximumWalkingDist) {
			time = dist / 5;
			g[n + 1].push_back(make_pair(i, make_pair(dist, time)));
			g[i].push_back(make_pair(n + 1, make_pair(dist, time)));
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
  
    //removing the edges of the start/end nodes from the graph
	g[n].clear();
	g[n + 1].clear();
}

pair<ld,ld> Map::dijkstra(int s, int dest) {
	vector<ld> minimum_time(n + 2); //vector that has minimum time from source to every vertex
	vector<ld> distance(n + 2); //vector of distance from source to each node
	vector<int> parent_node(n + 2);
	vector<bool> visited(n + 2);

	for (int i = 0; i < n + 2; i++) //initialize time to infinity (long double max)
		minimum_time[i] = LDBL_MAX; 

	minimum_time[s] = 0; //time to source equals 0

	priority_queue<pairr, vector<pairr>, greater<pairr> >pq; //minimum heap
	pq.push(make_pair(make_pair(0, 0), s)); //push time, length, node of source node
	parent_node[s] = -1; //parent of source doesn't exist
	while (!pq.empty()) {
		ld time = pq.top().first.first;
		ld length = pq.top().first.second;
		int node = pq.top().second;

		pq.pop();

		if (visited[node])
			continue;

		visited[node] = 1;

		if (node == dest) //stop if destination is reached
			break;

		for (int i = 0; i < g[node].size(); i++) { //traverse + relax children of current node
			int child_node = g[node][i].first;
			ld child_distance = g[node][i].second.first;
			ld child_time = g[node][i].second.second;

			if (visited[child_node])
				continue;

			if (minimum_time[child_node] > minimum_time[node] + child_time) {
				minimum_time[child_node] = minimum_time[node] + child_time;
				distance[child_node] = distance[node] + child_distance;
				pq.push(make_pair(make_pair(minimum_time[child_node], distance[child_node]), child_node));
				parent_node[child_node] = node; //update parent of this node
			}
		}
	}

	build_path(parent_node, dest);

	int startNode = nodes_path[1];	// The id of the start node
	int startNodeIND;				// The index of the start node
	for(int i=0 ; i < g[n].size() ; i++) {
		if(startNode == g[n][i].first) {
			startNodeIND = i;	// The actual index in the graph connection
			break;
		}
	}
	int endNode = nodes_path[nodes_path.size() - 2];	// The id of the end node
	int endNodeIND;										// The index of the end node
	for(int i=0 ; i < g[n + 1].size() ; i++) {
		if(endNode == g[n + 1][i].first) {
			endNodeIND = i;	// The actual index in the graph connection
			break;
		}
	}

	ld walkingToStartDist = g[n][startNodeIND].second.first;
	ld walkingToEndDist = g[n + 1][endNodeIND].second.first;
	ld totalWalkingDist = walkingToStartDist + walkingToEndDist;
	ld vehicleDist = distance[endNode] - distance[startNode];
	ld totalDistance = totalWalkingDist + vehicleDist;

	ld totalTime = minimum_time[dest] * 60;

	pair<ld, ld> answer = make_pair(totalTime, totalDistance);
  
	cout << "Total time = " << precision << answer.first << " mins" << endl;
	cout << "Total distance: " << precision << answer.second << " km" << endl;
	cout << "Walking distance = " << precision << totalWalkingDist << " km"<< endl;
	cout << "Vehicle distance = " << precision << vehicleDist << " km " << endl << endl;

	return answer;
}

void Map::build_path(vector<int> parents, int destination_node) {
	int node = parents[destination_node];
	nodes_path.push_front(destination_node);
	while (node != -1) {
		nodes_path.push_front(node);
		node = parents[node];
	}

	//viewing path
	cout << "Path: source, ";
	for (int i = 1; i < nodes_path.size() - 1; i++)
		cout << nodes_path[i] << ", ";
	cout << "destination.";
		
	cout << endl;
}

Map::~Map() {}
