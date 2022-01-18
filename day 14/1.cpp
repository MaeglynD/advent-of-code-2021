#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main () {
	ifstream input("../inputs/14.txt");
	ll maxOccurence = 0, minOccurence = 0;
	int cycles = 10;
	string polymerTemplate, line;

	map<string, pair<char, ll>> polymers;
	map<char, ll> totals;

	getline(input, polymerTemplate);

	totals.insert({ polymerTemplate[0], 1 });

	while(getline(input, line)) {
		int delimPos = line.find('-');

		if (delimPos != string::npos) 
			polymers.insert({ line.substr(0, delimPos - 1), { line.back(), 0 }});
	}

	for (int i = 0; i < polymerTemplate.size(); ++i) {
		if (i != polymerTemplate.size() - 1) 
			polymers[polymerTemplate.substr(i, 2)].second++;
	}

	auto addToUpdates = [polymers](map<string, ll>& updates, string& pattern, ll& total) {
		if (updates.find(pattern) == updates.end())
			updates.insert({ pattern, total });
		else
			updates[pattern] += total;
	};

	for (int i = 0; i < cycles; ++i) {
		map<string, ll> updates;

		for (auto& [pattern, result] : polymers) {
			if (result.second > 0) {
				string leftPattern{ pattern[0], result.first };
				string rightPattern{ result.first, pattern[1] };

				addToUpdates(updates, leftPattern, result.second);
				addToUpdates(updates, rightPattern, result.second);
			}
		}

		for (auto& [pattern, result] : polymers)
			result.second = updates.find(pattern) == updates.end() ? 0 : updates[pattern];
	}

	for (auto& [pattern, result] : polymers) {
		char letter = pattern[1];
		ll total = result.second;

		if (total > 0) {
			if (totals.find(letter) == totals.end()) 
				totals.insert({ letter, total });
			else
				totals[letter] += total; 
		}
	}

	minOccurence = (*min_element(totals.begin(), totals.end(), [](const auto& a, const auto& b){ return a.second < b.second; })).second;
	maxOccurence = (*max_element(totals.begin(), totals.end(), [](const auto& a, const auto& b){ return a.second < b.second; })).second;

	cout << maxOccurence - minOccurence;
	
	return 0;
}