// cHWCV.cpp : CcHWCV 的实现

#include "stdafx.h"
#include "cHWCV.h"


// CcHWCV



STDMETHODIMP CcHWCV::aspHWCV(BSTR filepath, BSTR* _arg2)
{
	// TODO:  在此添加实现代码
	//调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试
	char *fo = "H:\\HWCVDLL2.txt";
	char rec[200] = "可以调用com端口!\n";
	//char* filepath_c = (_bstr_t)filepath;
	strcat(rec, (char*)filepath);
	strcat(rec, "\n");
	FILE *fpzz3 = NULL;//需要注意
	fpzz3 = fopen(fo, "w");  //创建文件
	if (NULL == fpzz3) return NULL;//要返回错误代码
	fprintf(fpzz3, rec);
	fclose(fpzz3);
	fpzz3 = NULL;//需要指向空，否则会指向原打开文件地址
	//调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息
	*_arg2 = L"success";
	return S_OK;
}
