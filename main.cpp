#include <iostream>
#include "main.h"

int main(int argc, char* argv[]) {
    vector<int> vertices;
    vector< vector<int> > adjList;
    int numOfVertices;

    cout << "Enter number of vertices: " << endl;
    cin >> numOfVertices;

    adjList.resize(numOfVertices);

    for(int i = 1; i <= numOfVertices; ++i) {
        vertices.push_back(i);

        cout << "Enter vertices adjacent to vertex " << i << " separated by a space.";

        int adjacent;
        do {
            cin >> adjacent;
            adjList[i - 1].push_back(adjacent);
        } while(cin.peek() != '\n');
    }


}