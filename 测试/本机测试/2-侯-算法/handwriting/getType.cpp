/*程序名：getType.c
功能：读入图像文件名，得到图像类型
*/
#pragma once
#include <stdio.h>
#include <string.h>
char * getType(char fileName[], char type[])
{
	int i=strlen(fileName)-1, j;
	char ch;

	for(type[0]='\0';i>=0;i--)
	{
		if(fileName[i] == '.')
		{// 遇到文件类型分隔符 
			for(j=i; fileName[j]!='\0'; j++)
			{
				ch = fileName[j];
				type[j-i] = ('A'<=ch && ch<='Z') ? (ch+'a'-'A'): ch;
			} 

			type[j-i] = '\0'; 
			break;
		}
		else if(fileName[i] == '/' || fileName[i]=='\\') break;// 遇到目录分割符，退出 
	}
	return type;
}