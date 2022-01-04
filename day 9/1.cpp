#include <bits/stdc++.h>
using namespace std;

int main () {
	ifstream input("../inputs/9.txt");
	string line;

	int total = 0;
	vector<pair<int, bool>> previousRow;

	while(getline(input, line)) {
		vector<pair<int, bool>> currentRow;

		for (int i = 0; i < line.size(); ++i) {
			currentRow.push_back({ line[i] - 48, false });

			auto& [num, isLowest] = currentRow[i];

			if (previousRow.size() != 0) {
				auto const& [prevNum, prevIsLowest] = previousRow[i];

				if (prevNum < num) 
					continue;

				if (prevIsLowest)
					total -= (prevNum + 1);

				if (prevNum == num)
					continue;
			} 

			bool right = (i + 1) >= line.size() 
				? true
				: num < (line[i + 1] - 48);

			bool left = (i - 1) < 0
				? true
				: num < (line[i - 1] - 48);

			isLowest = left && right;

			if (isLowest) 
				total += (num + 1);
		}

		previousRow = currentRow;
	}

	cout << total;

	return 0;
}