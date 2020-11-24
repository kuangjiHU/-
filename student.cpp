#include "student.h"


// 默认构造
Student::Student() {}

// 有参构造，学号，姓名，密码
Student::Student(int id, string name, string pwd) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId&& ifs >> com.m_MaxNum) {
		vCom.push_back(com);
	}
	ifs.close();

}

// 菜单
void Student::operMenu() {
	cout << "欢迎学生代表：" << this->m_Name << "登录！" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         1. 申请预约          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         2. 查看我的预约      |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         3. 查看所有预约      |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         4. 取消预约          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         0. 注销登录          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t-------------------------------\n";

}

// 申请预约
void  Student::applyOrder() {
	cout << "机房开放时间为周一至周五！" << endl;
	int date = 0;
	int interval = 0;
	int room = 0;
	string dateTip = "请输入申请预约时间：\n1、周一\n2、周二\n3、周三\n4、周四\n5、周五\n";
	string intervalTip = "请输入时间段：\n1、上午\n2、下午\n";
	string roomTip = "请输入预约房间编号";
	while (true) {
		GET_INPUT(dateTip, date);
		if (date >= 1 && date <= 5) {
			break;
		}
		dateTip = "输入有误，请重新输入申请预约时间：\n1、周一\n2、周二\n3、周三\n4、周四\n5、周五\n";
	}
	while (true) {
		GET_INPUT(intervalTip, interval);
		if (interval >= 1 && interval <= 2) {
			break;
		}
		intervalTip = "输入有误，请重新输入时间段：\n1、上午\n2、下午\n";
	}

	while (true) {
		for (int i = 0; i < vCom.size(); i++) {
			cout << vCom[i].m_ComId << "号机房容量为：" << vCom[i].m_MaxNum << endl;
		}
		GET_INPUT(roomTip, room);
		if (room >= 1 && room <= vCom.size()) {
			break;
		}
		roomTip = "输入有误,请输入预约房间编号";
	}
	cout << "预约成功！审核中" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:"<<this->m_Name << " ";
	ofs << "roomId:" << room <<" ";
	ofs << "status:" << 1 << endl;
	ofs.close();
	CLEAN_SCREEN;
}

// 查看我的预约
void Student::showMyOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录"<<endl;
		CLEAN_SCREEN;
		return;

	}
	for (int i = 0; i < of.m_Size; i++) {
		// 先转换成c语言风格字符串c_str()
		// atoi(const char*)//string 转int
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			cout << "预约日期：周" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房编号" << of.m_orderData[i]["roomId"];
			
			string status = " 状态: ";
			if (of.m_orderData[i]["status"] == "1") {
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2") {
				status += "预约成功";
			} 
			else if(of.m_orderData[i]["status"] == "3") {
				status += "预约失败，审核未通过";
			}
			else {
				status += "预约已取消";
			}
			cout << status<< endl;
			
		}
	
	}
	CLEAN_SCREEN;
	return;
}

// 显示所有人的预约
void Student::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		CLEAN_SCREEN;
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		cout << i + 1<< "、";
		cout << " 预约日期：周" << of.m_orderData[i]["date"];
		cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号： "<< of.m_orderData[i]["stuId"];
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

// 取消预约
void Student::cancelOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		CLEAN_SCREEN;
		return;
	}
	cout << "审核中或预约成功的记录可以取消" << endl;;
	vector<int> v;// 存放最大容器中的下标编号
	int index = 1;
	for (int i = 0; i < of.m_Size; i++) {
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			// 筛选状态
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
				// 
				v.push_back(i);
				cout << index++<< "、";
				cout << " 预约日期：周" << of.m_orderData[i]["date"];
				cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房编号" << of.m_orderData[i]["roomId"];
				string status = " 状态: ";
				if (of.m_orderData[i]["status"] == "1") {
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2") {
					status += "预约成功";
				}
				cout << status << endl;
			}

		}
	}

	int select = 0;
	string Tip = "请输入取消的记录，0代表返回";
	while (true){
		GET_INPUT(Tip, select);
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
			}
		
		}
		Tip = "请重新输入，0 代表返回";

	}
	CLEAN_SCREEN;
	return;
}