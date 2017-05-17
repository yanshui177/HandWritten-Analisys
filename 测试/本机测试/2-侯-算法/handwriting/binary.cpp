/* 	程序名：binary.c
功能：读入图像文件，进行二值化
*/
#pragma once
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>
int*  binary(IplImage*  img,int bithro)
{
	int height,width,step,channels;
	uchar *data;
	int i,j;
	static int black[1000];   //C语言不提倡返回一个局部变量的地址以外的功能，所以你必须定义的局部变量，如静态变量。
	/* 获取图像信息*/
  	height    = img->height;  
  	width     = img->width;	
  	step      = img->widthStep;	
  	channels  = img->nChannels;
  	data      = (uchar *)img->imageData;

	/*二值化，并统计黑像素的个数*/
	for(i=0;i<height;i++)
	{
			for(j=0;j<width;j++)//对图像每个点进行二值化,原值为128
				data[i*step+j*channels]=(data[i*step+j*channels]>bithro)?255:0;
	}

    /*计算每一行的黑像素个数*/
	int tempBlackPixel=0;
	
	memset(black,0,1000);            //##初始化内存，这里用做清零black数组
	for(i=height-1;i>0;i--)
	{ 
		for(int j=0;j<width;j++)
		{
		   	if(data[i*step+j*channels]==0)        //计算黑色的像素数
		   		tempBlackPixel+=1;
		}
		black[height-i]=tempBlackPixel;   //black记录黑色像素数
		tempBlackPixel=0;
	}
	//二值化，并统计黑像素的个数**********
	return black;
}


