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


//�ַ�������ļ��ֶ��巽ʽ
void main() {
	//��һ��
	char* names[10] = { "Jensen","Tom" };
	print(names, 2);

	//char** names2 = {"Jensen","Tom"};//��ô�����ǲ��еģ���������Ϊcahr**�Ǹ�����ָ��

	//��ôд���е�ʱ�򱨴�
	//char** names2 = { "Jensen" };
	//print(names2, 1);

	//�ڶ���
	//char name1[5][30] = names;//"name1": ��ʼ����Ҫ�����ŵĳ�ʼ�����ʽ�б�
	char name1[5][30] = { "Jensen","Tom" };
	//print(name1, 5);//���־Ͳ�����ָ��ķ�ʽȥ��ӡ�ˣ���Ϊָ������Ĳ�����ͬ
	PrintArray(name1, 5);

	int number = 4;
	char** names3 = malloc(sizeof(char*) * number);
	
	for (int i=0;i<number;i++)
	{
		names3[i] = malloc(sizeof(char) * 20);
		sprintf(names3[i], "i=%d",i);//sprintf_s�ᱨ��
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