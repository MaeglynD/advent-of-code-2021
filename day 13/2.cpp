#include <bits/stdc++.h>
using namespace std;

void foldY(int fp, vector<vector<bool>>& matrix) {
	int xs = matrix[0].size(), ys = matrix.size();
	int fys = max(fp +1, ys - fp) -1;
	vector<vector<bool>>foldedMatrix(fys, vector<bool>(xs));

	for (int i = 0; i < ys + 1; ++i) {
		for (int col = 0; col < xs; ++col) {
			if ((i <= fp && matrix[fp -i][col]) || (i < ys - fp && matrix[fp + i][col]))
				foldedMatrix[fys -i][col] = true;
		}
	}

	matrix = foldedMatrix;
}

void foldX(int fp, vector<vector<bool>>& matrix) {
	int xs = matrix[0].size(), ys = matrix.size();
	int fxs = max(fp +1, xs - fp) - 1;
	vector<vector<bool>>foldedMatrix(ys, vector<bool>(fxs));

	for (int row = 0; row < ys; ++row) {
		for (int i = 0; i < fxs + 1; ++i) {
			if ( (i <= fp && matrix[row][fp -i]) || (i < xs - fp && matrix[row][fp + i]))
				foldedMatrix[row][fxs -i] = true;
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

	for (auto& row : matrix) {
		for (auto col : row) 
			cout << (col ? (char)254u : ' ') << " ";
		
		cout << endl;
	}
	
	return 0;
}