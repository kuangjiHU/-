#pragma once
#include<iostream>
#include<fstream>
#include<map>
#include<algorithm>

#include"globalFile.h"

using namespace std;

class OrderFile
{
public:
	OrderFile();
	// ����ԤԼ��¼
	void updateOrder();
	// ��¼ԤԼ����
	int m_Size;
	// ��¼����ԤԼ��Ϣ�� key ��¼������ value��¼
	map<int, map<string, string >> m_orderData;
};

