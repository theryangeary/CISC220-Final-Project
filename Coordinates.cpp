#include "Coordinates.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

void line_populate_coordinates(vector<string> &record, const string& line, char delimiter) {
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

bool readUnorderedMapFromFile(std::unordered_map<std::string, Coordinates*> & m, char * fileName) {
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
  int numCoordinates;

  int state = 0; // 0 for vertex #, 1 for edges #, > 1 for all else

  while(getline(inFile, line, '\n') && inFile.good() ) {
    line_populate_coordinates(row, line, ' ');
    
    if (state == 0) {
      numCoordinates = atoi(row[0].c_str());
      state++;
    }
    else if (numCoordinates > 0) {
      string label = row[0];
      double lon;
      double lat;
      sscanf(row[1].c_str(), "%lf", &lon);
      sscanf(row[2].c_str(), "%lf", &lat);
      double a = 39.123456789;

      Coordinates * c = new Coordinates(lon, lat);
      std::pair<string, Coordinates*> location (label, c);
      m.insert(location); 
      numCoordinates--;
    }
  }

  return true;
}
