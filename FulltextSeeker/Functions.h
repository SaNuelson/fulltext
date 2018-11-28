#ifndef IG_181124_2049
#define IG_181124_2049

#include<iostream>
#include<string>
#include<vector>
#include<map>

/*
	Custom structs
*/

struct Article {
public:
	std::string ID_;
	std::string Title_;
	std::string Text_;
	Article(std::string ID, std::string Title, std::string Text) : ID_(ID), Title_(Title), Text_(Text) { };
};


#endif
