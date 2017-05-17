/* 	程序名：getFiles.c
功能：返回一个文件夹下的所有文件名
*/
#include<io.h>
#include <stdio.h>
#include<vector>
#include<iostream>
using namespace std;
#include <string.h>

void getFiles(string path, vector<string>& files ){  
	using namespace std;//引入整个名空间
    //文件句柄  
    long   hFile   =   0;  
    //文件信息  
    struct _finddata_t fileinfo;  
    string p;  
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{  
        do
		{  
            //如果是目录,迭代之  
             
            if((fileinfo.attrib &  _A_SUBDIR))
			{  
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );  
            } //如果不是,加入列表  
            else
			{  
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
            }  
        }while(_findnext(hFile, &fileinfo)  == 0);  

        _findclose(hFile);  
    }  
}  