#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*void main() {
	//���һ���ַ�����Ϊ\0������������ֵ��ַ���
	//C���ַ�����0Ϊ����������0�Ż�ͣ�������������Ϊ�����ַ���������
	char str[] = {'J','e','n','s','e','n','\0'};
	str[0] = 'j';
	printf("str��ֵΪ%s\n", str);


	//char*�ķ�ʽ���Ϊ���������ַ�ʽ������{'A'}�ķ�ʽ��ֵ���ᱨ��Ҳ�����޸��ַ���
	//���Ƿ��㰡����
	char *str1 = "Jensen";
	printf("str1��ֵΪ%s\n", str1);

	//ֻҪ��������ʽ�Ķ����Ը�
	char str2[] = "Jensen";
	str2[0] = 'j';
	printf("str2��ֵΪ%s\n", str2);



	system("pause");

//}*/


//�������鳤��

int strlen_l(char * str) {
	int count = 0;//������
	while (*str != '\0')//ָ��ȡֵ���ַ�����'\0'��ʾ����
	{
		count++;
		str++;//ָ����һ���ַ�
	}
	//return sizeof(str) / sizeof(char);
	return count;
}


/*void main() {
	char str[] = { 'J','e','n','s','e','n','\0' };
	char *str1 = "Lily";

	printf("%p\n", str);//��ӡͷָ��
	printf("%s\n", str);//��ӡ�ַ���

	printf("%s����Ϊ%d\n", str, strlen(str));
	printf("%s����Ϊ%d\n", str1, strlen(str1));
	printf("%s����Ϊ%d\n", str, strlen_l(str));
	printf("%s����Ϊ%d\n", str1, strlen_l(str1));

	getchar();
}*/

//�ַ���ת��
/*void main() {
	char* str = "618";
	//���ᱨ��ת��ʧ�ܷ���0
	int num = atoi(str);
	printf("atoiתint���͵�ֵΪ%d\n", num);//618

	double num_f = atof(str);//��������ôfloaat��double���ܽӣ�
	printf("atoiתfloat���͵�ֵΪ%lf\n", num_f);//618.000000


	getchar();
}*/

//�ַ����Ƚ�
/*void main() {
	char * str1 = "Jensen";
	char * str2 = "jensen";

	char * str3 = "Jensen pro";
	char * str4 = "jensen";

	//int ret = strcmp(str1, str2);//���ִ�Сд
	//int ret = strcmpi(str1, str2);//�����ִ�Сд// error C4996: 'strcmpi': The POSIX name for this item is deprecated. Instead, use the ISO C and C++ conformant name: _strcmpi. See online help for details.
	//�����˵�Ǹ÷��������ã�ʹ������ļ������
	//int ret = _strcmpi(str1, str2);


	//int ret = strncmp(str3, str4, 6);//���ִ�Сд���Ƚ�ͷ�����ַ�
	int ret = _strnicmp(str3, str4, 6);//�����ִ�Сд���Ƚ�ͷ�����ַ�
	//��Щ����������Ī������

	if (ret==0)
	{
		printf("���");
	}
	else
	{
		printf("�����");
	}

	getchar();


}*/


//�����ַ�������ȡ�������Ƿ����
/*void main() {

	char * str1 = "My name is Jensen";
	char * str2 = "666";//���û�ҵ�����(null)
	char* pos = strstr(str1, str2);//�ڴ��в���ָ���ַ����ĵ�һ�γ��� ������ָ��

	printf("%s\n", pos);

	//��javaһ����ȡ��һ�γ��ֵ�����
	if (pos)//��Ϊnull��ʱ����ܼ���
	{
		int index = pos - str1;
		printf("��һ�γ��ֵ�λ��%d\n", index);
	}
	else
	{
		printf("û�ҵ�");
	}

	getchar();

}*/

//�ַ����ĸ��ơ�ƴ��
/*void main() {
	char* str = "Jensen";

	//����
	char dest[20];

	//error C4996: 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	//strcpy(dest, str);

	//printf("%s\n", dest);

	//ƴ��

	char dest2[20] = {};//�����õ�ƴ�ӷ�������Ҫ��ʼ�������������������
	strcat(dest2, str);
	strcat(dest2, "666");

	printf("%s\n", dest2);

	char destination[25];
	char *blank = " ", *c = "C++", *Borland = "Borland";

	strcpy(destination, Borland);
	strcat(destination, blank);
	strcat(destination, c);

	printf("%s\n", destination);


	getchar();

}*/


//��ȡ�����ʹ�����ͷ����β
char* strsub(char* str, int start, int end)
{
	int len = end - start;
	//char dest[end - start];//��vs���޷�ʹ�����ַ�ʽ�����ڴ棬ֻ��ʹ�ö�̬���ٷ�ʽ��
	//������NDK������һ��ʹ������ľ�ͷ��������Ϊ�ܹ��Զ������ڴ�
	char* dest = (char*)malloc(sizeof(char)*(len + 1));//+1������\0

	str = str + start;

	int i = 0;
	for (; i < len; i++)
	{
		dest[i] = *str;
		str++;
	}
	dest[len] = '\0';
	return dest;
}

//�ַ�����ȡ
/*void main() {

	char* str = "Hello World";
	char* sub = strsub(str, 2, 5);

	printf("ԭ�ַ���=%s\n", str);
	printf("��ȡ����ַ���=%s\n", sub);

	//��̬�ڴ棬����Ҫ�ͷŵ�
	free(sub);

	getchar();

}*/

//��Сдת��

void lower(char* des, char* src)
{
	while (*src != '\0')
	{
		*des = tolower(*src);
		des++;
		src++;
	}
	*des = '\0';

}

void upper(char* des, char* src)
{
	while (*src != '\0')
	{
		*des = toupper(*src);
		des++;
		src++;
	}
	*des = '\0';//���Ͻ�������ֹ����

}


/*void main() {

	char* str = "Jensen";
	char str_lower[10];
	char str_upper[10];

	lower(str_lower, str);
	upper(str_upper, str);

	printf("%s\n", str);
	printf("%s\n", str_lower);
	printf("%s\n", str_upper);

	getchar();
}*/

//�ַ����滻
//aabbcc��bb�滻Ϊdd
//ʹ�õݹ��ѭ���ķ�ʽ
char* sub_replace(char* str, char* src, char* des) {
	//�Ƿ����bb
	char * pos = strstr(str, src);
	//û��bbֱ�ӷ���ԭ�ַ���
	if (!pos)
	{
		return str;
	}

	//�����µ��ڴ��С��ԭ�ַ�������-���滻�ĳ���+�滻�ĳ���
	int newArrSize = strlen(str) - strlen(src) + strlen(des);
	//vs�ж�̬�����ڴ棬AS�в���ô��
	char *result = (char*)malloc(sizeof(char)*newArrSize);
	//ƴ���ַ��� aabbcc bb->dd
	//ȡ��Ŀ��֮ǰ�Ĳ��� aa
	strcpy(result, strsub(str, 0, pos - str));
	//�滻Ŀ�� bb
	strcat(result, des);
	//ȡ��Ŀ��֮��Ĳ��� cc 
	strcat(result, strsub(str, strlen(str) - strlen(pos + strlen(src)), strlen(str)));//��ʵ�е��ѿ�

	return sub_replace(result, src, des);//�ݹ��滻��һ��
}

void main() {
	char* str = "aabbccbb";
	char* str2 = sub_replace(str, "bb", "dd");
	printf("%s\n", str2);

	getchar();
}