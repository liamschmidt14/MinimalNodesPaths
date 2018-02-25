//
// Created by liams on 2/21/2018.
//

#ifndef MINIMALNODESPATHS_MAIN_H
#define MINIMALNODESPATHS_MAIN_H
#include <vector>

using namespace std;
struct Vertex {
    bool visitedFromStart = false;
    bool visitedFromEnd = false;

    vector<int> pathFromStart;
    vector<int> pathFromEnd;

    int parents[2];
};

void bfs(int, int, vector<Vertex *>&, vector< vector<int> >&);
void buildAdjacencyList(int, vector<Vertex *>&, vector< vector<int> >&);
void addNeighborsToQueue(int, queue<int> &, vector<int> &);
#endif //MINIMALNODESPATHS_MAIN_H
