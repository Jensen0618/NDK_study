#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <set>

using namespace std;

/*
void main(){

	//vector
	//构造函数
	//vector<int> v;
	//vector<int> v(10);
	//vector<int> v(10, 35);

	vector<int> v;

	//增
	v.insert(v.begin(), 10);
	v.insert(v.begin(), 2, 20);
	v.push_back(30);

	//删
	v.erase(v.begin());//参数是指针
	//v.erase(v.end()-1);//-1才是最后一个元素
	//删最后一个元素用下面这个更好
	v.pop_back();

	cout << "首元素：" << v.front() << endl;
	cout << "尾元素：" << v.back() << endl;



	for (int i=0;i<v.size();i++)
	{
		//cout << v[i] << endl;
		cout << v.at(i) << endl;
	}

	//v.assign(3, 40);//设置向量中前n个元素的值为x

	//修改
	//at()返回的是引用，既可以做
	v.at(0) = 100;



	//使用迭代器遍历（其实是指针）        头指针        尾指针
	for (vector<int>::iterator it=v.begin();it<v.end();it++)
	{
		cout << *it << endl;
	}


	getchar();
}
*/


/*
//stack 栈，先进后出
void main(){
	//创建
	stack<int> s;

	//压栈
	s.push(10);
	s.push(20);
	s.push(30);

	//弹栈
	s.pop();

	//不算循环的循环
	while (!s.empty()) {
		int i = s.top();
		cout << i << endl;
		s.pop();
	}


	getchar();
}
*/


/*
//queue 队列 先进先出
void main(){

	queue<int> q;

	q.push(10);
	q.push(20);
	q.push(30);

	q.front() = 40;

	cout << q.front() << endl;


	//先进先出，和stack是相反的
	q.pop();
	cout << q.front() << endl;

	getchar();

}
*/


//list 双向链表（不知道有没有头尾相连）
/*
void main(){
	list<int> l;

	//插入
	l.insert(l.begin(), 10);
	l.push_front(11);
	l.push_back(20);

	//修改
	l.back() = 30;
	l.front() = 40;

	//移除
	l.erase(l.begin());
	l.pop_front();
	l.pop_back();

	//不能通过索引访问，也不能修改，因为链表的结构就不是在一块连续的内存上；
	//Java里可以是因为内部做了从第一个找第二个，再从第二个找第三个这个的妥协，导致查找的速度较慢

	for (list<int>::iterator it=l.begin();it!=l.end();it++)
	{
		cout << *it << endl;
	}

	getchar();

}
*/

//set容器
/*
void main() {
	//升序，默认，不写也行
	set<int, less<int>> s;
	//降序
	//set<int, greater<int>> s;

	s.insert(3);
	s.insert(1);
	s.insert(2);

	//返回值不止一个的时候可以使用pair接收，这是系统提供的
	pair<set<int>::iterator, bool> ret = s.insert(5);

	cout << ret.second << endl;

	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << endl;
	}


	getchar();
}
*/



//自定义类排序
class Person
{
public:
	Person(string name, int age) {
		this->name = name;
		this->age = age;
	}
	~Person(){}

	string getName() {
		return name;
	}

	int getAge() {
		return age;
	}

	string name;
	int age;
};

//自定义排序方法
//函数对象 仿函数
struct personComp 
{
	//函数重载了()运算符，函数对象，仿函数
	bool operator() (const Person& _left, const Person& _right) const {
		//return _left.getAge() > _right.getAge();//这种写法不行，应该是const的缘故
		return _left.age > _right.age;
	}

};

void main(){
	//这里使用了自定义排序
	set<Person, personComp> s;
	s.insert(Person("Jensen",20));
	s.insert(Person("Jensen",40));
	s.insert(Person("Jensen",30));


	for (set<Person>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << it->name<<","<<it->age << endl;
	}

	getchar();
}

//multiset 可以重复的set
//跟set是一样的，但是可以添加重复的元素