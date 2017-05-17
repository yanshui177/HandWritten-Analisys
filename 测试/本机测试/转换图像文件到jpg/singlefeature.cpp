/* 	程序名：singlefeature.c
功能：分总程序：读入图像文件，得出单个文件的特征值
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "Point.h"
#include "FreeImage.h"     //用于读gif的图像
#include<io.h>             //下面的5个用于读取文件夹下的所有文件名
#include<vector>
#include<iostream>
using namespace std;
#include <string.h>
#include <direct.h>
#include"Thinner.h"

/*各种声明*/

void		getFiles(string path, vector<string>& files );//读取文件名下所有文件                             
char*		getType(char fileName[], char type[]); //获取图像类型       
int*		binary(IplImage*  img,int bithro);  //二值化图像      
int			outlinefeature(IplImage* imglk,int feature[ ][50]);//计算图像的轮廓特征值                         
IplImage*	Cjbsb(IplImage* img,IplImage* imgjbsb,int jbwhite,int jbblack);//图像角标识别
IplImage*	gif2ipl(const char* filename);     //读取gif的外部函数

IplImage* singlefeature(char* path,int feature[ ][50],int flag){
	//定义变量
  	IplImage* img = 0;          //原图
    IplImage* imglk = 0;        //轮廓图
	IplImage* imggj = 0;        //骨架图
	IplImage* imgjbsb = 0;      //角标识别图
	IplImage* imgbj = 0;        //只提取笔记部分的图像

	char imgtype[10];           //判断图像类型
  	int height,width,step,channels;
  	uchar *data;

	int *black;                 //用于返回图像每行黑像素的个数
	//int feature[50][50]={0};    //特征值初始化

	getType(path, imgtype);
	if(strcmp(".gif", imgtype) == 0)
	{
		IplImage* Iplimg=gif2ipl(path);                   //gif 转 rgb 三维
	    img=cvCreateImage(cvGetSize(Iplimg),Iplimg->depth,1);

		cvCvtColor(Iplimg,img,CV_RGB2GRAY);                 //rgb 转灰度
		cvReleaseImage(&Iplimg);                            //释放临时图像的内存
		cvFlip(img,NULL, 0);                                //由于得到的灰度图是翻转的，所以再翻转回来
	}
	else if(strcmp(".jpg", imgtype) == 0 || strcmp(".png", imgtype) == 0)
		img=cvLoadImage(path,0);
	else 
		return NULL;

  	if(!img)
	{
   		printf("Could not load image file: %s\n",path);
    	exit(0);
  	}


  	// 获取图像信息
  	height    = img->height;  
  	width     = img->width;	
  	step      = img->widthStep;	
  	channels  = img->nChannels;
  	data      = (uchar *)img->imageData;

	//开始处理

    //图像放大
    IplImage* imgbig = 0;          //原图的放大图
    CvSize dst_cvsize;             //目标图像的大小
	float scale=1;
	if(width<850){
        scale=(float)850/width;
		dst_cvsize.width=850;
		dst_cvsize.height=(int)(height*scale);
	}
	else
	{
		dst_cvsize.width=width;
		dst_cvsize.height=height;
	}

	imgbig=cvCreateImage(dst_cvsize,img->depth,img->nChannels);
    cvResize(img,imgbig,CV_INTER_LINEAR);	// CV_INTER_NN - 最近邻插值,
											//CV_INTER_LINEAR - 双线性插值 (缺省使用),
											//CV_INTER_AREA - 使用象素关系重采样。当图像缩小时候，该方法可以避免波纹出现。
											//CV_INTER_CUBIC - 立方插值.

	//二值化
	int bithro=230;                              //输入二值化的阈值   (0--255)
    black=binary(imgbig,bithro);                    //二值化，并统计黑像素的个数，返回每行黑像素的个数(black)
    //cvNamedWindow("二值化结果图",CV_WINDOW_AUTOSIZE);	//显示图像
    //cvShowImage("二值化结果图",img); 
	//printf("二值化求解完成！！\n");

    //角标识别,裁切出图像
	int jbwhite=5,jbblack=4;
	imgjbsb = cvCreateImage(cvGetSize(imgbig),imgbig->depth,imgbig->nChannels);
    imgbj=Cjbsb(imgbig,imgjbsb,jbwhite,jbblack);                              //返回文字的笔迹部分
 
	//存储裁剪后的图像
	//D:/xiangmu/Img/imgjiaobiao/010211100059x/0359.gif
	char isavePath[200]="E";

	//此处需要新建一个新建文件夹的选项
	string name=path;
	strcat(isavePath, name.substr(1, 39).c_str());

	string md="mkdir ";
	md += isavePath;
	//组合出新名字
	strcat(isavePath, name.substr(40, 5).c_str());
	strcat(isavePath, ".jpg");
	//创建文件夹
	if(flag) system(md.c_str());
	//保存图像
	cvSaveImage(isavePath,imgbj);



	cvReleaseImage(&imgbig);
  	cvReleaseImage(&img );  
	cvReleaseImage(&imgbj ); 
    cvDestroyAllWindows();  
	cout<<".";
  	return imggj;
}


