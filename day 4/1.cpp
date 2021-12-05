#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main () {
	istringstream strStream;
	ifstream input;
	string line;
	int correctBoard, winningBingoNumber;

	vector<int> bingoNumbers;
	vector<vector<vector<int>>> boards;
	
	input.open("../inputs/4.txt");

	// The first line holds a comma delimitated list of numbers
	getline(input, line);
	strStream.str(line);
	
	// Parse the bingo numbers
	while(getline(strStream, line, ',')) {
		bingoNumbers.push_back(stoi(line));
	}

	// Parse the bingo boards
	while (getline(input, line)) {
		if (!line.size()) {
			boards.push_back({});
		} else {
			int boardsUpperIndex, boardUpperIndex, num;
			
			boardsUpperIndex = boards.size() - 1;
			boards[boardsUpperIndex].push_back({});

			boardUpperIndex = boards[boardsUpperIndex].size() - 1;

			strStream.clear();
			strStream.str(line);

			while (strStream >> num) {
				boards[boardsUpperIndex][boardUpperIndex].push_back(num);
			}
		}
	}

	// For every number that will be called...
	for (int num_i = 0; num_i < bingoNumbers.size(); ++num_i) {
		int bingoNum = bingoNumbers[num_i];

		// For every possible board....
		for (int board_i = 0; board_i < boards.size(); ++board_i) {
			vector<vector<int>> &board = boards[board_i];

			// For every row in the board...
			for (int row_i = 0; row_i < board.size(); ++row_i) {
				vector<int> &row = board[row_i];
				auto it = find(row.begin(), row.end(), bingoNum);

				if (it != row.end()) {
					int foundIndex = it - row.begin();

					row[foundIndex] = -1;
					
					// If its possible to achieve bingo...
					if (num_i > 3) {
						// Check the row for bingo
						if (all_of(row.begin(), row.end(), [](int num){ return num == - 1; })) {
							winningBingoNumber = bingoNum;
							correctBoard = board_i;

							goto BINGO;
						}

						// Check the columns for bingo
						for (int i = 0; i < row.size(); ++i) {
							int col = board[i][foundIndex];

							if (col != -1) {
								break;
							}

							if (i == row.size() -1) {
								winningBingoNumber = bingoNum;
								correctBoard = board_i;

								goto BINGO;
							}
						}
					}
				}
			}
		}
	}

	BINGO:
		vector<vector<int>> &board = boards[correctBoard];
		int total, multiplier = board.size();

		// Loop through the matrix, add all unmarked values
		for (int i = 0; i < multiplier * multiplier; ++i) {
			int val = board[i / multiplier][i % multiplier];

			if (val != -1) {
				total += val;
			}
		}

		cout << total * winningBingoNumber;
	
	return 0;
}