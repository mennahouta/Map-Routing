#include"Map.h"
#include<chrono>

using namespace std::chrono;

vector<string> inputFiles(int testCase, vector<string> v) {
	string mp = "map", q = "queries", out = "output";
	switch(testCase)
	{
	case 1:
		for(char i = '1' ; i <= '5' ; i++) {
			v.push_back("[1] Sample Cases\\" + mp + i + ".txt");	// The Folder Path Here
			v.push_back("[1] Sample Cases\\" + q + i + ".txt");
			v.push_back("[1] Sample Cases\\" + out + i + ".txt");
		}
		break;
	case 2:
		v.push_back("[2] Medium Cases\\OLMap.txt");
		v.push_back("[2] Medium Cases\\OLQueries.txt");
		v.push_back("[2] Medium Cases\\OLOutput.txt");
		break;
	case 3:
		v.push_back("[3] Large Cases\\SFMap.txt");
		v.push_back("[3] Large Cases\\SFQueries.txt");
		v.push_back("[3] Large Cases\\SFOutput.txt");
		break;
	default:
		break;
	}
	return v;
}

int main() {
	
	 high_resolution_clock::time_point program_start = high_resolution_clock::now(); //Time when the Program started
	 
	 int totalExecutionTime;
	 do{
		 totalExecutionTime = 0;

		 vector <string> fileNames;
		 cout << "Map Routing:\n[1] Sample test cases\n[2] Medium test case\n[3] Large test case\n\nEnter your choice[1, 2, 3]: ";
		 int testCase;
     cin >> testCase;
		 if(testCase < 1 || testCase > 3) // Invalid input
			 return 0;
		 fileNames = inputFiles(testCase, fileNames);
		 for(int i = 0, counter = 1 ; i < fileNames.size() ; i += 3, counter++) { // Skip 3 files per iteration {map, query, output}
			 cout << "\nCase " << counter << ":\n";

			 Map M(fileNames[i]);

			 int queries; //number of queries
			 ld x, y;
			 pair<ld, ld> s, d; //source, destination
			 ld radius; //maximum walking radius
			 ifstream file;
			 file.open(fileNames[i+1]);
			 if (file.is_open()) {
				 file >> queries;
				 for (int i = 0; i < queries ; i++) {
					 file >> x >> y;
					 s = make_pair(x, y);

					 file >> x >> y;
					 d = make_pair(x, y);

					 file >> radius;
			
					 high_resolution_clock::time_point query1_time1 = high_resolution_clock::now(); //Time before query
					 M.solveQuery(s, d, radius);
					 high_resolution_clock::time_point query1_time2 = high_resolution_clock::now(); // Time after query
	
					 M.writeOutput();

					 auto query_duration = duration_cast<milliseconds>(query1_time2- query1_time1).count(); //Time per query
					 cout << query_duration << " ms" << endl << endl;
					 totalExecutionTime += query_duration;
				 }
				 file.close();
         
				 //high_resolution_clock::time_point total_time = high_resolution_clock::now(); //Time after all queries
				 //auto Total_duration = duration_cast<milliseconds>(total_time- program_start).count(); //Time of the whole program

				 cout << totalExecutionTime << " ms" <<  endl;
			 }
		 }

		 cout << "Do you wish to test another case (y/n)? ";
		 char choice; 
		 cin >> choice;
		 if(choice != 'y' && choice != 'Y')
			 break;

	 }while(true);
	 //system("pause");
	 return 0;
}