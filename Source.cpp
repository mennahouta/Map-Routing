#include"Map.h"
#include<chrono>

using namespace std::chrono;

vector<string> inputFiles(int testCase, vector<string> fileNames);

void checkOutput(string filename, string ourfilename);

int main() {
	int timeOfAllQueries;
	 do{
		 vector <string> fileNames;
		 cout << "Map Routing:\n[1] Sample test cases\n[2] Medium test case\n[3] Large test case\n\nEnter your choice[1, 2, 3]: ";
		 int testCase;
		 cin >> testCase;
		 if(testCase < 1 || testCase > 3) // Invalid input
			 return 0;
		 fileNames = inputFiles(testCase, fileNames);

		 timeOfAllQueries = 0;
		 for(int i = 0, counter = 1 ; i < fileNames.size() ; i += 3, counter++) { // Skip 3 files per iteration {map, query, output}
			 cout << "\nMap " << counter << ":\n";

			 high_resolution_clock::time_point program_start = high_resolution_clock::now(); //Time when this map started

			 Map M(fileNames[i]);

			 int queries; //number of queries
			 ld x, y;
			 pair<ld, ld> s, d; //source, destination
			 ld radius; //maximum walking radius
			 ifstream file;
			 file.open(fileNames[i+1]);
			 
			 ofstream outputFile;
			 int position = fileNames[i+2].find('\\') + 1;
			 string ourFileName = fileNames[i+2].substr(position); // Just retrieve the filename as the original without the folder's path
			 outputFile.open(ourFileName);

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

					 //M.writeOutput();
					 M.writeOutputFile(outputFile);

					 auto queryDuration = duration_cast<milliseconds>(query1_time2- query1_time1).count(); //Time per query
					 timeOfAllQueries += queryDuration;
					 //cout << query_duration << " ms" << endl << endl;

					 //outputFile << query_duration << " ms" << endl << endl;
				 }
				 file.close();
				 high_resolution_clock::time_point total_time = high_resolution_clock::now(); //Time after all queries
				 auto totalExecutionTime = duration_cast<milliseconds>(total_time - program_start).count(); //Time of the current map
				 cout << "Total time of execution: " << totalExecutionTime << " ms" <<  endl;
				 outputFile << timeOfAllQueries << " ms\n\n";
				 outputFile << totalExecutionTime << " ms\n";
			 }
			 outputFile.close();

			 checkOutput(fileNames[i + 2], ourFileName); //checks right or wrong answer per query
				 
		 }
		 cout << "\nDo you wish to test another case (y/n)? ";
		 char choice; 
		 cin >> choice;
		 if(choice != 'y' && choice != 'Y')
			 break;
		 cout << endl;
	 }while(true);
	 //system("pause");
	 return 0;
}

vector<string> inputFiles(int testCase, vector<string> fileNames) {
	string mp = "map", q = "queries", out = "output";
	switch (testCase) {
	case 1:
		for (char i = '1'; i <= '5'; i++) {
			fileNames.push_back("[1] Sample Cases\\" + mp + i + ".txt");	// The Folder Path Here
			fileNames.push_back("[1] Sample Cases\\" + q + i + ".txt");
			fileNames.push_back("[1] Sample Cases\\" + out + i + ".txt");
		}
		break;
	case 2:
		fileNames.push_back("[2] Medium Cases\\OLMap.txt");
		fileNames.push_back("[2] Medium Cases\\OLQueries.txt");
		fileNames.push_back("[2] Medium Cases\\OLOutput.txt");
		break;
	case 3:
		fileNames.push_back("[3] Large Cases\\SFMap.txt");
		fileNames.push_back("[3] Large Cases\\SFQueries.txt");
		fileNames.push_back("[3] Large Cases\\SFOutput.txt");
		break;
	default:
		break;
	}
	return fileNames;
}

void checkOutput(string filename, string ourfilename) { // The output file
	ifstream correct, ours;
	correct.open(filename);
	ours.open(ourfilename);

	if (correct.is_open() && ours.is_open()) {
		int queryNum = 0, correctQueries = 0;

		ours.ignore();
		correct.ignore();

		string correctPath;
		getline(correct, correctPath);

		string path;
		getline(ours, path);

		while (!correct.eof() && !ours.eof()) {

			bool answer = true;

			if (path != correctPath) {
				cout << "Our path: " << path << endl;
				cout << "Correct path: " << correctPath << endl;
				answer = false;
			}

			ours.ignore();
			correct.ignore();

			string correctTime, Time;
			getline(correct, correctTime);
			getline(ours, Time);


			if (correctTime != Time) {
				cout << "Wrong total time\n";
				cout << "Time = " << Time << "\nActual time = " << correctTime << endl;
				answer = false;
			}


			string walking, vehicle, total, correctWalking, correctVehicle, correctTotal;

			correct.ignore();
			getline(correct, correctVehicle);

			correct.ignore();
			getline(correct, correctWalking);

			correct.ignore();
			getline(correct, correctTotal);

			ours.ignore();
			getline(ours, vehicle);

			ours.ignore();
			getline(ours, walking);

			ours.ignore();
			getline(ours, total);

			if (walking != correctWalking) {
				cout << "Wrong walking distance\n";
				cout << "Walking distance =  " << walking << "\nActual walking distance =  " << correctWalking << endl;
				answer = false;
			}

			if (vehicle != correctVehicle) {
				cout << "Wrong vehicle distance\n";
				cout << "Vehicle distance = " << vehicle << "\nActual vehicle distance " << correctVehicle << endl;
				answer = false;
			}

			if (total != correctTotal) {
				cout << "Wrong total distance\n";
				cout << "Total distance = " << total << "\nActual total distance =  " << correctTotal << endl;
				answer = false;
			}
			if (answer)
				correctQueries++;
			else
				cout << "\nQuery " << queryNum << " is wrong!!!!\n";
			queryNum++;

			string emptyy;
			getline(ours, emptyy);
			getline(correct, emptyy);

			ours.ignore();
			correct.ignore();

			string correctPath;
			getline(correct, correctPath);

			string path;
			getline(ours, path);

			if (path[path.size() - 1] == 's')
				break;
		}
		cout << correctQueries << " out of " << queryNum << " queries are correct!\n";
		ours.close();
		correct.close();
		return;
	}
	cout << "\nSomething went wrong with the files\n";
}
