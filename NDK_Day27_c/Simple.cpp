#include <iostream>
using namespace std;

class
{
public:
	void hell() const{
		//name = "hello";//���ʽ�����ǿ��޸ĵ���ֵ 
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
	
	//const��ʹ�ó������������캯������������ء��������棨�����������ǵĳ�Ա���ɸı䣩

	Person p1("jack");
	//getName����������һ�����ã����Կ��Ա���ֵ
	p1.getName() = "lose";
	cout << "name=" << p1.getName() << endl;


	getchar();
}