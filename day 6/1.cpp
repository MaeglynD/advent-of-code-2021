#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main () {
	size_t days = 80;
	vector<int> colony;

	ifstream input("../inputs/6.txt");
	string line;
	
	while(getline(input, line, ',')) {
		colony.push_back(stoi(line));
	}

	for (int i = 0; i < days; ++i) {
		int newborns = 0;

		for (int &fish : colony) {
			if (fish == 0) {
				newborns++;
				fish = 6;
			} else {
				fish--;
			}
		}

		colony.resize(colony.size() + newborns, 8);
	}

	cout << colony.size();


	return 0;
}