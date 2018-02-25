#include <iostream>
#include <queue>
#include <stack>
#include "main.h"

int main(int argc, char* argv[]) {
    vector<Vertex*> vertices;
    vector< vector<int> > adjList;
    int numOfVertices;

    cout << "Enter number of vertices: " << endl;
    cin >> numOfVertices;

    adjList.resize(numOfVertices);

    //Build the adjacency list for this graph from the command line
    buildAdjacencyList(numOfVertices, vertices, adjList);

    //Get start/target vertices
    int startingVertex, targetVertex;
    cout << "Enter starting vertex: ";
    cin >> startingVertex;
    cout << "Enter target vertex: ";
    cin >> targetVertex;

    bfs(startingVertex, targetVertex, vertices, adjList);

}

void bfs(int startVertex, int targetVertex, vector<Vertex *>& vertices, vector< vector<int> >& adjList) {
    for (int i = 0, bfsStartPoint = startVertex; i < 2; i++, bfsStartPoint = targetVertex) {
        queue<int> nextVerticesToCheck;
        stack<int> currentPath;

        nextVerticesToCheck.push(bfsStartPoint);

        int currentVertex;
        while(!nextVerticesToCheck.empty()) {
            currentVertex = nextVerticesToCheck.front();
            nextVerticesToCheck.pop();

            vector<int> currentNeighbors = adjList[currentVertex - 1];

            addNeighborsToQueue(currentVertex, nextVerticesToCheck, currentNeighbors);


        }
    }

}

void addNeighborsToQueue(int vertex, queue<int> &queue, vector<int>& neighbors) {
    for(int i : neighbors)
        queue.push(i);
}

void buildAdjacencyList(int numOfVertices, vector<Vertex *>& vertices, vector< vector<int> >& adjList) {
    for(int i = 1; i <= numOfVertices; ++i) {
        //Store vertex information in a struct for each vertex
        vertices.push_back(new Vertex);

        cout << "Enter vertices adjacent to vertex " << i << " separated by a space.";

        //do-while builds each vertex's adjacency list
        int adjacent;
        do {
            cin >> adjacent;
            adjList[i - 1].push_back(adjacent);
        } while(cin.peek() != '\n');
    }
}