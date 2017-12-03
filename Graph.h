#ifndef GRAPH_H_
#define GRAPH_H_

#ifndef NULL
#define NULL 0
#endif

#include <vector>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

// not always the best idea but we're lazy today
using namespace std;

// Reserve the name for each Class to allow recursive definition
class Vertex;
class Edge;

#ifndef DEFAULT_VERTEX_STATUS
#define UNKNOWN 0
#define IDENTIFIED 1
#define VISITED 2
#define DEFAULT_VERTEX_STATUS 0
#endif

class Edge {
  public:
    Vertex * source;
    Vertex * target;
    double weight;

    Edge(Vertex * pSource, Vertex * pTarget, double pWeight)
        : source(pSource), target(pTarget), weight(pWeight){ }

    ~Edge() {}
};

// a simple Vertex that has an id and label and status marker
class Vertex {
  public:
  int id; // id represents the order this Vertex was added to a graph
  string label; // label must be unique
  int status; // sometimes called color in algorithms, helps with processing

  vector<Edge*> edges;
  Vertex(int pId, string pLabel) :
    id(pId), label(pLabel), status(DEFAULT_VERTEX_STATUS) {}

  ~Vertex() {
    for (auto iter = edges.begin();
          iter != edges.end(); iter++) {
      Edge * l = *iter;
      delete l;
    }
  }
};

// a Graph is just a lookup "table" of vertex label to Vertex
class Graph {
  public:
  unordered_map<string,Vertex*> vertices;

  Graph(){}
  ~Graph() {
    for (auto iter = vertices.begin();
              iter != vertices.end(); iter++) {
      Vertex * v = iter->second;
      delete v;
    }
  }

  string toString() const {
    stringstream s;
    for (auto iterV = vertices.begin();
          iterV != vertices.end(); iterV++) {
      Vertex * v = iterV->second;
      s << v->label << ": ";
      for (auto iterE = v->edges.begin();
            iterE != v->edges.end(); iterE++) {
          Edge * e = *iterE;
          s << e->target->label << "(" << e->weight << ") ";
      }
      s << endl;
    }

    return s.str();

  }
};

bool readDirectedGraphFromFile(Graph & g, char * fileName);

#endif // GRAPH_H_
