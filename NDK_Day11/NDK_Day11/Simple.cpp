#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//���ļ�
/*void main() {
	char* filename = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\text.txt";

	FILE* file = fopen(filename, "r");

	if (file)
	{
		//���建����
		char buffers[10];//���ﲻ����char*�ķ�ʽ
		while (fgets(buffers, 10, file))
		{
			printf("%s", buffers);
		}


		fclose(file);//���Ҫ�ر�
	}
	else
		printf("�ļ���ʧ��");

	getchar();
}*/

//д�ļ�
/*void main() {
	char* filename = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\text2.txt";

	FILE* file = fopen(filename, "w");

	if (file)
	{
		fputs("Hello Jensen", file);

		fclose(file);//���Ҫ�ر�
	}
	else
		printf("�ļ���ʧ��");

	getchar();
}*/

//ʹ�ö����Ʒ�ʽ�����ļ�
/*void main() {

	//char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\text.txt";
	//char* filename_des = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\text1.txt";//д�ı��ļ�����������

	//����ͼƬ����
	char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a.png";
	char* filename_des = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a1.png";



	FILE* file_src = fopen(filename_src, "rb");//b:ʹ�ö����Ʒ�ʽ
	//�÷������Զ������ļ�
	FILE* file_des = fopen(filename_des, "wb");//b:ʹ�ö����Ʒ�ʽ

	if (file_src&&file_des)
	{
		const int size = 1024;
		int buffers[size];//�ļ�������
		int len;//��ȡ���ĳ���
		//ΪʲôҪ��������ȣ���fread������ȡ�������ݳ���С�ڻ���������ʱ�����������û�б����ǣ��ͻᵼ�����ݳ���
		while (len = fread(buffers, sizeof(int), size, file_src) != 0)
		{
			fwrite(buffers, sizeof(int), len, file_des);//���������õ�ʱlen������size
		}

		fclose(file_src);
		fclose(file_des);
	}
	else
	{
		printf("�ļ��򿪳���");
	}


	getchar();
}*/


long filesize(FILE* file) {
	long curpos, length;
	//��ס��ǰλ��
	curpos = ftell(file);
	//�ƶ���ĩβ
	fseek(file, 0L, SEEK_END);
	//��ȡ�ļ���С
	length = ftell(file);
	//��ָ���ƶ���ͷ��
	fseek(file, 0L, SEEK_SET);
	return length;
}


//��ȡ�ļ���С
/*void main() {
	char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a.png";

	FILE* file_src = fopen(filename_src, "r");

	if (file_src)
	{
		//�ض�λ���ϵ��ļ�ָ�룬�ƶ�ָ�뵽���ļ�β��
		//Դ�ļ���ƫ��������㣻����Ĵ�����˼�ǽ�ָ���ƶ��������ļ�ĩβƫ��Ϊ0��λ�ã�����ĩβ
		//int ret = fseek(file_src, 0L, SEEK_END);
		//printf("�ض�λ���(0�ɹ����򷵻�����ֵ)��%d\n", ret);
		////���ص�ǰ�ļ�ָ��
		//long size = ftell(file_src);

		printf("�ļ���С%ld", filesize(file_src));

		fclose(file_src);
	}
	else
	{
		printf("�ļ���ʧ��");
	}
	getchar();

}*/


//�ļ�����
/*void  main(){
	 //�������ӽ��ܣ���ͬΪ1����ͬΪ0
	//����10^5
	//10:1010    ����:1111
	// 5:0101��������  0101������������
	//   1111        1010


	char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a.png";//ԭͼ
	char* filename_encode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a2.png";//����ͼ

	FILE* file_src = fopen(filename_src, "rb");//b:ʹ�ö����Ʒ�ʽ
	//"wb"���Զ������ļ�
	FILE* file_encode = fopen(filename_encode, "wb");//b:ʹ�ö����Ʒ�ʽ

	if (file_src&&file_encode)
	 {
		//����
		int src;
		while ((src=fgetc(file_src))!=EOF)//!=�����ȼ�����=����Ҫ�Ѹ�ֵ���������Ű���������֤����˳��
		{
			fputc(src ^ 5, file_encode);
		}

		fclose(file_src);
		fclose(file_encode);

	}
	else
	{
		printf("�ļ��򿪳���");
	}


	getchar();

}*/


//�ļ�����
/*void  main() {
	//�������ӽ��ܣ���ͬΪ1����ͬΪ0
	//����10^5
	//10:1010    ����:1111
	// 5:0101��������  0101������������
	//   1111        1010


	char* filename_encode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a2.png";//����ͼ
	char* filename_decode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a3.png";//����ͼ

	FILE* file_encode = fopen(filename_encode, "rb");//b:ʹ�ö����Ʒ�ʽ
											   //"wb"���Զ������ļ�
	FILE* file_decode = fopen(filename_decode, "wb");//b:ʹ�ö����Ʒ�ʽ

	if (file_encode&&file_decode)
	{
		//����
		int src;
		while ((src = fgetc(file_encode)) != EOF)//!=�����ȼ�����=����Ҫ�Ѹ�ֵ���������Ű���������֤����˳��
		{
			fputc(src ^ 5, file_decode);

		}

		fclose(file_encode);
		fclose(file_decode);

	}
	else
	{
		printf("�ļ��򿪳���");
	}


	getchar();

}*/


