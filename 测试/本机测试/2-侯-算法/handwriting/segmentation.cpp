/* 	程序名：segmentation.c
功能：总程序：读入图像文件，分析特征，输出效果
*/
//#include "stdafx.h"
#pragma once
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include "Point.h"
#include "Cword.h"
//#include "FreeImage.h"     //用于读gif的图像,（将gif图像转换为png）
#include<io.h>             //下面的5个用于读取文件夹下的所有文件名
#include<vector>
#include<iostream>
#include <string.h>
#include<windows.h>        //用于弹出提示框,,,切记！当调用<windows.h>时，不要调用MFC！（Afx.h)
#include<string.h>
using namespace std;
#ifdef WIN32                            //屏蔽VC6对STL的一些不完全支持造成
#pragma warning (disable: 4514 4786)
#endif

void		getFiles(string	path, vector<string>& files );//9、读取文件名下所有文件名  
void		on_mouse( int event, int x, int y, int flags, void* ustc);            
char*		getType(char fileName[], char type[]);  //2、获取图像类型  
int*		binary(IplImage* img,int bithro); //3、二值化图像 
int			getFolders(string path, vector<string>& files );//11、读取文件名下所有文件夹的名称          
int			read_scanf(const string &filename,const int &cols,vector<double *> &_vector);//12、读取已经存好的特征值
int			outlinefeature(IplImage* imglk,int feature[ ][50]);    //7、计算图像的轮廓特征值
int			searchDir(char* path, vector<string> &dir);//获取目录下一层的所有文件夹
IplImage*	Cjbsb(IplImage*	img,IplImage* imgjbsb,int jbwhite,int jbblack);//4、图像角标识别        
IplImage*	worddivide(IplImage* imgbj,int hthro,int wthro,int *gridx,int *gridy,int *gxx,int *gyy); //5、为文字区域画上方格
IplImage*	outline(IplImage* imgbj); //6、计算图像对应的轮廓图                  
IplImage*	gif2ipl(const char* filename);  //1、读取gif的外部函数
IplImage*	wordrecognize(IplImage* imgbj,int *gridx,int *gridy,Cword *wordbox,int gx,int gy);//8、判断方格中的是否为文字       
IplImage*	singlefeature(char* path,int feature[ ][50]);//10、得出单个文件的特征值  

int pos_x=0,pos_y=0;
bool pos_flag=false;
IplImage* src;
int picAll = 0, picSus = 0;
int stuAll = 0, stuSus = 0;

