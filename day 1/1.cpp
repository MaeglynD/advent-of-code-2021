#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main () {
	int current, acc = 0, prev = -1;
	ifstream input;
	string line;
	
	input.open("../inputs/1.txt");

	while(getline(input, line)) {
		current = stoi(line);

		if (prev != -1 && current > prev) {
			acc++;
		}

		prev = current;
	}
	
	cout << acc;

	return 0;
}