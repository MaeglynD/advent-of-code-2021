#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib> 
#include <numeric>
using namespace std;

int main () {
	int minPos, maxPos, optimalFuelUsage = INT_MAX;
	vector<int> positions; 

	ifstream input("../inputs/7.txt");
	string line;
	
	while(getline(input, line, ',')) {
		positions.emplace_back(stoi(line));
	}

	minPos = *min_element(positions.begin(), positions.end());
	maxPos = *max_element(positions.begin(), positions.end());

	for (int i = minPos; i <= maxPos; ++i) {
		int fuelUsage = accumulate(positions.begin(), positions.end(), 0, [&](int& total, int& pos) {
			return total + abs(i - pos);
		});

		if (fuelUsage < optimalFuelUsage) {
			optimalFuelUsage = fuelUsage;
		}
	}

	cout << optimalFuelUsage;

	return 0;
}