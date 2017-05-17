//图像的二值化
#include <cv.h>
#include <highgui.h>
#include <string>
using namespace std;

int* Binary2(IplImage *g_pGrayImage,int bithro)
{
	IplImage *g_pBinaryImage = NULL;
	// 转为二值图
	cvThreshold(g_pGrayImage, g_pBinaryImage, bithro, 255, CV_THRESH_BINARY);
	cvCopy(g_pGrayImage, g_pBinaryImage,NULL);
	return 0;
}