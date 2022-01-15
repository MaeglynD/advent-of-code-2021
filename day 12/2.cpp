#include <bits/stdc++.h>
using namespace std;

int totalPaths = 0;
unordered_map<string, set<string>> cipher;

void findPaths(pair<vector<string>, bool> pathPair) {
	auto& [path, canVisitTwice] = pathPair;

	for (const string& step : cipher[path.back()]) {
		vector<string> tempPath = path;

		if (step == "end") {
			totalPaths++;
		} else {
			tempPath.push_back(step);

			if (islower(step[0])) {
				int occurences = count(tempPath.begin(), tempPath.end(), step);

				if (canVisitTwice) {
					if (occurences > 2) continue;
				} else {
					if (occurences > 1) continue;
				}

				findPaths({ tempPath, canVisitTwice ? occurences < 2 : false });
			} else {
				findPaths({ tempPath, canVisitTwice });
			}
		}
	}
}

void addToCipher(string& a, string& b) {
	if (b != "start") {
		if (cipher.find(a) == cipher.end())
			cipher.insert({ a, { b }});
		else
			cipher[a].insert(b);
	}
}

int main () {
	ifstream input("../inputs/12.txt");
	string line;

	while(getline(input, line)) {
		int delimPos = line.find_first_of('-');
		string a = line.substr(0, delimPos);
		string b = line.substr(delimPos + 1);

		addToCipher(a, b);
		swap(a, b);
		addToCipher(a, b);
	}

	findPaths({{ "start" }, true });

	cout << totalPaths;

	return 0;
}