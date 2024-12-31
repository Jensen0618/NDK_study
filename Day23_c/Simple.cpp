#include <iostream>

using namespace std;


class Vector
{
public:
	Vector(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	void setX(int x) {
		this->x = x;
	}
	void setY(int y) {
		this->y = y;
	}

	void print() {
		cout << "x=" << this->x << ", y=" << this->y << endl;
	}

	/*
	//д�����ڲ�������дһ��������ֱ����this
	Vector operator - (Vector v) {
		int x = this->x - v.x;//
		int y = this->x - v.getY();
		Vector vec(x, y);
		return vec;
	}
	*/
	//�������������������������Ǹ��õ�д������������������������

	//ͨ����ʹ�����ú�const
	//ΪʲôҪ�����ã�Ϊ�˷�ֹ�ظ�����������ÿ������췽��
	//ΪʲôҪ��const��Ϊ�˷�ֹ�޸�ֵ
	Vector operator - (const Vector& v) {
		cout << "haha" << endl;
		int x = this->x - v.x;//ʹ�����ú�Ͳ��ܵ��÷����ˣ�������ֱ��ʹ������
		int y = this->x - v.y;
		Vector vec(x, y);
		return vec;//�����鷵�����á�
		//�����Ǳ�����������������ջ�еı��������������ÿ���ָ����һ���յĵ�ַ
	}

	//���� ǰ��
	void operator ++() {
		this->x++;
		this->y++;
	}
	//���� ����
	//����֮ǰ�İ汾����ǿ����ôд
	//�����Ǳ�����ôд�����򱨴�
	void operator ++(int) {
		this->x++;
		this->y++;
	}

	//�������������
	friend ostream& operator << (ostream& o, const Vector& vector) {
		cout << vector.x << "," << vector.y;
		return o;
	}

	//�������������
	bool operator == (const Vector& vector) {
		return (this->x == vector.x && this->y == vector.y);
	}


protected:
private:
	int x;
	int y;
};


//��������������ز�������һ��д�����ڲ����ȽϺã�
//����+�ţ�ʵ�������������
Vector operator + (Vector v1, Vector v2) {
	int x = v1.getX() + v2.getX();
	int y = v1.getY() + v2.getY();
	return Vector(x, y);
}


/*void main() {

	Vector v1(1, 2);
	Vector v2(2, 3);

	v1.print();
	v2.print();

	//��
	Vector v3 = v1 + v2;

	v3.print();

	//��
	Vector v4 = v1 - v2;
	v4.print();

	//����
	Vector v5(1, 2);
	++v5;
	v5.print();
	v5++;
	v5.print();

	//���
	cout << v5 << "," << v4 << endl;


	Vector v6(1, 2);

	bool isEqual = v1 == v6;

	//���������
	cout << isEqual << endl;

	getchar();
}*/


class Array
{
public:
	Array(int size) {
		this->size = size;
		this->array = (int*)malloc(sizeof(int) * size);
	}

	//�������캯��
	Array(const Array& arr) {
		//��дthisҲ����ȫû����ģ�д�ϱȽ���������
		size = arr.size;
		//��ȿ���
		array = (int*)malloc(sizeof(int) * size);
		for (int i = 0; i < this->size; i++)
		{
			array[i] = arr.array[i];
		}
	}

	~Array() {
		if (this->array)
		{
			free(this->array);
			this->array = NULL;
		}
	}

	//���Ժͷ�������������
	//int size() {
	//	return this->size;
	//}


	int getSize() {
		return this->size;
	}

	void set(int index, int val) {
		this->array[index] = val;
	}

	int get(int index) {
		return this->array[index];
	}

	//����[]
	int operator [](int index) {
		return this->array[index];
	}



private:
	int size;
	int* array;
};

//���ô󷨺ð�
//���ֱ�Ӵ�����Ļ��ͻ���ÿ������캯��
void printArray(Array arr) {
	for (int i = 0; i < arr.getSize(); i++)
	{
		//cout << arr.get(i) << endl;
		//����[]��ֱ�ӵõ������е�Ԫ��
		cout << arr[i] << endl;
	}
}

/*
void main() {
	Array* array = new Array(3);

	array->set(0, 0);
	array->set(1, 1);
	array->set(2, 2);

	printArray(*array);

	delete(array);

	getchar();
}
*/


//��ļ̳�

//����
class Person
{
public:
	Person(char* name, int age) {
		this->name = name;
		this->age = age;
		cout << "Person ���캯��" << endl;
	}

	~Person() {}

	void print() {
		cout << this->name << "," << this->age << endl;
	}


private:
	char* name;
	int age;
};


//����
			   //��̳����η�
class Student :public Person {
private:
	Teacher teacher;
public:
	Student(char* name, int age) :Person(name, age), teacher("Jensen", 50,"����") {//��Teacher������Ĭ�Ϲ��캯��
		cout << "Student ���캯��" << endl;
	}
};


//��ʼ������
class Teacher :public Person {

private:
	//char* course;
	Course course;
public:
	//Java��һ��ѳ�Ա�������ڹ��캯���ڲ���ʼ��
	//C++һ��������������д
	Teacher(char* name, int age, char* course) :Person(name, age),course(course) {
		cout << "Teacher ���캯��:" << name << "," << age << endl;
	}
};

class Course
{
private:
	char* name;
public:
	Course(char* courseName) {
		this->name = courseName;
	}

private:

};




void main() {
	//Person p1("Jensen", 20);

	Student s1("Jensen", 20);

	s1.print();//��Ҫ�ڼ̳еĸ���ǰ����public���η����ܵ��ø����ṩ�ķ���

	Teacher t1("lily", 20, "����");

	getchar();
}
