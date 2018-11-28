#include<iostream>
#include<fstream>
#include<sstream>

#include<string>

#include<vector>
#include<map>

#include "fulltext.h"

using namespace std;

// DEBUG DEFINITION
#define DEBUG
// DEBUG DEFINITION

fulltext::~fulltext() {
};

void fulltext::proccess() {

#ifdef DEBUG
	validateStreams();
#endif

	readArticles();

#ifdef DEBUG
	printArticles();
#endif

	readQueries();

#ifdef DEBUG
	printQueries();
#endif

	generateDict();

#ifdef DEBUG
	printWordDict();
#endif

	//procQueries();
}

void fulltext::readArticles() {
	string id;
	string title;
	string text;
	// assuming 3k+1 lines in file, last being empty
	while (getline(articles_in_,id)) {
		cout << "ID" << id << endl;
		if (id == "")
			break;
		getline(articles_in_, title);
		getline(articles_in_, text);
		Article ar(id, title, text);
		ar.toString();
		articles_.push_back(ar);
	}
}

void fulltext::readQueries() {
	string line;
	string word;
	while (getline(queries_in_,line)) {
		stringstream ss(line);
		vector<string> query;
		while (getline(ss, word))
			query.push_back(word);
		queries_.push_back(query);
	}
}

void fulltext::generateDict() {
	for (const Article &ar : articles_) {
		unsigned wordStart;
		bool isBuilding = false;
		string buffer = "";
		for (unsigned int it = 0; it <= ar.text.size(); ++it) {
			char c;
			if (it < ar.text.size())
				c = ar.text.at(it);
			else
				c = '\0';

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
					cout << "Saving " << buffer << " - " << ar.id << " - " << wordStart << endl;
					stringToLower(buffer);
					word_dict_[buffer][&ar] = wordStart;
					/*
					if (word_dict_[buffer].find(&ar) == word_dict_[buffer].end())
						word_dict_[buffer][&ar] = wordStart;
					*/
					buffer = "";
				}
			}
		}
	}
}

void fulltext::procQueries() {

	for (vector<string> query : queries_) {
		vector<string> wordIntersection;
		vector<Article*> queryPositions;
		for (string word : query) {
			queryPositions.push_back(word_dict_[word].begin()->first);
		}

			// take all words of query and start at their first Article*s.
			// if all of them equal, add to wordIntersection
			// else move ++Article* to every word that is less than max Article*
			for (;;) {

			}
	}

}

void fulltext::printQuery() {

}

void fulltext::stringToLower(std::string & s){
	transform(s.begin(), s.end(), s.begin(), tolower);
}

#pragma region Debug

void fulltext::printArticles() {

	cout << "Printing articles: " << endl;

	for (Article ar : articles_) {
		ar.toString();
	}
	cout << "Done." << endl;
}

void fulltext::printQueries() {

	cout << "Printing queries: " << endl;

	for (vector<string> query : queries_) {
		for (string word : query) {
			cout << word << " ";
		}
		cout << endl;
	}
	cout << "Done." << endl;

}

void fulltext::printWordDict() {
	
	cout << "Printing generated word dictionary: " << endl;
	
	for (auto wordPair : word_dict_) {
		cout << " \" " << wordPair.first << " \" " << endl;
		cout << "There are " << wordPair.second.size() << " inputs." << endl;
		for (pair<Article*, unsigned int> articlePair : wordPair.second) {
			auto ar = articlePair.first;
			cout << (*ar).id << endl;

		}
		cout << endl;
	}
	cout << "Done." << endl;
}

void fulltext::validateStreams() {
	string temp;
	
	cout << " --- Starting fulltext stream validation. --- " << endl;

	try{
		cout << "Reading articles_in_..." << endl;
		temp = articles_in_.peek();
		cout << "Articles_in_ read: " << temp << endl;
	}
	catch (exception& e) {
		cout << "Failed to read articles_in_" << endl
			<< e.what() << endl;
	}

	try {
		cout << "Reading queries_in_..." << endl;
		temp = articles_in_.peek();
		cout << "Queries_in_ read: " << temp << endl;
	}
	catch (exception& e) {
		cout << "Failed to read queries_in_" << endl
			<< e.what() << endl;
	}

	try {
		cout << "Writing to output_..." << endl;
		output_ << "Test string to output_." << endl;
		cout << "Written to output_." << endl;
	}
	catch (exception& e) {
		cout << "Failed to write to output_." << endl
			<< e.what() << endl;
	}

	cout << " --- Ending fulltext stream validation. --- " << endl;

}

#pragma endregion

void Article::toString()
{
	cout << endl
		<< "    " << id << endl
		<< "  " << title << endl
		<< "  " << text << endl
		<< endl;
}
