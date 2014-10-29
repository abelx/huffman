/*************************************************************************
	> File Name: huffman.h
	> Author: abelx
	> Mail: 708841832@qq.com 
	> Created Time: 2014年10月20日 星期一 19时13分15秒
 ************************************************************************/
#include<stdlib.h>
#define MAXVALUE 100000
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


HCode * HuffmanCoding( int *, int);

HCode * getHuffmanCode(int *, int, HNode *);