int ComputeImage(vector<string> files, double bzckesa[50][50], double *wcd, int conti)
{	int i,ii,jj,k,size;
	double	bzcu[50][50]={0};			//标准差中的u
	double	featurep[50][50][30]={0};	//所有图像的轮廓方向特征初始化//干什么	//30
	int		feature[50][50][30]={0};	//所有图像的特征值初始化	//所有图像指的什么意思	//30找出30的位置或者50的位置限制。。。。带入num_dir==49的情况进行类比
	int		featx[50][50]={0};			//循环赋值的feature
	int		featureall;					//图像特征值和				//做什么用
	IplImage* imglk[30];				//轮廓图变量				//30

	size=files.size();
	for (i = 0;i < size;i++)
	{  
		memset(featx,0,sizeof(featx));
//		strcpy(str,files[i].c_str());
		imglk[i]=singlefeature((char*)files[i].c_str(),featx);				//featx[][50]
		featureall=0;                                    //图像特征值和的初始化
		for(ii=0;ii<48;ii++)                             //将featx存起来,回头看能不能用函数换掉
			for(jj=ii+1;jj<47;jj++)
			{
				feature[ii][jj][i]=featx[ii][jj];
				featureall=featureall+featx[ii][jj];
			}
		//求轮廓方向特征featurep，式(5)  与标准差中的u的和
		for(ii=0;ii<48;ii++)                               
			for(jj=ii+1;jj<47;jj++)
			{
				featurep[ii][jj][i]=(double)featx[ii][jj]/featureall;
				bzcu[ii][jj]+=(double)featx[ii][jj]/featureall*1000;     //标准差的值过小,进行放大（1）
			}
	}
	//处理完一个人的每一张图片后
	for(ii=0;ii<48;ii++)//求标准差中的u
		for(jj=ii+1;jj<47;jj++)
			bzcu[ii][jj]=bzcu[ii][jj]/size;
	   //求相似性就是带权卡方wcd
	for (i = 0;i < size;i++)
		for(ii=0;ii<48;ii++)
			for(jj=ii+1;jj<47;jj++)	
				if(featurep[ii][jj][i]*featurep[ii][jj][conti]!=0 && bzckesa[ii][jj]!=-1)
					wcd[i]+=pow((featurep[ii][jj][i]-featurep[ii][jj][conti]),2)/((featurep[ii][jj][i]+featurep[ii][jj][conti])*bzckesa[ii][jj]);
	memset(imglk,0,sizeof(imglk));
	memset(feature,0,sizeof(feature));
	memset(featurep,0,sizeof(featurep));

	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	// 定义变量    
	vector<string> dir;				//存储目录
	int conti=1;     //对比图像的标号
	int size_dir,num_dir;
	char	record[2400]={0};

	// 准备结果文件
	char*	fpname= "C:/Users/闫帅帅/Desktop/result2.txt"; 
	FILE*	fpzz=NULL;//需要注意
	//fpzz=fopen(fpname,"w+");  //创建文件 //a		
	//if(NULL==fpzz) return -1;//要返回错误代码
	//fprintf(fpzz,record); //从控制台中读入并在文本输出
	//fclose(fpzz);
	//fpzz=NULL;//需要指向空，否则会指向原打开文件地址  
	
	// 获取待检测文件夹到size
	char path[100] =  "E:/xiangmu/Img/imgjiaobiao/";//D:/xiangmu/Img/imgjiaobiao/
	searchDir(path, dir);//获取filePath下的所有一级目录并存储到dir中
	
//	dir.push_back("E:/xiangmu/Img/imgjiaobiao/010211100518"); //存储目录
	size_dir=dir.size(); //dir的大小就是学生的数量
	stuAll = size_dir;
	cout << "学生总数为" << stuAll << endl;
	
	// 开始检测每个文件夹下的
	for(num_dir=0;num_dir<size_dir;num_dir++)//对每一个学生目录进行循环
	{
		int		size,i,ii,jj;				//通用变量
		double	bzckesa[50][50]={0};		//标准差				
		double	wcd[30]={0};				//记录卡方距离				//30应该指的就是每个人的图片数目
		int		featdif[30]={0};			//每幅图的特征值与总特征平均值的差	//30
		int		maxi;float maxx=0;			//最大特征值的标号与值
		int		xyimgnum=0;					//嫌疑图片的数目

		vector<string> suspict;		//记录嫌疑图片地址
		vector<float> suspict_wcd;
		vector<string> files;		//存储文件路径
		
		getFiles(dir[num_dir].c_str(), files );	//遍历当前文件夹下的所有文件
		//输出
		printf("正在进行第%d，目录为：%s",num_dir,dir[num_dir].c_str());

		size = files.size();	//图像的数目
		//输出
		printf("文件个数为：%d\t",size);

		//将标准差中的kesa加载进来
		string bzcfile="D:/Xiangmu/Img/bzc/bzc.txt";
		//txt文件中有47列
		int bzccolumns=47;
		vector<double *> output_bzc;
		if(!read_scanf(bzcfile,bzccolumns,output_bzc)) return 0;
		//output_vector可视为二维数组;输出数组元素：
		//int rows=output_bzc.size();
		for(ii=0;ii<48;ii++)
			for(jj=ii+1;jj<47;jj++)
				bzckesa[ii][jj]=output_bzc[ii][jj];

		//开始对每一张图片进行处理
		for(int r=0;r<size;r++)
		{
			memset(wcd, 0, sizeof(wcd));
			ComputeImage(files, bzckesa, wcd, r);
			xyimgnum=0;
			//求卡方距离的最大值 
			for (i = 0;i < size;i++)
			{
//				cout << files[i].c_str()<< "  " << wcd[i] << endl;
//				if(maxx<wcd[i]){ maxx=wcd[i]; maxi=i;}
				if(wcd[i]>0.12)
				{ 
					xyimgnum++; 
					suspict.push_back(files[i].c_str());
					suspict_wcd.push_back(wcd[i]);
				}
			}
			if (xyimgnum<3) break;
		}

		//将结果存入txt	
		//------------------------------------------------------//
		char record[8000];
		memset(record, 0, sizeof(record));
		char pic_num[20];
		memset(pic_num, 0, sizeof(pic_num));
		_itoa(size, pic_num, 10);
		strcat(record, dir[num_dir].substr(27, 22).c_str()); //学号
		strcat(record, "\t");
		strcat(record,pic_num);
		if(xyimgnum>0)
		{
			stuSus++;
			char b[20];
			sprintf(b, "\t%d", xyimgnum);
			strcat(record, b);
			strcat(record, "\n");
//			cout << xyimgnum << endl;;
			for(int t=0;t<xyimgnum;t++)
			{
				strcat(record,"\t\t\t");
				strcat(record,suspict[t].c_str());
				strcat(record,"\t");
				char a[80];
				memset(a,0, sizeof(a));
				//cout << "  " << suspict_wcd[t]<<endl;
				//cout<< "adwada"<<endl;
				sprintf(a, "%f", suspict_wcd[t]);
				strcat(record,a);
				strcat(record,"\n");
			}
		}
		else
		{
			strcat(record, "\t0\n");
		}

		fpzz=fopen(fpname,"a");  //创建文件 //a
		if(NULL==fpzz) return -1;//要返回错误代码
		fprintf(fpzz,record); //从控制台中读入并在文本输出
		fclose(fpzz);
		fpzz=NULL;//需要指向空，否则会指向原打开文件地址  

		suspict.clear();
		suspict_wcd.clear();
		output_bzc.clear();

		memset(record,0,2400);
		memset(bzckesa,0,sizeof(bzckesa));
		memset(wcd,0,sizeof(wcd));
		memset(featdif,0,sizeof(featdif));

		printf("嫌疑数量：%d\t",xyimgnum);
		
		picAll += size;
		picSus += xyimgnum;
		printf("全部:%d嫌疑：%d比例为：%g\n",picAll, picSus,((float)picSus)/((float)picAll));
		xyimgnum=0;

	}

	dir.clear();

	cout << "学生总数:" << stuAll << " 作弊人数：" << stuSus << endl;
	printf("已经打印到txt中！");
	system("start C:/Users/闫帅帅/Desktop/result2.txt");
	system("pause");

  	return 0; //(1-wcd[maxi])*100

}
