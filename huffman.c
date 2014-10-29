/*************************************************************************
	> File Name: huffman.c
	> Author: abelx
	> Mail: 708841832@qq.com 
	> Created Time: 2014年10月20日 星期一 17时27分19秒
 ************************************************************************/

#include "huffman.h"

HCode * HuffmanCoding(int *tab, int n){

	HCode * hc;
	HNode * ht;
	ht = createHuffmanTree(tab,n);
	
	int i,c,f,start;
	hc = (HCode *)malloc(n*sizeof(HCode));
	for (i=0; i<n; ++i)
	{
		start = n-1; //最后一位为hc[i].bit[n]
		for (c = i, f = ht[i].parent; f != -1; c = f, f = ht[f].parent )	
			if(ht[f].lchild == c)
				hc[i].bit[start--] = 0;
			else
				hc[i].bit[start--] = 1;
	
		hc[i].start = start + 1;
	}

	return hc;
}

HNode * createHuffmanTree(int * tab, int n){

	if(n <= 1) return;
	int m = 2*n - 1;
	HNode *ht, *p;
	int x1, x2, m1, m2, i, j;
	ht = (HNode *) malloc(m*sizeof(HNode));

	//初始化叶子节点信息
	for(p = ht,i = 0; i<n; ++i,++p)
	{
		p->weight = *(tab+i);
		p->value  = i;
		p->lchild = -1;
		p->rchild = -1;
		p->parent = -1;
	}
	
	//初始化分支节点信息
	for (; i<m; ++i,++p)
	{
		p->weight = 0;
		p->value	 = 0;
		p->lchild = -1;
		p->rchild = -1;
		p->parent = -1;
	}
	//寻找根节点权值最小的两颗子树
	for (i=n; i<m; ++i)
	{
		m1 = m2 = MAXVALUE;
		x1 = x2 = 0;
		for (j = 0; j < i; ++j)
		{
			if (ht[j].parent == -1 && ht[j].weight<m1)
			{
				m2 = m1;
				x2 = x1;
				m1 = ht[j].weight;
				x1 = j;
			}
			else if( ht[j].parent == -1 && ht[j].weight<m2){
				m2 = ht[j].weight;
				x2 = j;
			}
		}
		//合并成一个新的子树
		ht[x1].parent = i;
		ht[x2].parent = i;
		ht[i].lchild  = x1;
		ht[i].rchild  = x2;
		ht[i].weight  = m1 + m2;
		
	}
	return ht; 

}
