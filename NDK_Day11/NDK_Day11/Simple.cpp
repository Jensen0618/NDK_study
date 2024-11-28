#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//读文件
/*void main() {
	char* filename = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\text.txt";

	FILE* file = fopen(filename, "r");

	if (file)
	{
		//定义缓冲区
		char buffers[10];//这里不能用char*的方式
		while (fgets(buffers, 10, file))
		{
			printf("%s", buffers);
		}


		fclose(file);//务必要关闭
	}
	else
		printf("文件打开失败");

	getchar();
}*/

//写文件
/*void main() {
	char* filename = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\text2.txt";

	FILE* file = fopen(filename, "w");

	if (file)
	{
		fputs("Hello Jensen", file);

		fclose(file);//务必要关闭
	}
	else
		printf("文件打开失败");

	getchar();
}*/

//使用二进制方式复制文件
/*void main() {

	//char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\text.txt";
	//char* filename_des = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\text1.txt";//写文本文件后面有乱码

	//复制图片正常
	char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a.png";
	char* filename_des = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a1.png";



	FILE* file_src = fopen(filename_src, "rb");//b:使用二进制方式
	//该方法会自动创建文件
	FILE* file_des = fopen(filename_des, "wb");//b:使用二进制方式

	if (file_src&&file_des)
	{
		const int size = 1024;
		int buffers[size];//文件缓冲区
		int len;//读取到的长度
		//为什么要有这个长度？当fread方法读取到的数据长度小于缓冲区长度时，其余的数据没有被覆盖，就会导致数据出错
		while (len = fread(buffers, sizeof(int), size, file_src) != 0)
		{
			fwrite(buffers, sizeof(int), len, file_des);//所以这里用的时len而不是size
		}

		fclose(file_src);
		fclose(file_des);
	}
	else
	{
		printf("文件打开出错");
	}


	getchar();
}*/


long filesize(FILE* file) {
	long curpos, length;
	//记住当前位置
	curpos = ftell(file);
	//移动到末尾
	fseek(file, 0L, SEEK_END);
	//获取文件大小
	length = ftell(file);
	//将指针移动回头部
	fseek(file, 0L, SEEK_SET);
	return length;
}


//获取文件大小
/*void main() {
	char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a.png";

	FILE* file_src = fopen(filename_src, "r");

	if (file_src)
	{
		//重定位流上的文件指针，移动指针到到文件尾巴
		//源文件，偏移量，起点；下面的代码意思是将指针移动到距离文件末尾偏移为0的位置，就是末尾
		//int ret = fseek(file_src, 0L, SEEK_END);
		//printf("重定位结果(0成功否则返回其他值)：%d\n", ret);
		////返回当前文件指针
		//long size = ftell(file_src);

		printf("文件大小%ld", filesize(file_src));

		fclose(file_src);
	}
	else
	{
		printf("文件打开失败");
	}
	getchar();

}*/


//文件加密
/*void  main(){
	 //利用异或加解密，不同为1，相同为0
	//比如10^5
	//10:1010    解密:1111
	// 5:0101　　　　  0101　　　　　　
	//   1111        1010


	char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a.png";//原图
	char* filename_encode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a2.png";//加密图

	FILE* file_src = fopen(filename_src, "rb");//b:使用二进制方式
	//"wb"会自动创建文件
	FILE* file_encode = fopen(filename_encode, "wb");//b:使用二进制方式

	if (file_src&&file_encode)
	 {
		//加密
		int src;
		while ((src=fgetc(file_src))!=EOF)//!=的优先级高于=，需要把赋值部分用括号包裹起来保证运行顺序
		{
			fputc(src ^ 5, file_encode);
		}

		fclose(file_src);
		fclose(file_encode);

	}
	else
	{
		printf("文件打开出错");
	}


	getchar();

}*/


//文件解密
/*void  main() {
	//利用异或加解密，不同为1，相同为0
	//比如10^5
	//10:1010    解密:1111
	// 5:0101　　　　  0101　　　　　　
	//   1111        1010


	char* filename_encode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a2.png";//加密图
	char* filename_decode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a3.png";//解密图

	FILE* file_encode = fopen(filename_encode, "rb");//b:使用二进制方式
											   //"wb"会自动创建文件
	FILE* file_decode = fopen(filename_decode, "wb");//b:使用二进制方式

	if (file_encode&&file_decode)
	{
		//解密
		int src;
		while ((src = fgetc(file_encode)) != EOF)//!=的优先级高于=，需要把赋值部分用括号包裹起来保证运行顺序
		{
			fputc(src ^ 5, file_decode);

		}

		fclose(file_encode);
		fclose(file_decode);

	}
	else
	{
		printf("文件打开出错");
	}


	getchar();

}*/


