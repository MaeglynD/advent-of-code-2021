#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct BingoResult {
	vector<vector<int>> board;
	int winningNumber;
};

int main () {
	istringstream strStream;
	ifstream input;
	string line;
	BingoResult lastWinningBoard;

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
		for (int board_i = 0; boards.size() && board_i < boards.size(); ++board_i) {
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
						// Check for bingo
						if (
							// Check rows...
							all_of(row.begin(), row.end(), [](int num){ return num == - 1; }) ||
							// Check cols...
							all_of(board.begin(), board.end(), [foundIndex](auto vec) { return vec[foundIndex] == -1; })
						) {
							lastWinningBoard = { boards[board_i], bingoNum };
							boards.erase(boards.begin() + board_i);
							board_i--;

							break;
						}
					}
				}
			}
		}
	}

	// Loop through the matrix, add all unmarked values
	int total = 0, multiplier = lastWinningBoard.board.size();
	
	for (int i = 0; i < multiplier * multiplier; ++i) {
		int val = lastWinningBoard.board[i / multiplier][i % multiplier];

		if (val != -1) {
			total += val;
		}
	}
	
	cout << "test " << total * lastWinningBoard.winningNumber;
	
	return 0;
}