#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <stack>
#include "Graph.h"

using namespace std;

int findShortestPath(Graph & g) {
	return pow(2, 32) - 1;
}

int main(int argc, char **argv) {
	cout << argv[1] << endl;
	
	Graph g;
	readDirectedGraphFromFile(g, argv[1]);
	cout << g.toString();

	cout << "The class schedule that requires the minimum distance travelled is " << findShortestPath(g) << endl;

	return 0;
}
