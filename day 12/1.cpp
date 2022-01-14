#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> paths;
unordered_map<string, set<string>> cipher;

void findPaths(vector<string> path) {
	set<string>& adjacentSteps = cipher[path.back()];

	for (const string& step : adjacentSteps) {
		vector<string> tempPath = path;

		if (step == "end") {
			tempPath.push_back(step);
			paths.push_back(tempPath);
		} else if (islower(step[0]) && any_of(path.begin(), path.end(), [step](string x) { return x == step; })) {
			continue;
		} else {
			tempPath.push_back(step);
			findPaths(tempPath);
		}
	}
}

int main () {
	ifstream input("../inputs/12.txt");
	string line;

	while(getline(input, line)) {
		int delimPos = line.find_first_of('-');
		string a = line.substr(0, delimPos);
		string b = line.substr(delimPos + 1);

		if (cipher.find(a) == cipher.end()) 
			cipher.insert({ a, { b }});
		else 
			cipher[a].insert(b);
		
		if (cipher.find(b) == cipher.end()) 
			cipher.insert({ b, { a }});
		else 
			cipher[b].insert(a);
	}

	findPaths({ "start" });

	cout << paths.size();

	return 0;
}