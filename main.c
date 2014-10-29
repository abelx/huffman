/*************************************************************************
	> File Name: main.c
	> Author: abelx
	> Mail: 708841832@qq.com 
	> Created Time: 2014年10月20日 星期一 15时51分10秒
 ************************************************************************/

#include "huffman.h"

void createTab(int *, char *);
void doCoding(HCode *,char *, char *, int *, int);
void query(char *);

int main(int argc,char *argv[]){

	if(access(argv[2],0) == 0)
		query(argv[2]);
	
	if(strcmp(argv[3],"-u") == 0)
	{
		decoding(argv[1],argv[2]);
	}
	else if (strcmp(argv[3],"-c") == 0)
	{
		int tab[TABLEN];
		HCode * hc;
		memset(tab,0,sizeof(tab));
		createTab(tab,argv[1]);
		hc = HuffmanCoding(tab,TABLEN);
	/*
	//TEST
	int i,j;
	for(i=0;i<TABLEN;i++)
	{
		printf("%hhx:",i);
		for(j=hc[i].start;j<TABLEN;j++)
			printf("%d ",hc[i].bit[j]);
		printf("\n");
	}
	*/
		doCoding(hc,argv[1],argv[2],tab,TABLEN);
	}
	return 0;
}

void createTab(int * tab,char * file){
		
	FILE * fp = fopen(file,"rb");
	unsigned char c;
	if(fp == NULL)
		naerror(file);
	while((char)(c = fgetc(fp)) != EOF)
		tab[(int)c]++;
	fclose(fp);
}

void doCoding(HCode * hc,char *sfile, char *dfile,int *tab,int n){
	FILE * sfp = fopen(sfile,"rb");
	FILE * dfp = fopen(dfile,"wb");
	unsigned char c,buf = 0;
	int i,num = 0;
	if(sfp == NULL)
		naerror(sfile);
	if(dfp == NULL)
		naerror(dfile);

	//写入词频表
	fwrite(tab,sizeof(int),TABLEN,dfp);
	//写入编码后内容
	while(c = fgetc(sfp), feof(sfp) == 0)
	{
		//test
		//printf("code:%hhx ",c);
		for(i = hc[(int)c].start; i < TABLEN; i++){
			//test
			//printf("%d ",hc[(int)c].bit[i]);
			buf <<= 1;
			buf |=  hc[(int)c].bit[i];
			if( ++num==8){
				//test
				//printf("%hhx",buf);	
				fputc(buf,dfp);
				num = 0;
			}
		}
	}
//尾字节不足填充，增加一字节表示前一字节有效位数
	if(num != 0)
	{
		buf <<= (8-num);
		fputc(buf,dfp);
	}
	else
		num = 8;
	fputc(num,dfp);
	
	fclose(sfp);
	fclose(dfp);
	

}

void decoding(char * sfile, char * dfile){

	FILE * sfp = fopen(sfile,"rb");
	FILE * dfp = fopen(dfile,"wb");
	int i,num = 0;
	
	int tab[TABLEN];
	HNode * hn;
	unsigned char lc,c,nc;

	int start = 2*TABLEN - 2;
	if(sfp == NULL)
		naerror(sfile);
	if(dfp == NULL)
		naerror(dfile);

	//读取词频表
	fread(tab,sizeof(int),TABLEN,sfp);

	hn = createHuffmanTree(tab, TABLEN);
	if(feof(sfp) != 0) return;
			lc = fgetc(sfp);
	if(feof(sfp) != 0) return;
			c = fgetc(sfp);
	while(nc = fgetc(sfp),feof(sfp) == 0)
	{
		//printf("test");
		for(i = 0; i<8; i++)
		{
			if((lc & ((unsigned char)1 << (7 - i))) == ((unsigned char)1 << (7 - i)))
				start = hn[start].rchild;
			else
				start = hn[start].lchild;
			if(start < TABLEN && start > 0){
				fputc((unsigned char)start,dfp);
				start = 2*TABLEN - 2;
			}
		}
		lc = c;
		c  = nc;
	}
	//test
	//printf("%hhx,%d",lc,(int)c);
		//代码写的略但疼、、、 处理尾字节
		for(i = 0; i<(int)c; i++)
		{
			//test
			//printf(".%d",i);
			if((lc & ((unsigned char)1 << (7 - i))) == (unsigned char)1 << (7 -i))
				start = hn[start].rchild;
			
			else	
				start = hn[start].lchild;
			
			if(start < TABLEN && start > 0){
				//test
				//printf("%d",start);
				fputc((unsigned char)start,dfp);
				start = 2*TABLEN - 2;
			}
		}

		fclose(sfp);
		fclose(dfp);
}

void query(char * file){
	printf("文件%s存在，是否覆盖？(n+回车结束，y+回车继续)",file);
	char c;
	scanf("%c",&c);
	if(c == 'n')
		exit(0);
}
