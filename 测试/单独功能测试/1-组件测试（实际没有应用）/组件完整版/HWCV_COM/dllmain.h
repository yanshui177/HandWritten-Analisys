// dllmain.h : 模块类的声明。

class CHWCV_COMModule : public ATL::CAtlDllModuleT< CHWCV_COMModule >
{
public :
	DECLARE_LIBID(LIBID_HWCV_COMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HWCV_COM, "{779F27F9-BF68-4742-840B-DD9A273C8CDA}")
};

extern class CHWCV_COMModule _AtlModule;
