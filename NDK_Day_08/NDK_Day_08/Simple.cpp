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
	//��̬�����ڴ�
	int* p = (int*)malloc(0.1 * 1024 * 1024 * sizeof(int));

	//�ͷ��ڴ�
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
	printf("���������ָ���\n");
	scanf_s("%d", &num);
	printf("������%d����\n",num);

	//int arr[num];//���ܾ�̬�����ڴ棬�÷���Ҫ��num�Ǹ�����

	//��̬�����ڴ�
	int* arr = (int *)malloc(num*sizeof(int));

	int i = 0;
	int num2;
	for (; i < num; i++)
	{
		printf("�����%d����\n", i+1);
		scanf_s("%d", &num2);

		arr[i] = num2;
		printf("�����%d������%d\n", i+1, arr[i]);
	}

	free(arr);

	getchar();

}*/


//��̬�ı�����õ��ڴ��С
void main() {
	int num;
	printf("���������ָ���\n");
	scanf_s("%d", &num);
	//printf("������%d����\n", num);

	//int arr[num];//���ܾ�̬�����ڴ棬�÷���Ҫ��num�Ǹ�����

	//��̬�����ڴ�
	int* arr = (int *)malloc(num*sizeof(int));

	//ָ��Ҳ�Ǳ���
	printf("*arr��ַ%p\n", arr);

	if (arr)
	{
		int num_value;
		int i = 0;
		for (; i < num; i++)
		{
			//printf("�����%d����\n", i + 1);
			//scanf_s("%d", &num_value);

			arr[i] = i;
			//printf("�����%d������%d\n", i + 1, arr[i]);
			printf("��%d����ֵΪ%d����ַΪ%p\n", i, arr[i], &arr[i]);
		}
	}

	//�ı��ڴ�
	int num_new;
	printf("����Ҫ������ٸ���\n");
	scanf_s("%d", &num_new);
	//Ĭ��������Ƿ���ԭ��ָ���ֵ���������ԭ��ַ�����Ѿ�û���㹻�������ռ��˾ͻ�����¯��
	int* newArr = (int*)realloc(arr, sizeof(int)*(num + num_new));
	printf("*newArr��ַ%p\n", newArr);

	//���û�пռ��˾ͻ�ʧ�ܣ�����һ��NULL
	if (newArr)
	{
		int i = num;
		for (; i < num + num_new; i++)
		{
			newArr[i] = i;
			printf("��%d����ֵΪ%d����ַΪ%p\n", i, newArr[i], &newArr[i]);
		}

		//�ͷ��ڴ����ҲҪ�пգ��ͷź���ΪNULL
		free(newArr);
		newArr = NULL;
		//��Ҫ�����ͷţ��ͷ�ָ���õ�ַ�п����Ѿ�����ȥ���ˣ���ȥ�ͷſ��ܻ�������
	}



	//ͻȻû���ˣ��������Ǹ�
	getchar();

	system("pause");

}