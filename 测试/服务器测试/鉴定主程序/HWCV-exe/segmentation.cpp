/*
主函数文件：segmentation.cpp 主函数的实现文件
*/
#include "segmentation.h"
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )//没有界面运行

int ComputeImage(vector<string> files, vector<int> flag_exist,  double bzckesa[50][50], double *wcd, int conti)
{
	cout << "ComputeImage" << endl;
	int i, ii, jj, size;
	double	bzcu[50][50] = { 0 };			//标准差中的u
	double	featurep[50][50][30] = { 0 };	//所有图像的轮廓方向特征初始化//干什么	//30
	int		feature[50][50][30] = { 0 };	//所有图像的特征值
	int		featx[50][50] = { 0 };			//循环赋值的feature
	int		featureall;					//图像特征值和				//做什么用

	size = flag_exist.size();
	for (i = 0; i < size; i++)
	{
		memset(featx, 0, sizeof(featx));
		cout << "singlefeature:" << (char*)files[flag_exist[i]].c_str() << endl;
		//检查文件存在与否


		singlefeature((char*)files[flag_exist[i]].c_str(), featx);				//featx[][50]
		featureall = 0;                                    //图像特征值和的初始化
		for (ii = 0; ii < 48; ii++)                             //将featx存起来,回头看能不能用函数换掉
			for (jj = ii + 1; jj < 47; jj++)
			{
			feature[ii][jj][i] = featx[ii][jj];
			featureall = featureall + featx[ii][jj];
			}
		//求轮廓方向特征featurep，式(5)  与标准差中的u的和
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
			{
			featurep[ii][jj][i] = (double)featx[ii][jj] / featureall;
			bzcu[ii][jj] += (double)featx[ii][jj] / featureall * 1000;     //标准差的值过小,进行放大（1）
			}
	}
	//处理完一个人的每一张图片后
	for (ii = 0; ii < 48; ii++)//求标准差中的u
		for (jj = ii + 1; jj < 47; jj++)
			bzcu[ii][jj] = bzcu[ii][jj] / size;
	//求相似性就是带权卡方wcd
	for (i = 0; i < size; i++)
		for (ii = 0; ii < 48; ii++)
			for (jj = ii + 1; jj < 47; jj++)
				if (featurep[ii][jj][i] * featurep[ii][jj][conti] != 0 && bzckesa[ii][jj] != -1)
					wcd[i] += pow((featurep[ii][jj][i] - featurep[ii][jj][conti]), 2) / ((featurep[ii][jj][i] + featurep[ii][jj][conti])*bzckesa[ii][jj]);

	memset(feature, 0, sizeof(feature));
	memset(featurep, 0, sizeof(featurep));

	return 1;
}


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
	int		i, ii, jj;
	double  bzckesa[50][50] = { 0 };
	double  wcd[30] = { 0 };

	int		featdif[30] = { 0 };
	float	maxx = 0;			//最大特征值的标号与值
	int		xyimgnum = 0;				//嫌疑图片的数目
	char	str[80];					//存储地址

	vector<string> suspict;		//记录嫌疑图片地址
	vector<float> suspict_wcd;	//嫌疑图片的wcd值
	vector<string> files;		//存储该生所有考试文件路径
	vector<string> dateVec, subjectVec, stuNum2;
	vector<string> flagVec;//记录查到的学生的所有考试信息

	//读取配置文件，并配置各项参数
	memset(g_log_rec, 0, sizeof(g_log_rec));
	strcat(g_log_rec, GetTime());
	if (!ReadConfig("D:/HWCV/config/configure.cfg"))
	{
		strcat(g_log_rec, ",config failed！\n");
		SaveLog(g_log_rec, g_log_adr, "a");
		return 0;
	}
	cout<<"ReadConfig success"<<endl;

	//初始化log文件
	strcat(g_log_rec, ",");
	strcat(g_log_rec, fpname1);//考号
	strcat(g_log_rec, ",");

	/*
	string temp=g_db_hostName;
	temp+=g_db_dBName;temp+=g_db_userName;temp+=g_db_password;
	SaveLog((char*)temp.c_str(), g_log_adr, "a");
	*/

	/*步骤：读取标准差文件*/
	int bzccolumns = 47;//txt文件中有47列
	vector<double *> output_bzc;
	if (!ReadScanf("D:\\HWCV\\config\\stdfile.db", bzccolumns, output_bzc)) return 0;
	for (ii = 0; ii < 48; ii++)//output_vector可视为二维数组;输出数组元素：
		for (jj = ii + 1; jj < 47; jj++)
			bzckesa[ii][jj] = output_bzc[ii][jj];

	//查询数据库
	string stuNum = fpname1;
	cout << "查询数据库" << endl;
	DbImg(stuNum, dateVec, subjectVec, stuNum2);

	//生成路径();
	cout << "生成路径-dateVec的个数：" << dateVec.size() << endl;
	vector<int> flag_exist;
	fstream _file;
	for (int cp_i = 0; cp_i < dateVec.size(); cp_i++)
	{
		string path_t = CrPath(dateVec[cp_i], subjectVec[cp_i], stuNum2[cp_i]); 
		cout << path_t << endl;
		SaveLog((char*)path_t.c_str(), "D:/HWCV/1.txt", "a"); 
		SaveLog("\n", "D:/HWCV/1.txt", "a");
		files.push_back(path_t);
		_file.open(path_t.c_str(), ios::in);

		if (_file) 
		{
			//SaveLog("OK", "D:/HWCV/1.txt", "a");
			flag_exist.push_back(cp_i);
		}
	}
	int size = flag_exist.size();
	cout << "最终size个数：" << size << endl;
	if (size == 0)
	{
		system("pause");
		return 0; //没找到人，直接返回	
	}
	//开始对每一张图片进行处理
	cout << "对每一张图片进行处理" << endl;
	for (int r = 0; r < size; r++)
	{
		memset(wcd, 0, sizeof(wcd));
		ComputeImage(files, flag_exist, bzckesa, wcd, r);

		xyimgnum = 0;
		int flagc = 0;
		//疑似作弊
		for (i = 0; i < files.size(); i++)
		{
			if (i == flag_exist[flagc])
			{
				flagc++;
				if (wcd[i]>0.12)
				{
					flagVec.push_back("1");//嫌疑标记1
					xyimgnum++;
					suspict.push_back(files[i].c_str());
					suspict_wcd.push_back(wcd[i]);
				}
				else
				{
					flagVec.push_back("0");//嫌疑标记1
				}
			}
			else
			{
				flagVec.push_back("0");//嫌疑标记1
				continue;
			}
		}

		// 验证作弊数量
		if (xyimgnum < 3)
		{
			break;
		}
		flagVec.clear();
	}

	// 结果更新数据库
	cout << "更新数据库" << endl;
	DbUpdate(stuNum, dateVec, subjectVec, stuNum2, flagVec);

	// 将结果存入log文件
	char pic_num[20];
	_itoa(size, pic_num, 10);
	strcat(g_log_rec, pic_num);
	if (xyimgnum > 0)
	{
		g_stu_sus++;
		//输出嫌疑图片数量到csv
		char b[20];
		sprintf(b, ",%d", xyimgnum);
		strcat(g_log_rec, b);
		strcat(g_log_rec, "\n");
		//逐个输出嫌疑图像
		for (i = 0; i < xyimgnum; i++)
		{
			strcat(g_log_rec, ",,,");
			strcat(g_log_rec, suspict[i].c_str());
			strcat(g_log_rec, ",");
			float sim=(1.0-suspict_wcd[i])*100;
			char a[20];
			sprintf(a, "%g", sim);
			strcat(g_log_rec, a);
			strcat(g_log_rec, "%%\n");
		}
	}
	else strcat(g_log_rec, "\n"); 
	//strcat(g_log_rec, "\n");

	SaveLog(g_log_rec, g_log_adr, "a");
	cout << "结果存入log文件：" << g_log_adr <<" 完毕"<< endl;


	/*善后*/
	suspict.clear();
	suspict_wcd.clear();
	output_bzc.clear();
	memset(g_log_rec, 0, sizeof(g_log_rec));
	memset(bzckesa, 0, sizeof(bzckesa));
	memset(wcd, 0, sizeof(wcd));
	memset(featdif, 0, sizeof(featdif));
	files.clear();
	dateVec.clear();
	subjectVec.clear();
	stuNum2.clear();
	flagVec.clear();

	system("pause");
	/*返回值*/
	return 0;
}


