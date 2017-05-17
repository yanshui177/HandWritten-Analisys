#include "Main.h"
#include "Check.h"


using namespace std;
int main(int argc, char** argv)
{
	//监控..\Check\路径下有没有新文件
	char * path = "./Check/";
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

			try{
				ShellExecute(NULL,"open",
					"HWCV-exe.exe",
					(char*)files[iter].c_str(),
					NULL,
					SW_SHOWNORMAL);
			}catch(exception e)
			{
			
			}
		}
		files.clear();

		Sleep(SLEEP_TIME);
	}
	
	WriteToLog(GetTime());
	WriteToLog("--结束服务--\n");
	
	return 1;
}
