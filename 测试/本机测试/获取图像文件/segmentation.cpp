/* 	程序名：segmentation.c
功能：总程序：读入图像文件，分析特征，输出效果
*/
//#include "stdafx.h"
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include<io.h>             //下面的5个用于读取文件夹下的所有文件名
#include<vector>
#include<iostream>
#include <string.h>
#include<windows.h>
#include<string.h>
using namespace std;
#ifdef WIN32                            //屏蔽VC6对STL的一些不完全支持造成
#pragma warning (disable: 4514 4786)
#endif

/*-----------各种声明-----------------------*/

void		getFiles(string	path, vector<string>& files );//9、读取文件名下所有文件名  
int			getFolders(string path, vector<string>& files );//11、读取文件名下所有文件夹的名称          
int			searchDir(char* path, vector<string> &dir);//获取目录下一层的所有文件夹

int main()
{

	char path[100] =  "E:/xiangmu/Img/imgjiaobiao/";
    
	vector<string> dir; //存储目录
	int size_dir,num_dir;

	char*	fpname= "C:/Users/闫帅帅/Desktop/result2.txt"; 
	char	record[2400]={0};
	FILE*	fpzz=NULL;//需要注意

	searchDir(path, dir);//获取filePath下的所有一级目录并存储到dir中
	size_dir=dir.size(); //dir的大小就是学生的数量
	
	
	//开始检测
	//-------------------------------------------------------------//
	for(num_dir=0;num_dir<size_dir;num_dir++)//对每一个学生目录进行循环
	{
		int i=0;
		vector<string> files;		//存储文件路径
		
		getFiles(dir[num_dir].c_str(), files );	//遍历当前文件夹下的所有文件
		int size=files.size();
		cout<<"numdir: "<<num_dir<<" size: "<<size<<endl;

		//开始对每一张图片进行处理
		//------------------------------------------------------//
		for (i = 0;i < size;i++)	 cout<<"\t"<<files[i].c_str()<<endl;
		cout<<endl;
		

	}

}