#include<iostream>
#include<fstream>

#include"Identity.h"
#include"globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

using namespace std;



// ����ȫ�ֺ����Ĺ���Ա���Ӳ˵�
void managerMenu(Identity * &manager) {
	while (true)
	{
		// ���ù���Ա���Ӳ˵�
		manager->operMenu();
		// ������ָ�� ת��Ϊ����ָ�룬���������е������ӿ�
		Manager* man = (Manager*)manager;
		int select = 0;
		GET_INPUT("���������ѡ��", select);
		if (select == 1) {
			// ����˺�
			man->adderson();
		}
		else if (select == 2) {
			// �鿴�˺�
			man->showPerson();
		}
		else if (select == 3) 
		{
			man->showComputer();
			// �鿴����
		}
		else if (select == 4){
			// ���ԤԼ
			man->cleanFile();
		}
		else
		{
			// ע����¼, 
			delete manager;// ���ٶ�������
			cout << "��ע����¼" << endl;
			CLEAN_SCREEN;
			return;
		}

	}
}


// teacher
void teacherMenu(Identity*& teacher) {
	while (true) {
		// �����Ӳ˵�
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select=0;
		GET_INPUT("��ѡ�����Ĳ���", select);
		if (select == 1) {
			// �鿴���е�ԤԼ
			tea->showAllOrder();
		}
		else if (select == 2) {
			// ���
			tea->validOrder();
		}
		else {
			// ע��ԤԼ
			delete teacher;
			cout << "ע���ɹ�" << endl;
			CLEAN_SCREEN;
			return;
		}
	}
}

//ѧ�����Ӳ˵�
void stuentMenu(Identity* & student) {
	while (true)
	{
		// ����ѧ���Ӳ˵�
		student->operMenu();
		Student* stu = (Student*)student;
		int select=0;
		GET_INPUT("���������ѡ�", select);// �����û�ѡ��
		if (select == 1) {
		// ����ԤԼ
			stu->applyOrder();
		}
		else if (select == 2) {
		// �鿴����ԤԼ
			stu->showMyOrder();
		}
		else if (select == 3) {
			// �鿴�����˵�ԤԼ
			stu->showAllOrder();
		}
		else if (select == 4) {
			// ȡ��ԤԼ
			stu->cancelOrder();
		}
		else {
			// ע��ԤԼ
			delete student;
			cout << "ע���ɹ�" << endl;
			CLEAN_SCREEN;
			return;
		}
	}
}


// ��¼����
void Login(string fileName, int type) {
	// ����ָ�룬ָ���������
	Identity* person = NULL;
	// ���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);
	// �ж��Ƿ�����ļ�
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	// ׼�������û���Ϣ
	int id=0;
	string name;
	string pwd;

	//�ж����
	if (type == 1) 
	{
		GET_INPUT("����������ѧ��", id);
	}
	else if(type==2)
	{
		GET_INPUT("����������ְ����", id);
	}
	GET_INPUT("�������û���", name);
	GET_INPUT("����������", pwd);

	if (type == 1) {
		// ѧ�������֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if ((fId == id && fName == name && fPwd == pwd)) {
				cout <<"ѧ����֤ͨ��" << endl;
				system("cls");
				person = new Student(id, name, pwd);
				

				// �����Ӳ˵�
				stuentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) {
		// ��ʦ�����֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if ((fId == id && fName == name && fPwd == pwd)) {
				cout << "��ʦ��֤ͨ��" << endl;
				system("cls");

				person = new Teacher(id, name, pwd);
				// �����Ӳ˵�
				teacherMenu(person);

				return;
			}
		}
	}
	else {
		// ����Ա�����֤
		string fName;
		string fPwd;
		while ( ifs >> fName && ifs >> fPwd) {
			if ((fName == name && fPwd == pwd)) {
				/*cout << "����Ա��֤ͨ��" << endl;*/
				system("cls");

				person = new Manager(name, pwd);
				// �����Ӳ˵�
				managerMenu(person);
				return;
			}
		}
	}

	cout << "��֤��¼ʧ��" << endl;
	CLEAN_SCREEN;
}


int main() {

	int select;// ���ڽ����û���ѡ��
	while (true) {
		cout << "=======================��ӭ�������˻���ԤԼϵͳ==========================" << endl;
		cout << endl;
		cout << "��¼���ѡ��" << endl;
		cout << "\t\t-------------------------------------------\n" ;
		cout << "\t\t|                                         |\n";
		cout << "\t\t|              1. ѧ������                |\n";
		cout << "\t\t|                                         |\n";
		cout << "\t\t|              2. ��    ʦ                |\n";
		cout << "\t\t|                                         |\n";
		cout << "\t\t|              3. �� �� Ա                |\n";
		cout << "\t\t|                                         |\n";
		cout << "\t\t|              0. ��     ��               |\n";
		cout << "\t\t|                                         |\n";
		cout << "\t\t-------------------------------------------\n";

		GET_INPUT("��ѡ���������", select);
		switch (select)
		{
		case 0:
			// �˳�
			cout << "��ӭ�´�ʹ��" << endl;
			cout << endl;
			system("pause");
			return 0;
			break;
		case 1:
			// ѧ��
			Login(STUDENT_FILE, 1);
			break;
		case 2:
			// ��ʦ
			Login(TEACHER_FILE, 2);

			break;
		case 3:
			// ����Ա
			Login(ADMIN_FILE, 3);
			break;

		default:
			cout << "������������������" << endl;
			CLEAN_SCREEN;
			break;
		}
	}
	
	CLEAN_SCREEN;

	return 0;
}