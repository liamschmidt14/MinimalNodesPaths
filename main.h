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
};
#endif //MINIMALNODESPATHS_MAIN_H
