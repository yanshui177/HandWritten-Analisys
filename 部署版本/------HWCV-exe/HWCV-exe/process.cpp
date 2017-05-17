/*
实现文件：process.cpp 图像处理过程的实现文件
*/
#include "process.h"

/*
功能：读入图像文件，进行二值化

@变量 img iplimage图像文件
@变量 bithro 二值化阈值
@返回值 黑像素的数目（待用）
*/
int*  binary(IplImage*  img, int g_bi_threshold)
{
	int height, width, step, channels;
	uchar *data;
	int i, j;
	static int black[1000];   //C语言不提倡返回一个局部变量的地址以外的功能，所以你必须定义的局部变量，如静态变量。
	/* 获取图像信息*/
	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *)img->imageData;

	/*二值化，并统计黑像素的个数*/
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)//对图像每个点进行二值化,原值为128
			data[i*step + j*channels] = (data[i*step + j*channels]>g_bi_threshold) ? 255 : 0;
	}

	/*计算每一行的黑像素个数*/
	int tempBlackPixel = 0;

	memset(black, 0, 1000);            //##初始化内存，这里用做清零black数组
	for (i = height - 1; i>0; i--)
	{
		for (int j = 0; j<width; j++)
		{
			if (data[i*step + j*channels] == 0)        //计算黑色的像素数
				tempBlackPixel += 1;
		}
		black[height - i] = tempBlackPixel;   //black记录黑色像素数
		tempBlackPixel = 0;
	}
	//二值化，并统计黑像素的个数**********
	return black;
}



/* 	
功能：读入图像文件，对图像进行裁剪

@变量 img iplimage图像文件
@变量 img 裁剪后的iplimage图像文件
@jbwhite
@jbblack
@返回值 返回裁剪后的图像
*/
IplImage* Cjbsb(IplImage* img, IplImage* imgjbsb, int jbwhite, int jbblack)
{
	/*定义变量*/
	int i, j, jbi = 0, jbj = 0;
	int height, width, step, channels;
	uchar *data;
	int brklab = 0;
	/* 获取图像信息*/
	height = img->height;
	width = img->width;
	step = img->widthStep;
	channels = img->nChannels;
	data = (uchar *)img->imageData;

	//    IplImage* imgjbsb = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
	cvCopy(img, imgjbsb, NULL);
	uchar *imgjbsbdata = (uchar *)imgjbsb->imageData;

	//以角标为起点进行裁剪与画框
	CvSize jbcjsize = cvSize(835, 165);           //角标裁剪框的大小，宽为835象素，高为165象素
	IplImage* imgjbcj = cvCreateImage(jbcjsize, img->depth, img->nChannels);
	uchar *imgjbcjdata = (uchar *)imgjbcj->imageData;
	int jbcjstep = imgjbcj->widthStep;
	int jbcjchannels = imgjbcj->nChannels;
	for (i = 0; i<165; i++)
		for (j = 0; j<835; j++)
			imgjbcjdata[i*jbcjstep + j*jbcjchannels] = data[(i + jbi)*step + (j + jbj)*channels];
	for (i = 0; i<165; i = i + 2)
	{
		imgjbsbdata[(i + jbi)*step + jbj*channels] = 0;
		imgjbsbdata[(i + jbi)*step + (jbj + 835)*channels] = 0;
	}
	for (j = 0; j<835; j = j + 2)
	{
		imgjbsbdata[jbi*step + (j + jbj)*channels] = 0;
		imgjbsbdata[(jbi + 165)*step + (j + jbj)*channels] = 0;
	}

	return imgjbcj;
}


/*
功能：计算图像的特征

@变量 imgbj 笔迹部分的图像
@返回值 计算得到的特征图像
*/
IplImage* outline(IplImage* imgbj)
{
	/*定义变量*/
	int i, j;
	int height, width, step, channels;
	uchar *data;

	/*定义新的图像*/
	IplImage* imglk = cvCreateImage(cvGetSize(imgbj), imgbj->depth, imgbj->nChannels);

	/* 获取图像信息*/
	height = imgbj->height;
	width = imgbj->width;
	step = imgbj->widthStep;
	channels = imgbj->nChannels;
	data = (uchar *)imgbj->imageData;

	//	printf("--outline--");
	for (j = 0; j<height; j++){
		for (i = 0; i<width; i++){
			imglk->imageData[j*step + i*channels] = 255;
		}
		for (i = 0; i<width - 1; i++){
			if (data[j*step + (i + 1)*channels] - data[j*step + i*channels] == 255)             //竖线右侧框
				imglk->imageData[j*step + i*channels] = 0;
			else if (data[j*step + i*channels] - data[j*step + (i + 1)*channels] == 255)        //竖线左侧框
				imglk->imageData[j*step + (i + 1)*channels] = 0;
		}
	}

	for (i = 0; i<width; i++){
		for (j = 0; j<height - 1; j++){
			if (data[j*step + i*channels] - data[(j + 1)*step + i*channels] == 255)             //横线下侧框
				imglk->imageData[(j + 1)*step + i*channels] = 0;
			else if (data[(j + 1)*step + i*channels] - data[j*step + i*channels] == 255)        //横线上侧框
				imglk->imageData[j*step + i*channels] = 0;
		}
	}
	return imglk;
}


