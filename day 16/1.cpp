#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string binary = "";
string hexChars = "0123456789ABCDEF";
int versionTotal = 0;

string hexToBinary (char hexChar) {
	return ((bitset<4>)hexChars.find(hexChar)).to_string();
}

int binaryToInt(string binarySnippet) {
	return stol(binarySnippet, nullptr, 2);
}

string takeFromBinary(int amount) {
	string result = binary.substr(0, amount);
	binary.erase(0, amount);
	return result;
}

void parseNextPacket() {
	int version = binaryToInt(takeFromBinary(3));
	int typeId = binaryToInt(takeFromBinary(3));

	versionTotal += version;

	if (typeId == 4) {
		string literal = "";

		while(binary[0] == '1') 
			literal += takeFromBinary(5).substr(1);

		literal += takeFromBinary(5).substr(1);
	} else {
		int result;
		string binaryId = takeFromBinary(1);
		bool isIdZero = binaryId == "0";

		if (isIdZero) {
			if (binary.size() < 15) {
				binary = "";
			} else {
				int prevBinarySize = binary.size();

				result = binaryToInt(takeFromBinary(15));

				while(prevBinarySize - binary.size() < result)
					parseNextPacket();
			}
		} else {
			result = binaryToInt(takeFromBinary(11));

			for (int i = 0; i < result; ++i)
				parseNextPacket();
		}
	}
}

int main () {
	ifstream inputStream("../inputs/16.txt");
	string hexInput;

	getline(inputStream, hexInput);

	for (char& hexChar : hexInput)
		binary += hexToBinary(hexChar);

	parseNextPacket();

	cout << versionTotal;
	
	return 0;
}