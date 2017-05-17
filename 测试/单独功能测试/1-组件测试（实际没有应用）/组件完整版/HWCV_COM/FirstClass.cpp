// FirstClass.cpp : CFirstClass 的实现

#pragma once
#include "stdafx.h"
#include "FirstClass.h"
#include <windows.h>
#include <iostream>
#include <dos.h>
#include <stdio.h>
#include <comdef.h>


// CFirstClass


int _Check(char *fpname1, char *dest);

STDMETHODIMP CFirstClass::Check(BSTR stuNum, BSTR* result)
{
	// TODO:  在此添加实现代码
	/*转换num格式*/
	_bstr_t num = stuNum;
	char* num_c = num;

	// TODO:  在此添加实现代码
	//调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试
	char *fo = "D:\\HWCV_COM_log.txt";
	char rec[200] = "可以调用com端口!\n";
	strcat(rec, num_c);
	strcat(rec, "\n");
	FILE *fpzz3 = NULL;//需要注意
	fpzz3 = fopen(fo, "a");  //创建文件
	if (NULL == fpzz3) return NULL;//要返回错误代码
	fprintf(fpzz3, rec);
	fclose(fpzz3);
	fpzz3 = NULL;//需要指向空，否则会指向原打开文件地址
	//调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息调试信息

	/* 开始调用HWCV.dll */
	char* stu_p = num;
	char* out = new char[100];

	///*需要把HWCV.dll放到同同一个目录下面*/
	//HINSTANCE   hDllInst = LoadLibrary(L"HWCV.dll");
	//if (hDllInst)
	//{
	//	/*定义实例化的接口*/
	//	typedef char*(WINAPI *HWCV)(char*, char*);
	//	HWCV   hwcv = NULL;   //hwcv 函数别名 

	//	/*获取线程*/
	//	hwcv = (HWCV)GetProcAddress(hDllInst, "HWCV");

	//	if (hwcv)
	//	{
	//		char* resu = hwcv(stu_p, out);
	//		*result = (_bstr_t)resu;
	//	}

	//	FreeLibrary(hDllInst);
	//}
	//

	_Check(stu_p, out);
	return S_OK;
}
