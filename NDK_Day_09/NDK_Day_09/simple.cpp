#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*void main() {
	//最后一个字符必须为\0，否则会输出奇怪的字符；
	//C的字符串以0为结束，遇到0才会停下来，否则会认为都是字符串的内容
	char str[] = {'J','e','n','s','e','n','\0'};
	str[0] = 'j';
	printf("str的值为%s\n", str);


	//char*的方式则更为常见，这种方式不能用{'A'}的方式赋值，会报错，也不能修改字符串
	//但是方便啊啊啊
	char *str1 = "Jensen";
	printf("str1的值为%s\n", str1);

	//只要是数组形式的都可以改
	char str2[] = "Jensen";
	str2[0] = 'j';
	printf("str2的值为%s\n", str2);



	system("pause");

//}*/


//计算数组长度

int strlen_l(char * str) {
	int count = 0;//计数用
	while (*str != '\0')//指针取值！字符串用'\0'表示结束
	{
		count++;
		str++;//指向下一个字符
	}
	//return sizeof(str) / sizeof(char);
	return count;
}


/*void main() {
	char str[] = { 'J','e','n','s','e','n','\0' };
	char *str1 = "Lily";

	printf("%p\n", str);//打印头指针
	printf("%s\n", str);//打印字符串

	printf("%s长度为%d\n", str, strlen(str));
	printf("%s长度为%d\n", str1, strlen(str1));
	printf("%s长度为%d\n", str, strlen_l(str));
	printf("%s长度为%d\n", str1, strlen_l(str1));

	getchar();
}*/

//字符串转换
/*void main() {
	char* str = "618";
	//不会报错，转换失败返回0
	int num = atoi(str);
	printf("atoi转int类型的值为%d\n", num);//618

	double num_f = atof(str);//这玩意怎么floaat，double都能接？
	printf("atoi转float类型的值为%lf\n", num_f);//618.000000


	getchar();
}*/

//字符串比较
/*void main() {
	char * str1 = "Jensen";
	char * str2 = "jensen";

	char * str3 = "Jensen pro";
	char * str4 = "jensen";

	//int ret = strcmp(str1, str2);//区分大小写
	//int ret = strcmpi(str1, str2);//不区分大小写// error C4996: 'strcmpi': The POSIX name for this item is deprecated. Instead, use the ISO C and C++ conformant name: _strcmpi. See online help for details.
	//上面的说是该方法已弃用，使用下面的兼容替代
	//int ret = _strcmpi(str1, str2);


	//int ret = strncmp(str3, str4, 6);//区分大小写，比较头几个字符
	int ret = _strnicmp(str3, str4, 6);//不区分大小写，比较头几个字符
	//这些方法名真是莫名其妙

	if (ret==0)
	{
		printf("相等");
	}
	else
	{
		printf("不相等");
	}

	getchar();


}*/


//查找字符串，获取索引，是否包含
/*void main() {

	char * str1 = "My name is Jensen";
	char * str2 = "666";//如果没找到返回(null)
	char* pos = strstr(str1, str2);//在串中查找指定字符串的第一次出现 ，返回指针

	printf("%s\n", pos);

	//像java一样获取第一次出现的索引
	if (pos)//不为null的时候才能计算
	{
		int index = pos - str1;
		printf("第一次出现的位置%d\n", index);
	}
	else
	{
		printf("没找到");
	}

	getchar();

}*/

//字符串的复制、拼接
/*void main() {
	char* str = "Jensen";

	//复制
	char dest[20];

	//error C4996: 'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
	//strcpy(dest, str);

	//printf("%s\n", dest);

	//拼接

	char dest2[20] = {};//下面用到拼接方法，需要初始化，否则会有乱码乱入
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


//截取，国际惯例含头不含尾
char* strsub(char* str, int start, int end)
{
	int len = end - start;
	//char dest[end - start];//在vs中无法使用这种方式开辟内存，只能使用动态开辟方式；
	//但是在NDK开发中一般使用上面的镜头方法，因为能够自动管理内存
	char* dest = (char*)malloc(sizeof(char)*(len + 1));//+1用来存\0

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

//字符串截取
/*void main() {

	char* str = "Hello World";
	char* sub = strsub(str, 2, 5);

	printf("原字符串=%s\n", str);
	printf("截取后的字符串=%s\n", sub);

	//动态内存，用完要释放掉
	free(sub);

	getchar();

}*/

//大小写转换

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
	*des = '\0';//加上结束符防止乱入

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

//字符串替换
//aabbcc，bb替换为dd
//使用递归或循环的方式
char* sub_replace(char* str, char* src, char* des) {
	//是否包含bb
	char * pos = strstr(str, src);
	//没有bb直接返回原字符串
	if (!pos)
	{
		return str;
	}

	//计算新的内存大小：原字符串长度-被替换的长度+替换的长度
	int newArrSize = strlen(str) - strlen(src) + strlen(des);
	//vs中动态开辟内存，AS中不这么作
	char *result = (char*)malloc(sizeof(char)*newArrSize);
	//拼接字符串 aabbcc bb->dd
	//取出目标之前的部分 aa
	strcpy(result, strsub(str, 0, pos - str));
	//替换目标 bb
	strcat(result, des);
	//取出目标之后的部分 cc 
	strcat(result, strsub(str, strlen(str) - strlen(pos + strlen(src)), strlen(str)));//着实有点难看

	return sub_replace(result, src, des);//递归替换下一个
}

void main() {
	char* str = "aabbccbb";
	char* str2 = sub_replace(str, "bb", "dd");
	printf("%s\n", str2);

	getchar();
}