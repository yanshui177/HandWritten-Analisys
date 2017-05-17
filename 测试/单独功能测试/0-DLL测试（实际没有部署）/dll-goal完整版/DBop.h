/*
头文件：DBop.h  数据库操作头文件
*/
#pragma once
#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF","EndOfFile")
#include <vector> 
#include <string> 
#include <iostream> 
#include <windows.h> 
#include <iomanip> 
#include <stdio.h> 

using namespace std;

/*全局变量*/

extern char *g_log_adr;				/*全局变量 程序日志存储地址*/
extern char g_log_rec[500];				/*全局变量 程序日志专用变量*/
extern FILE *g_log_fpzz;				/*全局变量 程序日志专用文件句柄*/

extern string g_db_hostName;		/*全局变量 服务器ip或名称*/
extern string g_db_dBName;			/*全局变量 服务器ODBC数据源*/
extern string g_db_userName;		/*全局变量 服务器用户名*/
extern string g_db_password;		/*全局变量 服务器密码*/

extern string g_db_qurry_start;		/*全局变量 数据库查询_开始日期*/
extern string g_db_qurry_end;		/*全局变量 数据库查询_结束日期*/
extern string g_db_qurry_zone;		/*全局变量 数据库查询_特定区域*/
extern string g_db_qurry_stu_num;	/*全局变量 数据库查询_特定考号*/
extern bool   g_db_qurry_all;		/*全局变量 数据库查询_查询全部标记*/
extern string g_db_hoster_zk;		/*全局变量 数据库用户，zk（考试院的zk，本地的yannsy）*/
/*****************************************函数原型*************************************/


/**
程序功能：	根据string类的stu【存储学号】，搜索出所有此人的考试信息,并分别存储在不同的变量中

@变量 stuNum 学号
@变量 date<vector>	考试时间
@变量 subject<vector> 考试科目
@变量 stuNum<vector> 考号
@返回值 成功1 失败0
*/
int DbImg(string stuNum, vector<string>& dateVec, vector<string>& subjectVec, vector<string>& stuNum2);


/**
程序功能：	更新学生数据库信息,根据学生的鉴定结果，将结果输出到数据库中

@变量 stuNum：学号
@变量 subject：考试科目
@变量 flagCheat：作弊标记
@返回值 成功1失败0
*/
int DbUpdate(string stuNum, vector<string> dateVec, vector<string> subjectVec, vector<string> stuNum2, vector<string> flagVec);