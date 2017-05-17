/* 	程序名：getFolders.c
功能：返回一个文件夹下的所有文件夹的名称
*/
#include<io.h>
#include <stdio.h>
#include<vector>
#include<iostream>
using namespace std;
#include <string.h>

int getFolders(string path, vector<string>& files )  
{   
	using namespace std;//引入整个名空间
    //文件句柄  
    long   hFile   =   0;  
    //文件信息  
    struct _finddata_t fileinfo;  
    string p; 
	
    int i=0;	 
    if((hFile = _findfirst(p.assign(path).append("/*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {  
			if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)		
			{
                files.push_back(p.assign(path).append("/").append(fileinfo.name) );  
				printf("文件夹：%s\n",files[i].c_str());
				i++;
			}

        }while(_findnext(hFile, &fileinfo)  == 0);  

        _findclose(hFile);  
    }  
    return 0;	
	
}  