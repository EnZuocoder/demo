#pragma once
#include<iostream>
#include<string>
using namespace std;
//��Ŀ�࣬������Ŀ��ɣ���ѡ���
class qstore {
public:
	qstore(string qb, string op, string aw);
	void getq();

//��ʵֻ��qmanage����
	string qbody;//���
	string opt;//ѡ��
	string ans;//��
};
