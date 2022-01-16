#include <bits/stdc++.h>
using namespace std;

void foldY(int foldIndex, vector<vector<bool>>& matrix) {
	// 
}

void foldX(int foldIndex, vector<vector<bool>>& matrix) {
	int xSize = matrix[0].size();
	int ySize = matrix.size();
	int foldedXSize = max(foldIndex, xSize - 1 - foldIndex);

	vector<vector<bool>>foldedMatrix(ySize, vector<bool>(foldedXSize));

	for (int row = 0; row < ySize; ++row) {
		// Right side
		for (int col = 0; col < foldedXSize; ++col)
			if (matrix[row][xSize -1 -col])
				foldedMatrix[row][col] = true;

		// Lef side
		for (int i = 0; i < foldIndex; ++i) 
			if (matrix[row][i])
				foldedMatrix[row][foldIndex < foldedXSize ? (foldedXSize - foldIndex) + i : i] = true;
	}

	matrix = foldedMatrix;
}

	
int main () {
	ifstream input("../inputs/13.txt");
	string line;
	int total = 0, xSize = 0, ySize = 0;

	vector<vector<bool>> matrix;
	vector<pair<int, int>> markedPositions;
	vector<pair<char, int>> foldingInstructions;

	while(getline(input, line)) {
		int commaDelim = line.find(',');
		int equalsDelim = line.find('=');

		if (commaDelim != string::npos) {
			int x = stoi(line.substr(0, commaDelim));
			int y = stoi(line.substr(commaDelim + 1));

			xSize = max(xSize, x+1);
			ySize = max(ySize, y+1);

			markedPositions.push_back({ x, y });
		}

		if (equalsDelim != string::npos) {
			foldingInstructions.push_back({ line[equalsDelim -1], stoi(line.substr(equalsDelim +1)) });
			break;
		}
	}

	matrix.resize(ySize, vector<bool>(xSize));

	for (auto& [x, y] : markedPositions)
		matrix[y][x] = true;

	for (auto& [axis, index] : foldingInstructions) {
		if (axis == 'y')
			foldY(index, matrix);
		else
			foldX(index, matrix);
	}

	for (auto& row : matrix) 
		total += count(row.begin(), row.end(), true);

	cout << total;
	

	return 0;
}