#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

void updateHeatmapSize(vector<vector<int>> &heatmap, size_t &size) {
	for (vector<int> &row : heatmap) {
		row.resize(size);
	}

	heatmap.resize(size, vector<int>(size));
}


int main () {
	int overlapCount = 0;
	vector<vector<int>> heatmap;

	ifstream input;
	string line;
	
	input.open("../inputs/5.txt");

	while (getline(input, line)) {
		size_t delimPos = line.find(' ');

		if (delimPos != string::npos) {
			string posA = line.substr(0, delimPos);
			string posB = line.substr(delimPos + 4);

			size_t delimA = posA.find(',');
			size_t delimB = posB.find(',');

			size_t x1, x2, y1, y2;

			x1 = stoi(posA.substr(0, delimA));
			y1 = stoi(posA.substr(delimA + 1));

			x2 = stoi(posB.substr(0, delimB));
			y2 = stoi(posB.substr(delimB + 1));

			// Get diagonals outta here.
			if (x1 != x2 && y1 != y2) continue;

			size_t maxCoordSize = max({ x1, x2, y1, y2 }) + 1;

			// If the biggest coordinate is larger than the dimension of
			// the heatmap, update the heatmaps size accordingly
			if (maxCoordSize > heatmap.size()) {
				updateHeatmapSize(heatmap, maxCoordSize);
			}

			size_t start, finish;
			bool isYIncreasing = x1 == x2;
			
			if (isYIncreasing) {
				start = min(y1, y2);
				finish = max(y1, y2);
			} else {
				start = min(x1, x2);
				finish = max(x1, x2);
			}

			for (size_t i = start; i <= finish; ++i) {
				int* coord = isYIncreasing ? &heatmap[i][x1] : &heatmap[y1][i];
				(*coord)++;

				if (*coord == 2) overlapCount++;
			}
		}
	}

	cout << "Overlap count: " << overlapCount;

	return 0;
}