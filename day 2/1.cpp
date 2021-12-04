#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main () {
	ifstream input;
	string line;
	input.open("../inputs/2.txt");

	int forwardAcc = 0, horizontalAcc = 0;

	while(getline(input, line)) {
		size_t pos = line.find(" ");
		string word = line.substr(0, pos);
		int amount = stoi(line.substr(pos + 1));

		if (word == "forward") {
			forwardAcc += amount;
		} else {
			horizontalAcc += (word == "up" ? -amount : amount);
		}
	}
	
	cout << forwardAcc * horizontalAcc;

	return 0;
}