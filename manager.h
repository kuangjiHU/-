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
	// Ĭ�Ϲ���
	Manager();
	// �вι���
	Manager(string name, string pwd);
	// �˵�
	virtual void operMenu();
	// ����˺�
	void adderson();
	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();

	// ��ʼ������
	void initVector();
	// ����ظ����ظ�����true�� ����һְ���Ż���id
	bool checkRepeat(int id, int type);


	// ����
	vector<Student> vStu;
	vector<Teacher> vTea;
	vector<ComputerRoom> vCom;
	

};

