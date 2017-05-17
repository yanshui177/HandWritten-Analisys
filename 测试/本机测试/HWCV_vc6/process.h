/*
头文件：process.h 图像处理函数头文件
*/
#pragma once
#include "StdAfx.h"
#include "Point.h"
#include "path.h"
#include "process.h"
#include <cv.h> 
#include <direct.h>
#include <io.h> 
#include <iostream>
#include <math.h>
#include <malloc.h>
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

/*全局变量*/
extern IplImage* src;

/***************************************函数原型****************************************/

int ComputeImage(vector<string> files, double bzckesa[50][50], double *wcd, int conti);
/*
功能：读入图像文件，进行二值化

@变量 img iplimage图像文件
@变量 bithro 二值化阈值
@返回值 黑像素的数目（待用）
*/
int*  binary(IplImage*  img, int bithro);


/*
功能：读入图像文件，对图像进行裁剪

@变量 img iplimage图像文件
@变量 img 裁剪后的iplimage图像文件
@jbwhite
@jbblack
@返回值 返回裁剪后的图像
*/
IplImage* Cjbsb(IplImage* img, IplImage* imgjbsb, int jbwhite, int jbblack);


/*
功能：计算图像的特征

@变量 imgbj 笔迹部分的图像
@返回值 计算得到的特征图像
*/
IplImage* outline(IplImage* imgbj);


/*
功能：输入图像的特征轮廓图，返回图像的特征值
@变量 imglk 输入的图像轮廓图
@变量 feature 得到的图像特征
@返回值 成功1失败0
*/
int outlinefeature(IplImage* imglk, int feature[][50]);


/*
功能：对单张图像的处理，最终得到一个特征值，用来计算各个图像之间的卡方距离

@变量 path 图像的物理地址
@变量 feature 图像的特征值
@返回值 处理后的图像
*/
IplImage* singlefeature(char* path, int feature[][50]);


/*
功能：细化之前的图像颜色处理，将颜色范围转换到0-1

@变量 ip 图像的句柄
@变量 jp
@变量 lx 图象宽度
@变量 ly 图象高度
@返回值 空
*/
void beforethin(unsigned char *ip, unsigned char *jp, unsigned long lx, unsigned long ly);


/*功能：细化算法 ，Rosenfeld细化算法，用于完成对笔迹图像的股价提取

@变量 image 代表图象的一维数组
@变量 lx 图象宽度
@变量 ly 图象高度
@返回值 无返回值
*/
void ThinnerRosenfeld(void *image, unsigned long lx, unsigned long ly);