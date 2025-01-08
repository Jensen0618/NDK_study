#include <iostream>
#include <string.h>
using namespace std;

void main() {
	//构建
	string str1("111");
	string str2 = "222";
	string str3(3, '3');
	string* str4 = new string("444");

	cout << str1.c_str() << endl;
	cout << str2.c_str() << endl;
	cout << str3.c_str() << endl;
	cout << str4->c_str() << endl;

	//string与char*互转
	string temp = string("555");
	const	char* char1 = temp.c_str();

	string str5 = string(char1);

	cout << char1 << endl;
	cout << str5.c_str() << endl;

	//增删查改，大小写转换


 	getchar();
}