/*
功能：输入图像的特征轮廓图，返回图像的特征值
@变量 imglk 输入的图像轮廓图
@变量 feature 得到的图像特征
@返回值 成功1失败0
*/
int outlinefeature(IplImage* imglk, int feature[][50])
{
	//定义变量
	int i, j;
	int height, width, step, channels;
	uchar *data;

	int feat[50][50] = { 0 };             //特征值初始化  
	Point featblk[32];                //标记相同H的黑点坐标
	int featk;                        //标记相同H的黑点数目
	int m;                            //for 里面的变量
	//	printf("--outlinefeature--");
	// 获取图像信息
	height = imglk->height;
	width = imglk->width;
	step = imglk->widthStep;
	channels = imglk->nChannels;
	data = (uchar *)imglk->imageData;

	//初始化特征矩阵    最大值为47    ，非空的特征字有1081个
	int outllab[9][9] = { \
	{3, 37, 10, 36, 2, 35, 9, 34, 1}, { 38, 3, 21, 20, 2, 19, 18, 1, 33 }, \
	{11, 22, 3, 10, 2, 9, 1, 17, 8}, { 39, 23, 11, 3, 2, 1, 8, 16, 32 }, \
	{4, 4, 4, 4, 0, 0, 0, 0, 0}, { 40, 24, 12, 5, 6, 7, 15, 31, 47 }, \
	{12, 25, 5, 13, 6, 14, 7, 30, 15}, { 41, 5, 26, 27, 6, 28, 29, 7, 46 }, \
	{5, 42, 13, 43, 6, 44, 14, 45, 7} };


	for (i = 4; i <= width - 5; i++){
		for (j = 4; j <= height - 5; j++){
			if (data[j*step + i*channels] == 0){
				//**************H=1

				memset(featblk, 0, sizeof(Point) * 32);              //归零                
				featk = 0;
				if (data[j*step + (i + 1)*channels] == 0){                 //右侧点
					featblk[featk].x = i + 1;
					featblk[featk].y = j;
					featk++;
				}
				for (m = i + 1; m >= i - 1; m--){                              //上排点
					if (data[(j - 1)*step + m*channels] == 0) {
						featblk[featk].x = m;
						featblk[featk].y = j - 1;
						featk++;
					}
				}
				if (data[j*step + (i - 1)*channels] == 0){                 //左侧点
					featblk[featk].x = i - 1;
					featblk[featk].y = j;
					featk++;
				}
				for (m = i - 1; m <= i + 1; m++) {                             //下排点
					if (data[(j + 1)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j + 1;
						featk++;
					}
				}
				//统计特征点
				if (featk >= 2){
					for (m = 1; m <= featk - 1; m++){
						feat[outllab[featblk[m - 1].x - i + 4][featblk[m - 1].y - j + 4]][outllab[featblk[m].x - i + 4][featblk[m].y - j + 4]]++;
					}
				}
				//H=1*******************


				//*********************H=2
				memset(featblk, 0, sizeof(Point) * 32);                 //归零                
				featk = 0;

				for (m = j + 1; m >= j - 2; m--){
					if (data[m*step + (i + 2)*channels] == 0){                //右排点
						featblk[featk].x = i + 2;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i + 1; m >= i - 2; m--){                                  //上排点
					if (data[(j - 2)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j - 2;
						featk++;
					}
				}
				for (m = j - 1; m <= j + 2; m++){                                  //左侧点
					if (data[m*step + (i - 2)*channels] == 0){
						featblk[featk].x = i - 2;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i - 1; m <= i + 2; m++){                                 //下排点
					if (data[(j + 2)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j + 2;
						featk++;
					}
				}
				//统计特征点
				if (featk >= 2){
					for (m = 1; m <= featk - 1; m++){
						feat[outllab[featblk[m - 1].x - i + 4][featblk[m - 1].y - j + 4]][outllab[featblk[m].x - i + 4][featblk[m].y - j + 4]]++;
					}
				}
				//H=2********************

				//*********************H=3
				memset(featblk, 0, sizeof(Point) * 32);                 //归零                
				featk = 0;

				for (m = j + 2; m >= j - 3; m--){
					if (data[m*step + (i + 3)*channels] == 0){                //右排点
						featblk[featk].x = i + 3;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i + 2; m >= i - 3; m--){                                  //上排点
					if (data[(j - 3)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j - 3;
						featk++;
					}
				}
				for (m = j - 2; m <= j + 3; m++){                                  //左侧点
					if (data[m*step + (i - 3)*channels] == 0){
						featblk[featk].x = i - 3;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i - 2; m <= i + 3; m++){                                  //下排点
					if (data[(j + 3)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j + 3;
						featk++;
					}
				}
				//统计特征点
				if (featk >= 2){
					for (m = 1; m <= featk - 1; m++){
						feat[outllab[featblk[m - 1].x - i + 4][featblk[m - 1].y - j + 4]][outllab[featblk[m].x - i + 4][featblk[m].y - j + 4]]++;
					}
				}
				//H=3********************

				//*********************H=4  
				memset(featblk, 0, sizeof(Point) * 32);                 //归零                
				featk = 0;

				for (m = j + 3; m >= j - 4; m--){
					if (data[m*step + (i + 4)*channels] == 0){                 //右排点
						featblk[featk].x = i + 4;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i + 3; m >= i - 4; m--) {                                 //上排点
					if (data[(j - 4)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j - 4;
						featk++;
					}
				}
				for (m = j - 3; m <= j + 4; m++){                                  //左侧点
					if (data[m*step + (i - 4)*channels] == 0){
						featblk[featk].x = i - 4;
						featblk[featk].y = m;
						featk++;
					}
				}
				for (m = i - 3; m <= i + 4; m++){                                 //下排点
					if (data[(j + 4)*step + m*channels] == 0){
						featblk[featk].x = m;
						featblk[featk].y = j + 4;
						featk++;
					}
				}
				//统计特征点
				if (featk >= 2){
					for (m = 1; m <= featk - 1; m++){
						feat[outllab[featblk[m - 1].x - i + 4][featblk[m - 1].y - j + 4]][outllab[featblk[m].x - i + 4][featblk[m].y - j + 4]]++;
					}
				}
				//H=4***********************
			}// if    		
		}  //for j
	}  //for i

	//****注：最终特征值为feat(x,y)+feat(y,x)，放入feat(x,y)中，x<y
	for (i = 1; i<50; i++)
		for (j = 0; j<i; j++){
		feat[j][i] = feat[i][j] + feat[j][i];
		feat[i][j] = 0;
		}
	memcpy(feature, feat, 2500 * 4);        //int有四个字节
	//	printf("轮廓特征值计算完成\n");
	return 0;
}


/*
功能：对单张图像的处理，最终得到一个特征值，用来计算各个图像之间的卡方距离

@变量 path 图像的物理地址
@变量 feature 图像的特征值
@返回值 处理后的图像
*/
IplImage* singlefeature(char* path, int feature[][50])
{
	//定义变量
	        //原图
	IplImage* imglk = 0;        //轮廓图
	IplImage* imggj = 0;        //骨架图
	IplImage* imgjbsb = 0;      //角标识别图
	IplImage* imgbj = 0;        //只提取笔记部分的图像
	IplImage* imgbjhf = 0;      //为文字区域画上方格
	IplImage* imgwzbj = 0;      //为文字区域标出是否为文字（文字标记）

	int height, width, step, channels;
	uchar *data;

	int i, j;                //用于返回图像每行黑像素的个数
	//int feature[50][50]={0};    //特征值初始化

	IplImage* img  = cvLoadImage(path, 0);

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
	binary(imgbig, g_bi_threshold);
	//SaveLog("singlefeature_binary\n", "D:\\HWCV\\numtxt.txt", "a");



	/*裁剪识别*/
	int jbwhite = 5, jbblack = 4;
	imgjbsb = cvCreateImage(cvGetSize(imgbig), imgbig->depth, imgbig->nChannels);
	imgbj = Cjbsb(imgbig, imgjbsb, jbwhite, jbblack);                              //返回文字的笔迹部分


	/*计算骨架图*/
	imggj = cvCreateImage(cvGetSize(imgbj), imgbj->depth, imgbj->nChannels);   //复制
	cvCopy(imgbj, imggj, NULL);
	uchar *gjdata = (uchar *)imggj->imageData;

	beforethin(gjdata, gjdata, imggj->width, imggj->height);

	/*笔迹图像颜色范围转换，以进行细化*/
	for (j = 0; j<imggj->height; j++)//取值范围转到0--1  
	{ 
		for (i = 0; i<imggj->width; i++)
		{
			if (gjdata[j*imggj->widthStep + i] == 255)
				gjdata[j*imggj->widthStep + i] = 1;
		}
	}

	/*细化*/
	ThinnerRosenfeld(imggj->imageData, imggj->height, imggj->width);

	/*笔记图像颜色范围转化回正常水平*/
	for (j = 0; j<imggj->height; j++)//取值范围转到0--255,反转过来
	{
		for (i = 0; i<imggj->width; i++)
		{
			if (gjdata[j*imggj->widthStep + i] == 1)
				gjdata[j*imggj->widthStep + i] = 0;
			else
				gjdata[j*imggj->widthStep + i] = 255;
		}
	}

	/*计算骨架特征徝*/
	outlinefeature(imggj, feature);   //特征值占48*48的右上三角形，feature调用返回

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



/*
功能：细化之前的图像颜色处理，将颜色范围转换到0-1

@变量 ip 图像的句柄
@变量 jp
@变量 lx 图象宽度
@变量 ly 图象高度
@返回值 空
*/
void beforethin(unsigned char *ip, unsigned char *jp, unsigned long lx, unsigned long ly)
{
	unsigned long i, j;

	for (i = 0; i<ly; i++){
		for (j = 0; j<lx; j++){
			//这里要视前景是白点还是黑点而定，可以改动
			//如果前景是白点，就是这样；反之反过来
			//jp[i*lx+j]=ip[i*lx+j];
			/*  jp[i*lx+j]=255;*/
			if (ip[i*lx + j]>0)
				jp[i*lx + j] = 0;
			else
				jp[i*lx + j] = 255;
		}
	}
}


/*功能：细化算法 ，Rosenfeld细化算法，用于完成对笔迹图像的股价提取

@变量 image 代表图象的一维数组
@变量 lx 图象宽度
@变量 ly 图象高度
@返回值 无返回值
*/
void ThinnerRosenfeld(void *image, unsigned long lx, unsigned long ly)
{
	char *f, *g;
	char n[10];
	char a[5] = { 0, -1, 1, 0, 0 };
	char b[5] = { 0, 0, 0, 1, -1 };
	char nrnd, cond, n48, n26, n24, n46, n68, n82, n123, n345, n567, n781;
	short k, shori;
	unsigned long i, j;
	long ii, jj, kk, kk1, kk2, kk3, size;

	//	printf("--Thinner_Rosenfeld--");
	size = (long)lx * (long)ly;

	g = (char *)malloc(size);
	if (g == NULL){
		printf("error in alocating mmeory!\n");
		return;
	}

	f = (char *)image;
	for (kk = 0l; kk<size; kk++){
		g[kk] = f[kk];
	}

	do{
		shori = 0;
		for (k = 1; k <= 4; k++){
			for (i = 1; i<lx - 1; i++){
				ii = i + a[k];

				for (j = 1; j<ly - 1; j++){
					kk = i*ly + j;

					if (!f[kk])
						continue;

					jj = j + b[k];
					kk1 = ii*ly + jj;

					if (f[kk1])
						continue;

					kk1 = kk - ly - 1;
					kk2 = kk1 + 1;
					kk3 = kk2 + 1;
					n[3] = f[kk1];
					n[2] = f[kk2];
					n[1] = f[kk3];
					kk1 = kk - 1;
					kk3 = kk + 1;
					n[4] = f[kk1];
					n[8] = f[kk3];
					kk1 = kk + ly - 1;
					kk2 = kk1 + 1;
					kk3 = kk2 + 1;
					n[5] = f[kk1];
					n[6] = f[kk2];
					n[7] = f[kk3];

					nrnd = n[1] + n[2] + n[3] + n[4]
						+ n[5] + n[6] + n[7] + n[8];
					if (nrnd <= 1)
						continue;

					cond = 0;
					n48 = n[4] + n[8];
					n26 = n[2] + n[6];
					n24 = n[2] + n[4];
					n46 = n[4] + n[6];
					n68 = n[6] + n[8];
					n82 = n[8] + n[2];
					n123 = n[1] + n[2] + n[3];
					n345 = n[3] + n[4] + n[5];
					n567 = n[5] + n[6] + n[7];
					n781 = n[7] + n[8] + n[1];

					if (n[2] == 1 && n48 == 0 && n567>0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[6] == 1 && n48 == 0 && n123>0)	{
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[8] == 1 && n26 == 0 && n345>0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[4] == 1 && n26 == 0 && n781>0)	{
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[5] == 1 && n46 == 0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[7] == 1 && n68 == 0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[1] == 1 && n82 == 0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					if (n[3] == 1 && n24 == 0){
						if (!cond)
							continue;
						g[kk] = 0;
						shori = 1;
						continue;
					}
					cond = 1;
					if (!cond)
						continue;
					g[kk] = 0;
					shori = 1;
				}
			}

			for (i = 0; i<lx; i++){
				for (j = 0; j<ly; j++){
					kk = i*ly + j;
					f[kk] = g[kk];
				}
			}
		}
	} while (shori);
	free(g);
}
