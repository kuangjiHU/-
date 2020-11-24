#include "orderFile.h"


void streachString(map<string, string>&m,string s) {
	
	string key;
	string value;
	size_t pos = s.find(":");
	if (pos != -1) {
		
		key = s.substr(0, pos);
		value = s.substr(pos + 1, s.size() - pos - 1);
		/*cout << "key=" << key << endl;
		cout << "value=" << value << endl;*/
		m.insert(make_pair(key, value));
	}
}

void printMap(pair<string, string> val) {
	cout << val.first << " " << val.second << endl;
}


OrderFile::OrderFile() {
	// ����
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	string date;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string  status;
	// ��¼����
	this->m_Size = 0;
	while (ifs >> date && ifs >> interval 
		&& ifs >> stuId && ifs >> stuName
		&& ifs >> roomId && ifs >> status)
	{
		/*cout << date << endl; // date:1
		cout << interval << endl;
		cout << stuId << endl;
		cout << stuName << endl;
		cout << roomId << endl;
		cout << status << endl;
		cout << endl;*/
		map<string, string>m;
		streachString(m, date);
		streachString(m, interval);
		streachString(m, stuId);
		streachString(m, stuName);
		streachString(m, roomId);
		streachString(m, status);
		this->m_orderData.insert(make_pair(this->m_Size++, m));
		
		//for_each(m.begin(), m.end(), printMap);
		//this->m_Size++;
	}
	
	
	ifs.close();

}

void OrderFile::updateOrder() {
	// ����ԤԼ��¼
	if (this->m_Size == 0) {
		return;
	}
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::trunc);
	// ����д��
	for (int i = 0; i < this->m_Size; i++) {
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}
}
