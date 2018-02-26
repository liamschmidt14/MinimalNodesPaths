#include <iostream>
#include <queue>
#include <stack>
#include <set>
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

    //Do 2 simple BFSes, one from the "source" vertex given, and one from the "target."
    //The resulting shortest paths from source and target to each vertex will be concatenated to produce the shortest path
    //from source to target containing that vertex.
    bfs(startingVertex, targetVertex, vertices, adjList);

    set<string, CompareByLength> allPaths = constructAllPaths(vertices);
    cout << endl << "All paths from vertex " << startingVertex << " to vertex " << targetVertex << " with a minimal number of nodes per path:" << endl;
    for(string path : allPaths)
        cout << path << endl;

}

set<string, CompareByLength> constructAllPaths(vector<Vertex *> vertices) {
    //Using a set to prevent listing duplicate paths.
    set<string, CompareByLength> allPaths;

    //Finds the shortest path (based on the BFSes done earlier) from each node in the graph to the source vertex and to the target.
    for (int i = 0; i < vertices.size(); ++i) {
        string pathFromSource = getPathFromSource(vertices, i);
        string pathFromTarget = getPathFromTarget(vertices, i);
        //Concatenates the two shortest paths calculated with the vertex for which paths are being built.
        string completePath = pathFromSource + to_string(i + 1) + pathFromTarget;
        //Adds the path to the unordered set.
        allPaths.insert(completePath);
    }
    
    return allPaths;
}

string getPathFromSource(const vector<Vertex *>& vertices, int vertexToGetPathFor) {
    //Using a stack because this path string will need to be built in a LIFO order.
    stack<int> pathBuilder;

    Vertex *current = vertices[vertexToGetPathFor];
    int parentVertex = current->parents[0];

    //Adds vertices to the stack until the source vertex is reached.
    while(parentVertex != -1) {
        pathBuilder.push(parentVertex);
        current = vertices[parentVertex - 1];
        parentVertex = current->parents[0];
    }

    string path = "";

    //Builds the path from the stack.
    while(!pathBuilder.empty()) {
        int nextVertex = pathBuilder.top();
        pathBuilder.pop();

        path += to_string(nextVertex) + " ";
    }

    return path;
}

string getPathFromTarget(const vector<Vertex *>& vertices, int vertexToGetPathFor) {
    //This method uses a queue because the path string needs to be constructed in a FIFO fashion.
    queue<int> pathBuilder;

    Vertex *current = vertices[vertexToGetPathFor];
    int parentVertex = current->parents[1];

    while(parentVertex != -1) {
        pathBuilder.push(parentVertex);
        current = vertices[parentVertex - 1];
        parentVertex = current->parents[1];
    }

    string path = "";

    while(!pathBuilder.empty()) {
        int nextVertex = pathBuilder.front();
        pathBuilder.pop();

        path += " " + to_string(nextVertex);
    }

    return path;
}

void bfs(int startVertex, int targetVertex, vector<Vertex *>& vertices, const vector< vector<int> >& adjList) {

    //Each vertex has a 2-element array for marking it visited and saving its parent node for the search from source
    //and for the search from target. i serves as the "selector" for these two member arrays.
    //The starting point of the BFS (source or target) is also changed between loops.
    for (int i = 0, bfsStartPoint = startVertex; i < 2; i++, bfsStartPoint = targetVertex) {
        queue<int> nextVerticesToCheck;
        //Classic BFS. Uses a queue, marks starting point as visited, and adds it to the queue first.
        nextVerticesToCheck.push(bfsStartPoint);
        markStartVisited(vertices, bfsStartPoint, i);
        
        int currentVertex;
        while(!nextVerticesToCheck.empty()) {
            currentVertex = nextVerticesToCheck.front();
            nextVerticesToCheck.pop();

            //Gets all neighboring vertices of the current vertex.
            vector<int> currentNeighbors;
            getAndMarkUnvisitedNeighbors(currentVertex, adjList, vertices, i, currentNeighbors);

            //If there are unvisited neighbors, set their "parent" vertex (to be used when reconstructing the shortest
            //path) to the current vertex, then mark these neighbors as visited.
            bool hasUnvisitedNeighbors = !currentNeighbors.empty();
            if(hasUnvisitedNeighbors) {
                setParentOfNeighbors(vertices, i, currentVertex, currentNeighbors);

                addNeighborsToQueue(nextVerticesToCheck, currentNeighbors);
            }
            
        }
    }

}

void addNeighborsToQueue(queue<int> &queue, const vector<int>& neighbors) {
    //Simply adds unvisited neighbors to the queue.
    for(int i : neighbors)
        queue.push(i);
}

void getAndMarkUnvisitedNeighbors(int vertex, const vector<vector<int> > &adjList, vector<Vertex *> &vertices, int visitedSelector, vector<int>& neighbors) {
    //Finds all neighbors of the current vertex that are not marked visited for the current direction
    for(int i : adjList[vertex - 1]) {
        Vertex* neighborToCheck = vertices[i - 1];
        //Checks if the vertex has been visited yet on this iteration of the BFS (as determined by "visitedSelector."
        bool unvisited = !neighborToCheck->visited[visitedSelector];
        if(unvisited) {
            //If it has not yet been visisted, adds it to the list of neighbors to check and marks it visited.
            neighbors.push_back(i);
            neighborToCheck->visited[visitedSelector] = true;
        }
    }
}

void setParentOfNeighbors(const vector<Vertex *> &vertices, int parentSelector, int currentVertex,
                          const vector<int> &currentNeighbors) {
    //Sets the parent vertex of all unvisited neighbors of the currently selected vertex to that vertex.
    for(int i : currentNeighbors)
                vertices[i - 1]->parents[parentSelector] = currentVertex;
}

void markStartVisited(vector<Vertex *>& vertices, int vertexToMark, int visitedSelector) {
    //Marks the starting vertex of the BFS visited.
    Vertex *startingVertex = vertices[vertexToMark - 1];
    startingVertex->visited[visitedSelector] = true;
}

void buildAdjacencyList(int numOfVertices, vector<Vertex *>& vertices, vector< vector<int> >& adjList) {
    for(int i = 1; i <= numOfVertices; ++i) {
        //Store vertex information in a struct for each vertex
        vertices.push_back(new Vertex);

        cout << "Enter vertices adjacent to vertex " << i << " separated by a space. ";

        //do-while builds each vertex's adjacency list
        int adjacent;
        do {
            cin >> adjacent;
            adjList[i - 1].push_back(adjacent);
        } while(cin.peek() != '\n');
    }
}