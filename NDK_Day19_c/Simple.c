#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
	char* name;
	int age;

} student;

/*void main() {

	student std1 = { "Jensen",20 };
	student std2 = std1;//java����ôд�Ļ���ʵstd1��std2ָ�����ͬһ������,������c���൱�ڸ�����һ��
	std1.name = "Lily";
	std1.age = 19;

	printf("std1 name=%s,age=%d\n", std1.name, std1.age);
	printf("std2 name=%s,age=%d\n", std2.name, std2.age);
	
	//��������ַ�ǲ�һ����
	printf("&std1=%p\n&std2=%p\n", &std1, &std2);

	//�������������ģ����Կ����޸���std1��û�иı�std2�����ǵ��ڴ��ַҲ�ǲ�ͬ��
	//std1 name = Lily, age = 19
	//std2 name = Jensen, age = 20
	//& std1 = 00000092ABB6F7C8
	//& std2 = 00000092ABB6F7F8
	

	getchar();

}*/

/*void main() {
	student std1;

	//std1.name = "Jensen";//��ôдû����


	std1.name = malloc(sizeof(char) * 20);//���ٸ��ڴ��ֿ�����

	strcpy(std1.name, "Lily");//��ôд���ǲ��Ե��ˣ�std1.name�Ǹ�ָ��

	printf("name=%s", std1.name);

	getchar();
}*/

void main(){
	//��ٵ�const
	//c�п���ͨ����ַ�޸�const���εĳ���
	const int a = 10;
	int* b = &a;
	*b = 20;
	printf("a=%d\n", a);

	getchar();
}