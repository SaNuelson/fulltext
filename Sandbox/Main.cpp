#include<map>
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;


void stringToLower(string input) {
	transform(input.begin(), input.end(), input.begin() , ::tolower);
}


void stringToLowerAt(string& input) {
	transform(input.begin(), input.end(), input.begin(), ::tolower);
}

void stringToLowerStarAt(string* input) {
	transform(&input->begin(), &input->end(), &input->begin(), ::tolower);
}

int main() {

	string s1 = "String1";
	string s2 = "String2";
	string s3 = "String3";
	stringToLower(s1);
	stringToLowerAt(s2);
	stringToLowerStarAt(&s3);
	cout << s1 << endl << s2 << endl << s3 << endl;

	return 0;
}
