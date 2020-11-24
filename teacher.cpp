#include "teacher.h"


// Ĭ�Ϲ���
Teacher::Teacher() {}
// �вι���
Teacher::Teacher(int empId, string name, string pwd) {
    this->m_empId = empId;
    this->m_Name = name;
    this->m_Pwd = pwd;
}


// �˵�
void Teacher::operMenu() {
	cout << "��ӭ��ʦ��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|        1. �鿴����ԤԼ       |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|        2. ���ԤԼ           |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|        0. ע����¼           |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t-------------------------------\n";
}

// �鿴����ԤԼ
void Teacher::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼" << endl;
		CLEAN_SCREEN;
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		cout << i + 1 << "��";
		cout << " ԤԼ���ڣ���" << of.m_orderData[i]["date"];
		cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " ѧ�ţ� " << of.m_orderData[i]["stuId"];
		cout << " ������ " << of.m_orderData[i]["stuName"];
		cout << " �������" << of.m_orderData[i]["roomId"];

		string status = " ״̬: ";
		if (of.m_orderData[i]["status"] == "1") {
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2") {
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "3") {
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else {
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;

	}
	CLEAN_SCREEN;
	return;
}

// ���ԤԼ
void Teacher::validOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼" << endl;
		CLEAN_SCREEN;
		return;
	}
	cout << "�ȴ���˵�ԤԼ��¼����:" << endl;
	vector<int> v;
	int index = 1;
	for (int i = 0; i < of.m_Size; i++) {

		if (of.m_orderData[i]["status"]=="1") {
			v.push_back(index);
			cout <<index++ << "��";
			cout << " ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ѧ�ţ� " << of.m_orderData[i]["stuId"];
			cout << " ������ " << of.m_orderData[i]["stuName"];
			cout << " �������" << of.m_orderData[i]["roomId"];

			string status = " ״̬: ";
			if (of.m_orderData[i]["status"] == "1") {
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2") {
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_orderData[i]["status"] == "3") {
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else {
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
		

	}
	
	string Tip = "��������˵�ԤԼ��¼��0������";
	string retTip = "��������˽��\n1��ͨ��\n2����ͨ��";
	int select = 0;
	int ret = 0; // ����ԤԼ����ļ�¼
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
						// ͨ��
						of.m_orderData[v[select - 1]]["status"] = 2;
						break;
					}else if(ret == 2) {
						of.m_orderData[v[select - 1]]["status"] = -1;
						break;
					}
					else {
						retTip= "��������,������������˽��\n1��ͨ��\n2����ͨ��";
						continue;
					}
				}

			}
		}
		Tip = "��������������������˵�ԤԼ��¼��0������";	
	}
	of.updateOrder();// ����ԤԼ��¼��
	cout << "������" << endl;
	
	CLEAN_SCREEN;
	return;

}
