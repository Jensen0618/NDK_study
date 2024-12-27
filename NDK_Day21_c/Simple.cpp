#include <iostream>

using namespace std;

class Student
{
public:
	Student();
	Student(char* name);
	Student(char* name, int age);
	~Student();//~��������
	char* getName();
	int getAge();

	void setName(char* name);
	void setAge(int age);

	//�������캯��
	Student(const Student& stu);


private:
	char* name;
	int age;

};

Student::Student()
{
	cout << "���ÿղι��캯��" << endl;
}

Student::Student(char* name) :Student(name, 40)//�������������������캯�����൱��java��ʹ��this�����������캯��
//Student::Student(char* name) :age(30)//����������ֵ�����Ǹо������
{
	cout << "����1�ι��캯��" << endl;
	this->name = name;
}

Student::Student(char* name, int age) {
	cout << "����2�ι��캯��" << endl;
	this->name = name;
	//this->name = (char*)malloc(sizeof(char));
	this->age = age;
}

// ��main��������ʱ������obj�����٣����������ᱻ�Զ�����
Student::~Student() {
	//����ڹ��캯����ʹ��malloc�����˶��ڴ棬����������������ͷŵ�
	//free(this->name);
	cout << "��������������" << endl;
}

//�������캯����һ������Ĺ��캯�����ɱ������������ã�����ڹ��캯���ж�̬�����ڴ棬���������ʵ����ȸ���
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
	Student std1;//�������ţ�C++�������͵�����Ĭ�ϵĹ��캯����

	Student std2("Jensen");
	cout << "std2.name=" << std2.getName() << ",age=" << std2.getAge() << endl;

	Student std3("Jensen", 35);


	Student* std4 = new Student("Tom", 20);//ʹ��newһ�����ù��캯��

	Student* std5 = (Student*)malloc(sizeof(Student));//ʹ��malloc������ù��캯������ֻ�����ڴ�

	delete(std4);//new�����Ĳ�����delete

	// ��main��������ʱ������obj�����٣����������ᱻ�Զ�����

	//malloc��free��һ�ԣ�new��delete��һ��

	getchar();
}