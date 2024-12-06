#include <stdio.h>

void main(){
	//真正的const
	//c++中编译器不让这么搞
	const int a = 10;
	int* b = &a;
	*b = 20;
	printf("a=%d\n", a);

	getchar();
}