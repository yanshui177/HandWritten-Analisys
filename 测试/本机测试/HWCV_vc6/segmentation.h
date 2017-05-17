/*
头文件：segmentation.h 主函数头文件
*/
#pragma once
#ifdef WIN32                            //屏蔽VC6对STL的一些不完全支持造成
#pragma warning (disable: 4514 4786)
#endif
#include "StdAfx.h"
#include "path.h"
#include "Point.h"
#include "process.h"

using namespace std;

/*定义全局变量*/


int		g_bi_threshold = 230;				/* 全局变量 二值化阈值*/
double  g_std_kesa[50][50];			/* 全局变量 标准差数组*/
float   g_doubt_threshold = 0.12;	/* 全局变量 作弊嫌疑阈值*/
string  g_dir = "Y:/";						/* 全局变量 总路径的目录*/
int		g_cheat_num_threshold = 0;	/* 全局变量 默认作弊阈值*/
int		g_conti = 1;					/* 全局变量 默认作弊比较的图片*/

int g_all_img_num = 0;				/* 全局变量 已鉴定的全部图片数量*/
int g_doubt_img_num = 0;			/* 全局变量 已鉴定怀疑的图片数量*/
int g_all_stu_num = 0;				/* 全局变量 已鉴定的全部学生数量*/
int g_doubt_stu_num = 0;			/* 全局变量 已鉴定怀疑的学生数量*/

bool g_output_cmd_config = false;	/*全局变量 输出参数控制*/
bool g_output_txt_config = false;	/*全局变量 输出中间文件选项*/
char g_log_adr[50] = "D:/HWCV/log_ori.txt";	/*全局变量 程序日志存储地址*/
char g_log_rec[500] = { 0 };		/*全局变量 程序日志专用变量*/
char g_err_adr[50]= "D:/HWCV/err_ori.txt";					/*错误日志路径*/
/*全局变量 输出txt结果文件*/
/*全局变量 输出txt结果文件地址*/



time_t ltime;
char *srcTime=NULL;
char timeNow[32]={0};
char msg[100]={0};