/* 	程序名：Cjbsb.c
功能：读入图像文件，甄别图像的角标
*/
#pragma once
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>

extern IplImage* src;

IplImage* Cjbsb(IplImage* img,IplImage* imgjbsb,int jbwhite,int jbblack)
{
/*定义变量*/
    int i,j,ii,jj,sumjb1,sumjb2,jbi=0,jbj=0;
    int height,width,step,channels;
	uchar *data;
	int brklab=0;
/* 获取图像信息*/
  	height    = img->height;  
  	width     = img->width;	
  	step      = img->widthStep;	
  	channels  = img->nChannels;
  	data      = (uchar *)img->imageData;

//    IplImage* imgjbsb = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
	cvCopy(img,imgjbsb,NULL);
	uchar *imgjbsbdata= (uchar *)imgjbsb->imageData;




	//以角标为起点进行裁剪与画框
    CvSize jbcjsize=cvSize(835,165);           //角标裁剪框的大小，宽为835象素，高为165象素
    IplImage* imgjbcj = cvCreateImage(jbcjsize,img->depth,img->nChannels);
    uchar *imgjbcjdata= (uchar *)imgjbcj->imageData;
	int jbcjstep      = imgjbcj->widthStep;	
  	int jbcjchannels  = imgjbcj->nChannels;
	for(i=0;i<165;i++) 
		for(j=0;j<835;j++)
			imgjbcjdata[i*jbcjstep+j*jbcjchannels]=data[(i+jbi)*step+(j+jbj)*channels];
	for(i=0;i<165;i=i+2)
	{
		imgjbsbdata[(i+jbi)*step+jbj*channels]=0;
        imgjbsbdata[(i+jbi)*step+(jbj+835)*channels]=0;
	}
	for(j=0;j<835;j=j+2)
	{
        imgjbsbdata[jbi*step+(j+jbj)*channels]=0;
		imgjbsbdata[(jbi+165)*step+(j+jbj)*channels]=0;
	}

	return imgjbcj;
}