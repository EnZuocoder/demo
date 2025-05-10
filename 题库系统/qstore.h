#pragma once
#include<iostream>
#include<string>
using namespace std;
//题目类，包含题目题干，备选项，答案
class qstore {
public:
	qstore(string qb, string op, string aw);
	void getq();

//其实只给qmanage访问
	string qbody;//题干
	string opt;//选项
	string ans;//答案
};
