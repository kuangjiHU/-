#include "manager.h"



void printStu(Student &p) {
	cout <<"ѧ��: " <<p.m_Id << "\t������"<< p.m_Name << "\t���룺"<< p.m_Pwd << endl;
}
void printTea(Teacher &p) {
	cout <<"��ְ������: " <<p.m_empId << "\t������"<< p.m_Name << "\t���룺" << p.m_Pwd  << endl;
}
void printCom(ComputerRoom &c) {
	cout <<"�������: " <<c.m_ComId << "\t�������������"<< c.m_MaxNum << endl;
}

// Ĭ�Ϲ���
Manager::Manager() {}

// �вι���
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;
	// ��ʼ������������ȡ������ʦ��ѧ������Ϣ
	this->initVector();
	// ��ʼ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "������Ϣ�ļ�ȱʧ" << endl;
		system("pause");
		exit(0);
	}
	ComputerRoom com;
	while (ifs >> com.m_ComId&& ifs >> com.m_MaxNum) {
		this->vCom.push_back(com);
	}
	ifs.close();
	// �������������
	cout << "����������Ϊ��" << this->vCom.size() << endl;

}

// �˵�
void Manager::operMenu(){
	cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         1. ����˺�          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         2. �鿴�˺�          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         3. �鿴����          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         4. ���ԤԼ          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         0. ע����¼          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t-------------------------------\n";

}

// ����˺�
void Manager::adderson() {

	string fileName;
	string tip; // id����ְ�����
	string errorTip;

	ofstream ofs;// �ļ�����
	int select=0;
	GET_INPUT("����������˺ŵ�����,1-���ѧ�� 2-�����ʦ", select);
	if (select == 1) {
		fileName = STUDENT_FILE;
		tip = "������ѧ��";
		errorTip = "ѧ���ظ�,����������";
	}
	else{
		// Ĭ������ʦ
		fileName = TEACHER_FILE;
		tip = "�������ʦְ����";
		errorTip = "ְ�����ظ���,����������";

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
	GET_INPUT("����������", name);
	GET_INPUT("����������", pwd);
	// ���ļ����������
	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ�" << endl;
	CLEAN_SCREEN;
	ofs.close();
	// ���ó�ʼ�������Ľӿ����»�ȡ�ļ��е�����
	this->initVector();

}

//�鿴�˺�
void Manager::showPerson() {

	int select = 0;
	GET_INPUT("��ѡ��鿴�����ݣ�1-�鿴���е�ѧ���� 2-�鿴���е���ʦ", select);
	if (select == 1) {
	// ѧ��
		cout << "���е�ѧ����Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printStu);
	}
	else {
		//��ʦ
		cout << "���е���ʦ��Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printTea);
	}
	CLEAN_SCREEN;
}


//�鿴������Ϣ
void Manager::showComputer() {
	cout << "��������Ϣ����:" << endl;
	for_each(vCom.begin(), vCom.end(), printCom);
	CLEAN_SCREEN;
}

//���ԤԼ��¼
void Manager::cleanFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "��ճɹ�!" << endl;
	CLEAN_SCREEN;
}

// ��ʼ������
void Manager::initVector() {
	// ��ȷ���������״̬
	this->vStu.clear();
	this->vTea.clear();
	
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()){
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id&& ifs >> s.m_Name&& ifs >> s.m_Pwd) {
		this->vStu.push_back(s);
	}
	ifs.close();
	// ��ǰ��ѧ��
	cout << "��ǰ��ѧ������Ϊ: " << vStu.size() << endl;
	Teacher t ;
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	while (ifs >> t.m_empId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		this->vTea.push_back(t);
	}
	cout << "��ǰ����ʦ����Ϊ: " << vTea.size() << endl;

}

// ����ظ����ظ�����true�� ����һְ���Ż���id
bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		// ���ѧ��
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++) {
			if (id == it->m_Id) {
				return true;
			}
		}
	}
	else {
		// �����ʦ
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
			if (id == it->m_empId) {
				return true;
			}
		}
	}
	return false;
}

