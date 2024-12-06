#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int print(char** names, int length) {
	for (int i = 0; i < length; i++)
	{
		printf("%s\n", names[i]);
	}
	return 0;
}

int PrintArray(char names[5][20], int length) {
	for (int i = 0; i < length; i++)
	{
		printf("%s\n", names[i]);
	}
	return 0;
}


//字符串数组的几种定义方式
void main() {
	//第一种
	char* names[10] = { "Jensen","Tom" };
	print(names, 2);

	//char** names2 = {"Jensen","Tom"};//这么定义是不行的，编译器认为cahr**是个二级指针

	//这么写运行的时候报错
	//char** names2 = { "Jensen" };
	//print(names2, 1);

	//第二种
	//char name1[5][30] = names;//"name1": 初始化需要带括号的初始化表达式列表
	char name1[5][30] = { "Jensen","Tom" };
	//print(name1, 5);//这种就不能用指针的方式去打印了，因为指针操作的步长不同
	PrintArray(name1, 5);

	int number = 4;
	char** names3 = malloc(sizeof(char*) * number);
	
	for (int i=0;i<number;i++)
	{
		names3[i] = malloc(sizeof(char) * 20);
		sprintf(names3[i], "i=%d",i);//sprintf_s会报错啊
	}

	print(names3,number);

	for (int i = 0; i < number; i++)
	{
		if (names3[i]!=NULL)
		{
			free(names3[i]);
			names3[i] = NULL;
		}
	}

	if (names3!=NULL)
	{
		free(names3);
		names3 = NULL;
	}


	getchar();
}