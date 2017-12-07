#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <stack>
#include "Graph.h"
#include "Coordinates.h"
#include "CourseSection.h"

using namespace std;

float distance(Coordinates* c1, Coordinates* c2) {
	double PI = 4.0 * atan(1.0);

	double dlat1 = c1->latitude * (PI/180);
	double dlat2 = c2->latitude * (PI/180);
	double dlon1 = c1->longitude * (PI/180);
	double dlon2 = c2->longitude * (PI/180);

	double delLon = dlon1 - dlon2;
	double delLat = dlat1 - dlat2;

	double aHarv = pow(sin(delLat/2.0),2.0)+cos(dlat1)*pow(sin(delLon/2),2);
	double cHarv = 2*atan2(sqrt(aHarv), sqrt(1.0-aHarv));

	const double earthRadius = 3963.19;

	double distance = earthRadius*cHarv;

	return distance;
}


bool createDirectedGraph(Graph & g, unordered_map<std::string, Coordinates*> locations, unordered_map<std::string, CourseSection*> courseSections) {
	for (auto it : courseSections) {
		g.vertices[it.first] = new Vertex(g.vertices.size(), it.first);		
	}
	
	for (auto v : g.vertices) {
		for (auto otherV : g.vertices) {
			if (courseSections[v.second->label]->course !=
			    courseSections[otherV.second->label]->course &&
			    courseSections[otherV.second->label]->startsAfter(
				    courseSections[v.second->label])) {
				v.second->edges.push_back(new Edge(v.second, otherV.second, distance(
								locations[courseSections[v.second->label]->location], locations[courseSections[otherV.second->label]->location])));
			}
			if (otherV.second->label == v.second->label) {
				cout << "We got one" << endl;	
			}
		}
	}
}

int findShortestPath(Graph & g) {
	return pow(2, 32) - 1;
}

int main(int argc, char **argv) {
	cout.precision(8);
	cout << argv[1] << endl;
	cout << argv[2] << endl;

	Graph g;
	// turn this into a graph using the locations and courseSections hash maps below

	unordered_map<std::string, Coordinates*> locations;
	
	readUnorderedMapFromFile(locations, argv[1]);
	for (auto iter = locations.begin(); iter != locations.end(); ++iter) {
		cout << iter->first << ": " << iter->second->toString();
	}

	unordered_map<std::string, CourseSection*> courseSections;	
	readCourseSectionMapFromFile(courseSections, argv[2]);

	for (auto iter = courseSections.begin(); iter != courseSections.end(); ++iter) {
		cout << iter->first << ": " << iter->second->toString() << endl;
	}

	createDirectedGraph(g, locations, courseSections);
	

	cout << g.toString() << endl;

	cout << "The class schedule that requires the minimum distance travelled is " << findShortestPath(g) << endl;

	return 0;
}
