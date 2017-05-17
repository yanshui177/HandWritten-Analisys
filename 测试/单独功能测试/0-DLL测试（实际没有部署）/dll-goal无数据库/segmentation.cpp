#pragma once
#ifdef WIN32                            //屏蔽VC6对STL的一些不完全支持造成
#pragma warning (disable: 4514 4786)
#endif
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cv.h>
#include<io.h>             //下面的5个用于读取文件夹下的所有文件名
#include<vector>
#include <string.h>
#include<windows.h>        //用于弹出提示框,,,切记！当调用<windows.h>时，不要调用MFC！（Afx.h)
#include<string.h>
using namespace std;

int*		binary(IplImage*  img,int bithro);				//二值化图像
int			outlinefeature(IplImage* imglk,int feature[ ][50]);  //计算图像的轮廓特征值            
int			read_scanf(const string &filename,const int &cols,vector<double *> &_vector);	//读取已经存好的特征值
IplImage*	Cjbsb(IplImage* img,IplImage* imgjbsb,int jbwhite,int jbblack);					//图像角标识别
IplImage*	outline(IplImage* imgbj);              //计算图像对应的轮廓图
IplImage*	singlefeature(char* path,int feature[ ][50]);	//得出单个文件的特征值

char *fo = "H:\\logs_dll_check_only.txt";
char rec[2000] = "\n结果集合为空:";
FILE *fpzz3 = NULL;//需要注意

