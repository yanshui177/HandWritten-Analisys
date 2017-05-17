/* 	程序名：outline.c
功能：输入文字图像。得到相应的轮廓图
*/
#pragma once
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>

IplImage* outline(IplImage* imgbj)
{
	/*定义变量*/
    int i,j;
    int height,width,step,channels;
  	uchar *data;

    /*定义新的图像*/
	IplImage* imglk = cvCreateImage(cvGetSize(imgbj),imgbj->depth,imgbj->nChannels);

    /* 获取图像信息*/
  	height    = imgbj->height;  
  	width     = imgbj->width;	
  	step      = imgbj->widthStep;	
  	channels  = imgbj->nChannels;
  	data      = (uchar *)imgbj->imageData;


	for(j=0;j<height;j++)
	{
		for(int i=0;i<width;i++)
			imglk->imageData[j*step+i*channels]=255;
		for( i=0;i<width-1;i++)
			if(data[j*step+(i+1)*channels]-data[j*step+i*channels]==255)             //竖线右侧框
		   		imglk->imageData[j*step+i*channels]=0;
		    else if(data[j*step+i*channels]-data[j*step+(i+1)*channels]==255)        //竖线左侧框
		   		imglk->imageData[j*step+(i+1)*channels]=0;
	}

	for(i=0;i<width;i++) 
		for(j=0;j<height-1;j++)
			if(data[j*step+i*channels]-data[(j+1)*step+i*channels]==255)             //横线下侧框
		   		imglk->imageData[(j+1)*step+i*channels]=0;
		    else if(data[(j+1)*step+i*channels]-data[j*step+i*channels]==255)        //横线上侧框
		   		imglk->imageData[j*step+i*channels]=0;

	return imglk;
}