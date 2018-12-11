#include"Map.h"

int main(){
	 Map M("map3.txt");
	 M.viewMap();

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

			 M.solveQuery(s, d, r);
		 }
		 file.close();
	 }
	 system("pause");
	 return 0;
}