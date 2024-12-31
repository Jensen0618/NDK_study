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
	//写在类内部可以少写一个参数，直接上this
	Vector operator - (Vector v) {
		int x = this->x - v.x;//
		int y = this->x - v.getY();
		Vector vec(x, y);
		return vec;
	}
	*/
	//↓↓↓↓↓↓↓↓↓↓下面是更好的写法↓↓↓↓↓↓↓↓↓↓↓

	//通常会使用引用和const
	//为什么要用引用，为了防止重复创建对象调用拷贝构造方法
	//为什么要用const，为了防止修改值
	Vector operator - (const Vector& v) {
		cout << "haha" << endl;
		int x = this->x - v.x;//使用引用后就不能调用方法了，但可以直接使用属性
		int y = this->x - v.y;
		Vector vec(x, y);
		return vec;//不建议返回引用。
		//引用是别名，当函数结束，栈中的变量被析构，引用可能指向了一个空的地址
	}

	//自增 前置
	void operator ++() {
		this->x++;
		this->y++;
	}
	//自增 后置
	//看来之前的版本并不强制这么写
	//现在是必须这么写，否则报错
	void operator ++(int) {
		this->x++;
		this->y++;
	}

	//重载输出操作符
	friend ostream& operator << (ostream& o, const Vector& vector) {
		cout << vector.x << "," << vector.y;
		return o;
	}

	//重载条件运算符
	bool operator == (const Vector& vector) {
		return (this->x == vector.x && this->y == vector.y);
	}


protected:
private:
	int x;
	int y;
};


//定义在类外的重载操作符（一般写在类内部，比较好）
//重载+号，实现两个向量相加
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

	//加
	Vector v3 = v1 + v2;

	v3.print();

	//减
	Vector v4 = v1 - v2;
	v4.print();

	//自增
	Vector v5(1, 2);
	++v5;
	v5.print();
	v5++;
	v5.print();

	//输出
	cout << v5 << "," << v4 << endl;


	Vector v6(1, 2);

	bool isEqual = v1 == v6;

	//条件运算符
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

	//拷贝构造函数
	Array(const Array& arr) {
		//不写this也是完全没问题的，写上比较清晰而已
		size = arr.size;
		//深度拷贝
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

	//属性和方法名不能重名
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

	//重载[]
	int operator [](int index) {
		return this->array[index];
	}



private:
	int size;
	int* array;
};

//引用大法好啊
//如果直接传对象的话就会调用拷贝构造函数
void printArray(Array arr) {
	for (int i = 0; i < arr.getSize(); i++)
	{
		//cout << arr.get(i) << endl;
		//重载[]，直接得到数组中的元素
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


//类的继承

//基类
class Person
{
public:
	Person(char* name, int age) {
		this->name = name;
		this->age = age;
		cout << "Person 构造函数" << endl;
	}

	~Person() {}

	void print() {
		cout << this->name << "," << this->age << endl;
	}


private:
	char* name;
	int age;
};


//子类
			   //类继承修饰符
class Student :public Person {
private:
	Teacher teacher;
public:
	Student(char* name, int age) :Person(name, age), teacher("Jensen", 50,"语文") {//类Teacher不存在默认构造函数
		cout << "Student 构造函数" << endl;
	}
};


//初始化对象
class Teacher :public Person {

private:
	//char* course;
	Course course;
public:
	//Java中一般把成员变量放在构造函数内部初始化
	//C++一般是像下面这样写
	Teacher(char* name, int age, char* course) :Person(name, age),course(course) {
		cout << "Teacher 构造函数:" << name << "," << age << endl;
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

	s1.print();//需要在继承的父类前加上public修饰符才能调用父类提供的方法

	Teacher t1("lily", 20, "语文");

	getchar();
}
