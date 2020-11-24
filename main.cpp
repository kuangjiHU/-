#include<iostream>
#include<fstream>

#include"Identity.h"
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

using namespace std;



// 进入全局函数的管理员的子菜单
void managerMenu(Identity * &manager) {
	while (true)
	{
		// 调用管理员的子菜单
		manager->operMenu();
		// 将父类指针 转化为子类指针，调用子类中的其他接口
		Manager* man = (Manager*)manager;
		int select = 0;
		GET_INPUT("请输入操作选项", select);
		if (select == 1) {
			// 添加账号
			man->adderson();
		}
		else if (select == 2) {
			// 查看账号
			man->showPerson();
		}
		else if (select == 3) 
		{
			man->showComputer();
			// 查看机房
		}
		else if (select == 4){
			// 清空预约
			man->cleanFile();
		}
		else
		{
			// 注销登录, 
			delete manager;// 销毁堆区对象
			cout << "已注销登录" << endl;
			CLEAN_SCREEN;
			return;
		}

	}
}


// teacher
void teacherMenu(Identity*& teacher) {
	while (true) {
		// 调用子菜单
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select=0;
		GET_INPUT("请选择您的操作", select);
		if (select == 1) {
			// 查看多有的预约
			tea->showAllOrder();
		}
		else if (select == 2) {
			// 审核
			tea->validOrder();
		}
		else {
			// 注销预约
			delete teacher;
			cout << "注销成功" << endl;
			CLEAN_SCREEN;
			return;
		}
	}
}

//学生的子菜单
void stuentMenu(Identity* & student) {
	while (true)
	{
		// 调用学生子菜单
		student->operMenu();
		Student* stu = (Student*)student;
		int select=0;
		GET_INPUT("请输出操作选项：", select);// 接收用户选择
		if (select == 1) {
		// 申请预约
			stu->applyOrder();
		}
		else if (select == 2) {
		// 查看自身预约
			stu->showMyOrder();
		}
		else if (select == 3) {
			// 查看所有人的预约
			stu->showAllOrder();
		}
		else if (select == 4) {
			// 取消预约
			stu->cancelOrder();
		}
		else {
			// 注销预约
			delete student;
			cout << "注销成功" << endl;
			CLEAN_SCREEN;
			return;
		}
	}
}


// 登录函数
void Login(string fileName, int type) {
	// 父类指针，指向子类对象
	Identity* person = NULL;
	// 读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);
	// 判断是否存在文件
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	// 准备接受用户信息
	int id=0;
	string name;
	string pwd;

	//判断身份
	if (type == 1) 
	{
		GET_INPUT("请输入您的学号", id);
	}
	else if(type==2)
	{
		GET_INPUT("请输入您的职工号", id);
	}
	GET_INPUT("请输入用户名", name);
	GET_INPUT("请输入密码", pwd);

	if (type == 1) {
		// 学生身份验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if ((fId == id && fName == name && fPwd == pwd)) {
				cout <<"学生验证通过" << endl;
				system("cls");
				person = new Student(id, name, pwd);
				

				// 进入子菜单
				stuentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) {
		// 老师身份验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if ((fId == id && fName == name && fPwd == pwd)) {
				cout << "教师验证通过" << endl;
				system("cls");

				person = new Teacher(id, name, pwd);
				// 进入子菜单
				teacherMenu(person);

				return;
			}
		}
	}
	else {
		// 管理员身份验证
		string fName;
		string fPwd;
		while ( ifs >> fName && ifs >> fPwd) {
			if ((fName == name && fPwd == pwd)) {
				/*cout << "管理员验证通过" << endl;*/
				system("cls");

				person = new Manager(name, pwd);
				// 进入子菜单
				managerMenu(person);
				return;
			}
		}
	}

	cout << "验证登录失败" << endl;
	CLEAN_SCREEN;
}


int main() {

	int select;// 用于接收用户的选择
	while (true) {
		cout << "=======================欢迎来到糊咚机房预约系统==========================" << endl;
		cout << endl;
		cout << "登录身份选择：" << endl;
		cout << "\t\t-------------------------------------------\n" ;
		cout << "\t\t|                                         |\n";
		cout << "\t\t|              1. 学生代表                |\n";
		cout << "\t\t|                                         |\n";
		cout << "\t\t|              2. 教    师                |\n";
		cout << "\t\t|                                         |\n";
		cout << "\t\t|              3. 管 理 员                |\n";
		cout << "\t\t|                                         |\n";
		cout << "\t\t|              0. 退     出               |\n";
		cout << "\t\t|                                         |\n";
		cout << "\t\t-------------------------------------------\n";

		GET_INPUT("请选择您的身份", select);
		switch (select)
		{
		case 0:
			// 退出
			cout << "欢迎下次使用" << endl;
			cout << endl;
			system("pause");
			return 0;
			break;
		case 1:
			// 学生
			Login(STUDENT_FILE, 1);
			break;
		case 2:
			// 老师
			Login(TEACHER_FILE, 2);

			break;
		case 3:
			// 管理员
			Login(ADMIN_FILE, 3);
			break;

		default:
			cout << "输入有误请重新输入" << endl;
			CLEAN_SCREEN;
			break;
		}
	}
	
	CLEAN_SCREEN;

	return 0;
}