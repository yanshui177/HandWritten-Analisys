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


	/*---此行6个，参考配置信息：网络配置参数*/
	file >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp;


	/*---此行5个，参考配置信息：控制参数*/
	file >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp;

	/*---此行5个，参考配置信息：数据库查询参数*/
	file >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> temp;

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
	return 1;
}


/*
功能：获取指定目录下的文件
@变量 path 路径
@变量 files 输出vector格式的文件
*/
void getFiles(string path, vector<string>& files)
{
	using namespace std;//引入整个名空间
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  

			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("/").append(fileinfo.name), files);
			} //如果不是,加入列表  
			else
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
}


/*
功能：获取指定目录下的目录
@变量 path 目录
@变量 files 返回的目录vector
@返回值 成功1失败0
*/
int getFolders(string path, vector<string>& files)
{
	using namespace std;//引入整个名空间
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;

	int i = 0;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
				printf("文件夹：%s\n", files[i].c_str());
				i++;
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
	return 0;

}


/*
功能：搜索目录
*/
int searchDir(char *path, vector<string> &dir)
{
	using namespace std;
	struct _finddata_t fa;//创建找到的结构体
	long handle;
	int flag = 0;
	char temp[100] = { 0 };
	string path_temp = path;
	//	path_temp=path_temp.substr(0,path_temp.length()-1);

	if ((handle = _findfirst(strcat(path, "*"), &fa)) == -1L)//如果不是目录的话
		return 0;

	do//是目录，先执行循环
	{
		if (fa.attrib == _A_SUBDIR && ~strcmp(fa.name, ".") && ~strcmp(fa.name, ".."))
		{
			strcat(temp, path_temp.c_str());
			strcat(temp, fa.name);

			if (flag++)
				dir.push_back(temp);
			else;

			memset(temp, 0, 100);
		}
	} while (_findnext(handle, &fa) == 0); /* 成功找到时返回0*/

	_findclose(handle);

	return 0;

}