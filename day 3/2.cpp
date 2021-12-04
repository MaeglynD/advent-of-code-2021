#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string getByCriteria (vector<string> &bytes, string criteria, int pos = 0) {
	vector<string> a, b;

	for (string &byte: bytes) {
		(byte[pos] == '1' ? a : b).push_back(byte);
	}

	size_t as = a.size(), bs = b.size();
	pos++;
	
	vector<string>& chosenVector = criteria == "oxygen" 
		? (as >= bs ? a : b)
		: (as >= bs ? b : a);

	if (max(as, bs) == 1) {
		return chosenVector[0];
	}
	
	return getByCriteria(chosenVector, criteria, pos);
}

int main () {
	ifstream input;
	string line, oxygenGeneratorRating, CO2Scrubber;
	input.open("../inputs/3.txt");

	vector<string> report;

	while(getline(input, line)) {
		report.push_back(line);
	}

	oxygenGeneratorRating = getByCriteria(report, "oxygen");
	CO2Scrubber = getByCriteria(report, "co2");

	cout << stoi(oxygenGeneratorRating, nullptr, 2) * stoi(CO2Scrubber, nullptr, 2);

	return 0;
}