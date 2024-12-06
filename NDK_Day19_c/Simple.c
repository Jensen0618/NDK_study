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
	student std2 = std1;//java中这么写的话其实std1和std2指向的是同一个变量,但是在c里相当于复制了一个
	std1.name = "Lily";
	std1.age = 19;

	printf("std1 name=%s,age=%d\n", std1.name, std1.age);
	printf("std2 name=%s,age=%d\n", std2.name, std2.age);
	
	//这两个地址是不一样的
	printf("&std1=%p\n&std2=%p\n", &std1, &std2);

	//输出结果是这样的，可以看到修改了std1并没有改变std2，他们的内存地址也是不同的
	//std1 name = Lily, age = 19
	//std2 name = Jensen, age = 20
	//& std1 = 00000092ABB6F7C8
	//& std2 = 00000092ABB6F7F8
	

	getchar();

}*/

/*void main() {
	student std1;

	//std1.name = "Jensen";//这么写没问题


	std1.name = malloc(sizeof(char) * 20);//开辟个内存又可以了

	strcpy(std1.name, "Lily");//这么写就是不对的了，std1.name是个指针

	printf("name=%s", std1.name);

	getchar();
}*/

void main(){
	//虚假的const
	//c中可以通过地址修改const修饰的常量
	const int a = 10;
	int* b = &a;
	*b = 20;
	printf("a=%d\n", a);

	getchar();
}