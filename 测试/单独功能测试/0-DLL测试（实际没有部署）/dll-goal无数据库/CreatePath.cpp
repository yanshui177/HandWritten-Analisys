#include <iostream>

using namespace std;
/**
根据学生信息创建文件路径，用于文件读取

@变量 date 考试日期
@变量 subject 考试科目
@变量 stuNum 考号
@返回值 返回生成的文件路径
*/
string CrPath(string date, string subject, string stuNum)
{
	string temp = "Z:/"; temp += date; temp += "/";
	temp += subject.substr(0, 4); temp += "/";
	temp += stuNum; temp += ".jpg";

	return temp;
}