extern "C" _declspec(dllexport) char * __stdcall  WINAPI TEST(char *fpname1){
	return fpname1;//总文件夹的路径
}
extern "C" _declspec(dllexport) char * __stdcall  WINAPI HWCV(char *fpname1,char *dest)
{
	int		conti = 1;		
	int		size, i, ii, jj, feature[50][50][30] = { 0 }, featureall;					
	double	featurep[50][50][30] = { 0 },bzcu[50][50] = { 0 }, bzckesa[50][50] = { 0 }, wcd[30] = { 0 };	

	int		featx[50][50] = { 0 }, featdif[30] = { 0 }, maxi; float maxx = 0;			//最大特征值的标号与值
	int		xyimgnum = 0;					//嫌疑图片的数目
	char	str[80];					//存储地址


	/*变量定义*/
	vector<string> suspict;		//记录嫌疑图片地址
	vector<float> suspict_wcd;
	vector<string> files;		//存储该生所有考试文件路径
	vector<string> dateVec, subjectVec, stuNum2;
	vector<int> flagVec;//记录查到的学生的所有考试信息
	
	files.push_back("D:\\tupian\\201110\\0534\\010209400748.jpg");
	files.push_back("D:\\tupian\\201010\\0665\\010209400748.jpg");
	files.push_back("D:\\tupian\\201606\\0668\\010209400748.jpg");
	files.push_back("D:\\tupian\\201101\\0799\\010209400748.jpg");
	files.push_back("D:\\tupian\\201101\\0883\\010209400748.jpg");
	files.push_back("D:\\tupian\\201201\\0884\\010209400748.jpg");
	files.push_back("D:\\tupian\\201107\\0885\\010209400748.jpg");
	files.push_back("D:\\tupian\\201307\\0886\\010209400748.jpg");
	files.push_back("D:\\tupian\\201307\\0887\\010209400748.jpg");
	files.push_back("D:\\tupian\\201107\\0888\\010209400748.jpg");
	files.push_back("D:\\tupian\\201404\\4685\\010209400748.jpg");
	files.push_back("D:\\tupian\\201104\\1180\\010209400748.jpg");
	files.push_back("D:\\tupian\\201110\\1181\\010209400748.jpg");
	files.push_back("D:\\tupian\\201510\\0359\\080215203444.jpg");
	files.push_back("D:\\tupian\\201212\\0101\\010209400748.jpg");
	files.push_back("D:\\tupian\\201606\\4927\\010209400748.jpg");

	size = files.size();	//图像的数目

	//开始对每一张图片进行处理
	for (i = 0; i < size; i++)
	{
		memset(str, 0, sizeof(str));
		memset(featx, 0, sizeof(featx));
		memset(bzcu, 0, sizeof(bzcu));

		strcpy(str, files[i].c_str());

		singlefeature(str, featx);				//featx[][50]
		featureall = 0;                                    //图像特征值和的初始化
		for (ii = 0; ii < 48; ii++)                             //将featx存起来,回头看能不能用函数换掉
			for (jj = ii + 1; jj < 47; jj++)
			{
			feature[ii][jj][i] = featx[ii][jj];
			featureall = featureall + featx[ii][jj];
			}
		//求轮廓方向特征featurep，式(5)  与标准差中的u的和
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
			{
			featurep[ii][jj][i] = (double)featx[ii][jj] / featureall;
			bzcu[ii][jj] += (double)featx[ii][jj] / featureall * 1000;     //标准差的值过小,进行放大（1）
			}
	}

	//处理完一个人的每一张图片后
	//----------------------------------------------------------//
	for (ii = 0; ii < 48; ii++)//求标准差中的u
		for (jj = ii + 1; jj < 47; jj++)
			bzcu[ii][jj] = bzcu[ii][jj] / size;


	/*将标准差中的kesa加载进来*/
	string bzcfile = "D:/Xiangmu/Img/bzc/bzc.txt";
	//txt文件中有47列
	int bzccolumns = 47;
	vector<double *> output_bzc;
	if (!read_scanf(bzcfile, bzccolumns, output_bzc)) return 0;

	//output_vector可视为二维数组;输出数组元素：
	//int rows=output_bzc.size();
	for (ii = 0; ii < 48; ii++)
		for (jj = ii + 1; jj < 47; jj++)
			bzckesa[ii][jj] = output_bzc[ii][jj];

	//求相似性就是带权卡方wcd
	for (i = 0; i < size; i++)
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
				if (featurep[ii][jj][i] * featurep[ii][jj][conti] != 0 && bzckesa[ii][jj] != -1)
					wcd[i] += pow((featurep[ii][jj][i] - featurep[ii][jj][conti]), 2) / ((featurep[ii][jj][i] + featurep[ii][jj][conti])*bzckesa[ii][jj]);

	//求卡方距离的最大值 
	for (i = 0; i < size; i++)
	{
		if (maxx < wcd[i]){ maxx = wcd[i]; maxi = i; }
		if (wcd[i] > 0.12)
		{
			xyimgnum++;
			suspict.push_back(files[i].c_str());
			suspict_wcd.push_back(wcd[i]);
			flagVec.push_back(1);//嫌疑标记
		}else
		{
			flagVec.push_back(0);
		}
	}
	
	/*存储文件记录*/
	//char*	fpname = "C:/Users/闫帅帅/Desktop/result2.txt";
	//char	record[2400] = { 0 };
	//FILE*	fpzz = NULL;//需要注意

	fpzz3 = fopen(fo, "a");  //创建文件 //a		
	if (NULL == fpzz3) return "ERR";//要返回错误代码
	fprintf(fpzz3, rec); //从控制台中读入并在文本输出
	fclose(fpzz3);
	fpzz3 = NULL;//需要指向空，否则会指向原打开文件地址  

	//将结果存入txt	
	memset(rec, 0, sizeof(rec));
	strcpy(rec, "图片总数为：");
	char pic_num[20];
	_itoa(size, pic_num, 10);
	strcat(rec, pic_num);
	if (xyimgnum > 0)
	{
		strcat(rec, "\n");
		for (i = 0; i < xyimgnum; i++)
		{
			strcat(rec, "\t");
			strcat(rec, suspict[i].c_str());
			strcat(rec, "\t");
			char a[20];
			sprintf(a, "%g", suspict_wcd[i]);
			strcat(rec, a);
			strcat(rec, "\n");
		}
	}
	else strcat(rec, "\t没有嫌疑图像！\n");

	fpzz3 = fopen(fo, "a");  //创建文件 //a
	if (NULL == fpzz3) return "ERR";//要返回错误代码
	fprintf(fpzz3, rec); //从控制台中读入并在文本输出
	fclose(fpzz3);
	fpzz3 = NULL;//需要指向空，否则会指向原打开文件地址  

	suspict.clear();
	suspict_wcd.clear();
	output_bzc.clear();

	//memset(record, 0, 2400);
	memset(feature, 0, sizeof(feature));
	memset(featurep, 0, sizeof(featurep));
	memset(bzckesa, 0, sizeof(bzckesa));
	memset(wcd, 0, sizeof(wcd));
	memset(featdif, 0, sizeof(featdif));




	char out[100]="成功！\n";
	strcat(out, fpname1);
	sprintf(dest, out );

	return "return_OK";
}


