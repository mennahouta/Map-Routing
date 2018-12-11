#include "Map.h"
#include<queue>
#include <functional> //for the greater in priority queue
typedef pair<pair<ld, ld>, int>pairr;
using namespace std; 

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
	pair<ld,ld> answer  = dijkstra(n,n+1);
	cout << "Source is " << n << " and destination is " << n + 1 << endl;
	cout << "Shortest time between both is " << answer.first << " and distance between then equal " << answer.second << endl;
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
}

pair<ld,ld> Map::dijkstra(int s, int dest)
{
	vector<double>minimum_time(g.size() + 1); //vector that has minimum time from source to every vertex
	vector<double>distance(g.size() + 1);//vector of distance from source to each node
	vector<int>parent_node(g.size() + 1);
	vector<bool>visited(minimum_time.size() + 1);

	for (int i = 0; i < minimum_time.size(); i++)//initialize time to infinity
		minimum_time[i] = 1e12;

	minimum_time[s] = 0; //time to source equal 0

	priority_queue<pairr, vector<pairr>, greater<pairr> >pq; //minimum heap
	pq.push({{ 0,0 }, s}); //push time, length, node of source node
	parent_node[s] = -1; //parent of source doesn't exist 
	while (!pq.empty())
	{
		ld time = pq.top().first.first;
		ld length = pq.top().first.second;
		int node = pq.top().second;
		
		pq.pop();
		visited[node] = 1;

		for (int i = 0; i < g[node].size(); i++) //add children of current node
		{
			int child_node = g[node][i].first;
			ld child_distance = g[node][i].second.first;
			ld child_time = g[node][i].second.second;

			if (visited[child_node])
				continue;

			if (minimum_time[child_node] > minimum_time[node] + child_time)
			{
				minimum_time[child_node] = minimum_time[node] + child_time;
				distance[child_node] = distance[node] + child_distance;
				pq.push({ {minimum_time[child_node],distance[child_node]},child_node });
				parent_node[child_node] = node; //update parent of the this node 
			}
		}
	}

	build_path(parent_node, dest);
	pair<ld, ld>answer = { minimum_time[dest]*60,distance[dest]};
	return answer;
}

void Map::build_path(vector<int>parents, int destination_node)
{
	nodes_path.clear();
	nodes_path.resize(0);

	int node = parents[destination_node];
	nodes_path.push_front(destination_node);
	while (node != -1)
	{
		nodes_path.push_front(node);
		node = parents[node];
	}
}
Map::~Map() {}
