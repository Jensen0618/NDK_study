#include <iostream>

using namespace std;



//��̳У�C++�����̳У��������ж����ԣ����壩

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

	//�����麯��������ʹ�ö�̬����
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

//��̳У�������ȷ
class C :public A, public B {
public:
	C(char* name, int age) :A(name), B(age) {
		cout << name << "," << age << endl;
	}
};


//��̳У����岻��ȷ
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

//����Ǿ�̬��̬

void add(float a, float b) {

}


//ģ�庯��
//�൱��Java�еķ���
template<typename T>
T addd(T num1, T num2) {
	return num1 + num2;
}



void main() {


	C c("Jensen", 34);

	F* f = new F("f");
	//����������ȷ�����õ���A����C��_name()����
	//����virtual��ô���ǲ��а�������
	//f->_name();


	//��̬��Ҫʹ������ָ����
	A* d = new D("d");
	A* e = new E("e");

	//�����Ƕ�̬��̬
	hello(d);
	hello(e);

	//��̬��̬���Ǻ��������أ���ͬһ�������в�ͬ�Ĳ���������

	//Ϊ�˽����̬��̬��Ҫд������������⣬ģ�庯�������ˣ��൱��Java�еķ���
	cout << addd(1, 2) << endl;
	cout << addd(1.0f, 2.0f) << endl;
	cout << addd(1, 2) << endl;


	getchar();

}


