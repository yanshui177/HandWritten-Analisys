/*
主函数文件：segmentation.cpp 主函数的实现文件
*/
#include "main.h"
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//没有界面运行

/*主函数*/
char *adr="D:/process.csv";
int main(int argc,char* argv[])
{

//	cout<<"开始鉴定"<<fpname1<<endl;
	//char *fpname1 = "010209400748";
	/*变量定义*/
	cout<<"1"<<endl;
	vector<string> stuNum;

	//读取配置文件，并配置各项参数
	memset(g_log_rec, 0, sizeof(g_log_rec));
	strcat(g_log_rec, GetTime());
	if (!ReadConfig("D:/HWCV/config/configure.cfg"))
	{
		cout<<"!ReadConfig"<<endl;
		strcat(g_log_rec, ",config failed！\n");
		SaveLog(g_log_rec, adr, "a");

		return 0;
	}
	cout<<"ReadConfig success"<<endl;

	//查询数据库
	cout<<"2"<<endl;
	DbStu(stuNum);

	//生成路径();
	FILE *fp;
	string name="D:/HWCV/Check/";
	cout<<"搜索到的数量："<<stuNum.size()<<endl;
	for(int i=0; i<stuNum.size();i++)
	{
		string temp=name;
		temp+=stuNum[i];
		fp=fopen((char*)temp.c_str(),"w+");
		fclose(fp);
		fp=NULL;

		system("pause");
	}

	/*返回值*/
	return 0;
}


