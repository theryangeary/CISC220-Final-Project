#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <algorithm>
#include <stack>
#include "Graph.h"
#include "Coordinates.h"
#include "CourseSection.h"

#define NUM_COURSES_PER_SEMESTER 5

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

	double result = earthRadius*cHarv;
	return fabs(result);
}

float distanceBetweenBuildings(
		string building1, 
		string building2, 
		unordered_map<string, Coordinates*> locations) {
	//cout << distance(locations[building1], locations[building2]) << endl;
	return distance(locations[building1], locations[building2]);
}

bool createDirectedGraph(
		Graph & g, 
		unordered_map<std::string, Coordinates*> locations, 
		unordered_map<std::string, CourseSection*> courseSections) {
	for (auto it : courseSections) {
		g.vertices[it.first] = new Vertex(g.vertices.size(), it.first);		
	}
	
	for (auto v : g.vertices) {
		for (auto otherV : g.vertices) {
			if (courseSections[v.second->label]->course !=
			    courseSections[otherV.second->label]->course &&
			    courseSections[otherV.second->label]->startsAfter(
				    courseSections[v.second->label])) {
				v.second->edges.push_back(
						new Edge(
							v.second, 
							otherV.second, 
							distance(
								locations[courseSections[v.second->label]->location], 
								locations[courseSections[otherV.second->label]->location])));
			}
		}
	}
}

bool isInside(string str, char c)
{
	return str.find(c) != std::string::npos;
}

string scheduleToString(vector<string> & classesInThisSchedule);

float findPathLength(
		vector<string> & classesInThisSchedule, 
		unordered_map<string, Coordinates *> locations, 
		unordered_map<string, CourseSection *> courseSections, 
		string placeOfResidence) {
	float totalDistance = 0.0;
	char currentDay = 'M'; //;
	string currentLocation = placeOfResidence;
	while (currentDay != 'S') {
		for (auto courseSection : classesInThisSchedule) {
			//if (courseSections[courseSection]->days[0] != currentDay) {
			//	totalDistance += distanceBetweenBuildings(
			//			placeOfResidence, 
			//			courseSections[courseSection]->location, 
			//			locations);
			//}
			//cout << "distance from " << currentLocation << " to " << courseSections[courseSection]->location << ": " << distanceBetweenBuildings(
			//		currentLocation,
			//		courseSections[courseSection]->location,
			//	locations)
//<< endl;
			if (isInside(courseSections[courseSection]->days, currentDay)) {
				totalDistance += distanceBetweenBuildings(
					currentLocation,
					courseSections[courseSection]->location,
				locations);
				currentLocation = courseSections[courseSection]->location;
			}
		}
		totalDistance += distanceBetweenBuildings(
			currentLocation,
			placeOfResidence,
			locations);
		currentLocation = placeOfResidence;
		switch(currentDay) {
			case 'M':
				currentDay = 'T';
				break;
			case 'T':
				currentDay = 'W';
				break;
			case 'W':
				currentDay = 'R';
				break;
			case 'R':
				currentDay = 'F';
				break;
			case 'F':
				currentDay = 'S';
				break;
			default:
				currentDay = 'S';
				break;
		}
	}
	//cout << "Path " << scheduleToString(classesInThisSchedule) << " length: " << totalDistance << endl;
	return totalDistance;
	
}

bool labelInList(string word, vector<string> & lst) {
	bool result = false;
	for (auto i : lst) {
		result = result | 0 == strcmp(
				word.substr(0, 7).c_str(), 
				i.substr(0, 7).c_str());
	}
	return result;
}

string scheduleToString(vector<string> & classesInThisSchedule) {
	stringstream s;
	for (auto i : classesInThisSchedule) {
		s << i;
		s << ", ";
	}
	return s.str();

}

bool noScheduleConflicts(
		string courseSection, 
		vector<string> classesInThisSchedule,
		unordered_map<string, CourseSection *> courseSections) {
	for (auto c : classesInThisSchedule) {
		if (courseSections[c]->startsAfter(courseSections[courseSection]) ||
				courseSections[courseSection]->startsAfter(courseSections[c])) {

		} else {
			return false;
		}
	}
}

