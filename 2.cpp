#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main () {
	ifstream input;
	string line;
	input.open("inputs/1.txt");

	vector<int> vec;
	int current, count = 0, acc = 0;

	while(getline(input, line)) {
		current = stoi(line);
		vec.push_back(current);

		if (vec.size() > 3) {
			int nextAcc = acc - vec[0] + current;

			vec.erase(vec.begin());

			if (nextAcc > acc) {
				count++;
			}	

			acc = nextAcc;
		} else {
			acc += current;
		}
	}
	
	cout << count;

	return 0;
}