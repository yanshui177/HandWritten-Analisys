/* 	程序名：cutName.cpp
功能：裁剪文件名
*/
#include<io.h>
#include <stdio.h>
#include<vector>
#include<iostream>
using namespace std;
#include <string.h>

int cutName(vector<string> &files){
	vector<string> files_temp;
	int num=files.size();
	int i=0;

	for(i=0;i<num;++i){
		string temp=files[i].c_str();
		temp= temp.substr(34,temp.length()-4);
		files_temp.push_back(temp);
	}

	files.clear();
	for(i=0;i<num;++i)
		files.push_back(files_temp[i].c_str());
	files_temp.clear();

	return 1;
}