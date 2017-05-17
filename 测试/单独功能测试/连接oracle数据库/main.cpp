#include <iostream>
#include <io.h>
#include <windows.h>
#include <string> 
#include <iomanip> 
#include <vector>

using namespace std;
int DbImg(string, vector<string>&, vector<string>&, vector<string>&);


void main()
{
	string num="010209400748";
	cout<<"查询的考生学号为："<<num<<endl;
	vector<string> date_vec,subject_vec,stu_num2;
	DbImg(num, date_vec, subject_vec, stu_num2);
	for (int i = 0; i < date_vec.size();i++)
	{
		cout << "考生：" << num << subject_vec[i] << " " << date_vec[i] << " " << stu_num2[i] << endl;
	}
}