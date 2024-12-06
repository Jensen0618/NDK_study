#include <iostream>
#include <stdarg.h>

using namespace std;

//可变参数

int sum(int count, ...) {
	int sum = 0;
	//套路
	//这是参数列表
	va_list args;
	//开始，传入参数列表和参数个数
	va_start(args, count);
	for (int i=0;i<count;i++)
	{
		//每次调用，索引往下走一个
		sum += va_arg(args, int);
	}
	//结束，应该是释放内存
	va_end(args);
	return sum;
}


void main(){
	cout << "sum=" << sum(3, 1, 2, 3) << endl;
	getchar();
}