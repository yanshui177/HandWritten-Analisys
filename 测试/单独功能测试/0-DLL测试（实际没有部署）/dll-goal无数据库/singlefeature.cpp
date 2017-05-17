/* 	程序名：singlefeature.c
功能：分总程序：读入图像文件，得出单个文件的特征值
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "Point.h"
#include<io.h>
#include<vector>
#include<iostream>
#include <string.h>
#include <direct.h>
#include"Thinner.h"

using namespace std;
/*各种声明*/                            
int*		binary(IplImage*  img, int bithro);  //二值化图像      
int			outlinefeature(IplImage* imglk, int feature[][50]);//计算图像的轮廓特征值                         
IplImage*	Cjbsb(IplImage* img, IplImage* imgjbsb, int jbwhite, int jbblack);//图像角标识别

IplImage* singlefeature(char* path, int feature[][50]){
	//定义变量
	IplImage* img = 0;          //原图
	IplImage* imglk = 0;        //轮廓图
	IplImage* imggj = 0;        //骨架图
	IplImage* imgjbsb = 0;      //角标识别图
	IplImage* imgbj = 0;        //只提取笔记部分的图像
	IplImage* imgbjhf = 0;      //为文字区域画上方格
	IplImage* imgwzbj = 0;      //为文字区域标出是否为文字（文字标记）

	int height, width, step, channels;
	uchar *data;

	int i, j;
	int *black;                 //用于返回图像每行黑像素的个数
	//int feature[50][50]={0};    //特征值初始化

	img = cvLoadImage(path, 0);

	/* 获取图像信息*/
	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *)img->imageData;

	/*开始处理*/

	/*图像放大*/
	IplImage* imgbig = 0;          //原图的放大图
	CvSize dst_cvsize;             //目标图像的大小
	float scale = 1;
	if (width<840){
		scale = (float)840 / width;
		dst_cvsize.width = 840;
		dst_cvsize.height = (int)(height*scale);
	}
	else
	{
		dst_cvsize.width = width;
		dst_cvsize.height = height;
	}

	imgbig = cvCreateImage(dst_cvsize, img->depth, img->nChannels);
	cvResize(img, imgbig, CV_INTER_LINEAR);	// CV_INTER_NN - 最近邻插值,
	//CV_INTER_LINEAR - 双线性插值 (缺省使用),
	//CV_INTER_AREA - 使用象素关系重采样。当图像缩小时候，该方法可以避免波纹出现。
	//CV_INTER_CUBIC - 立方插值.

	/*二值化*/
	int bithro = 230;                              //输入二值化的阈值   (0--255)
	black = binary(imgbig, bithro);                    //二值化，并统计黑像素的个数，返回每行黑像素的个数(black)
	//cvNamedWindow("二值化结果图",CV_WINDOW_AUTOSIZE);                   //显示图像
	//cvShowImage("二值化结果图",img); 
	//printf("二值化求解完成！！\n");



	/*角标识别*/
	int jbwhite = 5, jbblack = 4;
	imgjbsb = cvCreateImage(cvGetSize(imgbig), imgbig->depth, imgbig->nChannels);
	imgbj = Cjbsb(imgbig, imgjbsb, jbwhite, jbblack);                              //返回文字的笔迹部分


	/*计算骨架图*/
	imggj = cvCreateImage(cvGetSize(imgbj), imgbj->depth, imgbj->nChannels);   //复制
	cvCopy(imgbj, imggj, NULL);
	uchar *gjdata = (uchar *)imggj->imageData;

	beforethin(gjdata, gjdata, imggj->width, imggj->height);

	for (j = 0; j<imggj->height; j++)
	{ //取值范围转到0--1  

		for (i = 0; i<imggj->width; i++)
		{
			if (gjdata[j*imggj->widthStep + i] == 255)
				gjdata[j*imggj->widthStep + i] = 1;
		}
	}
	ThinnerRosenfeld(imggj->imageData, imggj->height, imggj->width);

	for (j = 0; j<imggj->height; j++)
	{//取值范围转到0--255,反转过来
		for (i = 0; i<imggj->width; i++)
		{
			if (gjdata[j*imggj->widthStep + i] == 1)
				gjdata[j*imggj->widthStep + i] = 0;
			else
				gjdata[j*imggj->widthStep + i] = 255;
		}
	}

	//保存图像 应先生成图像文件名
	/*
	char processPic[100]="E:/imggj/";
	char *namePic=new char[20];
	bool flag=false;
	string xuehao=path,kaoshihao=path;
	int num_iter=sizeof(path);
	for(int iter=0;iter<num_iter;iter++)
	{
	if(path[iter]=='x')
	{
	flag=true;
	break;
	}
	}
	if(flag)
	{
	xuehao=xuehao.substr(27,13);
	kaoshihao=kaoshihao.substr(40,5);
	}else
	{
	xuehao=xuehao.substr(27,12);
	kaoshihao=kaoshihao.substr(39,5);
	}
	strcat(processPic,xuehao.c_str());
	_mkdir(processPic);
	strcat(processPic,kaoshihao.c_str());
	strcat(processPic,".jpg");
	cvSaveImage(processPic,imggj);
	*/
	/*计算骨架特征徝*/
	outlinefeature(imggj, feature);   //特征值占48*48的右上三角形，feature调用返回
	//cvWaitKey(0);

	/*释放内存*/
	cvReleaseImage(&imgbig);
	cvReleaseImage(&img);
	cvReleaseImage(&imgbj);
	cvReleaseImage(&imglk);
	cvReleaseImage(&imgjbsb);
	cvReleaseImage(&imgbjhf);
	cvReleaseImage(&imgwzbj);
	cvDestroyAllWindows();

	return imggj;
}


