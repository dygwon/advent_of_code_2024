#include "lib.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const string FILE_FOUR = "input/four.txt";
const string SEARCH_STR1 = "XMAS";
const string SEARCH_STR2 = "MAS";

string h_str(vector<string> grid, int i, int j, int str_len);
string v_str(vector<string> grid, int i, int j, int str_len);
vector<string> d_strs(vector<string> grid, int i, int j, int str_len);
int check_str(string str, string search_str);
bool is_x(vector<string> grid, int i, int j, string search_str);

/*
if we extract string oriented in the following directions for a given starting
point, we can check if the given string matches "XMAS" or "SAMX"

(the functions for extraction should check for out of bounds)

horizontal
 forward
vertical
 down
diagonal
 down right
 down left
*/

int main() {
    int part_one = 0;
    int part_two = 0;
    vector<string> lines = read_lines(FILE_FOUR);

    for (int i = 0; i < lines.size(); i++) {
        string line = lines[i];
        for (int j = 0; j < line.size(); j++) {
            part_one += check_str(
                h_str(lines, i, j, SEARCH_STR1.size()), SEARCH_STR1);
            part_one += check_str(
                v_str(lines, i, j, SEARCH_STR1.size()), SEARCH_STR1);
            for (string str : d_strs(lines, i, j, SEARCH_STR1.size())) {
                part_one += check_str(str, SEARCH_STR1);
            }

            part_two += is_x(lines, i, j, SEARCH_STR2);
        }
    }

    cout << "Part one: " << part_one << "\n";
    cout << "Part two: " << part_two << endl;

    return 0;
}

int check_str(string str, string search_str) {
    int res = 0;

    if (str == search_str)
        res++;

    reverse(str.begin(), str.end());
    if (str == search_str)
        res++;

    return res;
}

string h_str(vector<string> grid, int i, int j, int str_len) {
    // this should only check right since we'll be processing the grid from
    // left to right
    if (j + str_len > grid[i].size())
        return "";
    else
        return grid[i].substr(j, str_len);
}

string v_str(vector<string> grid, int i, int j, int str_len) {
    // this should only check down since we'll be processing the grid from
    // top to bottom
    int end_idx = i + str_len;
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

vector<string> d_strs(vector<string> grid, int i, int j, int str_len) {
    // this will only check down since we'll be processing the grid from
    // top to bottom, but will check in both horizontal directions because
    // those will be unique to the horizontal position
    vector<string> strs;

    int h_beg_idx = j - str_len + 1; // so we can include j
    int h_end_idx = j + str_len;
    int v_end_idx = i + str_len;

    // right
    if (h_end_idx <= grid[i].size() && v_end_idx <= grid.size()) {
        string str = "";
        for (int k = 0; k < str_len; k++)
            str += grid[i+k][j+k];
        strs.push_back(str);
    }

    // left
    if (h_beg_idx >= 0 && v_end_idx <= grid.size()) {
        string str = "";
        for (int k = 0; k < str_len; k++)
            str += grid[i+k][j-k];
        strs.push_back(str);
    }

    return strs;
}

bool is_x(vector<string> grid, int i, int j, string search_str) {
    // only works with odd-length strings
    if (search_str.size() % 2 == 0)
        return false;

    int from_ctr = search_str.size() / 2;

    // end indices not inclusive to be consistent
    int h_beg_idx = j - from_ctr, h_end_idx = j + from_ctr + 1;
    int v_beg_idx = i - from_ctr, v_end_idx = i + from_ctr + 1;
    int res = 0;
    if (h_beg_idx >= 0 || v_beg_idx >= 0
        || h_end_idx <= grid[i].size() || v_end_idx <= grid.size()) {
        string str_x_one = "", str_x_two = "";
        for (int k = 0; k < search_str.size(); k++) {
            str_x_one += grid[v_beg_idx+k][h_beg_idx+k];
            str_x_two += grid[v_end_idx-1-k][h_beg_idx+k];
        }
        
        res += check_str(str_x_one, search_str);
        res += check_str(str_x_two, search_str);
    }

    if (res == 2)
        return true;
    return false;
}
