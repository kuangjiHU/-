#pragma once
#include<fstream>
#include<vector>
#include<algorithm>
#include "Identity.h"
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"


class Manager : public Identity
{
public:
	// 默认构造
	Manager();
	// 有参构造
	Manager(string name, string pwd);
	// 菜单
	virtual void operMenu();
	// 添加账号
	void adderson();
	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();

	// 初始化容器
	void initVector();
	// 检测重复；重复返回true， 参数一职工号或者id
	bool checkRepeat(int id, int type);


	// 属性
	vector<Student> vStu;
	vector<Teacher> vTea;
	vector<ComputerRoom> vCom;
	

};

