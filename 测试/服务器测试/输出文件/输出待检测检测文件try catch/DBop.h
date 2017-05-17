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

extern char g_log_adr[50];				/*全局变量 程序日志存储地址*/
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
功能：	查询所有学生的学号，将所有的指定位置的数据库信息(学号)全部存储在名为stu的vector<string>型的变量中

@变量 stu 学生学号存储
@返回值 成功1 失败0
*/
int DbStu(vector<string>& stu);
