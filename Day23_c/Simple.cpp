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
		size = arr.size;
		//深度拷贝
		array = (int*)malloc(sizeof(int) * size);
		for (int i=0;i<this->size;i++)
		{
			this->array[i] = arr.array[i];
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


void main() {
	Array* array = new Array(3);

	array->set(0, 0);
	array->set(1, 1);
	array->set(2, 2);

	printArray(*array);

	delete(array);

	getchar();
}

