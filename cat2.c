/*************************************************************************
	> File Name: cat2.c
	> Author: abelx
	> Mail: 708841832@qq.com 
	> Created Time: 2014年10月22日 星期三 00时07分07秒
 ************************************************************************/

#include<stdio.h>

int main(int argc, char * argv[]){

	FILE * fp = fopen(argv[1], "rb");
	unsigned char c;
	int num = 0;
	while((char)(c = fgetc(fp)) != EOF)
	{

	
		printf("%hhx ",c);
		if(++num == 16)
		{
			num = 0;
			printf("\n");
		}
	}
	printf("\n");
	close(fp);
}
