#include "lib.h"

#include <string>
#include <iostream>
#include <regex>
#include <vector>

using namespace std;

const string FILE_THREE = "input/three.txt";

int main() {
    string contents = read_file(FILE_THREE);
    vector<string> matches;
    regex pattern("mul\\((\\d+),(\\d+)\\)|do\\(\\)|don't\\(\\)");

    auto words_begin = sregex_iterator(
        contents.begin(), contents.end(), pattern);
    auto words_end = sregex_iterator();

    // capture do() and don't() in addition to mul(\d,\d)
    // iterate and continue adding to result if enabled
    // continue if we see a don't() until we see a do()
    // long part_one = 0;
    long part_two = 0;
    bool enabled = true;
    for (sregex_iterator i = words_begin; i != words_end; i++) {
        smatch match = *i;
        if (match.str() == "don't()") {
            enabled = false;
        } else if (match.str() == "do()") {
            enabled = true;
        } else {
            if (enabled)
                part_two += stoi(match[1].str()) * stoi(match[2].str());
        }
    }

    // Part one answer: 181345830
    // cout << "Part one: " << part_one << endl;
    cout << "Part two: " << part_two << endl;
}
