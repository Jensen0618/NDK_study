#include <iostream>
#include <stdarg.h>

using namespace std;

//�ɱ����

int sum(int count, ...) {
	int sum = 0;
	//��·
	//���ǲ����б�
	va_list args;
	//��ʼ����������б�Ͳ�������
	va_start(args, count);
	for (int i=0;i<count;i++)
	{
		//ÿ�ε��ã�����������һ��
		sum += va_arg(args, int);
	}
	//������Ӧ�����ͷ��ڴ�
	va_end(args);
	return sum;
}


void main(){
	cout << "sum=" << sum(3, 1, 2, 3) << endl;
	getchar();
}