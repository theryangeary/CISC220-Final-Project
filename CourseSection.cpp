#include "CourseSection.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

void line_populate_course_section(vector<string> &record, const string& line, char delimiter) {
  int linepos=0;
  char c;
  int i;
  int linemax=line.length();
  string curstring;
  record.clear();

  while(line[linepos]!=0 && linepos < linemax) {
    c = line[linepos];
    if (c==delimiter) {
      //end of field
      record.push_back( curstring );
      curstring="";
    }
    else if ((c=='\r' || c=='\n')) {
      record.push_back( curstring );
      return;
    }
    else {
      curstring.push_back(c);
    }
    linepos++;
  }
  record.push_back( curstring );
  return;
}

bool readCourseSectionMapFromFile(std::unordered_map<std::string, CourseSection*> & m, char * fileName) {
  ifstream inFile(fileName);
  if (!inFile) {
    cerr << "File could not be opened" << endl;
    return false;
  }
  if (inFile.fail()) {
    cerr << "File not found" <<endl;
    return false;
  }

  vector<string> row;
  string line;
  int numCourseSections;

  int state = 0; // 0 for vertex #, 1 for edges #, > 1 for all else

  while(getline(inFile, line, '\n') && inFile.good() ) {
    line_populate_course_section(row, line, ' ');
    
    if (state == 0) {
      numCourseSections = atoi(row[0].c_str());
      state++;
    }
    else if (numCourseSections > 0) {
      CourseSection * cs = new CourseSection(
		      row[0].c_str(), row[1].c_str(), 
		      atoi(row[2].c_str()), atoi(row[3].c_str()), 
		      row[4].c_str(), row[5].c_str());

      string label = cs->courseAndSectionNumber();

      std::pair<string, CourseSection*> courseSection (label, cs);
      m.insert(courseSection); 
      numCourseSections--;
    }
  }

  return true;
}
