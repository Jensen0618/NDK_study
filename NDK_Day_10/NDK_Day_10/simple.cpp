#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*struct Person {//第一种定义方式
	char name[30];
	int age;
	double salary;
};*/

struct Work
{
	char name[10];
	int grade;
};

struct Person
{
	char name[30];
	int age;
	double salary;
	struct Work work;//定义的地方一定要在调用之前，否则会报错未定义，也可以直接定义在这里，这样就只有内部能new
}jerry, alice;//可以直接在后面跟上变量



/*void main() {
	//struct Person tom = { "Tom",20,1000 };
	//struct Person tom = { "Tom",20 };
	//struct Person tom ;//不初始化是不行的：使用了未初始化的局部变量“tom”
	struct Person tom = {};//默认值0，字符串为空

	//tom.name = "666";//没法改艹
	strcpy(tom.name, "666");//得这么改，真的折磨
	tom.age = 12;


	printf("name=%s, age=%d, salary=%lf\n", tom.name, tom.age, tom.salary);

	printf("name=%s, age=%d, salary=%lf\n", jerry.name, jerry.age, jerry.salary);

	printf("name=%s, work=%s, grade=%d\n", jerry.name, jerry.work.name, jerry.work.grade);



	getchar();
}*/


typedef struct People
{
	char* name;//使用char*就可以直接改值，使用char数组就只能使用strcpy方法改值
	int age;
}Ren;

//结构体指针
/*void main() {
	struct People p1 = {};
	p1.name = "666";
	printf("name=%s, age=%d\n", p1.name, p1.age);

	//People* p2 = {};//这是指针，这么初始化是不对的
	People* p2 = (People*)malloc(sizeof(People));
	p2->name = "777";
	p2->age = 28;
	//初始化是必须的
	printf("name=%s, age=%d\n", p2->name, p2->age);

	getchar();
}*/

//结构体数组
/*void main() {
	//第一种 传统数组
	People ps[10];
	ps[0] = { "Tom",10 };
	printf("name=%s, age=%d\n", ps[0].name, ps[0].age);

	//第二种 指针
	People *pp = (People*)malloc(sizeof(People));
	*pp = { "Jerry",8 };

	//移动指针
	//pp += 5;
	//*pp = { "Jerry5",5 };
	printf("name=%s, age=%d\n", pp->name, pp->age);

	//似乎就是这里释放内存的问题
	//if (pp)
	//{
	//	free(pp);
	//	pp = NULL;
	//}

	getchar();
}*/

struct date
{
	int year;
	int month;
	int day;
};//12

struct student
{
	int number;//0,4               
	char sex;//4,1                   
	int age;//8,4
	char name[10];//12,10
	struct date birthday;//24,12
};//36



//计算结构体大小
void main() {
	printf("%d\n", sizeof(date));
	printf("%d\n", sizeof(student));
	getchar();
}

//typedef 别名
/*void main() {
	//给Person起个别名叫做Ren
	Ren r = { "PK" };
	//说是结构体不起别名的话使用的时候要加上struct关键字
	//否则会报错
	People p = {};

	printf("%s\n", r.name);
	getchar();
}*/


//联合体：定义n个变量，实际最后被赋值的变量能用
union Man
{
	int age;
	long score;
};

//枚举

enum MsgType
{
	//默认从0开始，可以自己赋值，后面的值默认+1
	TEXT,IMAGE=5,MEDIA,AUDIO
};

/*void main(){

	//Man m = { 20,100 };只能初始化一个值
	Man m = { 20 };
	printf("union age=%d, score=%ld\n", m.age, m.score);//union age=20, score=20

	m.age = 20;
	m.score = 100;
	printf("union age=%d, score=%ld\n", m.age, m.score); //union age = 100, score = 100

	m.age = 999;
	printf("union age=%d, score=%ld\n", m.age, m.score);//union age=999, score=999
	
	//只会输出最后赋值的变量


	MsgType type1 = TEXT;
	MsgType type2 = IMAGE;
	MsgType type3 = MEDIA;
	MsgType type4 = AUDIO;

	printf("%d\n", type1);
	printf("%d\n", type2);
	printf("%d\n", type3);
	printf("%d\n", type4);



	getchar();

}*/


