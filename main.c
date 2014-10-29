/*************************************************************************
	> File Name: main.c
	> Author: abelx
	> Mail: 708841832@qq.com 
	> Created Time: 2014年10月20日 星期一 15时51分10秒
 ************************************************************************/

#include "docode.h"

int main(int argc, char *argv[])
{
	char *sfile, *dfile;
	int option;

	sfile = argv[2];
	dfile = argv[3];

	option = analysArgv(argc, argv, sfile, dfile);

	if(option == 0)
		return 1;
	
	if(access(dfile,0) == 0)
	{
		if(!query(dfile))
			return 1;
	}
	
	if(option == ENCODE)
		compress(sfile, dfile);
	else if(option == DECODE)
		uncompress(sfile, dfile);

	return 0;
}
