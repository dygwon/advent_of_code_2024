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

    cout << "Result: " << diff_sum << endl;

    return 0;
}