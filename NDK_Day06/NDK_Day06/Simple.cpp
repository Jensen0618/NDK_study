#include<stdio.h>//导入头文件，.h，.hpp里面都是声明的方法，.c，.cpp都是方法的实现
/*void main() {
	printf("Hello world");//printf C的打印输出

	getchar();
}*/

//基本数据类型
/*void main() {
	int i = 100;
	double d = 200;
	float f = 200;
	long l = 100;
	short s = 100;
	char c = 'D';
	// 字符串 char*

	//输出打印
	//占位符是有规律的，整形是d，int和short就都是用d，long是长整型，用的就是ld
	//浮点型是f，float用f，double双精度，就是lf
	//char用自己的c
	//指针用的是p
	printf("i的值是：%d\n", i);
	printf("d的值是：%lf\n", d);
	printf("f的值是：%f\n", f);
	printf("l的值是：%ld\n", l);
	printf("s的值是：%d\n", s);
	printf("c的值是：%c\n", c);
	
	getchar();
}*/

/*void main() {
	int i = 100;
	//输出地址需要使用%p占位符！
	//【调试】-》【窗口】-》【内存】-》【内存1】
	//4字节整数，带符号显示
	printf("i的地址：%p", &i);

	getchar();
}*/

/*void main() {
	printf("int 所占字节数：%d\n", sizeof(int));
	printf("short 所占字节数：%d\n", sizeof(short));
	printf("float 所占字节数：%d\n", sizeof(float));
	printf("double 所占字节数：%d\n", sizeof(double));
	printf("char 所占字节数：%d\n", sizeof(char));

	getchar();
}*/

/*void main() {
	int i = 100;
	printf("i的值为：%d\n", i);

	int* p = &i;
	printf("i的值为：%d\n", *p);

	getchar();

	
}*/

//通过指针修改值
/*void main(){
	int i = 100;
	int* p = &i;

	i = 200;

	printf("i的值是：%d", i);

	//获取指针的值进行间接的修改
	*p = 300;
	printf("i的值是：%d", i);


	getchar();
}*/

//方法需要声明在调用的前面
/*void change(int* a) {
	*a = 200;
}
//通过方法修改int变量
void main() {
	int i = 100;
	printf("i=%d\n", i);
	change(&i);
	printf("i=%d\n", i);
	getchar();
}*/

