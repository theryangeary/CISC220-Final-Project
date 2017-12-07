#ifndef COURSESECTION_H_
#define COURSESECTION_H_

#ifndef NULL
#define NULL 0
#endif

#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

class CourseSection {
public:
    string course;
    string section;
    int startTime;
    int endTime;
    string days;
    string location;
    
    
    CourseSection(string c, string s, int st, int et, string d, string l) {
        course = c;
        section = s;
        startTime = st;
        endTime = et;
        days = d;
        location = l;
    }
    
    bool startsAfter(CourseSection * cs) {
	return (startTime > cs->endTime) || (days[0] == 'T' && cs->days[0] == 'M');
    }
    
    string toString() const {
        stringstream s;
        s << "(";
        s << course;
        s << section;
        s << ", ";
        s << startTime;
        s << ", ";
        s << endTime;
        s << ", ";
        s << days;
        s << ", ";
        s << location;
        s << ")";
        return s.str();
    }

    string courseAndSectionNumber() {
	    stringstream s;
	    s << course << section;
	    return s.str();
    }
    
};

bool readCourseSectionMapFromFile(unordered_map<string, CourseSection*> & m, char * fileName);

#endif // COURSESECTION_H_
