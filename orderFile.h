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
	// 更新预约记录
	void updateOrder();
	// 记录预约条数
	int m_Size;
	// 记录所有预约信息， key 记录条数， value记录
	map<int, map<string, string >> m_orderData;
};

