#include <stdio.h>
#include <string.h>
#include <malloc.h>

/*struct Person {//��һ�ֶ��巽ʽ
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
	struct Work work;//����ĵط�һ��Ҫ�ڵ���֮ǰ������ᱨ��δ���壬Ҳ����ֱ�Ӷ��������������ֻ���ڲ���new
}jerry, alice;//����ֱ���ں�����ϱ���



/*void main() {
	//struct Person tom = { "Tom",20,1000 };
	//struct Person tom = { "Tom",20 };
	//struct Person tom ;//����ʼ���ǲ��еģ�ʹ����δ��ʼ���ľֲ�������tom��
	struct Person tom = {};//Ĭ��ֵ0���ַ���Ϊ��

	//tom.name = "666";//û����ܳ
	strcpy(tom.name, "666");//����ô�ģ������ĥ
	tom.age = 12;


	printf("name=%s, age=%d, salary=%lf\n", tom.name, tom.age, tom.salary);

	printf("name=%s, age=%d, salary=%lf\n", jerry.name, jerry.age, jerry.salary);

	printf("name=%s, work=%s, grade=%d\n", jerry.name, jerry.work.name, jerry.work.grade);



	getchar();
}*/


typedef struct People
{
	char* name;//ʹ��char*�Ϳ���ֱ�Ӹ�ֵ��ʹ��char�����ֻ��ʹ��strcpy������ֵ
	int age;
}Ren;

//�ṹ��ָ��
/*void main() {
	struct People p1 = {};
	p1.name = "666";
	printf("name=%s, age=%d\n", p1.name, p1.age);

	//People* p2 = {};//����ָ�룬��ô��ʼ���ǲ��Ե�
	People* p2 = (People*)malloc(sizeof(People));
	p2->name = "777";
	p2->age = 28;
	//��ʼ���Ǳ����
	printf("name=%s, age=%d\n", p2->name, p2->age);

	getchar();
}*/

//�ṹ������
/*void main() {
	//��һ�� ��ͳ����
	People ps[10];
	ps[0] = { "Tom",10 };
	printf("name=%s, age=%d\n", ps[0].name, ps[0].age);

	//�ڶ��� ָ��
	People *pp = (People*)malloc(sizeof(People));
	*pp = { "Jerry",8 };

	//�ƶ�ָ��
	//pp += 5;
	//*pp = { "Jerry5",5 };
	printf("name=%s, age=%d\n", pp->name, pp->age);

	//�ƺ����������ͷ��ڴ������
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



//����ṹ���С
void main() {
	printf("%d\n", sizeof(date));
	printf("%d\n", sizeof(student));
	getchar();
}

//typedef ����
/*void main() {
	//��Person�����������Ren
	Ren r = { "PK" };
	//˵�ǽṹ�岻������Ļ�ʹ�õ�ʱ��Ҫ����struct�ؼ���
	//����ᱨ��
	People p = {};

	printf("%s\n", r.name);
	getchar();
}*/


//�����壺����n��������ʵ����󱻸�ֵ�ı�������
union Man
{
	int age;
	long score;
};

//ö��

enum MsgType
{
	//Ĭ�ϴ�0��ʼ�������Լ���ֵ�������ֵĬ��+1
	TEXT,IMAGE=5,MEDIA,AUDIO
};

/*void main(){

	//Man m = { 20,100 };ֻ�ܳ�ʼ��һ��ֵ
	Man m = { 20 };
	printf("union age=%d, score=%ld\n", m.age, m.score);//union age=20, score=20

	m.age = 20;
	m.score = 100;
	printf("union age=%d, score=%ld\n", m.age, m.score); //union age = 100, score = 100

	m.age = 999;
	printf("union age=%d, score=%ld\n", m.age, m.score);//union age=999, score=999
	
	//ֻ��������ֵ�ı���


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


