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

//引用&，引用不是定义一个新的变量，而是给已存在变量去了一个别名，编译器不会为引用开辟内存空间，它和它引用的变量共用同一块内存空间
//目前看起来就像是Java的引用传递
//只是地址传递的简便写法
/*void main(){
	int a = 10;
	int b = 20;
	cout << "a=" << a << ",b=" << b << endl;
	swap(a, b);
	cout << "a=" << a << ",b=" << b << endl;

	getchar();
}*/

//C不支持函数的重载，C++是可以的，还有默认参数
/*void main() {
	bool ret = -1;//0是false，非0都是true，负的也是！！！
	if (ret)
	{
		cout << "true" << endl;
	}
	else {
		cout << "false" << endl;

	}

	getchar();
}*/

#pragma region Student实现
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
#pragma endregion Student实现


//类的初探
//class定义类，跟java类似
//真正的开发过程中我们的cpp或者c文件最终会打包成dll或so库供调用者使用，所以为了确保类能够正常被调用，我们一般需要定义.h头文件
//实现方法的使用要用命名空间 xxx类名：xxx方法

void main() {
	Student std1;

	std1.setAge(20);
	std1.setName("Jensen");

	cout << "std1.name=" << std1.getName() << endl;

	//Student std2 = new Student();
	//new出来的是指针，上面的报错
	Student* std2 = new Student();
	std2->setName("Lily");
	cout << "std2.name=" << std2->getName() << endl;


	getchar();




}
