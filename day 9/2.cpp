#include <bits/stdc++.h>
using namespace std;

bool isValidPos(vector<vector<int>>& matrix, pair<int, int>& point) {
	auto& [y, x] = point;

	return (
		y < matrix.size() && y >= 0 &&
		x < matrix[0].size() && x >= 0 
	);
};

void searchSurroundings(vector<vector<int>>& matrix, int& total, pair<int, int>& point) {
	auto& [y, x] = point;
	int* midpoint = &matrix[y][x];

	if (*midpoint != 9) {
		*midpoint = 9;
		total++;

		vector<pair<int, int>> surroundings = {
			{ y -1, x }, // up
			{ y +1, x }, // down
			{ y, x -1 }, // left
			{ y, x +1 }, // right
		};

		for (auto& adjacentPoint : surroundings) {
			if (isValidPos(matrix, adjacentPoint)) {
				searchSurroundings(matrix, total, adjacentPoint);
			}
		}
	}
}

int main () {
	ifstream input("../inputs/9.txt");
	string line;

	vector<pair<int, int>> lowPoints;
	vector<vector<int>> matrix;
	vector<int> basins;

	while(getline(input, line)) {
		matrix.push_back(vector<int>());
		
		for (char letter : line) 
			matrix[matrix.size() - 1].push_back(letter - 48);
	}

	int ySize = matrix.size();
	int xSize = matrix[0].size();

	// find the low points
	for (int y = 0; y < ySize; ++y) {
		for (int x = 0; x < xSize; ++x) {
			vector<pair<int, int>> surroundings = {
				{ y, x -1 }, // up
				{ y, x +1 }, // down
				{ y -1, x }, // left
				{ y +1, x }, // right
			};

			for (int i = 0; i < surroundings.size(); ++i) {
				pair<int, int> point = surroundings[i];
				auto& [comparisonY, comparisonX] = point;

				if (isValidPos(matrix, point)) {
					if (matrix[y][x] >= matrix[comparisonY][comparisonX]) 
						break;
				}

				if (i == surroundings.size() -1) {
					lowPoints.push_back(make_pair(y, x));

					if (x < xSize - 1) 
						x++;
				}
			}
		}
	}

	// find the area of the polygon each lowpoint resides in
	for (auto& point : lowPoints) {
		int total = 0;

		searchSurroundings(matrix, total, point);
		basins.push_back(total);
	}

	nth_element(basins.begin(), basins.begin() + 3, basins.end(), greater<int>());

	cout << basins[0] * basins[1] * basins[2];

	return 0;
}