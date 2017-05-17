/*
头文件：path.h 与路径相关操作的函数头文件以及函数原型 
*/
#pragma once
#include "StdAfx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cv.h> 
#include <io.h>

using namespace std;


extern int    g_bi_threshold;		/*全局变量 二值化阈值*/
extern double g_std_kesa[50][50];	/*全局变量 标准差数组*/
extern float  g_doubt_threshold;	/*全局变量 作弊嫌疑阈值*/
extern string g_dir;				/*全局变量 总路径的目录*/
extern int    g_conti;				/*全局变量 比较标准*/

extern string g_db_hostName;		/*全局变量 服务器ip或名称*/	
extern string g_db_dBName;			/*全局变量 服务器ODBC数据源*/
extern string g_db_userName;		/*全局变量 服务器用户名*/	
extern string g_db_password;		/*全局变量 服务器密码*/	

extern char g_log_adr[50];				/*全局变量 程序日志存储地址*/
extern char g_err_adr[50];			/*全局变量 错误日志存储地址*/
extern char g_log_rec[500];			/*全局变量 程序日志专用变量*/
		/*全局变量 待定*/
		/*全局变量 待定*/

extern string g_db_qurry_start;		/*全局变量 数据库查询_开始日期*/
extern string g_db_qurry_end;		/*全局变量 数据库查询_结束日期*/
extern string g_db_qurry_zone;		/*全局变量 数据库查询_特定区域*/
extern string g_db_qurry_stu_num;	/*全局变量 数据库查询_特定考号*/
extern bool g_db_qurry_all;			/*全局变量 数据库查询_查询全部标记*/
extern string g_db_hoster_zk;



extern	time_t ltime;
extern	char *srcTime;
extern	char timeNow[32];
extern  char msg[100];

/**
获取并返回当前时间
 */
char* GetTime();


/**
根据学生信息创建文件路径，用于文件读取

@变量 date 考试日期
@变量 subject 考试科目
@变量 stuNum 考号
@返回值 返回生成的文件路径
*/
string CrPath(string date, string subject, string stuNum);


/*
功能：读取标准差文件
@变量 filesname 文件名
@变量 col 行数
@变量 _vector 读取到的标准差存到vector中
@返回值 成功1失败0
*/
int ReadScanf(const string &filename, const int &cols, vector<double *> &_vector);


/**
读取配置文件，并配置各项参数

@变量 filename 配置文件的路径
@返回值 成功1  失败0
*/
int ReadConfig(char *filename);


/**
函数功能：存储过程数据到txt文件

@变量： record 存储的语句
@变量 g_txt_file_path 存储的位置
@返回值 1成功 0失败
*/
int SaveLog(char *record, string txt_file_path, char *type);


/*
功能：保存中间鉴定图像
@变量 
@变量 
@返回值 
*/
int SaveImg(IplImage *img, char *g_process_img_adr);


/*
功能：获取指定目录下的文件
@变量 path 路径
@变量 files 输出vector格式的文件
*/
void getFiles(string path, vector<string>& files);


/*
功能：获取指定目录下的目录
@变量 path 目录
@变量 files 返回的目录vector
@返回值 成功1失败0
*/
int getFolders(string path, vector<string>& files);


/*
功能：搜索目录
*/
int searchDir(char *path, vector<string> &dir);