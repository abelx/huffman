/*************************************************************************
	> File Name: docode.c
	> Author: abelx
	> Mail: theabelx@163.com
	> Created Time: 2014年10月29日 星期三 21时55分08秒
 ************************************************************************/

#include "docode.h"

int analysArgv(int n, char *arg[], char * sfile, char * dfile)
{
	int i, op = 0;
	
	if(n != 4)
	{
		printf("you should use 3 args like : <source-file> <dest-file> -c\n");
		printf("-c:		compress\n");
		printf("-u:		uncompress\n");
	}

	if(strcmp(arg[1],"-c") == 0)
		op = ENCODE;
	else if(strcmp(arg[1],"-u") == 0)
		op = DECODE;
	
	return op;

}

int query(char * file)
{
	char c;
	int n = 0;
	printf("file %s exists, cover it?(n or y)", file);
	scanf("%c", &c);
	if(c == 'y')
		n = 1;
	return n;

}

void createTab(int * tab,char * file)
{		
	FILE * fp = fopen(file,"rb");
	unsigned char c;
	if(fp == NULL)
		naerror(file);
	while((char)(c = fgetc(fp)) != EOF)
		tab[(int)c]++;
	fclose(fp);
}

void compress(char * sfile, char * dfile)
{
	int tab[TABLEN];
	
	HCode * hc;
	HNode * hTree;

	memset(tab,0,sizeof(tab));

	createTab(tab, sfile);
	
	hTree = createHuffmanTree(tab, TABLEN);
	hc = getHuffmanCode(tab, TABLEN, hTree);
	
	enCoding(hc, sfile, dfile, tab, TABLEN);

}

void uncompress(char * sfile, char * dfile)
{
	FILE * sfp = fopen(sfile,"rb");
	FILE * dfp = fopen(dfile,"wb");

	int tab[TABLEN];
	getTabFromFile(tab,sfp,TABLEN);

	HNode * hTree;
	hTree = createHuffmanTree(tab, TABLEN);
	
	deCoding(sfp, dfp,hTree);

	fclose(sfp);
	fclose(dfp);
}

void getTabFromFile(int * tab, FILE * fp, int n)
{
	fread(tab,sizeof(int),TABLEN,fp);
}

void enCoding(HCode * hc,char *sfile, char *dfile,int *tab,int n)
{
	FILE * sfp = fopen(sfile,"rb");
	FILE * dfp = fopen(dfile,"wb");

	if(sfp == NULL)
		naerror(sfile);
	if(dfp == NULL)
		naerror(dfile);
	
	unsigned char c,buf = 0;
	
	int i,num = 0;
	
	if(sfp == NULL)
		naerror(sfile);
	if(dfp == NULL)
		naerror(dfile);

	fwrite(tab,sizeof(int),TABLEN,dfp);
	
	while(c = fgetc(sfp), feof(sfp) == 0)
	{
		for(i = hc[(int)c].start; i < TABLEN; i++){
			buf <<= 1;
			buf |=  hc[(int)c].bit[i];
			if( ++num==8){
				fputc(buf,dfp);
				num = 0;
			}
		}
	}
	
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

void deCoding(FILE * sfp, FILE * dfp, HNode * hn)
{	
	int i,num = 0;
		
	unsigned char lc,c,nc;

	int start = 2*TABLEN - 2;
	
	
	if(feof(sfp) != 0) return;
			lc = fgetc(sfp);
	if(feof(sfp) != 0) return;
			c = fgetc(sfp);
	
	while(nc = fgetc(sfp),feof(sfp) == 0)
	{
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
	
	for(i = 0; i<(int)c; i++)
	{
		if((lc & ((unsigned char)1 << (7 - i))) == (unsigned char)1 << (7 -i))
			start = hn[start].rchild;
		else	
			start = hn[start].lchild;
		
		if(start < TABLEN && start > 0){
			fputc((unsigned char)start,dfp);
			start = 2*TABLEN - 2;
		}
	}

}

