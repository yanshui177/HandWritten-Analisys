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

	/*
	hFile=_findfirst(p.assign(path).append("\\*").c_str(),&fileinfo);         //第一次查找     to_search???
    files.push_back(p.assign(path).append("\\").append(fileinfo.name) ); 
	if(-1==hFile)return -1;                        //当前文件夹下没有子文件

    printf("%s\n",fileinfo.name);                   //打印出找到的文件的文件名
	int i=0; 
    while(!_findnext(hFile,&fileinfo))             //循环查找其他符合的文件，知道找不到其他的为止
    {
         printf("%s\n",files[i].c_str());
		 i++;
	}
    _findclose(hFile);                                      //别忘了关闭句柄
    system("pause");
    return 0;
    */


	
    int i=0;	 
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {  
            //如果是目录,迭代之  
            //如果不是,加入列表  
            //if((fileinfo.attrib &  _A_SUBDIR))  
            //{  
            //    if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
            //        getFiles( p.assign(path).append("\\").append(fileinfo.name), files );  
            //}  
            //else  
            //{  
			if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0) 
			{
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
				printf("文件夹：%s\n",files[i].c_str());
				i++;
			}
            //}  
        }while(_findnext(hFile, &fileinfo)  == 0);  
        _findclose(hFile);  
    }  
    return 0;	
	
}  