/*
- one report per line
- each level in a report delimited by a space
- reports are num_safe if
    - all levels are increasing or all decreasing
    - adjacent levels differ by 1 to 3
 */

#include "lib.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

#define FILE "input/two.txt"

using namespace std;

const int MAX_DIFF = 3;
const int MIN_DIFF = 1;

vector<int> read_report(string report);
int check_safety(vector<int> levels);
vector<int> vector_no_i(vector<int> v, int i);

int main() {
    vector<string> reports = read_lines(FILE);
    int part_one = 0;
    int part_two = 0;

    for (string report : reports) {
        vector<int> levels = read_report(report);
        int num_bad = check_safety(levels);

        if (num_bad == 0) {
            part_one++;
        } else {
            /*
            brute force approach for part two:

            if you have only one unsafe level in the report, check for safety
            while excluding a single number each time, until you've excluded all
            numbers. If any of those iterations has no unsafe, it is considered
            safe in part two.
            */

            // check for safety while excluding a single number until you've
            // tried all combinations
            int num_bad_no_i = 0;
            for (int i = 0; i < levels.size(); i++) {
                vector<int> levels_no_i = vector_no_i(levels, i);
                num_bad_no_i = check_safety(levels_no_i);
                if (num_bad_no_i == 0) {
                    part_two++;
                    break;
                }
            }
        }
    }

    cout << "Part one: " << part_one << endl;
    cout << "Part two: " << part_one + part_two << endl;

    // 391 too high

    return 0;
}

vector<int> read_report(string report) {
    vector<int> levels;
    istringstream iss(report);
    int level;
    while (iss >> level)
        levels.push_back(level);
    return levels;
}

int check_safety(vector<int> levels) {
    if (levels.size() < 1) return 0;

    bool is_increasing = (levels[0] - levels[1]) < 0;
    int num_bad_levels = 0;
    if (is_increasing) {
        for (int i = 1; i < levels.size(); i++) {
            int diff = levels[i-1] - levels[i];
            if (diff >= 0 || abs(diff) > MAX_DIFF || abs(diff) < MIN_DIFF)
                num_bad_levels++;
        }
    } else {
        for (int i = 1; i < levels.size(); i++) {
            int diff = levels[i-1] - levels[i];
            if (diff <= 0 || abs(diff) > MAX_DIFF || abs(diff) < MIN_DIFF)
                num_bad_levels++;
        }
    }

    return num_bad_levels;
}

vector<int> vector_no_i(vector<int> v, int i) {
    vector<int> v2;
    for (int j = 0; j < v.size(); j++) {
        if (j == i) continue;
        v2.push_back(v[j]);
    }
    return v2;
}
