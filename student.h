#pragma once
#include<vector>
#include<fstream>
#include"globalFile.h"
#include "Identity.h"
#include"computerRoom.h"
#include "orderFile.h"


class Student : public Identity
{
public:
	// Ĭ�Ϲ���
	Student();
	// �вι��죬ѧ�ţ�����������
	Student(int id, string name, string pwd);
	// �˵�
	virtual void operMenu();

	// ����ԤԼ
	void  applyOrder();

	// �鿴�ҵ�ԤԼ
	void showMyOrder();
	
	// ��ʾ�����˵�ԤԼ
	void showAllOrder();

	// ȡ��ԤԼ
	void cancelOrder();
	
	// ע����¼
	
	int m_Id;
	// �Ż�����Ϣ������
	vector<ComputerRoom> vCom;
};

