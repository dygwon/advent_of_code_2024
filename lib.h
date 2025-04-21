#ifndef LIB_H
#define LIB_H

#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

inline vector<string> read_lines(const string file) {
    vector<string> res;
    ifstream file_s(file);
    string line;
    while (getline(file_s, line))
        res.push_back(line);
    return res;
}

inline string read_file(const string file) {
    ifstream file_s(file);
    stringstream buffer;
    buffer << file_s.rdbuf();
    return buffer.str();
}

#endif
