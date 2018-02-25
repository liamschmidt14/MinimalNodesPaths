//
// Created by liams on 2/21/2018.
//
#include <vector>
#ifndef POINTOFFAILURE_GRAPH_H
#define POINTOFFAILURE_GRAPH_H

using namespace std;

class Graph {
    vector<int> vertices;
    vector< vector <int> > adjList;

    Graph(vector<int>, vector< vector<int> >);

    vector<int> getNeighbors(int);

};


#endif //POINTOFFAILURE_GRAPH_H
