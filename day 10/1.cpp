#include <bits/stdc++.h>
using namespace std;

int main () {
	ifstream input("../inputs/10.txt");
	string line;

	string closers = ">)}]";
	int total = 0;
	
	unordered_map<char, char> bracketCipher = {
		{ ')', '(' },
		{ ']', '[' },
		{ '}', '{' },
		{ '>', '<' },
	};

	unordered_map<char, int> scoreCipher = {
		{ ')', 3 },
		{ ']', 57 },
		{ '}', 1197 },
		{ '>', 25137 }
	};

	auto isOpener = [&](char letter) {
		return closers.find(letter) == string::npos;	
	};

	while(getline(input, line)) {
		stack<char> stack;

		for (char& letter : line) {
			if (isOpener(letter)) {
				stack.push(letter);
			} else {
				if (!stack.empty() && isOpener(stack.top()) && bracketCipher[letter] == stack.top()) {
					stack.pop();
				} else {
					total += scoreCipher[letter];
					break;
				}
			}
		}
	}

	cout << total;

	return 0;
}