#include "student.h"


// Ĭ�Ϲ���
Student::Student() {}

// �вι��죬ѧ�ţ�����������
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

// �˵�
void Student::operMenu() {
	cout << "��ӭѧ������" << this->m_Name << "��¼��" << endl;
	cout << "\t\t-------------------------------\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         1. ����ԤԼ          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         2. �鿴�ҵ�ԤԼ      |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         3. �鿴����ԤԼ      |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         4. ȡ��ԤԼ          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t|         0. ע����¼          |\n";
	cout << "\t\t|                              |\n";
	cout << "\t\t-------------------------------\n";

}

// ����ԤԼ
void  Student::applyOrder() {
	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	int date = 0;
	int interval = 0;
	int room = 0;
	string dateTip = "����������ԤԼʱ�䣺\n1����һ\n2���ܶ�\n3������\n4������\n5������\n";
	string intervalTip = "������ʱ��Σ�\n1������\n2������\n";
	string roomTip = "������ԤԼ������";
	while (true) {
		GET_INPUT(dateTip, date);
		if (date >= 1 && date <= 5) {
			break;
		}
		dateTip = "����������������������ԤԼʱ�䣺\n1����һ\n2���ܶ�\n3������\n4������\n5������\n";
	}
	while (true) {
		GET_INPUT(intervalTip, interval);
		if (interval >= 1 && interval <= 2) {
			break;
		}
		intervalTip = "������������������ʱ��Σ�\n1������\n2������\n";
	}

	while (true) {
		for (int i = 0; i < vCom.size(); i++) {
			cout << vCom[i].m_ComId << "�Ż�������Ϊ��" << vCom[i].m_MaxNum << endl;
		}
		GET_INPUT(roomTip, room);
		if (room >= 1 && room <= vCom.size()) {
			break;
		}
		roomTip = "��������,������ԤԼ������";
	}
	cout << "ԤԼ�ɹ��������" << endl;

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

// �鿴�ҵ�ԤԼ
void Student::showMyOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼"<<endl;
		CLEAN_SCREEN;
		return;

	}
	for (int i = 0; i < of.m_Size; i++) {
		// ��ת����c���Է���ַ���c_str()
		// atoi(const char*)//string תint
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " �������" << of.m_orderData[i]["roomId"];
			
			string status = " ״̬: ";
			if (of.m_orderData[i]["status"] == "1") {
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2") {
				status += "ԤԼ�ɹ�";
			} 
			else if(of.m_orderData[i]["status"] == "3") {
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else {
				status += "ԤԼ��ȡ��";
			}
			cout << status<< endl;
			
		}
	
	}
	CLEAN_SCREEN;
	return;
}

// ��ʾ�����˵�ԤԼ
void Student::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼" << endl;
		CLEAN_SCREEN;
		return;
	}
	for (int i = 0; i < of.m_Size; i++) {
		cout << i + 1<< "��";
		cout << " ԤԼ���ڣ���" << of.m_orderData[i]["date"];
		cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " ѧ�ţ� "<< of.m_orderData[i]["stuId"];
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

// ȡ��ԤԼ
void Student::cancelOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼" << endl;
		CLEAN_SCREEN;
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ��" << endl;;
	vector<int> v;// �����������е��±���
	int index = 1;
	for (int i = 0; i < of.m_Size; i++) {
		if (this->m_Id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			// ɸѡ״̬
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
				// 
				v.push_back(i);
				cout << index++<< "��";
				cout << " ԤԼ���ڣ���" << of.m_orderData[i]["date"];
				cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << " �������" << of.m_orderData[i]["roomId"];
				string status = " ״̬: ";
				if (of.m_orderData[i]["status"] == "1") {
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2") {
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}

		}
	}

	int select = 0;
	string Tip = "������ȡ���ļ�¼��0������";
	while (true){
		GET_INPUT(Tip, select);
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "��ȡ��ԤԼ" << endl;
			}
		
		}
		Tip = "���������룬0 ������";

	}
	CLEAN_SCREEN;
	return;
}