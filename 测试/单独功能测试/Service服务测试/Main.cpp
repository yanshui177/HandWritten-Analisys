// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Service.h"
#include <windows.h>
#include <stdio.h>

#define SLEEP_TIME 5000	//两次查询的间隔
#define LOGFILE "D:\\HWCVServices\\memstatus.txt"	//日志目录

SERVICE_STATUS ServiceStatus; 
SERVICE_STATUS_HANDLE hStatus; 

void ServiceMain(int argc, char** argv); 
void ControlHandler(DWORD request); 
int InitService();
int WriteToLog(char* str);
int main(int argc, char* argv[])
{
	_Module.Init("Service","Service");
	if (argc > 1)
	{
		char seps[] = "-/";
		char *pToken;
		
		pToken = strtok(argv[1],seps);
		while (pToken)
		{
			if (!stricmp(pToken,"Install"))
			{
				_Module.Install();
			}
			else if (!stricmp(pToken,"Uninstall"))
			{
				_Module.Uninstall();
			}
			pToken = strtok( NULL, seps );
			return 0;
		}
	}
	_Module.m_bService = TRUE;
	_Module.Start();

	return 0;
}

int WriteToLog(char* str)
{
    FILE* log;
    log = fopen(LOGFILE, "a+");
    if (log == NULL)
    return -1;
    fprintf(log, "%s\n", str);
    fclose(log);
    return 0;
}