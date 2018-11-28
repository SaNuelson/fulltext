#ifndef IG_181125_1540
#define IG_181125_1540

#include<iostream>
#include<fstream>

#include<string>

#include<vector>
#include<map>

#include<algorithm>

struct Article {
public:
	std::string id;
	std::string title;
	std::string text;
	Article(std::string article_id, std::string article_title, std::string article_text) : id(article_id), title(article_title), text(article_text) {};
	void toString();
};

class fulltext
{

public:

	fulltext(std::istream& articles_in, std::istream& queries_in, std::ostream& output) : articles_in_(articles_in), queries_in_(queries_in), output_(output) {};
	~fulltext();

	void proccess();

private:

	// streams
	std::istream& articles_in_;
	std::istream& queries_in_;
	std::ostream& output_;

	// data containers
	std::vector<Article> articles_;
	std::vector<std::vector<std::string>> queries_;
	std::map<std::string, std::map<Article* const, unsigned>> word_dict_;


	// methods
	void readArticles();
	void readQueries();
	void generateDict();
	void procQueries();
	void printQuery();

	// Algo functions
	void stringToLower(std::string& s);

	// Debug
	void printArticles();
	void printQueries();
	void printWordDict();
	void validateStreams();

};

#endif