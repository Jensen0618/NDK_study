#include <iostream>
#include <stdarg.h>

using namespace std;

//可变参数

int sum(int count, ...) {
	int sum = 0;
	//套路
	//这是参数列表
	va_list args;
	//开始，传入参数列表和参数个数
	va_start(args, count);
	for (int i = 0; i < count; i++)
	{
		//每次调用，索引往下走一个
		sum += va_arg(args, int);
	}
	//结束，应该是释放内存
	va_end(args);
	return sum;
}


/*void main() {
	cout << "sum=" << sum(3, 1, 2, 3) << endl;
	getchar();
}*/

//static关键字
class Student
{
public:
	char* name;
	int age;
	static int tag;
	Student();//构造函数
	~Student();//析构函数

	static int getTag();//定义static方法
private:

};

Student::Student()
{
}

Student::~Student()
{
}

//static方法的实现，仔细看这里没有static关键字
int Student::getTag()
{
	return tag;
}

//静态变量必须初始化
int Student::tag = 12;

/*void main() {

	Student stu1;
	stu1.tag = 20;
	cout << stu1.getTag() << endl;
	cout << Student::getTag() << endl;
	cout << Student::tag << endl;

	getchar();
}*/

//const修饰函数
//不能修改函数内的值

//友元函数
//friend关键字修饰函数，可以访问类中的private属性

class People
{
public:
	friend void setAge(People *p,int age);
protected:
private:
	int age;
};

//实现友元函数
void setAge(People* p, int age)
{
	p->age = age;
}

void main(){
	People p1;
	setAge(&p1, 36);

	getchar();
}

//友元类
//Java的反射获取类的私有属性似乎就是使用了友元类？可以理解为类都有一个Class友元类