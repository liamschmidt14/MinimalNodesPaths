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
        cout << "Enter vertices adjacent to vertex " << i << " separated by a space. Use 0 to finish.";
        int adjacent;
        while(cin >> adjacent && adjacent != 0)
            adjList[i - 1].push_back(adjacent);
    }
    int i = 0;
    for(vector<int> v : adjList) {
        cout << ++i << ": ";
        for(int i : v) {
            cout << i << ' ';
        }
        cout << endl;
    }
}