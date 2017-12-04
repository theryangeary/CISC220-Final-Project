#ifndef COORDINATES_H_
#define COORDINATES_H_

#ifndef NULL
#define NULL 0
#endif

using namespace std;

class Coordinates {
	public:
		int longitude;
		int latitude;

		Coordinates(int lo, int la) {
			longitude = lo;
			latitude = la;
		}

		string toString() {
			stringstream s;
			s << "(";
			s << longitude;
			s << ", ";
			s << latitude;
			s << ")";
			s << endl;
			return s.str();
		}

}

#endif // COORDINATES_H_
