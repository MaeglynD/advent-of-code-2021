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
	int total = 0;
	istringstream strStream;

	ifstream input("../inputs/8.txt");
	string line;
	
	while(getline(input, line)) {
		string outputValues = line.substr(line.find('|') + 2, line.size());
		string value;

		strStream.clear();
		strStream.str(outputValues);

		while (getline(strStream, value, ' ')) {
			int segmentCount = value.size();

			if (segmentCount == 2 || segmentCount == 4 || segmentCount == 3 || segmentCount == 7) {
				total++;
			}
		}
	}

	cout << total;
	
	return 0;
}