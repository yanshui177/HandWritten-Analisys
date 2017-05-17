#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int read_scanf(const string &filename,const int &cols,vector<double *> &_vector){
// 功能：将filename 中的数据（共cols列）读取到_vector中，_vector可视为二维数组
	FILE *fp=fopen(filename.c_str(),"r");//打开并读取文件
	bool flag=true;
	int i=0;
	
//	printf("--read_scanf--");
	if(!fp){ cout<<"File open error!\n"; return 0; }
	while(flag){
		double *point=new double[cols];
		for(i=0;i<cols;i++){ //读取数据，存在_vector[cols]中
			if(EOF==fscanf(fp,"%lf",&point[i])) { 
				flag=false;break; 
			}
			if(EOF==fgetc(fp)) { 
				flag=false;i++;break;
			}
		}
		if(cols==i) 
			_vector.push_back(point);
	}
	fclose(fp);
	return 1;
}