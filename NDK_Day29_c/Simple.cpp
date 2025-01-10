#include<iostream>
#include <map>
#include<algorithm>
#include <vector>
#include <functional>

using namespace std;

/*
void main() {

	//map会对key排序
	map<int, string> m;

	//添加

	m.insert(pair<int, string>(01, "01"));

	m.insert(make_pair(02, "02"));

	m.insert(map< int, string>::value_type(03, "03"));
	//前三种方式key重复，添加不生效
	//m.insert(map< int, string>::value_type(03, "13"));

	//这种会覆盖
	m[04] = "04";

	//判断添加是否成功
	pair<map<int, string>::iterator, bool> ret = m.insert(map< int, string>::value_type(03, "03"));


	//循环-迭代器
	for (map<int, string>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << "," << it->second << endl;
	}

	//删除
	m.erase(01);

	//查找
	map<int, string>::iterator find_it = m.find(04);

	//不能用NULL判断
	if (find_it != m.end())
	{
		cout << "找到了:" << find_it->first << "," << find_it->second << endl;
	}
	else {
		cout << "没找到" << endl;
	}


	getchar();
}
*/


//multimap key可重复的map
/*
void main() {

	multimap<int, string> m;
	//基于key可重复的特性，可以用于需要分组的场景
	m.insert(make_pair(1, "11"));
	m.insert(make_pair(1, "12"));
	m.insert(make_pair(1, "13"));

	m.insert(make_pair(2, "21"));
	m.insert(make_pair(2, "22"));
	m.insert(make_pair(2, "23"));

	m.insert(make_pair(3, "31"));
	m.insert(make_pair(3, "32"));
	m.insert(make_pair(3, "33"));


	//遍历
	for (multimap<int, string>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout << it->first << "," << it->second << endl;
	}

	//查找指定分组
	int key = 2;
	multimap<int, string>::iterator find_it = m.find(key);

	//返回的是第一个该key值的指针，基于multimap的分组特性，接下来的值的key都是相同的
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


//仿函数
//其实是个对象
//class compare1
//{
//public:
//	//重载()操作符
//	void operator()() {
//		cout << "仿函数" << endl;
//	}
//};
//
//void compare2() {
//	cout << "普通函数" << endl;
//}

/*
void main(){

	//重载了()操作符
	compare1 compare;

	//像不像调用了一个函数
	compare();

	//太像了，难怪叫做仿函数

	//这是个普通函数
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


