#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Student.h"

using namespace std;


void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

//����&�����ò��Ƕ���һ���µı��������Ǹ��Ѵ��ڱ���ȥ��һ������������������Ϊ���ÿ����ڴ�ռ䣬���������õı�������ͬһ���ڴ�ռ�
//Ŀǰ������������Java�����ô���
//ֻ�ǵ�ַ���ݵļ��д��
/*void main(){
	int a = 10;
	int b = 20;
	cout << "a=" << a << ",b=" << b << endl;
	swap(a, b);
	cout << "a=" << a << ",b=" << b << endl;

	getchar();
}*/

//C��֧�ֺ��������أ�C++�ǿ��Եģ�����Ĭ�ϲ���
/*void main() {
	bool ret = -1;//0��false����0����true������Ҳ�ǣ�����
	if (ret)
	{
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;

	}

	getchar();
}*/

#pragma region Studentʵ��
void Student::setName(char* name) {
	this->name = name;
}

void Student::setAge(int age) {
	this->age = age;
}

char* Student::getName() {
	return this->name;
}

int Student::getAge() {
	return this->age;
}
#pragma endregion Studentʵ��


//��ĳ�̽
//class�����࣬��java����
//�����Ŀ������������ǵ�cpp����c�ļ����ջ�����dll��so�⹩������ʹ�ã�����Ϊ��ȷ�����ܹ����������ã�����һ����Ҫ����.hͷ�ļ�
//ʵ�ַ�����ʹ��Ҫ�������ռ� xxx������xxx����

void main() {
	Student std1;

	std1.setAge(20);
	std1.setName("Jensen");

	cout << "std1.name=" << std1.getName() << endl;

	//Student std2 = new Student();
	//new��������ָ�룬����ı���
	Student* std2 = new Student();
	std2->setName("Lily");
	cout << "std2.name=" << std2->getName() << endl;


	getchar();




}
