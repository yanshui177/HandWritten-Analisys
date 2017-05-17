/*
主函数文件：segmentation.cpp 主函数的实现文件
*/
#include "segmentation.h"

/*主函数*/
extern "C" _declspec(dllexport) char * __stdcall  WINAPI TEST(char *fpname1)
{
	return fpname1;//总文件夹的路径
}
extern "C" _declspec(dllexport) char * __stdcall  WINAPI HWCV(char *fpname1, char *dest){

	/*读取配置文件，并配置各项参数*/
	ReadConfig("D:\\HWCV\\config\\configure.cfg");

	/*初始化log文件*/
	memset(g_log_rec, 0, sizeof(g_log_rec));
	time_t timer;
	struct tm *tblock;
	timer = time(NULL);
	tblock = localtime(&timer);
	strcat(g_log_rec, "\n----------------------HWCV.dll--单数据库----\n");
	strcat(g_log_rec, asctime(tblock));
	SaveLog(g_log_rec, g_log_adr, "a");

	vector<string>  dateVec, subjectVec,stuNum2;

	/*查询数据库*/
	string stuNum = fpname1;
	DbImg(stuNum, dateVec, subjectVec, stuNum2);


	memset(g_log_rec, 0, sizeof(g_log_rec));
	/*生成路径*/
	for (int cp_i = 0; cp_i < dateVec.size(); cp_i++)
	{
		/*将结果存入log文件*/
		strcat(g_log_rec, stuNum.c_str());
		strcat(g_log_rec, "\t");
		strcat(g_log_rec, dateVec[cp_i].c_str());
		strcat(g_log_rec, "\t");
		strcat(g_log_rec, subjectVec[cp_i].c_str());
		strcat(g_log_rec, "\t");
		strcat(g_log_rec, stuNum2[cp_i].c_str());

		strcat(g_log_rec, "\n");
	}
	SaveLog(g_log_rec, g_log_adr, "a");

	/*返回到网页结果*/
/*	char out[200] = "当前时间为：";
	strcat(out, asctime(tblock));
	strcat(out, "<br>鉴定学号为：");
	strcat(out, fpname1);
	strcat(out, "<br>");
	sprintf(dest, out);
*/
	/*返回值*/
	return "SUCCEED";
}


