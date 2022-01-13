#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main () {
	ifstream input("../inputs/10.txt");
	string line;

	vector<ll> totals;
	string closers = ">)}]";
	
	unordered_map<char, char> bracketCipher = {
		{ ')', '(' },
		{ ']', '[' },
		{ '}', '{' },
		{ '>', '<' },
	};

	unordered_map<char, int> scoreCipher = {
		{ '(', 1 },
		{ '[', 2 },
		{ '{', 3 },
		{ '<', 4 }
	};

	auto isOpener = [&](char letter) {
		return closers.find(letter) == string::npos;	
	};

	while(getline(input, line)) {
		stack<char> stack;
		bool isCorrupted = false;
		ll total = 0;

		for (char& letter : line) {
			if (isOpener(letter)) {
				stack.push(letter);
			} else {
				if (!stack.empty() && isOpener(stack.top()) && bracketCipher[letter] == stack.top()) {
					stack.pop();
				} else {
					isCorrupted = true;
					break;
				}
			}
		}

		if (!isCorrupted) {
			while (!stack.empty()) {
				total *=5;
				total += scoreCipher[stack.top()];
				stack.pop();
			}
			
			totals.push_back(total);
		}
	}

	nth_element(totals.begin(), totals.begin() + (totals.size() / 2), totals.end());

	cout << totals[totals.size() / 2];

	return 0;
}