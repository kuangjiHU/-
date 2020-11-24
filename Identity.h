#pragma once
#include<iostream>

using namespace std;

class Identity 
{
public:
	// 菜单 纯虚函数
	virtual void operMenu()=0;

	// 用户名
	string  m_Name;

	// 密码
	string m_Pwd;
};