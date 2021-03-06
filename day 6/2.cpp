#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
using namespace std;
typedef long long ll;


int main () {
	ll total = 0;
	size_t days = 256;
	vector<int> colony;

	ifstream input("../inputs/6.txt");
	string line;
	
	while(getline(input, line, ',')) {
		colony.push_back(stoi(line));
	}

	for (int &fish : colony) {
		vector<ll> state(9, 0);

		state[fish] = 1;

		for (int i = 0; i < days; ++i) {
			ll births = state[0];

			state.erase(state.begin());
			state.push_back(births);

			state[6] += births;
		}
		
		total += accumulate(state.begin(), state.end(), 0LL);
	}

	cout << total;

	return 0;
}