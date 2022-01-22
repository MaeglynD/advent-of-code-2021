#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
	int weight;
	pair<int, int> position;
	int distance = 100000000;
};

vector<vector<Node>> matrix;

struct CompareNodes {
	bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
		return matrix[a.first][a.second].distance > matrix[b.first][b.second].distance;
	}
};

int main () {
	ifstream input("../inputs/15.txt");
	string line;
	
	int tileY, tileX;
	priority_queue<pair<int, int>, vector<pair<int, int>>, CompareNodes> unvisited;
	set<pair<int, int>> visited;

	while(getline(input, line)) {
		matrix.push_back({});
		
		for (int i = 0; i < line.size(); ++i) {
			matrix.back().push_back({ line[i] -48, { matrix.size() - 1, i }});
		}
	}

	tileY = matrix.size();
	tileX = matrix[0].size();

	// Enlarge X
	for (int i = 0; i < 4; ++i) {
		for (int y = 0; y < tileY; ++y) {
			for (int x = 0; x < tileX; ++x) {
				int parentWeight = matrix[y][matrix[y].size()-tileX].weight;
				matrix[y].push_back({ parentWeight == 9 ? 1 : parentWeight +1, { y, matrix[y].size()}});
			}
		}
	}

	// Enlarge Y
	for (int i = 0; i < 4; ++i) {
		for (int y = 0; y < tileY; ++y) {
			matrix.push_back({});

			for (int x = 0; x < tileX*5; ++x) {
				int parentWeight = matrix[matrix.size() -tileY-1][x].weight;
				matrix.back().push_back({ parentWeight == 9 ? 1 : parentWeight +1, { matrix.size() -1, x }});
			}
		}
	}

	matrix[0][0].distance = 0;
	matrix[0][0].weight = 0;
	
	unvisited.push({ 0, 0 });

	int& lastNodeDistance = matrix.back().back().distance;

	while(!unvisited.empty()) {
		auto& [y, x] = unvisited.top();
		Node& targettedNode = matrix[y][x];

		if (lastNodeDistance < targettedNode.distance) {
			break;
		}

		vector<pair<int, int>> surroundings = {
			{ y -1, x }, // up
			{ y +1, x }, // down
			{ y, x -1 }, // left
			{ y, x +1 }, // right
		};

		for (auto& [adjacentY, adjacentX] : surroundings) {
			bool isValidPos = (
				adjacentY < matrix.size() && adjacentY >= 0 &&
				adjacentX < matrix[0].size() && adjacentX >= 0 
			);

			if (isValidPos && !visited.count({ adjacentY, adjacentX })) {
				Node& adjacentNode = matrix[adjacentY][adjacentX];
				int newDistance = targettedNode.distance + adjacentNode.weight;

				if (newDistance < adjacentNode.distance) {
					adjacentNode.distance = newDistance;
					unvisited.push({ adjacentY, adjacentX });
				}
			}
		}

		visited.insert({ y, x });
		unvisited.pop();
	}

	cout << lastNodeDistance;

	return 0;
}