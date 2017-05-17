#include "Check.h"

char* GetTime();

/*功能：检查当前木有有无文件，若有，提取文件名，并删除此文件
@变量 path 检查文件位置
@返回值 返回检测到的变量向量
*/
int CheckFile(char* path, vector<string>& files)
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
			//如果是目录,直接返回
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
			}
			else //如果不是,加入列表 
			{
				//files.push_back(p.assign(path).append("/").append(fileinfo.name));
				files.push_back(fileinfo.name);
				remove(p.assign(path).append("\\").append(fileinfo.name).c_str());
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}

	return 0;
}


/**
功能：泻入文件日志
  */
int WriteToLog(char* str)
{
	FILE* log;
	log = fopen(LOGFILE, "a+");
	if (log == NULL) return -1;
	fprintf(log, "%s ", str);
	fclose(log);
	return 0;
}

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