#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main () {
	ifstream input;
	string line, gamma, epsilon;
	input.open("../inputs/3.txt");

	int lineCount;
	vector<int> totals;

	while(getline(input, line)) {
		lineCount++;

		if (lineCount == 1) {
			for (char &bit : line) {
				totals.push_back(bit - '0');
			}
		} else {
			for (size_t i = 0; i < totals.size(); i++) {
				totals[i] += line[i] - '0';
			}
		}
	}
	
	for (int &bitOccurrences : totals) {
		bool gtr = bitOccurrences > (lineCount / 2);

		gamma += (gtr ? '1' : '0');
		epsilon += (gtr ? '0' : '1');
	}

	cout << stoi(gamma, nullptr, 2) * stoi(epsilon, nullptr, 2);

	return 0;
}