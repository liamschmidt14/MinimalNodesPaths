//
// Created by liams on 2/21/2018.
//

#ifndef MINIMALNODESPATHS_MAIN_H
#define MINIMALNODESPATHS_MAIN_H
#include <vector>

using namespace std;

struct Vertex {
    bool visited[2] = {false, false};
    int parents[2] = {-1, -1};
};

void bfs(int, int, vector<Vertex *>&, const vector< vector<int> >&);
void buildAdjacencyList(int, vector<Vertex *>&, vector< vector<int> >&);
void addNeighborsToQueue(int, queue<int> &, const vector<int> &);
void setParentOfNeighbors(const vector<Vertex *> &, int, int, const vector<int> &);
void getAndMarkUnvisitedNeighbors(int, const vector<vector<int> > &, vector<Vertex *> &, int, vector<int>&);
void markStartVisited(vector<Vertex *>&, int, int);
#endif //MINIMALNODESPATHS_MAIN_H
