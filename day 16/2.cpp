#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string binary = "";
string hexChars = "0123456789ABCDEF";

string hexToBinary (char hexChar) {
	return ((bitset<4>)hexChars.find(hexChar)).to_string();
}

ll binaryToLl(string binarySnippet) {
	return stoll(binarySnippet, nullptr, 2);
}

string takeFromBinary(int amount) {
	string result = binary.substr(0, amount);
	binary.erase(0, amount);
					
	return result;
}

ll parseNextPacket() {
	int version = binaryToLl(takeFromBinary(3));
	int typeId = binaryToLl(takeFromBinary(3));

	// Literal
	if (typeId == 4) {
		string literal = "";
		while(binary[0] == '1') 
			literal += takeFromBinary(5).substr(1);

		literal += takeFromBinary(5).substr(1);

		return binaryToLl(literal);

	// Operator
	} else {
		ll result;
		vector<ll> subPackets;
		string binaryId = takeFromBinary(1);
		bool isIdZero = binaryId == "0";

		// Length type id 0
		if (isIdZero) {
			if (binary.size() < 15) {
				binary = "";
			} else {
				result = binaryToLl(takeFromBinary(15));

				int prevBinarySize = binary.size();

				while(prevBinarySize - binary.size() < result)
					subPackets.push_back(parseNextPacket());
			}
		
		// Length type id 1
		} else {
			result = binaryToLl(takeFromBinary(11));

			for (int i = 0; i < result; ++i)
				subPackets.push_back(parseNextPacket());
		}

		if (typeId == 0)
			return accumulate(subPackets.begin(), subPackets.end(), 0LL);

		if (typeId == 1)
			return accumulate(subPackets.begin(), subPackets.end(), 1LL, std::multiplies<ll>());

		if (typeId == 2)
			return *min_element(subPackets.begin(), subPackets.end());

		if (typeId == 3)
			return *max_element(subPackets.begin(), subPackets.end());

		if (typeId == 5)
			return subPackets[0] > subPackets[1];

		if (typeId == 6)
			return subPackets[0] < subPackets[1];

		if (typeId == 7)
			return subPackets[0] == subPackets[1];
	}
}

int main () {
	ifstream inputStream("../inputs/16.txt");
	string hexInput;

	getline(inputStream, hexInput);

	for (char& hexChar : hexInput)
		binary += hexToBinary(hexChar);

	cout << parseNextPacket();

	return 0;
}