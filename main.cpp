#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <stack>
#include "Graph.h"
#include "Coordinates.h"

using namespace std;

int findShortestPath(Graph & g) {
	return pow(2, 32) - 1;
}

int main(int argc, char **argv) {
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
