#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <windows.h> 


/*void main(void) {
	int i;
	time_t t;

	srand((unsigned)time(&t));



	printf("Ten random numbers from 0 to 99\n\n");
	for (i = 0; i < 10; i++)
		printf("%d\n", rand() % 100);

	getchar();

}*/


void dynamicGet() {
	//动态申请内存
	int* p = (int*)malloc(0.1 * 1024 * 1024 * sizeof(int));

	//释放内存
	free(p);
}

/*void main() {
	while (true)
	{
		dynamicGet();
		Sleep(100);
	}
	getchar();
}*/

/*void main() {
	int num;
	printf("请输入数字个数\n");
	scanf_s("%d", &num);
	printf("将输入%d个数\n",num);

	//int arr[num];//不能静态开辟内存，该方法要求num是个常量

	//动态开辟内存
	int* arr = (int *)malloc(num*sizeof(int));

	int i = 0;
	int num2;
	for (; i < num; i++)
	{
		printf("输入第%d个数\n", i+1);
		scanf_s("%d", &num2);

		arr[i] = num2;
		printf("输入第%d个数是%d\n", i+1, arr[i]);
	}

	free(arr);

	getchar();

}*/


//动态改变申请好的内存大小
void main() {
	int num;
	printf("请输入数字个数\n");
	scanf_s("%d", &num);
	//printf("将输入%d个数\n", num);

	//int arr[num];//不能静态开辟内存，该方法要求num是个常量

	//动态开辟内存
	int* arr = (int *)malloc(num*sizeof(int));

	//指针也是变量
	printf("*arr地址%p\n", arr);

	if (arr)
	{
		int num_value;
		int i = 0;
		for (; i < num; i++)
		{
			//printf("输入第%d个数\n", i + 1);
			//scanf_s("%d", &num_value);

			arr[i] = i;
			//printf("输入第%d个数是%d\n", i + 1, arr[i]);
			printf("第%d个数值为%d，地址为%p\n", i, arr[i], &arr[i]);
		}
	}

	//改变内存
	int num_new;
	printf("还需要输入多少个数\n");
	scanf_s("%d", &num_new);
	//默认情况下是返回原来指针的值，但是如果原地址后面已经没有足够的连续空间了就会另起炉灶
	int* newArr = (int*)realloc(arr, sizeof(int)*(num + num_new));
	printf("*newArr地址%p\n", newArr);

	//如果没有空间了就会失败，返回一个NULL
	if (newArr)
	{
		int i = num;
		for (; i < num + num_new; i++)
		{
			newArr[i] = i;
			printf("第%d个数值为%d，地址为%p\n", i, newArr[i], &newArr[i]);
		}

		//释放内存最好也要判空，释放后置为NULL
		free(newArr);
		newArr = NULL;
		//不要反复释放，释放指针后该地址有可能已经被拿去用了，再去释放可能会有问题
	}



	//突然没用了，换下面那个
	getchar();

	system("pause");

}