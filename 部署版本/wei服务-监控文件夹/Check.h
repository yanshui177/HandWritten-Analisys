#include <windows.h>
#include <iostream>
#include <dos.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string.h>
#include <io.h>

using namespace std;


/*时间获取函数u*/
#define LOGFILE "D:\\HWCV\\memstatus.txt"	//日志存储位置

extern time_t ltime;
extern char *srcTime;
extern char timeNow[22];
extern char msg[100];

/*功能：写入日志
@变量 str 写入内容
@返回值 固定
*/
int WriteToLog(char* str);


/**
功能:获取并返回当前时间
 */
char* GetTime();


/*功能：检查当前木有有无文件，若有，提取文件名，并删除此文件
@变量 path 检查文件位置
@变量 files 获取到的文件名称
@返回值 返回检测到的变量向量
*/
int CheckFile(char* path, vector<string>& files);


