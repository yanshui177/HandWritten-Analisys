/*
主函数文件：segmentation.cpp 主函数的实现文件
*/
#include "segmentation.h"
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//无界面运行
/*主函数*/
int main(int argc,char* argv[])
{
	if(argc<2) return -1;
	//for(int iii=0;iii<argc;iii++)
	//	cout<<"argv"<<iii<<" "<<argv[iii]<<endl;
	char *fpname1 = argv[1];
//	cout<<"开始鉴定"<<fpname1<<endl;
	//char *fpname1 = "010209400748";

	/*变量定义*/
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

	vector<string> suspict;		//记录嫌疑图片地址
	vector<float> suspict_wcd;	//嫌疑图片的wcd值
	vector<string> files;		//存储该生所有考试文件路径
	vector<string> dateVec, subjectVec, stuNum2;
	vector<string> flagVec;//记录查到的学生的所有考试信息

	/*读取配置文件，并配置各项参数*/
	if (!ReadConfig("D:/HWCV/config/configure.cfg"))
	{
		SaveLog("\t配置文件读取失败\n", g_log_adr, "a");

		return 0;
	}

//	cout<<"ReadConfig success"<<endl;
//
//	string temp=g_db_hostName;
//	temp+=g_db_dBName;temp+=g_db_userName;temp+=g_db_password;
//	SaveLog((char*)temp.c_str(), g_log_adr, "a");
//
	//查询数据库
	string stuNum = fpname1;
	if (!DbImg(stuNum, dateVec, subjectVec, stuNum2))
	{
		memset(g_log_rec, 0, sizeof(g_log_rec));

		strcat(g_log_rec, GetTime());

		strcat(g_log_rec, "\t数据库查询不到考号为：");
		strcat(g_log_rec,fpname1);
		strcat(g_log_rec, "的学生\n");
		SaveLog(g_log_rec, g_log_adr, "a");

		return 0;
	}
	//SaveLog("成功DB！！！\n", g_log_adr, "a");
//	cout << "成功DB\n数量为：" << subjectVec.size() << endl;

	//生成路径
	int nn = 0;
	for (int cp_i = 0; cp_i < subjectVec.size(); cp_i++)
	{
		if (!strcmp(subjectVec[cp_i].substr(0, 1).c_str(), "4") || !strcmp(subjectVec[cp_i].substr(0, 1).c_str(), "9"))
		{
//			cout << "无图像：" <<subjectVec[cp_i].c_str()<<" "<<dateVec[cp_i].c_str()<<" "<<stuNum2[cp_i].c_str()<< endl;
			continue;
		}
		files.push_back(CrPath(dateVec[cp_i], subjectVec[cp_i], stuNum2[cp_i]));
		
//		cout<<"PATH:"<<files[nn++].c_str()<<endl;
		
//		SaveLog((char*)files[cp_i].c_str(), g_log_adr, "a");
//		SaveLog("\n", g_log_adr, "a");

	}
//	cout << "生成路径结束" << endl;

	int size = files.size();/*找到的路径的数量*/
	/*对每一张图片进行处理*/

	int realSize = 0;
	for (i = 0; i < size; i++)
	{
		memset(str, 0, sizeof(str));
		memset(featx, 0, sizeof(featx));
		memset(bzcu, 0, sizeof(bzcu));

		strcpy(str, files[i].c_str());
		try{
			singlefeature(str, featx);//featx[][50]
			//正常处理了图像，说明图像可以照常处理
			realSize += 1;
		}
		catch (_com_error e)
		{
			//没有正常处理图像，说明此地址下的图像不可用
			memset(g_log_rec, 0, sizeof(g_log_rec));

			strcat(g_log_rec, "\n读取路径：");
			strcat(g_log_rec, str);
			strcat(g_log_rec, " 的图像失败:");
			strcat(g_log_rec, (char*)e.Description());
			strcat(g_log_rec, " 的图像失败！\n");
			SaveLog(g_log_rec, g_log_adr, "a");

			continue;
		}
//		cout << "可以opencv\n" << endl;
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
	if (realSize == 0)
	{
		SaveLog("\t此考生没有一张数据图像可用！\n", g_log_adr, "a");
		return 0;
	}
	/*求标准差中u*/
	for (ii = 0; ii < 48; ii++)
		for (jj = ii + 1; jj < 47; jj++)
			bzcu[ii][jj] = bzcu[ii][jj] / realSize;


	/*步骤：读取标准差文件*/
	int bzccolumns = 47;//txt文件中有47列
	vector<double *> output_bzc;
	if (!ReadScanf("D:\\HWCV\\config\\stdfile.db", bzccolumns, output_bzc))
	{
		memset(g_log_rec, 0, sizeof(g_log_rec));

		SaveLog("\n读取路径：D:\\HWCV\\config\\stdfile.db 的标准差文件失败！\n", g_log_adr, "a");
		return 0;
	}
	for (ii = 0; ii < 48; ii++)//output_vector可视为二维数组;输出数组元素：
		for (jj = ii + 1; jj < 47; jj++)
			bzckesa[ii][jj] = output_bzc[ii][jj];

	/*求相似性，即带权卡方wcd*/
	for (i = 0; i < realSize; i++)
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
				if (featurep[ii][jj][i] * featurep[ii][jj][g_conti] != 0 && bzckesa[ii][jj] != -1)
					wcd[i] += pow((featurep[ii][jj][i] - featurep[ii][jj][g_conti]), 2) / ((featurep[ii][jj][i] + featurep[ii][jj][g_conti])*bzckesa[ii][jj]);

	//标出所有有嫌疑的图像1，无嫌疑的图像0
	for (i = 0; i < dateVec.size(); i++)
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
	
	//结果更新数据库
	DbUpdate(stuNum, dateVec, subjectVec, stuNum2, flagVec);
//	cout << "数据库更新完毕" << endl;

	/*将结果存入log文件*/
	strcat(g_log_rec, "\n");
	memset(g_log_rec, 0, sizeof(g_log_rec));
	strcat(g_log_rec, GetTime());
	strcat(g_log_rec, "\t考生考号：");
	strcat(g_log_rec, fpname1);
	strcat(g_log_rec, " 图片总数为：");
	char pic_num[20];
	_itoa(realSize, pic_num, 10);
	strcat(g_log_rec, pic_num);
	if (xyimgnum > 0)
	{
		
	/*	strcat(g_log_rec, "\t");
		strcat(g_log_rec, suspict[0].c_str());
		strcat(g_log_rec, "\t");
		char a[20];
		sprintf(a, "%g", suspict_wcd[0]);
		strcat(g_log_rec, a);
	*/	strcat(g_log_rec, "\n");
		for (i = 0; i < xyimgnum; i++)
		{
			strcat(g_log_rec, "\t\t\t\t嫌疑图像：");
			strcat(g_log_rec, suspict[i].c_str());
			strcat(g_log_rec, "\t相似度：");
			float sim=(1.0-suspict_wcd[i])*100;
			char a[20];
			sprintf(a, "%g", sim);
			strcat(g_log_rec, a);
			strcat(g_log_rec, "%%\n");
		}
	}
	else 
		strcat(g_log_rec, "\t该考生没有嫌疑图像！\n"); 
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

	/*返回值*/
	return 0;
}


