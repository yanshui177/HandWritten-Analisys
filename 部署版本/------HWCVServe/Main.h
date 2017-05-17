#include <string>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <dos.h>
#include <time.h>
#pragma comment(lib, "Advapi32")

//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//没有界面运行

using namespace std;
/*定义全局变量*/
#define SLEEP_TIME	1000						//5000毫秒刷新一次


/*时间获取函数u*/
time_t ltime;
char *srcTime=NULL;
char timeNow[22]={0};
char msg[100]={0};