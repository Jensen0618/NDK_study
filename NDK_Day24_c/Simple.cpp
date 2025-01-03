#include <iostream>

using namespace std;



//多继承，C++允许多继承，但不能有二义性（歧义）

class A {
private:
	char* name;
public:
	A(char* name) {
		this->name = name;
	}

	char* _name() {
		return this->name;
	}

	//定义虚函数，才能使用多态特性
	virtual void hello() {
		cout << "hello A" << endl;
	}




};


class B {
private:
	int age;
public:
	B(int age) {
		this->age = age;
	}

	int _age() {
		return this->age;
	}
};

//多继承，语义明确
class C :public A, public B {
public:
	C(char* name, int age) :A(name), B(age) {
		cout << name << "," << age << endl;
	}
};


//多继承，语义不明确
class D : public A {
public:
	D(char* name) :A(name) {
	}

	void hello() {
		cout << "hello D" << endl;
	}
};

class E : public A {
public:
	E(char* name) :A(name) {
	}

	void hello() {
		cout << "hello E" << endl;
	}
};

class F :virtual public D, virtual public E {
public:
	F(char* name) :D(name), E(name) {
	}
};


void hello(A* obj) {
	obj->hello();
}




void add(int a, int b) {

}

//这就是静态多态

void add(float a, float b) {

}



void main() {


	C c("Jensen", 34);

	F f = new F("f");
	//编译器不能确定调用的是A还是C的_name()方法
	//加了virtual怎么还是不行啊？？？
	f._name();


	//多态需要使用子类指向父类
	A* d = new D("d");
	A* e = new E("e");

	//这种是动态多态
	hello(d);
	hello(e);

	//静态多态就是函数的重载，像同一个方法有不同的参数就是了

	getchar();

}


