#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int getDescendants(int days, int age){
	int futureDays = days - (age + 1);

	return futureDays >= 0
		? 1 + getDescendants(futureDays, 6) + getDescendants(futureDays, 8)
		: 0;
}

int main () {
	size_t total = 0;
	size_t days = 256;
	vector<int> colony;

	ifstream input("../inputs/6.txt");
	string line;
	
	while(getline(input, line, ',')) {
		colony.push_back(stoi(line));
	}

	for (int &fish : colony) {
		total += (1 + getDescendants(days, fish));
	}

	cout << total;

	return 0;
}