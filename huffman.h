/*************************************************************************
	> File Name: huffman.h
	> Author: abelx
	> Mail: 708841832@qq.com 
	> Created Time: 2014年10月20日 星期一 19时13分15秒
 ************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAXVALUE 100000
#define TABLEN 256
#define naerror(err) { perror(err);exit(1);}
#define MAXBIT   256 

typedef struct HNode{
	char	value;
	int		weight;
	int		parent,lchild,rchild;
 } HNode;
typedef struct HCode{
	char	bit[MAXBIT];
	int				start;
} HCode;


HNode * createHuffmanTree(int *, int);
HCode * HuffmanCoding( int *, int );
