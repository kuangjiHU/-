#pragma once
#include "Identity.h"
#include"globalFile.h"
#include"orderFile.h"
#include<vector>


class Teacher :public Identity
{
public:
	// 默认构造
	Teacher();
	// 有参构造
	Teacher(int empId, string name, string pwd);
	

	// 菜单
	virtual void operMenu();

	// 查看所有预约
	void showAllOrder();

	// 审核预约
	void validOrder();

	
	// 职工函数
	int m_empId;
};

