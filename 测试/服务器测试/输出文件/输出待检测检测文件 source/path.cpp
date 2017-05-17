/*
实现文件：path.cpp 路径操作实现文件
*/
#include "path.h"


/**
获取并返回当前时间
 */
char* GetTime()
{
	time(&g_ltime);
	g_srcTime = ctime(&g_ltime);
	strncpy(g_timeNow, g_srcTime, strlen(g_srcTime) - 1);  //不拷贝换行
	g_timeNow[strlen(g_srcTime) - 1] = '\0';   //加结束符'\0'

	return g_timeNow;
}


/**
读取配置文件，并配置各项参数

@变量 filename 配置文件的路径
@返回值 成功1  失败0
*/
int ReadConfig(char *filename)
{
	ifstream file(filename);

	if (!file)/*"配置文件不存在！"*/
	{
		/*写入时间*/
		memset(g_log_rec, 0, sizeof(g_log_rec));
//		cout<<"read"<<endl;

		strcat(g_log_rec, "--ERR:配置文件不存在!");
		SaveLog(g_log_rec, g_log_adr, "a");

		return 0;
	}

	cout<<"1.1"<<endl;
	/*步骤：开始读取信息*/
	/*仅用作过滤字符*/
	string temp;
	file >> temp >> temp;
	/*---此行6个，参考配置信息：图片对比参数*/
	file >> temp >> temp >> temp >> temp >> temp >>temp;
	file  >> g_dir >> temp >> temp >> temp;
	string g_log_adr_t;
	file  >> g_log_adr_t >> temp;

	memset(g_log_adr, 0, sizeof(g_log_adr));
	strcpy(g_log_adr, (char*)g_log_adr_t.c_str());
	cout<<"1.2"<<endl;

	//if (g_bi_threshold < 0 || g_bi_threshold >255)/*输出到日志错误信息*/{		
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	//	strcat(g_log_rec, "--MSG:配置参数有误-笔迹图像对比参数!");
	//	strcat(g_log_rec, g_dir.c_str());
	//	SaveLog(g_log_rec, g_err_adr, "a");

	//	return 0;
	//}


	/*---此行6个，参考配置信息：网络配置参数*/
	file >> temp >> temp >> g_db_hostName >> temp >> g_db_dBName >> temp >> g_db_userName >> temp >> g_db_password >> temp >> g_db_hoster_zk >> temp;

	cout<<"1.3"<<endl;
	///*检验参数*/
	////if (strcmp(g_db_hostName.c_str(), "") || g_bi_threshold >255 || g_bi_threshold < 1)/*输出到日志错误信息*/{
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	//	/*time_t timer;
	//	struct tm *tblock;
	//	timer = time(NULL);
	//	tblock = localtime(&timer);
	//	strcat(g_log_rec, asctime(tblock));*/
	//	strcat(g_log_rec, "--MSG:-网络配置参数!");
	//	strcat(g_log_rec, g_db_password.c_str());
	//	strcat(g_log_rec, "\n");

	//	SaveLog(g_log_rec, g_err_adr, "a");

//		return 0;
//	}


	/*---此行5个，参考配置信息：控制参数*/
	//备用
	file >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp;

	///*检验参数*/
	//if (0)/*输出到日志错误信息*/{
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	///*	time_t timer;
	//	struct tm *tblock;
	//	timer = time(NULL);
	//	tblock = localtime(&timer);
	//	strcat(g_log_rec, asctime(tblock));*/
	//	strcat(g_log_rec, "--ERR:配置参数有误-控制参数!");
	//	SaveLog(g_log_rec, g_err_adr, "a");

	//	return 0;
	//}

	/*---此行5个，参考配置信息：数据库查询参数*/
	file >> temp >> temp >> g_db_qurry_start >> temp >> g_db_qurry_end >> temp >> g_db_qurry_zone >> temp >> g_db_qurry_stu_num >> temp >> g_db_qurry_all >> temp;

	///*检验参数*/
	//if (0)/*输出到日志错误信息*/{
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	//	/*time_t timer;
	//	struct tm *tblock;
	//	timer = time(NULL);
	//	tblock = localtime(&timer);
	//	strcat(g_log_rec, asctime(tblock));*/
	//	strcat(g_log_rec, "--ERR:配置参数有误-数据库查询参数!");
	//	SaveLog(g_log_rec, g_err_adr, "a");

	//	return 0;
	//}



	//if (g_doubt_threshold < 0.01)
	//{
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	//	/*time_t timer;
	//	struct tm *tblock;
	//	timer = time(NULL);
	//	tblock = localtime(&timer);
	//	strcat(g_log_rec, asctime(tblock));*/
	//	strcat(g_log_rec, "--ERR:配置参数有误-笔迹图像对比参数!");
	//	SaveLog(g_log_rec, g_err_adr, "a");
	//
	//	return 0;
	//}

	//if (g_conti < 0 || g_conti > 10 || g_conti == NULL)
	//{
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	///*	time_t timer;
	//	struct tm *tblock;
	//	timer = time(NULL);
	//	tblock = localtime(&timer);
	//	strcat(g_log_rec, asctime(tblock));*/
	//	strcat(g_log_rec, "--ERR:配置参数有误-笔迹图像对比参数!\n\n");
	//	SaveLog(g_log_rec, g_err_adr, "a");

	//	return 0;
	//}
	file.close();/*关闭文件句柄*/

	return 1;
}


/**
函数功能：存储过程数据到txt文件

@变量： record 存储的语句
@变量 g_txt_file_path 存储的位置
@返回值 1成功 0失败
*/
int SaveLog(char *txt, string txt_file_path, char *type)
{
	FILE* fpzz = fopen(txt_file_path.c_str(), type);  //创建文件	
	if (!fpzz) 	return 0; 
	//要返回错误代码
	fprintf(fpzz, txt); //从控制台中读入并在文本输出
	fclose(fpzz);
	fpzz = NULL;//需要指向空，否则会指向原打开文件地址  

	return 1;
}
