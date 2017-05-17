/* 	程序名：outline.c
功能：输入文字另外由于轮廓图像。返回相应的轮廓特征值
*/
#pragma once
#include <cv.h>  
#include <highgui.h> 
#include <stdlib.h>
#include <stdio.h>
#include "Point.h"

int outlinefeature(IplImage* imglk,int feature[ ][50]){
/*定义变量*/
    int i,j;
	int height,width,step,channels;
  	uchar *data;

    int feat[50][50]={0};             //特征值初始化  
    Point featblk[32];                //标记相同H的黑点坐标
    int featk;                        //标记相同H的黑点数目
    int m;                            //for 里面的变量

/* 获取图像信息*/
  	height    = imglk->height;  
  	width     = imglk->width;	
  	step      = imglk->widthStep;	
  	channels  = imglk->nChannels;
  	data      = (uchar *)imglk->imageData;

//初始化特征矩阵    最大值为47    ，非空的特征字有1081个
	int outllab[9][9]={\
	{3,37,10,36,2,35,9,34,1},{38,3,21,20,2,19,18,1,33},\
	{11,22,3,10,2,9,1,17,8},{39,23,11,3,2,1,8,16,32},\
	{4,4,4,4,0,0,0,0,0},{40,24,12,5,6,7,15,31,47},\
	{12,25,5,13,6,14,7,30,15},{41,5,26,27,6,28,29,7,46},\
	{5,42,13,43,6,44,14,45,7}};
//    for(i=0;i<9;i++)      //输出测试
//    {
//      	for(j=0;j<9;j++)
//	        	printf("%d*",outllab[i][j]);
//      	printf("\n");
//    }
for(i=4;i<=width-5;i++)
{                
	for(j=4;j<=height-5;j++)
	{
		if(data[j*step+i*channels]==0)
		{
			//**************H=1

			memset(featblk, 0, sizeof(Point)*32);              //归零                
			featk=0;    
			if(data[j*step+(i+1)*channels]==0)                 //右侧点
			{
				featblk[featk].x=i+1;
				featblk[featk].y=j;
                featk++;
			}
			for(m=i+1;m>=i-1;m--)                              //上排点
			{
				if(data[(j-1)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j-1;
                    featk++;
				}
			}
			if(data[j*step+(i-1)*channels]==0)                 //左侧点
			{
				featblk[featk].x=i-1;
				featblk[featk].y=j;
                featk++;
			}
			for(m=i-1;m<=i+1;m++)                              //下排点
			{
				if(data[(j+1)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j+1;
                    featk++;
				}
			}
            //统计特征点
			//****************************************************
            if(featk>=2)
			{
				for(m=1;m<=featk-1;m++)
				{
					feat[outllab[featblk[m-1].x-i+4][featblk[m-1].y-j+4]][outllab[featblk[m].x-i+4][featblk[m].y-j+4]]++;
				}
			}
            //H=1


			//H=2
	        memset(featblk, 0, sizeof(Point)*32);                 //归零                
			featk=0;  
			
			for(m=j+1;m>=j-2;m--)
			{
			    if(data[m*step+(i+2)*channels]==0)                //右排点
				{
		    		featblk[featk].x=i+2;
		      		featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i+1;m>=i-2;m--)                                  //上排点
			{
				if(data[(j-2)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j-2;
                    featk++;
				}
			}
			for(m=j-1;m<=j+2;m++)                                  //左侧点
			{
			    if(data[m*step+(i-2)*channels]==0)    
				{
	    			featblk[featk].x=i-2;
    				featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i-1;m<=i+2;m++)                                 //下排点
			{
				if(data[(j+2)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j+2;
                    featk++;
				}
			}
            //统计特征点
			//****************************************************
            if(featk>=2)
			{
				for(m=1;m<=featk-1;m++)
				{
					feat[outllab[featblk[m-1].x-i+4][featblk[m-1].y-j+4]][outllab[featblk[m].x-i+4][featblk[m].y-j+4]]++;
				}
			}
			//H=2

        	//H=3
	        memset(featblk, 0, sizeof(Point)*32);                 //归零                
			featk=0;  
			
			for(m=j+2;m>=j-3;m--)
			{
			    if(data[m*step+(i+3)*channels]==0)                //右排点
				{
		    		featblk[featk].x=i+3;
		      		featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i+2;m>=i-3;m--)                                  //上排点
			{
				if(data[(j-3)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j-3;
                    featk++;
				}
			}
			for(m=j-2;m<=j+3;m++)                                  //左侧点
			{
			    if(data[m*step+(i-3)*channels]==0)    
				{
	    			featblk[featk].x=i-3;
    				featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i-2;m<=i+3;m++)                                  //下排点
			{
				if(data[(j+3)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j+3;
                    featk++;
				}
			}
            //统计特征点
			//******************************************
            if(featk>=2)
			{
				for(m=1;m<=featk-1;m++)
				{
					feat[outllab[featblk[m-1].x-i+4][featblk[m-1].y-j+4]][outllab[featblk[m].x-i+4][featblk[m].y-j+4]]++;
				}
			}
			//H=3

        	//H=4  
	        memset(featblk, 0, sizeof(Point)*32);                 //归零                
			featk=0;  
			
			for(m=j+3;m>=j-4;m--)
			{
			    if(data[m*step+(i+4)*channels]==0)                 //右排点
				{
		    		featblk[featk].x=i+4;
		      		featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i+3;m>=i-4;m--)                                  //上排点
			{
				if(data[(j-4)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j-4;
                    featk++;
				}
			}
			for(m=j-3;m<=j+4;m++)                                  //左侧点
			{
			    if(data[m*step+(i-4)*channels]==0)    
				{
	    			featblk[featk].x=i-4;
    				featblk[featk].y=m;
                    featk++;
				}
			}
			for(m=i-3;m<=i+4;m++)                                 //下排点
			{
				if(data[(j+4)*step+m*channels]==0)     
				{
			    	featblk[featk].x=m;
			    	featblk[featk].y=j+4;
                    featk++;
				}
			}
            //统计特征点
            if(featk>=2)
			{
				for(m=1;m<=featk-1;m++)
				{
					feat[ outllab[featblk[m-1].x-i+4][featblk[m-1].y-j+4]] [outllab[featblk[m].x-i+4][featblk[m].y-j+4] ]++;
				}
			}
			//H=4***********************

		}
           		
	}
}

	//****注：最终特征值为feat(x,y)+feat(y,x)，放入feat(x,y)中，x<y
	for(i=1;i<50;i++)
		for(j=0;j<i;j++)
		{
			feat[j][i]=feat[i][j]+feat[j][i];
            feat[i][j]=0;
		}

	memcpy(feature,feat,2500*4);        //int有四个字节

	return 0;


}