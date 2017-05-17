#include "Main.h"
#include "Check.h"

using namespace std;

#define SLEEP_TIME	1000						//2000毫秒刷新一次

int main(int argc, char** argv)
{
	//监控..\Check\路径下有没有新文件
	char * path = "D:\\HWCV\\Check\\";
//	char * path = "D:\\2017.2.28\\BJJB0702\\BJJB0702\\check\\";
	vector<string> files;
	WriteToLog(GetTime());
	WriteToLog("--开始运行服务--\n");

	while(true)
	{

		//检查有没有新的文件，若有，则都在vector files中存储
		CheckFile(path, files);	


		for (int iter = 0; iter < files.size();iter++)
		{	
		//	string cmd="D:/HWCV/config/HWCV-exe ";
		//	cmd += files[iter];

		//	WinExec((char*)cmd.c_str(),SW_HIDE);
			string EE = files[iter];

			try
			{
				ShellExecute(NULL,"open",
				"HWCV-exe.exe",
				(char*)files[iter].c_str(),
				NULL,
				SW_SHOWNORMAL);
//				EE += " 可以正常运行\n";
//				WriteToLog((char*)EE.c_str());

				Sleep(SLEEP_TIME);
			}
			catch(void)
			{
				EE += " 错误\n";
				WriteToLog((char*)EE.c_str());
				Sleep(SLEEP_TIME);
				continue;
			}


		}
		files.clear();

		Sleep(SLEEP_TIME);
	}
	
	WriteToLog(GetTime());
	WriteToLog("--结束服务--\n");
	
	return 1;
}
