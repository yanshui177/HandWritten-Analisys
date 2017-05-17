/*
头文件：segmentation.h 主函数头文件
*/
#pragma once
#ifdef WIN32                            //屏蔽VC6对STL的一些不完全支持造成
#pragma warning (disable: 4514 4786)
#endif
#include "StdAfx.h"
#include "DBop.h"
#include "path.h"
#include "Point.h"
#include "process.h"

using namespace std;

/*定义全局变量*/


int		g_bi_threshold;				/* 全局变量 二值化阈值*/
double  g_std_kesa[50][50];			/* 全局变量 标准差数组*/
float   g_doubt_threshold = 0.12;	/* 全局变量 作弊嫌疑阈值*/
string  g_dir;						/* 全局变量 总路径的目录*/
int		g_cheat_num_threshold = 0;	/* 全局变量 默认作弊阈值*/
int		g_conti;					/* 全局变量 默认作弊比较的图片*/

int g_all_img_num = 0;				/* 全局变量 已鉴定的全部图片数量*/
int g_doubt_img_num = 0;			/* 全局变量 已鉴定怀疑的图片数量*/
int g_all_stu_num = 0;				/* 全局变量 已鉴定的全部学生数量*/
int g_doubt_stu_num = 0;			/* 全局变量 已鉴定怀疑的学生数量*/

//string g_db_hostName = "192.168.200.97";	/*全局变量 服务器ip或名称*/
//string g_db_dBName = "purple";			/*全局变量 服务器ODBC数据源*/
//string g_db_userName = "BJSH";			/*全局变量 服务器用户名*/
//string g_db_password = "bjshadmin";		/*全局变量 服务器密码*/
string g_db_hostName = "localhost";		/*全局变量 服务器ip或名称*/
string g_db_dBName = "orcl123";			/*全局变量 服务器ODBC数据源*/
string g_db_userName = "yannsy";		/*全局变量 服务器用户名*/
string g_db_password = "123456";		/*全局变量 服务器密码*/

string	g_db_qurry_start = "200906";		/*全局变量 数据库查询_开始日期*/
string	g_db_qurry_end	 = "201610";		/*全局变量 数据库查询_结束日期*/
string	g_db_qurry_zone  = "0";		/*全局变量 数据库查询_特定区域*/
string	g_db_qurry_stu_num = "0";	/*全局变量 数据库查询_特定考号*/
bool	g_db_qurry_all   = true;	/*全局变量 数据库查询_查询全部标记*/
string  g_db_hoster_zk;				/*全局变量 数据库用户，zk（考试院的zk，本地的yannsy）*/


bool g_output_cmd_config = false;	/*全局变量 输出参数控制*/
bool g_output_txt_config = false;	/*全局变量 输出中间文件选项*/
char *g_log_adr = "D:/HWCV/log_ori.txt";	/*全局变量 程序日志存储地址*/
char g_log_rec[500] = { 0 };		/*全局变量 程序日志专用变量*/
char g_err_adr[30] = "D:/HWCV/err_ori.txt";					/*错误日志路径*/
/*全局变量 输出txt结果文件*/
/*全局变量 输出txt结果文件地址*/


int _Check(char *fpname1, char *dest);