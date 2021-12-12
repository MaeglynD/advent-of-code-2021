#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct Point {
	int x, y;
};

void updateHeatmapSize(vector<vector<int>> &heatmap, size_t &size) {
	for (vector<int> &row : heatmap) {
		row.resize(size);
	}

	heatmap.resize(size, vector<int>(size));
}

void markPoint(int *coord, int &overlapCount) {
	(*coord)++;

	if (*coord == 2) {
		overlapCount++;
	}
}


int main () {
	int overlapCount = 0;
	vector<vector<int>> heatmap;
	int test = 0;

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

			Point a = { stoi(posA.substr(0, delimA)), stoi(posA.substr(delimA + 1)) };
			Point b = { stoi(posB.substr(0, delimB)), stoi(posB.substr(delimB + 1)) };

			size_t maxCoordSize = max({ a.x, b.x, a.y, b.y }) + 1;

			// If the biggest coordinate is larger than the dimension of
			// the heatmap, update the heatmaps size accordingly
			if (maxCoordSize > heatmap.size()) {
				updateHeatmapSize(heatmap, maxCoordSize);
				
			}

			// Differences between the two points
			size_t xDiff = abs(a.x - b.x);
			size_t yDiff = abs(a.y - b.y);

			size_t baseX = max(a.x, b.x);
			size_t baseY = max(a.y, b.y);

			// If its a horizontal line
			if (xDiff == 0) {
				for (int i = yDiff; i >= 0; --i) {
					markPoint(&heatmap[baseY - i][a.x], overlapCount);
				}
			} 
			
			// If its a vertical line
			else if (yDiff == 0) {
				for (int i = xDiff; i >= 0; --i) {
					markPoint(&heatmap[a.y][baseX - i], overlapCount);
				}
			} 
			
			// If its a diagonal line
			else if (xDiff == yDiff) {
				if (a.x > b.x) swap(a, b);

				bool isYIncreasing = a.y < b.y;

				for (int i = xDiff; i >= 0; --i) {
					markPoint(&heatmap[a.y][a.x], overlapCount);

					isYIncreasing ? a.y++ : a.y--;
					a.x++;
				}
			}
		}
	}

	cout << "Overlap count: " << overlapCount;

	return 0;
}