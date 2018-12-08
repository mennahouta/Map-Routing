#include"Map.h"

int main(){
	 Map M("map1.txt");
	 M.viewMap();

	 int q; //number of queries
	 double x, y;
	 pair<double, double> s, d; //source, destination
	 double r; //maximum walking radius
	 ifstream file;
	 file.open("queries1.txt");
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

			 M.solveQuery(s, d, r);
		 }
		 file.close();
	 }

	 return 0;
}