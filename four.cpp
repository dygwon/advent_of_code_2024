#include "lib.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const string FILE_FOUR = "input/four.txt";
const string MATCH = "XMAS";

string horizontal_str(vector<string> grid, int i, int j);
string vertical_str(vector<string> grid, int i, int j);
vector<string> diagonal_strs(vector<string> grid, int i, int j);
int check_str(string str);

/*
if we extract string oriented in the following directions for a given starting
point, we can check if the given string matches "XMAS" or "SAMX"

(the functions for extraction should check for out of bounds)

horizontal
 forward
 backward
vertical
 down
 up
diagonal
 down right
 down left
 up right
 up left
*/

int main() {
    int part_one = 0;
    vector<string> lines = read_lines(FILE_FOUR);

    // for (string line : lines) {
    //     for (char c : line) {
    //         cout << c;
    //     }
    //     cout << "\n";
    // }
    for (int i = 0; i < lines.size(); i++) {
        string line = lines[i];
        for (int j = 0; j < line.size(); j++) {
            if (i == 139 && j == 4)
                cout << "";
            part_one += check_str(horizontal_str(lines, i, j));
            part_one += check_str(vertical_str(lines, i, j));
            for (string str : diagonal_strs(lines, i, j)) {
                part_one += check_str(str);
            }
        }
    }

    // 2178 too low
    cout << "Part one: " << part_one << endl;

    return 0;
}

int check_str(string str) {
    int res = 0;

    if (str == MATCH)
        res++;

    reverse(str.begin(), str.end());
    if (str == MATCH)
        res++;

    return res;
}

string horizontal_str(vector<string> grid, int i, int j) {
    // this should only check right since we'll be processing the grid from
    // left to right
    if (j + MATCH.size() > grid[i].size())
        return "";
    else
        return grid[i].substr(j, MATCH.size());
}

string vertical_str(vector<string> grid, int i, int j) {
    // this should only check down since we'll be processing the grid from
    // top to bottom
    int end_idx = i + MATCH.size();
    if (end_idx > grid.size()) {
        return "";
    } else {
        string str = "";
        for (int k = i; k < end_idx; k++) {
            str += grid[k][j];
        }
        return str;
    }
}

vector<string> diagonal_strs(vector<string> grid, int i, int j) {
    // this will only check down since we'll be processing the grid from
    // top to bottom, but will check in both horizontal directions because
    // those will be unique to the horizontal position
    vector<string> strs;

    int h_beg_idx = j - MATCH.size() + 1; // so we can include j
    int h_end_idx = j + MATCH.size();
    int v_end_idx = i + MATCH.size();

    // right
    if (h_end_idx <= grid[i].size() && v_end_idx <= grid.size()) {
        string str = "";
        for (int k = 0; k < MATCH.size(); k++)
            str += grid[i+k][j+k];
        strs.push_back(str);
    }

    // left
    if (h_beg_idx >= 0 && v_end_idx <= grid.size()) {
        string str = "";
        for (int k = 0; k < MATCH.size(); k++)
            str += grid[i+k][j-k];
        strs.push_back(str);
    }

    return strs;
}
