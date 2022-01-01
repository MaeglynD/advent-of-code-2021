#include <bits/stdc++.h>
using namespace std;

void splitBySpace(string inputStr, vector<string>& outputVec) {
	string value;
	istringstream strStream;

	strStream.clear();
	strStream.str(inputStr);

	while (getline(strStream, value, ' ')) {
		outputVec.push_back(value);
	}
}

bool doesWordHaveAllChars(string& word, string charStr) {
	for (const char& letter : charStr) {
		if (word.find(letter) == string::npos) {
			return false;
		}
	}

	return true;
}

void populateCipher(unordered_map<string, string>& cipher, vector<string> words) {
	char c, f;

	// Resolves 1, 4, 7, 8
	vector<pair<char, int>> wordsDeducedByLength = {
		{ '1', 2 },
		{ '4', 4 },
		{ '7', 3 },
		{ '8', 7 },
	};

	for (const auto& entry : wordsDeducedByLength) {
		char label = entry.first;
		int length = entry.second;

		vector<string>::iterator foundWord = find_if(words.begin(), words.end(), [&](string word){
			if (word.size() == length) {
				cipher[word] = label;
				cipher[string(1, label)] = word;

				return true;
			}

			return false;
		});

		if (foundWord != words.end()) {
			words.erase(foundWord);
		}
	}

	// Resolves 9
	vector<string>::iterator nineIter = find_if(words.begin(), words.end(), [&](string word){
		if (doesWordHaveAllChars(word, cipher["4"])) {
			cipher[word] = "9";

			return true;
		}

		return false;
	});

	if (nineIter != words.end()) {
		words.erase(nineIter);
	}

	// Resolves 0, 6
	words.erase(
		remove_if(words.begin(), words.end(), [&](string word) {
			if (word.size() == 6) {
				bool isSix = !doesWordHaveAllChars(word, cipher["1"]);

				if (isSix) {
					c = cipher["1"][0];
					f = cipher["1"][1];

					if (word.find(f) == string::npos) {
						swap(c, f);
					}
				}

				cipher[word] = isSix ? "6" : "0";
				
				return true;
			}

			return false;
		}),
		words.end()
	);

	// Resolves 2, 3, 5
	for (string& word : words) {
		bool hasC = word.find(c) != string::npos;
		bool hasF = word.find(f) != string::npos;

		if (hasC && hasF) {
			cipher[word] = '3';
		} else {
			cipher[word] = hasC ? '2' : '5';
		}
	}
}

int main () {
	int total = 0;

	ifstream input("../inputs/8.txt");
	string line;
	
	while(getline(input, line)) {
		unordered_map<string, string> cipher;
		vector<string> inputValues, outputValues;

		string digits = "";
		size_t delimPos = line.find('|');

		splitBySpace(line.substr(0, delimPos - 1), inputValues);
		splitBySpace(line.substr(delimPos + 2), outputValues);
		
		populateCipher(cipher, inputValues);

		for (string word : outputValues) {
			sort(word.begin(), word.end());

			string translatedWord = *find_if(inputValues.begin(), inputValues.end(), [&](string inputWord) {
				sort(inputWord.begin(), inputWord.end());
				
				return word == inputWord;
			});

			digits += cipher[translatedWord];
		}

		total += stoi(digits);
	}

	cout << total;
	
	return 0;
}