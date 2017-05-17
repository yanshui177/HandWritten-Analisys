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
	strcat(g_log_rec, "\n-----------------------------------HWCV完整版----\n");
	strcat(g_log_rec, asctime(tblock));
	SaveLog(g_log_rec, g_log_adr, "a");


	/*变量定义*/
	vector<string> suspict;		//记录嫌疑图片地址
	vector<float> suspict_wcd;	//嫌疑图片的wcd值
	vector<string> files;		//存储该生所有考试文件路径
	vector<string> dateVec, subjectVec, stuNum2;
	vector<string> flagVec;//记录查到的学生的所有考试信息

	int		i, ii, jj, feature[50][50][30] = { 0 }, featureall = 0;
	double	featurep[50][50][30] = { 0 };
	double  bzcu[50][50] = { 0 };
	double  bzckesa[50][50] = { 0 };
	double  wcd[30] = { 0 };

	int		featx[50][50] = { 0 };
	int		featdif[30] = { 0 };
	float	maxx = 0;			//最大特征值的标号与值
	int		xyimgnum = 0;				//嫌疑图片的数目
	char	str[80];					//存储地址

	/*查询数据库*/
	string stuNum = fpname1;
	SaveLog(fpname1, "D:\\HWCV\\numtxt.txt", "a");
	DbImg(stuNum, dateVec, subjectVec, stuNum2);


	/*生成路径*/
	for (int cp_i = 0; cp_i < dateVec.size(); cp_i++)
	{
		files.push_back(CrPath(dateVec[cp_i], subjectVec[cp_i], stuNum2[cp_i]));
	}
	int size = files.size();/*找到的路径的数量*/

	/*对每一张图片进行处理*/
	for (i = 0; i < size; i++)
	{
		memset(str, 0, sizeof(str));
		memset(featx, 0, sizeof(featx));
		memset(bzcu, 0, sizeof(bzcu));

		strcpy(str, files[i].c_str());

		singlefeature(str, featx);//featx[][50]
		featureall = 0;                       //图像特征值和的初始化
		for (ii = 0; ii < 48; ii++)           //将featx存起来,回头看能不能用函数换掉
			for (jj = ii + 1; jj < 47; jj++)
			{
			feature[ii][jj][i] = featx[ii][jj];
			featureall = featureall + featx[ii][jj];
			}
		/*求轮廓方向特征featurep，式(5)  与标准差中的u的和*/
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
			{
			featurep[ii][jj][i] = (double)featx[ii][jj] / featureall;
			bzcu[ii][jj] += (double)featx[ii][jj] / featureall * 1000;     //标准差的值过小,进行放大（1）
			}
	}/*处理完全部图片*/

	/*求标准差中u*/
	for (ii = 0; ii < 48; ii++)
		for (jj = ii + 1; jj < 47; jj++)
			bzcu[ii][jj] = bzcu[ii][jj] / size;


	/*步骤：读取标准差文件*/
	int bzccolumns = 47;//txt文件中有47列
	vector<double *> output_bzc;
	if (!ReadScanf("D:\\HWCV\\config\\stdfile.db", bzccolumns, output_bzc)) return 0;
	for (ii = 0; ii < 48; ii++)//output_vector可视为二维数组;输出数组元素：
		for (jj = ii + 1; jj < 47; jj++)
			bzckesa[ii][jj] = output_bzc[ii][jj];

	/*求相似性，即带权卡方wcd*/
	for (i = 0; i < size; i++)
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
				if (featurep[ii][jj][i] * featurep[ii][jj][g_conti] != 0 && bzckesa[ii][jj] != -1)
					wcd[i] += pow((featurep[ii][jj][i] - featurep[ii][jj][g_conti]), 2) / ((featurep[ii][jj][i] + featurep[ii][jj][g_conti])*bzckesa[ii][jj]);

	/*求卡方距离的最大值*/
	for (i = 0; i < size; i++)
	{
		if (wcd[i] > 0.12)
		{
			xyimgnum++;
			suspict.push_back(files[i].c_str());
			suspict_wcd.push_back(wcd[i]);
			flagVec.push_back("1");//嫌疑标记1
		}
		else
		{
			flagVec.push_back("0");
		}
	}

	/*结果更新数据库*/
	DbUpdate(stuNum, dateVec, subjectVec, stuNum2, flagVec);


	/*将结果存入log文件*/
	memset(g_log_rec, 0, sizeof(g_log_rec));
	strcpy(g_log_rec, "图片总数为：");
	char pic_num[20];
	_itoa(size, pic_num, 10);
	strcat(g_log_rec, pic_num);
	if (xyimgnum > 0)
	{
		strcat(g_log_rec, "\n");
		for (i = 0; i < xyimgnum; i++)
		{
			strcat(g_log_rec, "\t");
			strcat(g_log_rec, suspict[i].c_str());
			strcat(g_log_rec, "\t");
			char a[20];
			sprintf(a, "%g", suspict_wcd[i]);
			strcat(g_log_rec, a);
			strcat(g_log_rec, "\n");
		}
	}
	else strcat(g_log_rec, "\t没有嫌疑图像！\n");
	SaveLog(g_log_rec, g_log_adr, "a");


	/*善后*/
	suspict.clear();
	suspict_wcd.clear();
	output_bzc.clear();
	memset(g_log_rec, 0, sizeof(g_log_rec));
	memset(feature, 0, sizeof(feature));
	memset(featurep, 0, sizeof(featurep));
	memset(bzckesa, 0, sizeof(bzckesa));
	memset(wcd, 0, sizeof(wcd));
	memset(featdif, 0, sizeof(featdif));
	files.clear();
	dateVec.clear();
	subjectVec.clear();
	stuNum2.clear();
	flagVec.clear();


	/*返回到网页结果*/
	char out[40] = "当前时间为：";
	//strcat(out, asctime(tblock));
	//strcat(out, "<br>鉴定学号为：");
	strcat(out, fpname1);
	strcat(out, "\n");
	//if(xyimgnum>0)
	//	strcat(out,"作弊！<br>");
	sprintf(dest, out);

	/*返回值*/
	return "return_OK";
}


