/*
1. measure distance between sorted lists
2. sum the distances (absolute value)
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <map>

using namespace std;


int main()
{
    // Read in the data.
    vector<int> left;
    vector<int> right;
    string FILE = "input/one.txt";
    ifstream file(FILE);
    string line;
    while (getline(file, line))
    {
        int left_num;
        int right_num;
        istringstream iss(line);

        iss >> left_num;
        iss >> right_num;
        left.push_back(left_num);
        right.push_back(right_num);
    }

    if (left.size() != right.size())
        throw runtime_error("left and right location IDs are not of the same length.");

    // Sort the data.
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Calculate and sum differences.
    long diff_sum = 0;
    for (int i = 0; i < left.size(); i++)
        diff_sum += abs(left[i] - right[i]);

    cout << "Part One Result: " << diff_sum << endl;

    // Count the number of occurrences on the right list.
    map<int, int> right_map;
    for (int i = 0; i < right.size(); i++)
    {
        int curr = right[i];
        if (right_map.count(curr))
            right_map[curr] += 1;
        else
            right_map[curr] = 1;
    }

    // Calculate the similarity score.
    long sim_score = 0;
    for (int i = 0; i < left.size(); i++)
    {
        int curr = left[i];
        if (right_map.count(curr))
            // Similarity is sum of products between left ids and number of
            // occurrences in the right list.
            sim_score += curr * right_map[curr];
    }

    cout << "Part Two Result: " << sim_score << endl;

    return 0;
}