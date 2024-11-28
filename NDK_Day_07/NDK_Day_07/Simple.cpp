#include <stdio.h>

/*void main() {
	int num = 12;

	int* p = &num;

	int** p1 = &p;

	printf("num的值%d，p的值%p，p1的值%p\n", num, p, p1);
	//指针也就是个变量，有自己的值和地址
	printf("num=%d\n", **p1);

	getchar();
}*/

//数组与数组指针
/*void main() {
	int arr[] = { 1,2,3,4 };

	for (int i = 0; i < 4;i++)
	{
		printf("%d\n", arr[i]);
	}

	// for循环在c和c++中的正确写法，上面的写法在Linux下可能会有问题
	int i = 0;
	for (; i < 4; i++)
	{
		printf("%d\n", arr[i]);
	}


	printf("arr的值：%p\n", arr);
	printf("&arr的值：%p\n", &arr);
	printf("&arr[0]的值：%p\n", &arr[0]);
	printf("数组=数组取地址=数组首元素取地址")

	//数组取地址不需要&
	int* p = arr;

	printf("p取值%d\n", *p);
	p++;
	printf("p取值%d\n", *p);
	p++;
	printf("p取值%d\n", *p);
	p++;
	printf("p取值%d\n", *p);

	//超过数组边界了，但是不会报错，因为这个地址是存在的
	p++;
	printf("p取值%d\n", *p);

	getchar();
}*/

//采用指针遍历数组循环赋值
/*void main() {
	int arr[] = { 1,2,3,4 };
	int* p = arr;

	int i = 0;
	for (; i < 4;i++)
	{
		printf("索引%d,值%d\n", i, *(p + i));
	}

	getchar();

}*/

/*void main() {
	int arr[4] ;
	int* p = arr;

	int i = 0;
	for (; i < 4; i++)
	{
		arr[i] = i;
		//printf("索引%d,值%d\n", i, *(p + i));
	}

	i = 0;
	for (; i < 4;i++)
	{
		printf("索引%d,值%d\n", i, *(p + i));
	}

	getchar();

}*/

//指针为什么要要有类型？因为不同类型所需要的内存地址长度是不同的，指针需要知道真么偏移


//指针回调
void add(int a, int b) {
	printf("num1+num2=%d", a + b);
}

void operate(void(*func)(int, int), int a, int b) {
	func(a, b);
}

void main() {

	//add(1, 2);

	//方法指针怎么定义？
	//返回类型(*函数名)(参数...)
	//注意这个*号和函数名在一起
	void(*fun2)(int, int) = add;

	operate(fun2, 1, 2);




	getchar();


}