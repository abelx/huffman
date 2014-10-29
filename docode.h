/*************************************************************************
	> File Name: docode.h
	> Author: abelx
	> Mail: theabelx@163.com
	> Created Time: 2014年10月29日 星期三 22时16分45秒
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include "huffman.h"

#define ENCODE 1
#define DECODE 2
#define TABLEN 256

#define naerror(err){perror(err); exit(1);}

int analysArgv(int, char **, char *, char *);

int query(char *);

void createTab(int *, char *);

void deCoding(FILE *, FILE *, HNode *);

void enCoding(HCode *,char *, char *,int *,int);

void getTabFromFile(int *, FILE *, int);

void uncompress(char *, char *);

void compress(char *, char *);

