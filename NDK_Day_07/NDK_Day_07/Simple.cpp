#include <stdio.h>

/*void main() {
	int num = 12;

	int* p = &num;

	int** p1 = &p;

	printf("num��ֵ%d��p��ֵ%p��p1��ֵ%p\n", num, p, p1);
	//ָ��Ҳ���Ǹ����������Լ���ֵ�͵�ַ
	printf("num=%d\n", **p1);

	getchar();
}*/

//����������ָ��
/*void main() {
	int arr[] = { 1,2,3,4 };

	for (int i = 0; i < 4;i++)
	{
		printf("%d\n", arr[i]);
	}

	// forѭ����c��c++�е���ȷд���������д����Linux�¿��ܻ�������
	int i = 0;
	for (; i < 4; i++)
	{
		printf("%d\n", arr[i]);
	}


	printf("arr��ֵ��%p\n", arr);
	printf("&arr��ֵ��%p\n", &arr);
	printf("&arr[0]��ֵ��%p\n", &arr[0]);
	printf("����=����ȡ��ַ=������Ԫ��ȡ��ַ")

	//����ȡ��ַ����Ҫ&
	int* p = arr;

	printf("pȡֵ%d\n", *p);
	p++;
	printf("pȡֵ%d\n", *p);
	p++;
	printf("pȡֵ%d\n", *p);
	p++;
	printf("pȡֵ%d\n", *p);

	//��������߽��ˣ����ǲ��ᱨ����Ϊ�����ַ�Ǵ��ڵ�
	p++;
	printf("pȡֵ%d\n", *p);

	getchar();
}*/

//����ָ���������ѭ����ֵ
/*void main() {
	int arr[] = { 1,2,3,4 };
	int* p = arr;

	int i = 0;
	for (; i < 4;i++)
	{
		printf("����%d,ֵ%d\n", i, *(p + i));
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
		//printf("����%d,ֵ%d\n", i, *(p + i));
	}

	i = 0;
	for (; i < 4;i++)
	{
		printf("����%d,ֵ%d\n", i, *(p + i));
	}

	getchar();

}*/

//ָ��ΪʲôҪҪ�����ͣ���Ϊ��ͬ��������Ҫ���ڴ��ַ�����ǲ�ͬ�ģ�ָ����Ҫ֪����ôƫ��


//ָ��ص�
void add(int a, int b) {
	printf("num1+num2=%d", a + b);
}

void operate(void(*func)(int, int), int a, int b) {
	func(a, b);
}

void main() {

	//add(1, 2);

	//����ָ����ô���壿
	//��������(*������)(����...)
	//ע�����*�źͺ�������һ��
	void(*fun2)(int, int) = add;

	operate(fun2, 1, 2);




	getchar();


}