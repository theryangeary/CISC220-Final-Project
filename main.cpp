#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <stack>
#include "Graph.h"
#include "Coordinates.h"

using namespace std;

float distance(Coordinates* c1, Coordinates* c2) {
	double PI = 4.0 * atan(1.0);

	double dlat1 = c1->latitude * (PI/180);
	double dlat2 = c2->latitude * (PI/180);
	double dlon1 = c1->longitude * (PI/180);
	double dlon2 = c2->longitude * (PI/180);

	cout << dlat1 << ", " << dlon1 << " to " << dlat2 << ", " <<dlon2 << endl;
	cout << c1->latitude << ", " << c1->longitude << " to " << c2->latitude << ", " << c2->longitude<< endl;

	double delLon = dlon1 - dlon2;
	double delLat = dlat1 - dlat2;

	double aHarv = pow(sin(delLat/2.0),2.0)+cos(dlat1)*pow(sin(delLon/2),2);
	double cHarv = 2*atan2(sqrt(aHarv), sqrt(1.0-aHarv));

	const double earthRadius = 3963.19;

	double distance = earthRadius*cHarv;

	return distance;
}


int findShortestPath(Graph & g) {
	return pow(2, 32) - 1;
}

int main(int argc, char **argv) {
	cout.precision(8);
	cout << argv[1] << endl;
	cout << argv[2] << endl;

	Graph g;
	readDirectedGraphFromFile(g, argv[1]);
	cout << g.toString();

	unordered_map<std::string, Coordinates*> locations;
	
	readUnorderedMapFromFile(locations, argv[2]);
	for (auto iter = locations.begin(); iter != locations.end(); ++iter) {
		cout << iter->first << ": " << iter->second->toString();
	}

	cout << "The class schedule that requires the minimum distance travelled is " << findShortestPath(g) << endl;

	return 0;
}
