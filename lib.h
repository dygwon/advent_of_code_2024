#ifndef LIB_H
#define LIB_H

#include <vector>
#include <fstream>

using namespace std;

inline vector<string> read_lines(const string file) {
    vector<string> res;
    ifstream file_s(file);
    string line;
    while (getline(file_s, line))
        res.push_back(line);
    return res;
}

#endif
