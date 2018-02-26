//
// Created by liams on 2/21/2018.
//

#ifndef MINIMALNODESPATHS_MAIN_H
#define MINIMALNODESPATHS_MAIN_H

using namespace std;

struct Vertex {
    bool visited[2] = {false, false};
    int parents[2] = {-1, -1};
};

struct CompareByLength {
    bool operator()(const string& a, const string& b) {
        if(a.length() == b.length()) return a < b;
        return a.length() < b.length();
    }
};

bool pathIsNotSimple(const string &pathFromSource, const string &pathToTarget);
set<string, CompareByLength> constructAllPaths(vector<Vertex *>);
string getPathFromSource(const vector<Vertex *>& vertices, int vertexToGetPathFor) ;
string getPathFromTarget(const vector<Vertex *>& vertices, int vertexToGetPathFor) ;
void bfs(int, int, vector<Vertex *>&, const vector< vector<int> >&);
void buildAdjacencyList(int, vector<Vertex *>&, vector< vector<int> >&);
void addNeighborsToQueue(queue<int> &, const vector<int> &);
void setParentOfNeighbors(const vector<Vertex *> &, int, int, const vector<int> &);
void getAndMarkUnvisitedNeighbors(int, const vector<vector<int> > &, vector<Vertex *> &, int, vector<int>&);
void markStartVisited(vector<Vertex *>&, int, int);
#endif //MINIMALNODESPATHS_MAIN_H
