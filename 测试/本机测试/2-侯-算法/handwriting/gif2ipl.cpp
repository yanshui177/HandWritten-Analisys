/* 	程序名：gif2ipl.c
功能：输入gif图像。得到相应的rgb图像
*/
#include <cv.h>  
#include <highgui.h>  
#include "FreeImage.h"  
#include <stdio.h>
IplImage*  gif2ipl(const char* filename)
{  
    FreeImage_Initialise();         //load the FreeImage function lib  
    FREE_IMAGE_FORMAT fif = FIF_GIF;  
    FIBITMAP* fiBmp = FreeImage_Load(fif,filename,GIF_DEFAULT);  
    FIMULTIBITMAP * pGIF=FreeImage_OpenMultiBitmap(fif,filename,0,1,0,GIF_PLAYBACK); 
    //  FIBITMAPINFO fiBmpInfo = getfiBmpInfo(fiBmp);  
    int gifImgCnt=FreeImage_GetPageCount(pGIF); 
    FIBITMAP * pFrame; 
    int width,height; 
    width=FreeImage_GetWidth(fiBmp); 
    height=FreeImage_GetHeight(fiBmp); 
    IplImage * iplImg = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,3);  
        iplImg->origin = 1;//should set to 1-top-left structure(Windows bitmap style)  
    RGBQUAD* ptrPalette =new RGBQUAD; // = FreeImage_GetPalette(fiBmp);  
    BYTE intens;  
    BYTE* pIntensity = &intens;  
    //cvNamedWindow("gif",0); 
    //printf("gif包含图片的数目：%d \n",gifImgCnt); 
    for (int curFrame=0;curFrame<gifImgCnt;curFrame++)
	{ 
        pFrame= FreeImage_LockPage(pGIF,curFrame); 
        //ptrPalette = FreeImage_GetPalette(pFrame);  
        char * ptrImgDataPerLine; 
        for (int i=0;i<height;i++)
		{  
            ptrImgDataPerLine = iplImg->imageData + i*iplImg->widthStep;  
            for(int j=0;j<width;j++)
			{  
                //get the pixel index   
                //FreeImage_GetPixelIndex(pFrame,j,i,pIntensity);    
                FreeImage_GetPixelColor(pFrame,j,i,ptrPalette); 
                ptrImgDataPerLine[3*j] = ptrPalette->rgbBlue;  
                ptrImgDataPerLine[3*j+1] = ptrPalette->rgbGreen;  
                ptrImgDataPerLine[3*j+2] = ptrPalette->rgbRed;  
                //ptrImgDataPerLine[3*j] = ptrPalette[intens].rgbBlue;  
                //ptrImgDataPerLine[3*j+1] = ptrPalette[intens].rgbGreen;  
                //ptrImgDataPerLine[3*j+2] = ptrPalette[intens].rgbRed;  
            }  
        } 
         
        //printf("转换结束的图片序号： %d \n",curFrame); 
    //    cvShowImage("gif",iplImg); 
    //    cvWaitKey(30); 
    //    FreeImage_UnlockPage(pGIF,pFrame,1); 
    } 
    FreeImage_Unload(fiBmp);  
    FreeImage_DeInitialise();  
	
    return iplImg; 
}  