#include<stdio.h>//����ͷ�ļ���.h��.hpp���涼�������ķ�����.c��.cpp���Ƿ�����ʵ��
/*void main() {
	printf("Hello world");//printf C�Ĵ�ӡ���

	getchar();
}*/

//������������
/*void main() {
	int i = 100;
	double d = 200;
	float f = 200;
	long l = 100;
	short s = 100;
	char c = 'D';
	// �ַ��� char*

	//�����ӡ
	//ռλ�����й��ɵģ�������d��int��short�Ͷ�����d��long�ǳ����ͣ��õľ���ld
	//��������f��float��f��double˫���ȣ�����lf
	//char���Լ���c
	//ָ���õ���p
	printf("i��ֵ�ǣ�%d\n", i);
	printf("d��ֵ�ǣ�%lf\n", d);
	printf("f��ֵ�ǣ�%f\n", f);
	printf("l��ֵ�ǣ�%ld\n", l);
	printf("s��ֵ�ǣ�%d\n", s);
	printf("c��ֵ�ǣ�%c\n", c);
	
	getchar();
}*/

/*void main() {
	int i = 100;
	//�����ַ��Ҫʹ��%pռλ����
	//�����ԡ�-�������ڡ�-�����ڴ桿-�����ڴ�1��
	//4�ֽ���������������ʾ
	printf("i�ĵ�ַ��%p", &i);

	getchar();
}*/

/*void main() {
	printf("int ��ռ�ֽ�����%d\n", sizeof(int));
	printf("short ��ռ�ֽ�����%d\n", sizeof(short));
	printf("float ��ռ�ֽ�����%d\n", sizeof(float));
	printf("double ��ռ�ֽ�����%d\n", sizeof(double));
	printf("char ��ռ�ֽ�����%d\n", sizeof(char));

	getchar();
}*/

/*void main() {
	int i = 100;
	printf("i��ֵΪ��%d\n", i);

	int* p = &i;
	printf("i��ֵΪ��%d\n", *p);

	getchar();

	
}*/

//ͨ��ָ���޸�ֵ
/*void main(){
	int i = 100;
	int* p = &i;

	i = 200;

	printf("i��ֵ�ǣ�%d", i);

	//��ȡָ���ֵ���м�ӵ��޸�
	*p = 300;
	printf("i��ֵ�ǣ�%d", i);


	getchar();
}*/

//������Ҫ�����ڵ��õ�ǰ��
/*void change(int* a) {
	*a = 200;
}
//ͨ�������޸�int����
void main() {
	int i = 100;
	printf("i=%d\n", i);
	change(&i);
	printf("i=%d\n", i);
	getchar();
}*/

