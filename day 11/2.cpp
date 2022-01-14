#include <bits/stdc++.h>
using namespace std;

void flashSurroundings(vector<vector<int>>& matrix, int y, int x) {
	vector<pair<int, int>> surroundings = {
		{ y -1, x }, // up
		{ y +1, x }, // down
		{ y, x -1 }, // left
		{ y, x +1 }, // right
		{ y -1, x -1 }, // top left
		{ y -1, x +1 }, // top right
		{ y +1, x -1 }, // bottom left
		{ y +1, x +1 }, // bottom right 
	};

	matrix[y][x] = 11;

	for (auto& [adjacentY, adjacentX] : surroundings) {
		bool isValidPos = (
			adjacentY < matrix.size() && adjacentY >= 0 &&
			adjacentX < matrix[0].size() && adjacentX >= 0 
		);

		if (isValidPos) {
			int* item = &matrix[adjacentY][adjacentX];

			if (*item != 11) {
				(*item)++;

				if (*item > 9)
					flashSurroundings(matrix, adjacentY, adjacentX);
			}
		}
	}
}

int main () {
	ifstream input("../inputs/11.txt");
	string line;

	int step;
	int maxSteps = 1000;
	vector<vector<int>> matrix;

	while(getline(input, line)) {
		matrix.push_back(vector<int>());
		
		for (char letter : line) 
			matrix[matrix.size() - 1].push_back(letter - 48);
	}

	for (step = 0; step < maxSteps * 2; ++step) {
		bool hasEclipsed = true;

		for (int row = 0; row < matrix.size(); ++row) {
			for (int col = 0; col < matrix[row].size(); ++col) {
				int* point = &matrix[row][col];

				// Phase 1: increment all values
				if (step % 2 == 0) {
					if (*point == 11) {
						*point = 1;
					} else {
						hasEclipsed = false;

						if (*point < 10)
							(*point)++;
					}

					if (row == matrix.size() -1 && col == matrix[row].size() -1 && hasEclipsed)
						goto eclipsed;

				// Phase 2: record flashes
				} else {
					if (*point == 10)
						flashSurroundings(matrix, row, col);
				}
			}
		}
	}

	eclipsed:
		cout << "eclipsed: " << step / 2;

	return 0;
}