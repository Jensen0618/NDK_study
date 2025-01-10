#include<iostream>
#include <map>
#include<algorithm>
#include <vector>
#include <functional>

using namespace std;

/*
void main() {

	//map���key����
	map<int, string> m;

	//���

	m.insert(pair<int, string>(01, "01"));

	m.insert(make_pair(02, "02"));

	m.insert(map< int, string>::value_type(03, "03"));
	//ǰ���ַ�ʽkey�ظ�����Ӳ���Ч
	//m.insert(map< int, string>::value_type(03, "13"));

	//���ֻḲ��
	m[04] = "04";

	//�ж�����Ƿ�ɹ�
	pair<map<int, string>::iterator, bool> ret = m.insert(map< int, string>::value_type(03, "03"));


	//ѭ��-������
	for (map<int, string>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << "," << it->second << endl;
	}

	//ɾ��
	m.erase(01);

	//����
	map<int, string>::iterator find_it = m.find(04);

	//������NULL�ж�
	if (find_it != m.end())
	{
		cout << "�ҵ���:" << find_it->first << "," << find_it->second << endl;
	}
	else {
		cout << "û�ҵ�" << endl;
	}


	getchar();
}
*/


//multimap key���ظ���map
/*
void main() {

	multimap<int, string> m;
	//����key���ظ������ԣ�����������Ҫ����ĳ���
	m.insert(make_pair(1, "11"));
	m.insert(make_pair(1, "12"));
	m.insert(make_pair(1, "13"));

	m.insert(make_pair(2, "21"));
	m.insert(make_pair(2, "22"));
	m.insert(make_pair(2, "23"));

	m.insert(make_pair(3, "31"));
	m.insert(make_pair(3, "32"));
	m.insert(make_pair(3, "33"));


	//����
	for (multimap<int, string>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << "," << it->second << endl;
	}

	//����ָ������
	int key = 2;
	multimap<int, string>::iterator find_it = m.find(key);

	//���ص��ǵ�һ����keyֵ��ָ�룬����multimap�ķ������ԣ���������ֵ��key������ͬ��
	while (find_it!=m.end())
	{
		cout << find_it->first << "," << find_it->second << endl;
		find_it++;
		if (find_it==m.end()||find_it->first!=key)
		{
			break;
		}
	}

	getchar();
}
*/


//�º���
//��ʵ�Ǹ�����
//class compare1
//{
//public:
//	//����()������
//	void operator()() {
//		cout << "�º���" << endl;
//	}
//};
//
//void compare2() {
//	cout << "��ͨ����" << endl;
//}

/*
void main(){

	//������()������
	compare1 compare;

	//���������һ������
	compare();

	//̫���ˣ��ѹֽ����º���

	//���Ǹ���ͨ����
	compare2();



	getchar();
}
*/


bool compareInt(int i1) {
	return i1 > 2;
}

void printInt(int i1) {
	cout << i1 << endl;
}


void main() {
	vector<int> v = { 1,2,2,5,9,3 };
	//for_each(v.begin(), v.end(), compareInt);

	//for_each(v.begin(), v.end(), printInt);


	vector<int>::iterator it = find_if(v.begin(), v.end(), bind2nd(equal_to<int>(), 5));

	if (it!=v.end())
	{
		cout << *it << endl;
	}

	getchar();

}


