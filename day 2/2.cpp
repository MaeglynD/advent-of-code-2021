#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main () {
	ifstream input;
	string line;
	input.open("../inputs/2.txt");

	int aim = 0, horizontalPos = 0, depth = 0;

	while(getline(input, line)) {
		size_t pos = line.find(" ");
		string word = line.substr(0, pos);
		int amount = stoi(line.substr(pos + 1));

		if (word == "forward") {
			horizontalPos += amount;
			depth += (aim * amount);
		} else {
			aim += (word == "up" ? -amount : amount);
		}
	}
	
	cout << horizontalPos * depth;

	return 0;
}