//使用字符串密码加密
/*void  main() {
	//利用异或加解密，不同为1，相同为0
	//比如10^5
	//10:1010    解密:1111
	// 5:0101　　　　  0101　　　　　　
	//   1111        1010


	char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a.png";//原图
	char* filename_encode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a2.png";//加密图

	FILE* file_src = fopen(filename_src, "rb");//b:使用二进制方式
											   //"wb"会自动创建文件
	FILE* file_encode = fopen(filename_encode, "wb");//b:使用二进制方式

	if (file_src&&file_encode)
	{
		//加密

		char* password = "123456";
		int pass_index = 0;
		int pass_len = strlen(password);

		int data;
		//EOF end of file 文件结束符
		while ((data = fgetc(file_src)) != EOF)//!=的优先级高于=，需要把赋值部分用括号包裹起来保证运行顺序
		{
			fputc(data ^ password[pass_index%pass_len], file_encode);
			pass_index++;
		}

		fclose(file_src);
		fclose(file_encode);

	}
	else
	{
		printf("文件打开出错");
	}



}*/

//文件解密
/*void  main() {
	//利用异或加解密，不同为1，相同为0
	//比如10^5
	//10:1010    解密:1111
	// 5:0101　　　　  0101　　　　　　
	//   1111        1010


	char* filename_encode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a2.png";//加密图
	char* filename_decode = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a3.png";//解密图

	FILE* file_encode = fopen(filename_encode, "rb");//b:使用二进制方式
	//"wb"会自动创建文件
	FILE* file_decode = fopen(filename_decode, "wb");//b:使用二进制方式

	if (file_encode&&file_decode)
	{
		//解密
		char* password = "123456";
		int pass_index = 0;
		int pass_len = strlen(password);

		int data;
		//EOF end of file 文件结束符

		while ((data = fgetc(file_encode)) != EOF)//!=的优先级高于=，需要把赋值部分用括号包裹起来保证运行顺序
		{
			fputc(data ^ password[pass_index%pass_len], file_decode);
			pass_index++;

		}

		fclose(file_encode);
		fclose(file_decode);

	}
	else
	{
		printf("文件打开出错");
	}

}*/


//文件拼接
void main() {
	char* filename_src = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a.jpg";//原图

	FILE* file = fopen(filename_src, "rb");

	if (file)
	{
		//文件大小
		long size = filesize(file);
		//每份文件大小，这里用的除法，不能整除的情况占大多数，所以最后一份文件需要把余的部分也加上
		long file_size_per = 1024 * 10;
		//文件分成几份
		int file_count = size / file_size_per;

		char** file_names = (char**)malloc(sizeof(char*) * file_count);

		for (size_t i = 0; i < file_count; i++)
		{
			//每个字符串分配100个char
			file_names[i] = (char*)malloc(sizeof(char) * 100);
			//文件名赋值
			sprintf(file_names[i], "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\a_%d.jpg", i);
			printf("%s\n", file_names[i]);
		}

		//分解
		long index = 0;
		for (size_t i = 0; i < file_count; i++)
		{
			FILE* file_w = fopen(file_names[i], "wb");
			if (!file_w)
			{
				printf("分块文件打开异常");
				getchar();
			}
			else
			{

				for (; index < file_size_per * (i + 1); index++)
				{
					fputc(fgetc(file), file_w);
				}
				//最后一份文件，写满剩余部分
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

		//拼接
		char* filename_des = "D:\\Users\\linzs\\Documents\\Visual Studio 2015\\Projects\\NDK_Day11\\b.jpg";
		FILE* file_des = fopen(filename_des, "wb");
		if (!file_des)
		{
			printf("拼接文件打开异常！");
			getchar();
		}

		int read_index = 0;

		for (size_t i = 0; i < file_count; i++) {
			FILE* file_r = fopen(file_names[i], "rb");
			if (!file_r)
			{
				printf("待拼接文件打开异常！");
				getchar();
			}
			for (; read_index < file_size_per * (i + 1); read_index++)
			{
				fputc(fgetc(file_r), file_des);
			}
			//最后一份文件，写满剩余部分
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
		printf("文件打开异常");
	}
	getchar();
}