float shortestScheduleStartingAtVertex(
		Vertex * v, 
		vector<string> & classesInThisSchedule, 
		vector<string> & classesInShortestSchedule, 
		float runningMin, 
		unordered_map<string, Coordinates *> locations, 
		unordered_map<string, CourseSection *> courseSections, 
		string placeOfResidence) {
	//cout << "At vertex: " << v->label << endl;
	//cout << "runningMin: " << runningMin << endl;
	for (auto e : v->edges) {
		if (!labelInList(e->target->label, classesInThisSchedule) &&
				noScheduleConflicts(e->target->label, classesInThisSchedule, courseSections)) {
			classesInThisSchedule.push_back(e->target->label);
			
			if (classesInThisSchedule.size() == NUM_COURSES_PER_SEMESTER) {
	//cout << "Course list is: " << classesInThisSchedule.size()<< ": "  << scheduleToString(classesInThisSchedule) << endl;
				float x = findPathLength(
						classesInThisSchedule, 
						locations, 
						courseSections, 
						placeOfResidence);
				//cout << x << endl;
				if (x < runningMin) {
					//cout << "old shortest path: " << runningMin << endl;
					//cout << "new shortest path: " << x << endl;
					runningMin = x;
					classesInShortestSchedule = classesInThisSchedule;
				}
			} else {
				runningMin = shortestScheduleStartingAtVertex(
						e->target, 
						classesInThisSchedule, 
						classesInShortestSchedule, 
						runningMin, 
						locations, 
						courseSections, 
						placeOfResidence);
			}
			classesInThisSchedule.pop_back();
		}
	}
	//cout << "end foreach" << endl;
	return runningMin;
}

float findShortestPath(
		Graph & g, 
		unordered_map<string, Coordinates*> & locations, 
		unordered_map<string, CourseSection*> & courseSections, 
		vector<string> & classesInShortestSchedule, 
		string placeOfResidence) {
	vector<string> classesInThisSchedule;
	float minWalkingDistance = numeric_limits<float>::max();


	vector<string> tmpClassesInShortestSchedule;
	for (auto v : g.vertices) {
		//cout << "Starting at vertex: " << v.second->label << ", the shortest path is:" ; 
		classesInThisSchedule.push_back(v.second->label);
		float distance = shortestScheduleStartingAtVertex(
				v.second, 
				classesInThisSchedule, 
				tmpClassesInShortestSchedule, 
				numeric_limits<float>::max(), 
				locations, 
				courseSections, 
				placeOfResidence);
		//cout << distance << endl;
		if (distance < minWalkingDistance) {
			minWalkingDistance = distance;
			classesInShortestSchedule = tmpClassesInShortestSchedule;
		}	
		classesInThisSchedule.pop_back();
	}

	return minWalkingDistance;
}


int main(int argc, char **argv) {
	cout.precision(8);

	string placeOfResidence = argv[3];
	 
	bool verbose = false;
	if (argc > 4) {
		verbose = (strcmp(argv[4], "verbose") == 0);
		verbose = verbose | strcmp(argv[4], "v") == 0;
	}

	Graph g;

	if (verbose) {
		cout << argv[1] << endl;
		cout << argv[2] << endl;
		cout << argv[3] << endl;
		cout << endl;
	}

	unordered_map<std::string, Coordinates*> locations;
	
	readUnorderedMapFromFile(locations, argv[1]);
	if (verbose) {
		for (auto iter = locations.begin(); iter != locations.end(); ++iter) {
			cout << iter->first << ": " << iter->second->toString();
		}
	}

	unordered_map<std::string, CourseSection*> courseSections;	
	readCourseSectionMapFromFile(courseSections, argv[2]);

	if (verbose) {
		for (auto iter = courseSections.begin(); iter != courseSections.end(); ++iter) {
			cout << iter->first << ": " << iter->second->toString() << endl;
		}
	}

	createDirectedGraph(g, locations, courseSections);
	
	if (verbose) {
		cout << g.toString() << endl;
	}

	vector<string> classesInShortestSchedule;


	float distanceWalked = findShortestPath(
			g, 
			locations, 
			courseSections, 
			classesInShortestSchedule, 
			placeOfResidence);
	cout << "The class schedule that requires the minimum distance travelled is " << 
		scheduleToString(classesInShortestSchedule);
	cout << "and this schedule requires walking " << distanceWalked << " miles." << endl;

	for (auto i: classesInShortestSchedule) {
		cout << courseSections[i]->toString() << endl;
	}
	

	locations.clear();
	courseSections.clear();
	return 0;
}
