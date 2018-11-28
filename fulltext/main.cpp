#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "fulltext.h"
#include<fstream>

using namespace std;


int main(int argc, char* argv[]) {
	
	if (argc < 2 || argc > 3) {
		cout << "Argc: " << argc;
		return 1;
	}
	
	ifstream article_in;
	ifstream query_in;
	ofstream output;

	istream *query_in_ptr;
	istream *article_in_ptr;
	ostream *output_ptr;

	if (argc == 2) {
		// Queries from std_in
		string articlePath = argv[1];

		article_in.open(articlePath);

		query_in_ptr = &cin;
		article_in_ptr = &article_in;
		output_ptr = &cout;
	}
	else {
		// Queries from file
		string articlePath = argv[1];
		string queryPath = argv[2];

		article_in.open(articlePath);
		query_in.open(queryPath);

		article_in_ptr = &article_in;
		query_in_ptr = &query_in;
		output_ptr = &cout;
	}

	fulltext ft(*article_in_ptr, *query_in_ptr, *output_ptr);
	ft.proccess();

	try {
		article_in.close();
		query_in.close();
		output.close();
	}
	catch(exception e){
		;
	}

	return 0;

}