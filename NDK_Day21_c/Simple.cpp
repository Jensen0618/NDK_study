#include <iostream>

using namespace std;

class Student
{
public:
	Student();
	Student(char* name);
	Student(char* name, int age);
	~Student();//~析构函数
	char* getName();
	int getAge();

	void setName(char* name);
	void setAge(int age);

	//拷贝构造函数
	Student(const Student& stu);


private:
	char* name;
	int age;

};

Student::Student()
{
	cout << "调用空参构造函数" << endl;
}

Student::Student(char* name) :Student(name, 40)//可以这样调用其他构造函数，相当于java中使用this调用其他构造函数
//Student::Student(char* name) :age(30)//可以这样赋值，但是感觉很奇怪
{
	cout << "调用1参构造函数" << endl;
	this->name = name;
}

Student::Student(char* name, int age) {
	cout << "调用2参构造函数" << endl;
	this->name = name;
	//this->name = (char*)malloc(sizeof(char));
	this->age = age;
}

// 在main函数结束时，对象obj将销毁，析构函数会被自动调用
Student::~Student() {
	//如果在构造函数中使用malloc申请了堆内存，务必在析构函数中释放掉
	//free(this->name);
	cout << "调用了析构函数" << endl;
}

//拷贝构造函数，一种特殊的构造函数，由编译器自主调用；如果在构造函数中动态申请内存，务必在这里实现深度复制
Student::Student(const Student& std) {

}

char* Student::getName() {
	return this->name;
}

int Student::getAge() {
	return this->age;
}

void Student::setName(char* name) {
	this->name = name;
}

void Student::setAge(int age) {
	this->age = age;
}



void main() {
	Student std1;//难以置信，C++里这样就调用了默认的构造函数！

	Student std2("Jensen");
	cout << "std2.name=" << std2.getName() << ",age=" << std2.getAge() << endl;

	Student std3("Jensen", 35);


	Student* std4 = new Student("Tom", 20);//使用new一样调用构造函数

	Student* std5 = (Student*)malloc(sizeof(Student));//使用malloc不会调用构造函数，它只开辟内存

	delete(std4);//new出来的才能用delete

	// 在main函数结束时，对象obj将销毁，析构函数会被自动调用

	//malloc和free是一对，new和delete是一对

	getchar();
}