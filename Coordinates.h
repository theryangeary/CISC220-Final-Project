#ifndef COORDINATES_H_
#define COORDINATES_H_

#ifndef NULL
#define NULL 0
#endif

#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Coordinates {
	public:
		double longitude;
		double latitude;

		Coordinates(double lo, double la) {
			longitude = lo;
			latitude = la;
		}

		string toString() const {
			stringstream s;
			s.precision(8);
			s << "(";
			s << longitude;
			s << ", ";
			s << latitude;
			s << ")";
			s << endl;
			return s.str();
		}

};

bool readUnorderedMapFromFile(unordered_map<string, Coordinates*> & m, char * fileName);

#endif // COORDINATES_H_
