// FirstClass.h : CFirstClass 的声明

#pragma once
#include "resource.h"       // 主符号



#include "HWCV_COM_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// CFirstClass

class ATL_NO_VTABLE CFirstClass :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFirstClass, &CLSID_FirstClass>,
	public IDispatchImpl<IFirstClass, &IID_IFirstClass, &LIBID_HWCV_COMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CFirstClass()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FIRSTCLASS)


BEGIN_COM_MAP(CFirstClass)
	COM_INTERFACE_ENTRY(IFirstClass)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(Check)(BSTR stuNum, BSTR* result);
};

OBJECT_ENTRY_AUTO(__uuidof(FirstClass), CFirstClass)
