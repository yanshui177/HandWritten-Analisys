/*
主函数文件：segmentation.cpp 主函数的实现文件
*/
#include "segmentation.h"
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//无界面运行
/*主函数*/


int main(int argc, char* argv[])
{
	/*变量定义*/
	string dir = "E:/xiangmu/Img/imgjiaobiao/010211100518"; //存储目录
	//string dir;
	//if (argc < 2)
	//	return -1;
	//else
	//	dir = argv[1];
	cout << (char*)dir.c_str() << endl;
	char	record[2400] = { 0 };
	FILE*	fpzz = NULL;//需要注意
	int		i, ii, jj, feature[50][50][30] = { 0 }, featureall = 0;
	double	featurep[50][50][30] = { 0 };
	double  bzcu[50][50] = { 0 };
	double  bzckesa[50][50] = { 0 };
	double  wcd[30] = { 0 };

	int		featx[50][50] = { 0 };
	int		featdif[30] = { 0 };
	float	maxx = 0;			//最大特征值的标号与值
	int		xyimgnum = 0;				//嫌疑图片的数目

	vector<string> suspict;		//记录嫌疑图片地址
	vector<float> suspict_wcd;	//嫌疑图片的wcd值
	vector<string> files;		//存储该生所有考试文件路径
	/*读取配置文件，并配置各项参数*/
	if (!ReadConfig("D:/HWCV/config/configure.cfg"))
	{
//		SaveLog("\t配置文件读取失败\n", g_log_adr, "a");
		SaveLog("\n0\n", g_log_adr, "a");
		return 0;
	}
	char path[100] = "E:/xiangmu/Img/imgjiaobiao/";



	/*步骤：读取标准差文件*/
	int bzccolumns = 47;//txt文件中有47列
	vector<double *> output_bzc;
	if (!ReadScanf("D:\\HWCV\\config\\stdfile.db", bzccolumns, output_bzc))
	{
		memset(g_log_rec, 0, sizeof(g_log_rec));

//		SaveLog("\n读取路径：D:\\HWCV\\config\\stdfile.db 的标准差文件失败！\n", g_log_adr, "a");
		SaveLog("\n0\n", g_log_adr, "a");
		return 0;
	}
//	cout<<"标准差："<<endl;
	for (ii = 0; ii < 48; ii++)//output_vector可视为二维数组;输出数组元素：
		for (jj = ii + 1; jj < 47; jj++)
		{
			bzckesa[ii][jj] = output_bzc[ii][jj];
//			cout<<	bzckesa[ii][jj];
		}
//		cout<<endl;

	//开始检测
	//-------------------------------------------------------------//
	getFiles(dir.c_str(), files);	//遍历当前文件夹下的所有文件
	int size = files.size();
	cout << "考生文件数量" <<size<< endl;

	//开始对每一张图片进行处理
	for (int r = 0; r<size; r++)
	{
		memset(wcd, 0, sizeof(wcd));
		cout<<"-对每一张图片进行处理-："<<files[r].c_str()<<endl;
		ComputeImage(files, bzckesa, wcd, r);
		xyimgnum = 0;
		//求卡方距离的最大值 
		for (i = 0; i < size; i++)
		{
			cout << files[i].c_str()<< "  " << wcd[i] << endl;
			if (wcd[i]>0.12)
			{
				xyimgnum++;
				suspict.push_back(files[i].c_str());
				suspict_wcd.push_back(wcd[i]);
			}
		}
		if (xyimgnum<3) break;
	}

	/*将结果存入log文件*/
	strcat(g_log_rec, "\n");
	memset(g_log_rec, 0, sizeof(g_log_rec));
//	strcat(g_log_rec, GetTime());
//	strcat(g_log_rec, "\t考生考号：");
	strcat(g_log_rec, dir.substr(27, 22).c_str());
	strcat(g_log_rec, "\t");//图片总数为：
	char pic_num[20];
	_itoa(size, pic_num, 10);
	strcat(g_log_rec, pic_num);
	if (xyimgnum > 0)
	{
		char b[20];
		sprintf(b, "\t%d", xyimgnum);
		strcat(g_log_rec, b);
		strcat(g_log_rec, "\n");
		for (i = 0; i < xyimgnum; i++)
		{
			cout << "嫌疑图像：" << files[i].c_str() << endl;
			strcat(g_log_rec, "\t\t\t");//\t嫌疑图像：
			strcat(g_log_rec, suspict[i].c_str());
			strcat(g_log_rec, "\t");//相似度：
			float sim = (1.0 - suspict_wcd[i]) * 100;
			char a[20];
			sprintf(a, "%g", sim);
			strcat(g_log_rec, a);
			strcat(g_log_rec, "%%\n");
		}
	}
	else
	{
//		strcat(g_log_rec, "\t该考生没有嫌疑图像！\n");
		strcat(g_log_rec, "\t0\n");
		cout << "该考生无嫌疑图像！" << endl;
	}
	SaveLog(g_log_rec, g_log_adr, "a");


	/*善后*/
	suspict.clear();
	suspict_wcd.clear();
	memset(g_log_rec, 0, sizeof(g_log_rec));
	memset(feature, 0, sizeof(feature));
	memset(featurep, 0, sizeof(featurep));
	memset(bzckesa, 0, sizeof(bzckesa));
	memset(wcd, 0, sizeof(wcd));
	memset(featdif, 0, sizeof(featdif));
	files.clear();
	memset(g_log_rec, 0, sizeof(g_log_rec));

	/*返回值*/
	system("pause");
	return 0;
}
