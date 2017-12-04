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
		float longitude;
		float latitude;

		Coordinates(float lo, float la) {
			longitude = lo;
			latitude = la;
		}

		string toString() const {
			stringstream s;
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
