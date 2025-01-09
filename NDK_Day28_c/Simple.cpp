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
	//���캯��
	//vector<int> v;
	//vector<int> v(10);
	//vector<int> v(10, 35);

	vector<int> v;

	//��
	v.insert(v.begin(), 10);
	v.insert(v.begin(), 2, 20);
	v.push_back(30);

	//ɾ
	v.erase(v.begin());//������ָ��
	//v.erase(v.end()-1);//-1�������һ��Ԫ��
	//ɾ���һ��Ԫ���������������
	v.pop_back();

	cout << "��Ԫ�أ�" << v.front() << endl;
	cout << "βԪ�أ�" << v.back() << endl;



	for (int i=0;i<v.size();i++)
	{
		//cout << v[i] << endl;
		cout << v.at(i) << endl;
	}

	//v.assign(3, 40);//����������ǰn��Ԫ�ص�ֵΪx

	//�޸�
	//at()���ص������ã��ȿ�����
	v.at(0) = 100;



	//ʹ�õ�������������ʵ��ָ�룩        ͷָ��        βָ��
	for (vector<int>::iterator it=v.begin();it<v.end();it++)
	{
		cout << *it << endl;
	}


	getchar();
}
*/


/*
//stack ջ���Ƚ����
void main(){
	//����
	stack<int> s;

	//ѹջ
	s.push(10);
	s.push(20);
	s.push(30);

	//��ջ
	s.pop();

	//����ѭ����ѭ��
	while (!s.empty()) {
		int i = s.top();
		cout << i << endl;
		s.pop();
	}


	getchar();
}
*/


/*
//queue ���� �Ƚ��ȳ�
void main(){

	queue<int> q;

	q.push(10);
	q.push(20);
	q.push(30);

	q.front() = 40;

	cout << q.front() << endl;


	//�Ƚ��ȳ�����stack���෴��
	q.pop();
	cout << q.front() << endl;

	getchar();

}
*/


//list ˫��������֪����û��ͷβ������
/*
void main(){
	list<int> l;

	//����
	l.insert(l.begin(), 10);
	l.push_front(11);
	l.push_back(20);

	//�޸�
	l.back() = 30;
	l.front() = 40;

	//�Ƴ�
	l.erase(l.begin());
	l.pop_front();
	l.pop_back();

	//����ͨ���������ʣ�Ҳ�����޸ģ���Ϊ����Ľṹ�Ͳ�����һ���������ڴ��ϣ�
	//Java���������Ϊ�ڲ����˴ӵ�һ���ҵڶ������ٴӵڶ����ҵ������������Э�����²��ҵ��ٶȽ���

	for (list<int>::iterator it=l.begin();it!=l.end();it++)
	{
		cout << *it << endl;
	}

	getchar();

}
*/

//set����
/*
void main() {
	//����Ĭ�ϣ���дҲ��
	set<int, less<int>> s;
	//����
	//set<int, greater<int>> s;

	s.insert(3);
	s.insert(1);
	s.insert(2);

	//����ֵ��ֹһ����ʱ�����ʹ��pair���գ�����ϵͳ�ṩ��
	pair<set<int>::iterator, bool> ret = s.insert(5);

	cout << ret.second << endl;

	for (set<int>::iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << endl;
	}


	getchar();
}
*/



//�Զ���������
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

//�Զ������򷽷�
//�������� �º���
struct personComp 
{
	//����������()��������������󣬷º���
	bool operator() (const Person& _left, const Person& _right) const {
		//return _left.getAge() > _right.getAge();//����д�����У�Ӧ����const��Ե��
		return _left.age > _right.age;
	}

};

void main(){
	//����ʹ�����Զ�������
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

//multiset �����ظ���set
//��set��һ���ģ����ǿ�������ظ���Ԫ��