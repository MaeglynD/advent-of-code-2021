#include <bits/stdc++.h>
using namespace std;

void foldY(int foldIndex, vector<vector<bool>>& matrix) {
	// 
}

void foldX(int fp, vector<vector<bool>>& matrix) {
	int xs = matrix[0].size();
	int ys = matrix.size();
	int fxs = max(fp +1, xs - fp);
	vector<vector<bool>>foldedMatrix(ys, vector<bool>(fxs));

	for (int row = 0; row < ys; ++row) {
		for (int i = 0; i < fxs; ++i) {
			// bringing the left side to the new matrix
			if (i <= fp && matrix[row][fp -i]) foldedMatrix[row][fxs -1 -i] = true;
			// bringing the right side to the new matrix
			if (i < xs - fp && matrix[row][fp + i]) foldedMatrix[row][fxs -1 -i] = true;
		}
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