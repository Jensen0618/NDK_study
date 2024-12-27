#include <iostream>
#include <stdarg.h>

using namespace std;

//�ɱ����

int sum(int count, ...) {
	int sum = 0;
	//��·
	//���ǲ����б�
	va_list args;
	//��ʼ����������б�Ͳ�������
	va_start(args, count);
	for (int i = 0; i < count; i++)
	{
		//ÿ�ε��ã�����������һ��
		sum += va_arg(args, int);
	}
	//������Ӧ�����ͷ��ڴ�
	va_end(args);
	return sum;
}


/*void main() {
	cout << "sum=" << sum(3, 1, 2, 3) << endl;
	getchar();
}*/

//static�ؼ���
class Student
{
public:
	char* name;
	int age;
	static int tag;
	Student();//���캯��
	~Student();//��������

	static int getTag();//����static����
private:

};

Student::Student()
{
}

Student::~Student()
{
}

//static������ʵ�֣���ϸ������û��static�ؼ���
int Student::getTag()
{
	return tag;
}

//��̬���������ʼ��
int Student::tag = 12;

/*void main() {

	Student stu1;
	stu1.tag = 20;
	cout << stu1.getTag() << endl;
	cout << Student::getTag() << endl;
	cout << Student::tag << endl;

	getchar();
}*/

//const���κ���
//�����޸ĺ����ڵ�ֵ

//��Ԫ����
//friend�ؼ������κ��������Է������е�private����

class People
{
public:
	friend void setAge(People *p,int age);
protected:
private:
	int age;
};

//ʵ����Ԫ����
void setAge(People* p, int age)
{
	p->age = age;
}

void main(){
	People p1;
	setAge(&p1, 36);

	getchar();
}

//��Ԫ��
//Java�ķ����ȡ���˽�������ƺ�����ʹ������Ԫ�ࣿ�������Ϊ�඼��һ��Class��Ԫ��