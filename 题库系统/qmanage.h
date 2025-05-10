#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<qstore.h>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<random>
using namespace std;
//题库管理类
class qmanage
{
  public:
	qmanage();
	~qmanage();

	void showqmenu();//展现题库管理子菜单
	void saveq();//保存题目到文本文件
	int getqnum();//获取当前题库中题目数量
	void initq();//初始化题库，将文本题库读到堆区
	void addq();//增加题目
	void seeq();//看所有题目
	void cleanq();//清空题库
	void answerfunc();//答题模块
	void editq();//编辑修改题目板块
	int randnum(int i,int num);//产生随机数的函数
	bool isempty;//判断文件是否为空的布尔量
	int qnum;//记录现有题目数量
	qstore** qarry;//指向题目的二级指针 本系统最重要的东西
};

