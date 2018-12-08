#include<iostream>
#include"Map.h"
#include"Query.h"
using namespace std;
int main(){
	 Map M("map1");
	 // A temporary code to access and view the data
	 /* 
	 for(int i=0 ; i < M.n ; i++){
		 cout << "Node " << i << ": " << M.node[i].first << ' ' << M.node[i].second << '\n';
	 }
	 cout << "\nConnections between: \n"; 
	 for(int i=0 ; i < M.n ; i++){
		 cout << i << ": ";
		 for(int j=0 ; j < M.g[i].size() ; j++){
			 cout << M.g[i][j].first << ' ';
		 }
		 cout << '\n';
	 }
	 */
 return 0;
}