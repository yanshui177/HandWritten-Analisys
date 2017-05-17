/*
实现文件：path.cpp 路径操作实现文件
*/
#include "path.h"


/**
获取并返回当前时间
 */
char* GetTime()
{
	time( &ltime );
	srcTime = ctime( &ltime );
	strncpy(timeNow, srcTime, strlen(srcTime)-1);  //不拷贝换行
	timeNow[strlen(srcTime)-1] = '\0';   //加结束符'\0'

	return timeNow;
}


/**
根据学生信息创建文件路径，用于文件读取

@变量 date 考试日期
@变量 subject 考试科目
@变量 stuNum 考号
@返回值 返回生成的文件路径
*/
string CrPath(string date, string subject, string stuNum)
{
	string temp = g_dir; temp += date; temp += "/";
	temp += subject.substr(0, 4); temp += "/";
	temp += stuNum; temp += ".jpg";

	return temp;
}


/*
功能：读取标准差文件
@变量 filesname 文件名
@变量 col 行数
@变量 _vector 读取到的标准差存到vector中
@返回值 成功1失败0
*/
int ReadScanf(const string &filename, const int &cols, vector<double *> &_vector)
{
	// 功能：将filename 中的数据（共cols列）读取到_vector中，_vector可视为二维数组
	FILE *fp = fopen(filename.c_str(), "r");//打开并读取文件
	bool flag = true;
	int i = 0;

	//	printf("--read_scanf--");
	if (!fp){ return 0; }
	while (flag){
		double *point = new double[cols];
		for (i = 0; i<cols; i++){ //读取数据，存在_vector[cols]中
			if (EOF == fscanf(fp, "%lf", &point[i])) {
				flag = false; break;
			}
			if (EOF == fgetc(fp)) {
				flag = false; i++; break;
			}
		}
		if (cols == i)
			_vector.push_back(point);
	}
	fclose(fp);

	return 1;
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
		cout<<"read"<<endl;

		strcat(g_log_rec, "--ERR:配置文件不存在!");
		SaveLog(g_log_rec, g_err_adr, "a");

		return 0;
	}

	/*步骤：开始读取信息*/

	string temp;/*仅用作过滤字符*/
	file >> temp >> temp;
	/*---此行6个，参考配置信息：图片对比参数*/
	file >> temp >> temp >> temp >> temp >> temp >>temp;
	file  >> g_dir >> temp >> temp >> temp;
	string g_log_adr_t;
	file  >> g_log_adr_t >> temp;

	memset(g_log_adr, 0, sizeof(g_log_adr));
	strcpy(g_log_adr, (char*)g_log_adr_t.c_str());

	//if (g_bi_threshold < 0 || g_bi_threshold >255)/*输出到日志错误信息*/{		
	//	memset(g_log_rec, 0, sizeof(g_log_rec));
	//	strcat(g_log_rec, "--MSG:配置参数有误-笔迹图像对比参数!");
	//	strcat(g_log_rec, g_dir.c_str());
	//	SaveLog(g_log_rec, g_err_adr, "a");

	//	return 0;
	//}


	/*---此行6个，参考配置信息：网络配置参数*/
	file >> temp >> temp >> g_db_hostName >> temp >> g_db_dBName >> temp >> g_db_userName >> temp >> g_db_password >> temp >> g_db_hoster_zk >> temp;

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
	if (NULL == fpzz) 
	{
		return 0; 
	}//要返回错误代码
	fprintf(fpzz, txt); //从控制台中读入并在文本输出
	fclose(fpzz);
	fpzz = NULL;//需要指向空，否则会指向原打开文件地址  

	return 1;
}


/*
功能：保存中间鉴定图像(不实现，没有必要)
@变量
@变量
@返回值
*/
int SaveImg(IplImage *img, char *g_process_img_adr){
	/*char processPic[100] = "E:/imggj/";
	char *namePic = new char[20];
	bool flag = false;
	string xuehao = path, kaoshihao = path;
	int num_iter = sizeof(path);
	for (int iter = 0; iter < num_iter; iter++)
	{
		if (path[iter] == 'x')
		{
			flag = true;
			break;
		}
	}
	if (flag)
	{
		xuehao = xuehao.substr(27, 13);
		kaoshihao = kaoshihao.substr(40, 5);
	}
	else
	{
		xuehao = xuehao.substr(27, 12);
		kaoshihao = kaoshihao.substr(39, 5);
	}
	strcat(processPic, xuehao.c_str());
	_mkdir(processPic);
	strcat(processPic, kaoshihao.c_str());
	strcat(processPic, ".jpg");
	cvSaveImage(processPic, imggj);*/
	return 1;
}