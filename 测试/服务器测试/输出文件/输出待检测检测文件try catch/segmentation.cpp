/*
主函数文件：segmentation.cpp 主函数的实现文件
*/
#include "segmentation.h"

/*主函数*/
int main(int argc,char* argv[])
{
	FILE *file = NULL;
	string checkpath="D:/HWCV/Check/";

	//读取配置文件，并配置各项参数
	ReadConfig("D:/HWCV/config/configure.cfg");
	cout<<"ReadConfig success"<<endl;

	//初始化log文件
	memset(g_log_rec, 0, sizeof(g_log_rec));	
	strcat(g_log_rec, "\n");
	strcat(g_log_rec, GetTime());
	strcat(g_log_rec, "  配置文件读取完毕 ");

	vector<string> stuNum;

	while(true)
	{
		//查询数据库
		stuNum.clear();
		DbStu(stuNum);
		for(int i=0;i<stuNum.size();i++)
		{
			//首先合成地址
			string temp = checkpath;
			temp +=stuNum[i];
			file = fopen((char*)temp.c_str(),"w");
			fclose(file);  
			SaveLog(".", g_log_adr, "a");
		}

		Sleep(SLEEP_TIME);

	}
	/*返回值*/
	return 0;
}


