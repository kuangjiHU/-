#pragma once
#include<vector>
#include<fstream>
#include"globalFile.h"
#include "Identity.h"
#include"computerRoom.h"
#include "orderFile.h"


class Student : public Identity
{
public:
	// 默认构造
	Student();
	// 有参构造，学号，姓名，密码
	Student(int id, string name, string pwd);
	// 菜单
	virtual void operMenu();

	// 申请预约
	void  applyOrder();

	// 查看我的预约
	void showMyOrder();
	
	// 显示所有人的预约
	void showAllOrder();

	// 取消预约
	void cancelOrder();
	
	// 注销登录
	
	int m_Id;
	// 放机房信息的容器
	vector<ComputerRoom> vCom;
};

