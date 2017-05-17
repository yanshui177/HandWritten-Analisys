/* 	程序名：Cjbsb.c
功能：读入图像文件，甄别图像的角标
	参数设置：
		img 大图
		imgjbsb 角标图像头
		jbwhite 未知参数1
		jbblack 未知参数2
	【返回文字的笔迹部分】

  注意：这个方法不行，另外一个号的方法：取一个方块，移动方块，确定方块中的样子，如果有横线或者数显就确定为脚标
*/
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

IplImage* Cjbsb(IplImage* img,IplImage* imgjbsb,int jbwhite,int jbblack){
/*定义变量*/
    int i,j,ii,jj,sumjb1,sumjb2,jbi=0,jbj=0;
    int height,width,step,channels;
	uchar *data;
	int brklab=0;
//1、 获取图像信息
  	height    = img->height;  
  	width     = img->width;	
  	step      = img->widthStep;	
  	channels  = img->nChannels;
  	data      = (uchar *)img->imageData;
	//IplImage* imgjbsb = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
	cvCopy(img,imgjbsb,NULL);
	uchar *imgjbsbdata= (uchar *)imgjbsb->imageData;
//----------------------------------------//
//2、找脚标的位置
//----------------------------------------//
	for(i=0;i<height/3;i++){ 
		for(j=0;j<width/5;j++){
			sumjb1=0;
			for(ii=0;ii<=14;ii++)  //计算特征点的下侧14与右侧14的白点数目(是因为脚标就是14的长度吧？)
		           sumjb1=sumjb1+imgjbsbdata[(i+ii)*step+j*channels];//下侧14列的单点的白点数目
			for(jj=0;jj<=14;jj++)
		           sumjb1=sumjb1+imgjbsbdata[i*step+(j+jj)*channels];//右侧14行的单点的白点数目
            if(sumjb1<=255*jbwhite){		//jbwhite为允许角标上白点数，第一次提取                                                 
               sumjb2=0;
               for(ii=i+2;ii<i+12;ii++)            
	               for(jj=j+2;jj<j+12;jj++){
						if(imgjbsbdata[ii*step+jj*channels]>=200)
					       sumjb2=sumjb2+imgjbsbdata[ii*step+jj*channels];
				   }
			   if(sumjb2>=255*(100-jbblack)){                                 //允许角标内黑点数，第二次提取
				   jbi=i;//脚标位置
				   jbj=j;
				for(ii=i-2;ii<i+22;ii=ii+2)                                  //标出位置
	               for(jj=j-2;jj<j+22;jj=jj+2){
					   imgjbsbdata[ii*step+jj*channels]=0;
				   }
				   brklab=1;
				   break;
			   }
			}
		}

		if(1==brklab){
			brklab=0;break;//退出标记
		}
	}
	if(jbi==0 && jbj==0)
	{
	//	jbi=142;
	//	jbj=25;
		
		jbi=0;
		jbj=0;
		printf("\t\t\t甄别图像的角标失败,使用设定值Cjbsb（角标识别）\n");
	}

	cout<<"JB:"<<jbi<<" "<<jbj<<endl;
//----------------------------------------//
//3、以角标为起点进行裁剪与画框
//----------------------------------------//
//    CvSize jbcjsize=cvSize(835,165);           //角标裁剪框的大小，宽为835象素，高为165象素
	CvSize jbcjsize=cvSize(833, 476);
    IplImage* imgjbcj = cvCreateImage(jbcjsize,img->depth,img->nChannels);
    uchar *imgjbcjdata= (uchar *)imgjbcj->imageData;
	int jbcjstep      = imgjbcj->widthStep;	
  	int jbcjchannels  = imgjbcj->nChannels;
	for(i=0;i<476;i++){ 
		for(j=0;j<833;j++){
			imgjbcjdata[i*jbcjstep+j*jbcjchannels]=data[(i+jbi)*step+(j+jbj)*channels];
		}
	}
	//此处是yss进行注释，没发现有什么用处
	for(i=0;i<476;i=i+2){
		imgjbsbdata[(i+jbi)*step+jbj*channels]=0;
        imgjbsbdata[(i+jbi)*step+(jbj+833)*channels]=0;
	}
	for(j=0;j<833;j=j+2){
        imgjbsbdata[jbi*step+(j+jbj)*channels]=0;
		imgjbsbdata[(jbi+476)*step+(j+jbj)*channels]=0;
	}
	
	return imgjbcj;

}