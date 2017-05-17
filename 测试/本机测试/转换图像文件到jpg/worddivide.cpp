/* 	程序名：Cjbsb.c
功能：读入只有文字区域的图像文件，将文字划分开来
输入参数：只有文字区域的图像文件，行阈值，列阈值，划格后的行标与列标
默认：hthro=10，wthro=6
*/
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>

IplImage* worddivide(IplImage* imgbj,int hthro,int wthro,int *gridx,int *gridy,int *gxx,int *gyy){
	/*定义变量*/
    int height,width,step,channels;
  	uchar *data;

	int i,j,black[1000];
	int blackend=0;                      //标记分割线结束 
    int mi=0,mx=500;                     //标记分割线内含黑色最少的线号与值
	int gx=0,gy=0;                       //记录该画线的网线的行号与列号    gridx[10],gridy[30],
    memset(gridx,0,10);                  //初始化内存，这里用做清零
	memset(gridy,0,30);                  //初始化内存，这里用做清零

	/*定义新的图像*/
	IplImage* imgbjhf = cvCreateImage(cvGetSize(imgbj),imgbj->depth,imgbj->nChannels);   //笔迹划分图
	cvCopy(imgbj,imgbjhf,NULL);

    /* 获取图像信息*/
  	height    = imgbjhf->height;  
  	width     = imgbjhf->width;	
  	step      = imgbjhf->widthStep;	
  	channels  = imgbjhf->nChannels;
  	data      = (uchar *)imgbjhf->imageData;
	

	/*横向的表格*/
	/*计算每一行的黑色像素点数（此参数不能使用二值化得到的）*/
	int tempBlackPixelx=0;          //循环记录每一行的黑色像素点数
	
	memset(black,0,1000);            //初始化内存，这里用做清零
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
		   	if(data[j*step+i*channels]==0)        //计算黑色的像素数
		   		tempBlackPixelx+=1;		
		}
		black[j]=tempBlackPixelx;                 //black记录黑色像素数
		tempBlackPixelx=0;
		//printf("The %dth black num is %d \n",j,black[j]); 
	}

    /*计算横线位置*/
 	for(i=0;i<height;i++){
		if(black[i]<=hthro && blackend==0){
            blackend=1;             
            if(black[i]<=mx){                     //更新黑色最少的的线标
				mx=black[i];
				mi=i;
			}
		}
		else if((blackend==1 && black[i]>hthro) || i==height-1){
			blackend=0;

			gridx[gx]=mi;
			//printf("<行标：%d>",gridx[gx]);
			gx++;             
			mx=500;
			mi=i;			
		}
	}

	 /*纵向的表格*/

    //计算每一列的黑像素个数
	int tempBlackPixely=0;	
	memset(black,0,1000);                         //初始化内存，这里用做清零
	for(i=0;i<width;i++) {
		for(j=0;j<height;j++){
		   	if(data[j*step+i*channels]==0)        //计算黑色的像素数
		   		tempBlackPixely+=1;
		}
		black[i]=tempBlackPixely;                 //black记录黑色像素数
		tempBlackPixely=0;
	}

    /*计算纵线位置*/
	for(i=0;i<width;i++){
		if(black[i]<=wthro){
			if(blackend==0){
				blackend=1;
			}
            if(black[i]<=mx){        //更新黑色最少的的线标
				mx=black[i];
				mi=i;
			}
		}
		else if((blackend==1 && black[i]>wthro)){
			blackend=0;

			if(gy==0){
                gridy[gy]=mi;                         //记下黑色最少的的线位置
			    gy++;
			}
			else if(mi-gridy[gy-1]<=25){               //考虑方格太小的情况，将其分入上一个方格中
				gridy[gy-1]=mi;                        //
			}
			else{
				gridy[gy]=mi;                         //记下黑色最少的的线位置
				//printf("<列标：%d>",gridy[gy]);
			    gy++;
			}			
			mx=500; 
			mi=i;
		}
	}

	gridy[gy]=mi;                         //对最后一列进行处理
	gy++;
	//for(j=0;j<gy;j++)
    //    printf("The %dth row is %d \n",j,gridy[j]); 
	//for(i=0;i<gx;i++)
    //    printf("The %dth line is %d \n",i,gridx[i]); 
 
	/*笔迹划分图上画上方格*/
    for(i=0;i<height;i++)
		for(j=0;j<gy;j++)
			 data[i*step+gridy[j]*channels]=0;

	for(i=0;i<width;i++)
		for(j=0;j<gx;j++)
			data[gridx[j]*step+i*channels]=0;

	*gxx=gx;
	*gyy=gy;
	//printf("分割完成\n");

	return imgbjhf;
}