//ʹ���ַ����������
/*void  main() {
	//�������ӽ��ܣ���ͬΪ1����ͬΪ0
	//����10^5
	//10:1010    ����:1111
	// 5:0101��������  0101������������
	//   1111        1010


	char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a.png";//ԭͼ
	char* filename_encode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a2.png";//����ͼ

	FILE* file_src = fopen(filename_src, "rb");//b:ʹ�ö����Ʒ�ʽ
											   //"wb"���Զ������ļ�
	FILE* file_encode = fopen(filename_encode, "wb");//b:ʹ�ö����Ʒ�ʽ

	if (file_src&&file_encode)
	{
		//����

		char* password = "123456";
		int pass_index = 0;
		int pass_len = strlen(password);

		int data;
		//EOF end of file �ļ�������
		while ((data = fgetc(file_src)) != EOF)//!=�����ȼ�����=����Ҫ�Ѹ�ֵ���������Ű���������֤����˳��
		{
			fputc(data ^ password[pass_index%pass_len], file_encode);
			pass_index++;
		}

		fclose(file_src);
		fclose(file_encode);

	}
	else
	{
		printf("�ļ��򿪳���");
	}



}*/

//�ļ�����
/*void  main() {
	//�������ӽ��ܣ���ͬΪ1����ͬΪ0
	//����10^5
	//10:1010    ����:1111
	// 5:0101��������  0101������������
	//   1111        1010


	char* filename_encode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a2.png";//����ͼ
	char* filename_decode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a3.png";//����ͼ

	FILE* file_encode = fopen(filename_encode, "rb");//b:ʹ�ö����Ʒ�ʽ
	//"wb"���Զ������ļ�
	FILE* file_decode = fopen(filename_decode, "wb");//b:ʹ�ö����Ʒ�ʽ

	if (file_encode&&file_decode)
	{
		//����
		char* password = "123456";
		int pass_index = 0;
		int pass_len = strlen(password);

		int data;
		//EOF end of file �ļ�������

		while ((data = fgetc(file_encode)) != EOF)//!=�����ȼ�����=����Ҫ�Ѹ�ֵ���������Ű���������֤����˳��
		{
			fputc(data ^ password[pass_index%pass_len], file_decode);
			pass_index++;

		}

		fclose(file_encode);
		fclose(file_decode);

	}
	else
	{
		printf("�ļ��򿪳���");
	}

}*/


//�ļ�ƴ��
void main() {
	char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a.jpg";//ԭͼ

	FILE* file = fopen(filename_src, "rb");

	if (file)
	{
		//�ļ���С
		long size = filesize(file);
		//ÿ���ļ���С�������õĳ������������������ռ��������������һ���ļ���Ҫ����Ĳ���Ҳ����
		long file_size_per = 1024 * 10;
		//�ļ��ֳɼ���
		int file_count = size / file_size_per;

		char** file_names = (char**)malloc(sizeof(char*) * file_count);

		for (size_t i = 0; i < file_count; i++)
		{
			//ÿ���ַ�������100��char
			file_names[i] = (char*)malloc(sizeof(char) * 100);
			//�ļ�����ֵ
			sprintf(file_names[i], "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a_%d.jpg", i);
			printf("%s\n", file_names[i]);
		}

		//�ֽ�
		long index = 0;
		for (size_t i = 0; i < file_count; i++)
		{
			FILE* file_w = fopen(file_names[i], "wb");
			if (!file_w)
			{
				printf("�ֿ��ļ����쳣");
				getchar();
			}
			else
			{

				for (; index < file_size_per * (i + 1); index++)
				{
					fputc(fgetc(file), file_w);
				}
				//���һ���ļ���д��ʣ�ಿ��
				if (file_count - 1 == i)
				{
					int s;
					while ((s = fgetc(file)) != EOF)
					{
						fputc(s, file_w);
					}
				}

				fclose(file_w);
			}
		}
		fclose(file);

		//ƴ��
		char* filename_des = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\b.jpg";
		FILE* file_des = fopen(filename_des, "wb");
		if (!file_des)
		{
			printf("ƴ���ļ����쳣��");
			getchar();
		}

		int read_index = 0;

		for (size_t i = 0; i < file_count; i++) {
			FILE* file_r = fopen(file_names[i], "rb");
			if (!file_r)
			{
				printf("��ƴ���ļ����쳣��");
				getchar();
			}
			for (; read_index < file_size_per * (i + 1); read_index++)
			{
				fputc(fgetc(file_r), file_des);
			}
			//���һ���ļ���д��ʣ�ಿ��
			if (file_count - 1 == i)
			{
				int s;
				while ((s = fgetc(file_r)) != EOF)
				{
					fputc(s, file_des);
				}
			}



			fclose(file_r);
		}
		fclose(file_des);
	}
	else
	{
		printf("�ļ����쳣");
	}
	getchar();
}