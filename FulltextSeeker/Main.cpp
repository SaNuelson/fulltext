#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include<sstream>
#include<algorithm>

#include "Functions.h"

using namespace std;


/*
	Global Variables
*/

extern vector<Article> Articles;

// Word - Article ptr - Starting index in Text_
// WordDict[Word][Article*].push_back(Index);
extern map<string, map<Article*, unsigned>> WordDict;

extern vector<vector<string>> Queries;

/*
	Methods
*/

int main(int argc, char * argv[]) {
	if (argc <= 1 || argc > 3)
		cerr << "Argument count invalid.";
	
	ReadArticles(argv[1]);

	if (argc == 2) {
		// Reading queries from cin
		ReadQueriesCin();
	}
	else {
		// Reading queries from file
		ReadQueriesFile(argv[2]);
	}



}

#pragma region Reading

void ReadArticles(string Path) {
	ifstream file;
	file.open(Path);
	if (!file)
		cerr << "Article file not found.";
	else {
		string id;
		string title;
		string text;
		// assuming 3k+1 lines in file, last being empty
		while (!iswspace(file.peek)) {
			file >> id;
			file >> title;
			file >> text;
			Articles.push_back(Article(id, title, text));
		}
	}
}

void ReadQueriesFile(string Path) {
	ifstream file;
	file.open(Path);
	if (!file)
		cerr << "Queries file not found.";
	else {
		string line;
		string word;		
		while (file.peek) {
			file >> line;
			stringstream ss(line);
			vector<string> query;
			while (getline(ss, word))
				query.push_back(word);
			Queries.push_back(query);
		}
	}
}

void ReadQueriesCin() {
	string line;
	string word;
	while (getline(cin,line)) {
		if (line == "");
			break;
		stringstream ss(line);
		vector<string> query;
		while (getline(ss, word))
			query.push_back(word);
		Queries.push_back(query);
	}
}

#pragma endregion

#pragma region Proccessing

/*
	Alg: Go through all articles and build words, keeping start of it. When word found, add it to WordDict with specific article and it's starting index for quick access.
*/
void CreateWordDict() {
	for (Article ar : Articles) {
		unsigned wordStart;
		bool isBuilding = false;
		string buffer = "";
		for (unsigned it = ar.Text_.begin; it <= ar.Text_.end; ++it) {
			char c = ar.Text_.at(it);
			if (isalpha(c)) {
				// start or middle of word
				if (!isBuilding) {
					isBuilding = true;
					wordStart = it;
				}
				buffer += c;
			}
			else {
				isBuilding = false;
				if (buffer != "") {
					stringToLower(buffer);
					if (WordDict[buffer].find(&ar) == WordDict[buffer].end)
						WordDict[buffer][&ar] = wordStart;
					buffer = "";
				}
			}
		}
	}
}

void ProcQueries() {
	for (vector<string> query : Queries) {

	}
}

#pragma endregion

#pragma region Submethods

void stringToLower(string& input) {
	transform(input.begin, input.end, input.begin, ::tolower);
}

#pragma endregion

#pragma region Printing

void PrintArticles() {
	for (Article ar : Articles) {
		cout << ar.ID_ << endl
			<< ar.Title_ << endl
			<< ar.Text_ << endl;
	}
}

void PrintQuerries() {
	for (vector<string> query : Queries) {
		for (string word : query)
			cout << word;
		cout << endl;
	}
}

#pragma endregion