#include <iostream>
using namespace std;

class
{
public:
	void hell() const{
		//name = "hello";//表达式必须是可修改的左值 
	}
protected:
private:
	char* name;
};


class Person {
private:
	string name;
public:
	Person(string name) {
		this->name = name;
	}

	string & getName() {
		return this->name;
	}


};


void main() {
	
	//const的使用场景：拷贝构造函数、运算符重载、方法后面（都是由于它们的成员不可改变）

	Person p1("jack");
	//getName方法返回了一个引用，所以可以被赋值
	p1.getName() = "lose";
	cout << "name=" << p1.getName() << endl;


	getchar();
}