#include "manager.h"



void printStu(Student &p) {
	cout <<"学号: " <<p.m_Id << "\t姓名："<< p.m_Name << "\t密码："<< p.m_Pwd << endl;
}
void printTea(Teacher &p) {
	cout <<"教职工工号: " <<p.m_empId << "\t姓名："<< p.m_Name << "\t密码：" << p.m_Pwd  << endl;
}
void printCom(ComputerRoom &c) {
	cout <<"机房编号: " <<c.m_ComId << "\t机房最大容量："<< c.m_MaxNum << endl;
}

// 默认构造
Manager::Manager() {}

// 有参构造
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;
	// 初始化容器，并获取所有老师，学生的信息
	this->initVector();
	// 初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "机房信息文件缺失" << endl;
		system("pause");
		exit(0);
	}
	ComputerRoom com;
	while (ifs >> com.m_ComId&& ifs >> com.m_MaxNum) {
		this->vCom.push_back(com);
	}
	ifs.close();
	// 输出机房的数量
	cout << "机房的数量为：" << this->vCom.size() << endl;

}

// 菜单
void Manager::operMenu(){
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         1. 添加账号          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         2. 查看账号          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         3. 查看机房          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         4. 清空预约          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         0. 注销登录          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t-------------------------------\n";

}

// 添加账号
void Manager::adderson() {

	string fileName;
	string tip; // id还是职工编号
	string errorTip;

	ofstream ofs;// 文件操作
	int select=0;
	GET_INPUT("请输入添加账号的类型,1-添加学生 2-添加老师", select);
	if (select == 1) {
		fileName = STUDENT_FILE;
		tip = "请输入学号";
		errorTip = "学号重复,请重新输入";
	}
	else{
		// 默认是老师
		fileName = TEACHER_FILE;
		tip = "请输入教师职工号";
		errorTip = "职工号重复，,请重新输入";

	}
	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	while (true) {
		GET_INPUT(tip, id);
		bool ret = this->checkRepeat(id, select);
		if (ret) {
			tip = errorTip;
		}
		else {
			break;
		}
	}
	GET_INPUT("请输入姓名", name);
	GET_INPUT("请输入密码", pwd);
	// 向文件中添加数据
	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功" << endl;
	CLEAN_SCREEN;
	ofs.close();
	// 调用初始化容器的接口重新获取文件中的数据
	this->initVector();

}

//查看账号
void Manager::showPerson() {

	int select = 0;
	GET_INPUT("请选择查看的内容，1-查看所有的学生， 2-查看所有的老师", select);
	if (select == 1) {
	// 学生
		cout << "所有的学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStu);
	}
	else {
		//老师
		cout << "所有的老师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTea);
	}
	CLEAN_SCREEN;
}


//查看机房信息
void Manager::showComputer() {
	cout << "机房的信息如下:" << endl;
	for_each(vCom.begin(), vCom.end(), printCom);
	CLEAN_SCREEN;
}

//清空预约记录
void Manager::cleanFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功!" << endl;
	CLEAN_SCREEN;
}

// 初始化容器
void Manager::initVector() {
	// 先确保容器清空状态
	this->vStu.clear();
	this->vTea.clear();
	
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()){
		cout << "文件读取失败" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id&& ifs >> s.m_Name&& ifs >> s.m_Pwd) {
		this->vStu.push_back(s);
	}
	ifs.close();
	// 当前的学生
	cout << "当前的学生数量为: " << vStu.size() << endl;
	Teacher t ;
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件读取失败" << endl;
		return;
	}
	while (ifs >> t.m_empId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		this->vTea.push_back(t);
	}
	cout << "当前的老师数量为: " << vTea.size() << endl;

}

// 检测重复；重复返回true， 参数一职工号或者id
bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		// 检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++) {
			if (id == it->m_Id) {
				return true;
			}
		}
	}
	else {
		// 检测老师
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
			if (id == it->m_empId) {
				return true;
			}
		}
	}
	return false;
}

