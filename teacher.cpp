#include "teacher.h"


// 默认构造
Teacher::Teacher() {}
// 有参构造
Teacher::Teacher(int empId, string name, string pwd) {
    this->m_empId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}


// 菜单
void Teacher::operMenu() {
	cout << "欢迎教师：" << this->m_Name << "登录！" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|        1. 查看所有预约       |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|        2. 审核预约           |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|        0. 注销登录           |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t-------------------------------\n";
}

// 查看所有预约
void Teacher::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		CLEAN_SCREEN;
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		cout << i + 1 << "、";
		cout << " 预约日期：周" << of.m_orderData[i]["date"];
		cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号： " << of.m_orderData[i]["stuId"];
		cout << " 姓名： " << of.m_orderData[i]["stuName"];
		cout << " 机房编号" << of.m_orderData[i]["roomId"];

		string status = " 状态: ";
		if (of.m_orderData[i]["status"] == "1") {
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2") {
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "3") {
			status += "预约失败，审核未通过";
		}
		else {
			status += "预约已取消";
		}
		cout << status << endl;

	}
	CLEAN_SCREEN;
	return;
}

// 审核预约
void Teacher::validOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		CLEAN_SCREEN;
		return;
	}
	cout << "等待审核的预约记录如下:" << endl;
	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++) {

		if (of.m_orderData[i]["status"]=="1") {
			v.push_back(index);
			cout <<index++ << "、";
			cout << " 预约日期：周" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 学号： " << of.m_orderData[i]["stuId"];
			cout << " 姓名： " << of.m_orderData[i]["stuName"];
			cout << " 机房编号" << of.m_orderData[i]["roomId"];

			string status = " 状态: ";
			if (of.m_orderData[i]["status"] == "1") {
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2") {
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "3") {
				status += "预约失败，审核未通过";
			}
			else {
				status += "预约已取消";
			}
			cout << status << endl;
		}
		

	}
	
	string Tip = "请输入审核的预约记录，0代表返回";
	string retTip = "请输入审核结果\n1、通过\n2、不通过";
	int select = 0;
	int ret = 0; // 接受预约结果的记录
	while (true) {
		GET_INPUT(Tip, select);
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				while (true) {
					GET_INPUT(retTip, ret);
					if (ret == 1) {
						// 通过
						of.m_orderData[v[select - 1]]["status"] = 2;
						break;
					}else if(ret == 2) {
						of.m_orderData[v[select - 1]]["status"] = -1;
						break;
					}
					else {
						retTip= "输入有误,请重新输入审核结果\n1、通过\n2、不通过";
						continue;
					}
				}

			}
		}
		Tip = "输入有误，请重新输入审核的预约记录，0代表返回";	
	}
	of.updateOrder();// 更新预约记录；
	cout << "审核完毕" << endl;
	
	CLEAN_SCREEN;
	return;

}
