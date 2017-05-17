/*
实现文件：DBop.cpp 数据库操作实现文件
*/
#include "DBop.h"

/*本地的全局变量*/

_ConnectionPtr	p_conn;			/*全局变量 连接对象*/
_RecordsetPtr	p_recordset;	/*全局变量 记录集对象*/
_CommandPtr		p_cmd;			/*全局变量 操作集对象*/
string			str_conn;		/*全局变量 连接字符串设置*/


/**
功能：	查询所有学生的学号，将所有的指定位置的数据库信息(学号)全部存储在名为stu的vector<string>型的变量中

@变量 stu 学生学号存储
@返回值 成功1 失败0
*/
int DbStu(vector<string>& stu)
{
	/*字符转换，方便使用*/
	string userName(g_db_userName.c_str());
	string password(g_db_password.c_str());
	string hostName(g_db_hostName.c_str());
	string dBName(g_db_dBName.c_str());

	//连接字串设置	//因为strConn是全局变量，因此仅仅初始化一次
	str_conn = "Provider=OraOLEDB.Oracle";
	str_conn += ";Persist Security Info = true";
	str_conn += ";User ID = ";	//==================//	
	str_conn += userName;		//===仅初始化一次===//
	str_conn += ";Password=";	//==================//
	str_conn += password;
	str_conn += ";Data Source = (DESCRIPTION = (ADDRESS = (PROTOCOL = TCP)";
	str_conn += "(HOST=";
	str_conn += hostName;
	str_conn += ")(PORT=1521))(CONNECT_DATA=";
	str_conn += "(SERVICE_NAME=";
	str_conn += dBName;
	str_conn += ")))";

	::CoInitialize(NULL);//初始化com组件

	//连接数据库，并执行sql查询语句	【必须要用try catch捕获异常】
	try{
		p_conn.CreateInstance("ADODB.Connection");//创建连接
		p_recordset.CreateInstance("ADODB.Recordset");//创建结果集,也就是实例化
		p_cmd.CreateInstance("ADODB.Command");

		p_conn->CursorLocation = adUseClient; //存储过程同时返回记录集和返回值
		p_conn->Open(_bstr_t(str_conn.c_str()), _bstr_t(userName.c_str()), _bstr_t(password.c_str()), adConnectUnspecified);
		p_cmd->ActiveConnection = p_conn;

		//SELECT KS_ZKZ FROM ZK.V_BYSQ_BJSH_JQ_KS
		//SELECT DISTINCT(KS_ZKZ2) FROM ZK.T_BYSQ_KS_KC WHERE KSSJ BETWEEN '200907' AND '201510'
		//SELECT * FROM ZK.T_BYSQ_KS_KC WHERE (SUBSTR(KS_ZKZ2,1,2) = '02' OR SUBSTR(KS_ZKZ2,1,2) = '03')
		//SELECT KS_ZKZ2 FROM ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' AND (SUBSTR(KS_ZKZ2,1,2) = '02') AND BJSH_JG_JQ IS NULL GROUP BY KS_ZKZ2 HAVING COUNT(KS_ZKZ2)>1
		/*HRESULT hr1 = pRecordset->Open("SELECT KS_ZKZ FROM ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' AND (SUBSTR(KS_ZKZ2,1,2) = '02') AND BJSH_JG_JQ IS NULL GROUP BY KS_ZKZ HAVING COUNT(KS_ZKZ)>1",*/


		/*构造查询语句*/
		int zong_flag = g_db_qurry_zone.length();
		int num_flag = g_db_qurry_stu_num.length();
		int date_flag = g_db_qurry_start.length();

		string str_qurry = "SELECT KS_ZKZ FROM YANNSY.T_BYSQ_KS_KC WHERE KSSJ between ";
		str_qurry += g_db_qurry_start;
		str_qurry += " and ";
		str_qurry += g_db_qurry_end;

//		cout<<str_qurry.c_str()<<endl;
		if (num_flag - 1)//长度大于1，就是需要查询学号
		{
			str_qurry += "AND KS_ZKZ = ";
			str_qurry += g_db_qurry_stu_num;
		}
		else//不需要查询单个学号才会有区域的作用范围
		{
			if ((zong_flag - 1))//长度大于1,就是需要查询区域,且查询时间
			{
				str_qurry += " AND(SUBSTR(KS_ZKZ2, 1, 2) = ";
				str_qurry += g_db_qurry_zone;
				str_qurry += ")";
			}
		}
		if (g_db_qurry_all)
		{
			str_qurry += " AND BJSH_JG_JQ IS NULL";
		}
		str_qurry += " GROUP BY KS_ZKZ HAVING COUNT(KS_ZKZ)>1";
		_variant_t _vstr_qurry(str_qurry.c_str());/* 转换string为_variant_t */



		/*查询*/
		HRESULT hr1 = p_recordset->Open(_vstr_qurry,
			p_conn.GetInterfacePtr(),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		if (!(SUCCEEDED(hr1))){ exit(-1); }//读取不成功，直接退出程序

		int count_exit = 10;
		do
		{//读取成功，将每一行存到vector的stu末尾
			stu.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("KS_ZKZ"))->GetValue()));
			p_recordset->MoveNext();//移到下一条
		} while (!p_recordset->EndOfFile && count_exit--);//条件是没有到所有记录的末尾
	}
	catch (_com_error e){
		cout << "<提取学号(数据库):>查询失败--" << endl;
		cout<<e.Error()<<" "<<e.ErrorMessage()<<" "<<e.ErrorInfo()<<endl;
	}
	/*=================================================================================================*/

	//3、关闭查询====//执行读取完毕后要关闭连接
	try	{ ::CoUninitialize(); }
	catch (_com_error e){ /*cout << "<提取学号:关闭失败-->"  << e.ErrorInfo() << endl;*/ }

	cout<<"查询完毕"<<endl;
	return 1;
}