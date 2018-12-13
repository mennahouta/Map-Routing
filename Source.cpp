#include"Map.h"
#include<chrono>

using namespace std::chrono;

int main(){
	
	high_resolution_clock::time_point program_start = high_resolution_clock::now(); //Time when the Program started
	 Map M("map3.txt");
	 //M.viewMap();

	 int q; //number of queries
	 ld x, y;
	 pair<ld, ld> s, d; //source, destination
	 ld r; //maximum walking radius
	 ifstream file;
	 file.open("queries3.txt");
	 if (file.is_open()) {
		 file >> q;
		 for (int i = 0; i < q; i++) {
			 file >> x >> y;
			 s = {x, y};
			 //cout << x << ' ' << y << ' ';

			 file >> x >> y;
			 d = {x, y};
			 //cout << x << ' ' << y << ' ';

			 file >> r;
			 //cout << r << endl;
			 high_resolution_clock::time_point query1_time1 = high_resolution_clock::now(); //Time before query
			 M.solveQuery(s, d, r);
			 high_resolution_clock::time_point query1_time2 = high_resolution_clock::now(); // Time after query
			 auto query_duration = duration_cast<milliseconds>(query1_time2- query1_time1).count(); //Time per query
			 cout << "Execution time = " << query_duration << " ms" << endl << endl;
		 }
		 file.close();
		 high_resolution_clock::time_point total_time = high_resolution_clock::now(); //Time after all queries
		 auto Total_duration = duration_cast<milliseconds>(total_time- program_start).count(); //Time of the whole program
		 cout << "Total Duration = " << Total_duration << " ms" <<  endl;
	 }
	 system("pause");
	 return 0;
}