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
//��������
class qmanage
{
  public:
	qmanage();
	~qmanage();

	void showqmenu();//չ���������Ӳ˵�
	void saveq();//������Ŀ���ı��ļ�
	int getqnum();//��ȡ��ǰ�������Ŀ����
	void initq();//��ʼ����⣬���ı�����������
	void addq();//������Ŀ
	void seeq();//��������Ŀ
	void cleanq();//������
	void answerfunc();//����ģ��
	void editq();//�༭�޸���Ŀ���
	int randnum(int i,int num);//����������ĺ���
	bool isempty;//�ж��ļ��Ƿ�Ϊ�յĲ�����
	int qnum;//��¼������Ŀ����
	qstore** qarry;//ָ����Ŀ�Ķ���ָ�� ��ϵͳ����Ҫ�Ķ���
};

