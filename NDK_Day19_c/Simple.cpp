#include <stdio.h>

void main(){
	//������const
	//c++�б�����������ô��
	const int a = 10;
	int* b = &a;
	*b = 20;
	printf("a=%d\n", a);

	getchar();
}