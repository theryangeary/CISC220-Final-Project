

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <vector>
#include <limits>


using namespace std;

void line_populate(vector<string> &record, const string& line, char delimiter) {
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

bool readDirectedGraphFromFile(Graph & g, char * fileName) {
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
  int numVertices;
  int numEdges;

  int state = 0; // 0 for vertex #, 1 for edges #, > 1 for all else

  while(getline(inFile, line, '\n') && inFile.good() ) {
    line_populate(row, line, ' ');
    
    if (state == 0) {
      numVertices = atoi(row[0].c_str());
      state++;
    }
    else if (state == 1) {
      numEdges = atoi(row[0].c_str());
      state++;
    }
    else if (numVertices > 0) {
      string label = row[0];
      g.vertices[label] = new Vertex(g.vertices.size(), label);
      numVertices--;
    }
    else if (numEdges > 0) {
      string id1 = row[0];
      string id2 = row[1];
      double weight = atof(row[2].c_str());

      Vertex* v1 = g.vertices[id1];
      Vertex* v2 = g.vertices[id2];
      v1->edges.push_back(new Edge(v1,v2,weight));
      //v2->edges.push_back(new Edge(v2,v1,weight));
      numEdges--;
    }
  }

  return true;
}
