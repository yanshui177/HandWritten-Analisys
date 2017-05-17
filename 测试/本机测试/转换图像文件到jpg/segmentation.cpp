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
#include "Point.h"
#include "FreeImage.h"     //用于读gif的图像,（将gif图像转换为png）
#include<io.h>             //下面的5个用于读取文件夹下的所有文件名
#include<vector>
#include<iostream>
#include <string.h>
#include<windows.h>        //用于弹出提示框,,,切记！当调用<windows.h>时，不要调用MFC！（Afx.h)
#include<string.h>
using namespace std;
#ifdef WIN32                            //屏蔽VC6对STL的一些不完全支持造成
#pragma warning (disable: 4514 4786)
#endif

/*-----------各种声明-----------------------*/

void		getFiles(string	path, vector<string>& files );//9、读取文件名下所有文件名        
char*		getType(char fileName[], char type[]);  //2、获取图像类型  
int*		binary(IplImage* img,int bithro); //3、二值化图像 
int			getFolders(string path, vector<string>& files );//11、读取文件名下所有文件夹的名称          
int			read_scanf(const string &filename,const int &cols,vector<double *> &_vector);//12、读取已经存好的特征值
int			searchDir(char* path, vector<string> &dir);//获取目录下一层的所有文件夹
IplImage*	Cjbsb(IplImage*	img,IplImage* imgjbsb,int jbwhite,int jbblack);//4、图像角标识别                    
IplImage*	gif2ipl(const char* filename);  //1、读取gif的外部函数     
IplImage*	singlefeature(char* path,int feature[ ][50],int flag);//10、得出单个文件的特征值  

int pos_x=0,pos_y=0;
bool pos_flag=false;
IplImage* src;
int picAll=0,picSus=0;

int main()
{
	time_t start ,end ;//计时
	double cost;  time(&start); 

	//定义变量
	//------------------------------------------------------//
	char path[100] =  "D:\\xiangmu\\Img\\imgjiaobiao3\\";
	vector<string> dir;				//存储目录
	int conti=1;     //对比图像的标号
	int size_dir,num_dir;

	searchDir(path, dir);//获取filePath下的所有一级目录并存储到dir中
	size_dir=dir.size(); //dir的大小就是学生的数量

	//开始转换
	//-------------------------------------------------------------//
	for(num_dir=0;num_dir<size_dir;num_dir++)//对每一个学生目录进行循环  
	{
		int		size,i,j,ii,jj;				//通用变量
		char	str[80];					//存储地址
		int		featx[30][50];
		vector<string> files;		//存储文件路径
		
		getFiles(dir[num_dir].c_str(), files );	//遍历当前文件夹下的所有文件
		//输出
		printf("\n第%d，目录：%s",num_dir,dir[num_dir].c_str());

		size = files.size();	//图像的数目
		//输出
		printf("\t个数：%d\t",size);

		//开始对每一张图片进行处理
		//------------------------------------------------------//
		int flag=1;
		for (i = 0;i < size;i++)
		{  
			memset(str,0,sizeof(str));
			strcpy(str,files[i].c_str());
			try
			{
				singlefeature(str,featx,flag);//str图片路径 featx：图片特征值，存在变量中featx中
			}catch(int x)
			{
				
			}
			flag=0;
		}


	}
	return 0;
}

