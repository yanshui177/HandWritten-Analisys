/*
实现文件：DBop.cpp 数据库操作实现文件
*/
#include "DBop.h"
#include "path.h"

/*本地的全局变量*/

_ConnectionPtr	p_conn;			/*全局变量 连接对象*/
_RecordsetPtr	p_recordset;	/*全局变量 记录集对象*/
_CommandPtr		p_cmd;			/*全局变量 操作集对象*/
string			str_conn;		/*全局变量 连接字符串设置*/


/**
程序功能：	根据string类的stu【存储学号】，搜索出所有此人的考试信息,并分别存储在不同的变量中

@变量 stuNum 学号
@变量 date<vector>	考试时间
@变量 subject<vector> 考试科目
@变量 stuNum<vector> 考号
@返回值 成功1 失败0
*/
int DbImg(string stuNum, vector<string>& dateVec, vector<string>& subjectVec, vector<string>& stuNum2)//搜寻图片
{
	/*字符转换，方便使用*/
	string  userName(g_db_userName.c_str());
	string  password(g_db_password.c_str());
	string  hostName(g_db_hostName.c_str());
	string  dBName(g_db_dBName.c_str());

//	cout<<g_db_userName.c_str()<<endl;
//	cout<<g_db_password.c_str()<<endl;
//	cout<<g_db_hostName.c_str()<<endl;
//	cout<<g_db_dBName.c_str()<<endl;

	/*创建链接描述符*/
	//Provider=OraOLEDB.Oracle.1;Persist Security Info = true;User ID = BJSH;Password=bjshadmin;Data Source = (DESCRIPTION = (ADDRESS = (PROTOCOL = TCP)(HOST=192.168.200.97)(PORT=1521))
	//(CONNECT_DATA=(SERVICE_NAME=purple)))",
	str_conn = "Provider=OraOLEDB.Oracle.1;Persist Security Info = true;User ID = ";	
	str_conn += userName;		//===仅初始化一次===//
	str_conn += ";Password=";	//==================//
	str_conn += password;
	str_conn += ";Data Source = (DESCRIPTION = (ADDRESS = (PROTOCOL = TCP)(HOST=";
	str_conn += hostName;
	str_conn += ")(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=";
	str_conn += dBName;
	str_conn += ")))";

	//构造查询语句				下句注释是sql语句，需要构造成这种类型
	/*select KS_ZKZ, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' and KS_ZKZ = 010207203867*/
	/*string  sql = "select KS_ZKZ2, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201504' AND KS_ZKZ = ";*/
	// select KS_ZKZ, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' and KS_ZKZ = 010214100225
	//"select KS_ZKZ, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' and KS_ZKZ = 010214100225",
	string sql = "select KS_ZKZ2, KSSJ, TJ_KC_DM from ";
	sql += g_db_hoster_zk;
	sql += ".T_BYSQ_KS_KC WHERE KSSJ between ";
	sql += g_db_qurry_start;
	sql += " and ";
	sql += g_db_qurry_end;
	sql += " AND KS_ZKZ =";
	sql += stuNum.c_str();

	_bstr_t _vstr_sql(sql.c_str());/* 转换string为_variant_t */
	::CoInitialize(NULL);//初始化com组件

	/*创建、打开连接*/
	try{
		p_conn.CreateInstance("ADODB.Connection");//创建连接
		p_recordset.CreateInstance("ADODB.Recordset");//创建结果集,也就是实例化


		p_conn->CursorLocation = adUseClient; //存储过程同时返回记录集和返回值
		p_conn->Open(_bstr_t(str_conn.c_str()),
		//p_conn->Open("Provider=OraOLEDB.Oracle.1;Persist Security Info = true;User ID = BJSH;Password=bjshadmin;Data Source = (DESCRIPTION = (ADDRESS = (PROTOCOL = TCP)(HOST=192.168.200.97)(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=purple)))",
			_bstr_t(userName.c_str()),
			_bstr_t(password.c_str()),
			adConnectUnspecified);
		


		cout << _vstr_sql << endl;
		SaveLog(_vstr_sql, "D:/HWCV/1/txt", "a");
	//	SaveLog((char*)str_conn.c_str(), g_log_adr, "a");
		HRESULT hr = p_recordset->Open(_bstr_t(_vstr_sql),//执行sq语句，查询一个学生的所有考试信息
		//HRESULT hr = p_recordset->Open("select KS_ZKZ, KSSJ, TJ_KC_DM from ZK.T_BYSQ_KS_KC WHERE KSSJ between '200907' and '201510' and KS_ZKZ = 010214100225",
			p_conn.GetInterfacePtr(),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
//		cout<<"count:"<<p_recordset->RecordCount <<endl;
		//将结果集输出到三个vector变量中
		if (p_recordset->RecordCount < 1)//结果集为空
		{
			return 0;//没有信息，直接跳过这个人
		}
		do{ //将结果集输出到三个vector变量中
			string comp = (string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("KS_ZKZ2"))->GetValue());
			if (!strcmp(comp.substr(0, 1).c_str(), "4") || !strcmp(comp.substr(0, 1).c_str(), "9")) //将4，9 开头的考号（无图像）直接处理掉
				continue;
			dateVec.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("KSSJ"))->GetValue()));
			subjectVec.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("TJ_KC_DM"))->GetValue()));
			stuNum2.push_back((string)(_bstr_t)(p_recordset->Fields->GetItem(_variant_t("KS_ZKZ2"))->GetValue()));
			p_recordset->MoveNext();
		} while (!p_recordset->EndOfFile);
	}
	catch (_com_error e)
	{
		return 0;
//		printf("%x", e.Error());
		cout<<"Failed"<<endl;
	}

	/*关闭查询*/
	::CoUninitialize(); 

	return 1;
}



/**
程序功能：	更新学生数据库信息,根据学生的鉴定结果，将结果输出到数据库中

@变量 stuNum：学号
@变量 subject：考试科目
@变量 flagCheat：作弊标记
@返回值 成功1失败0
*/
int DbUpdate(string stuNum,	vector<string> dateVec,	vector<string> subjectVec,	vector<string> stuNum2,	vector<string> flagVec)
{
	/*字符转换，方便使用*/
	string  userName(g_db_userName.c_str());
	string  password(g_db_password.c_str());
	string  hostName(g_db_hostName.c_str());
	string  dBName(g_db_dBName.c_str());

	/*更新字串设置*/
	int count = subjectVec.size();

	vector<string> sqlKC; //课程表：作弊第一字段
	int ci = 0;	//循环
	string flag = "0";
	/*构造更新语句--KC表的更新 */
	for (ci = 0; ci < count; ++ci)
	{
		if(flagVec[ci]=="1") // 此人若有作弊嫌疑的图像，就认定此人为作弊嫌疑
			flag = "1";

		/*作弊的*/
		string  sqlKC1 = "UPDATE ";
		sqlKC1 += g_db_hoster_zk;
		sqlKC1 += ".T_BYSQ_KS_KC SET BJSH_JG_JQ =";//天津_课程_代码	
		sqlKC1 += flagVec[ci].c_str();
		sqlKC1 += " WHERE KS_ZKZ2=";
		sqlKC1 += stuNum2[ci].c_str();
		sqlKC1 += " AND TJ_KC_DM=";
		sqlKC1 += subjectVec[ci].c_str();
		sqlKC1 += " AND KSSJ=";
		sqlKC1 += dateVec[ci].c_str();
		sqlKC1 += " AND  KS_ZKZ=";
		sqlKC1 += stuNum.c_str();

		sqlKC.push_back(sqlKC1);
	}
	/* 更新语句--视图更新 */
	string sqlView = "UPDATE YANNSY.V_BYSQ_BJSH_JQ_KS SET BJSH_JG_JQ=";
	sqlView += flag;
	sqlView += "WHERE KS_ZKZ = ";
	sqlView += stuNum;
	::CoInitialize(NULL);//初始化com组件

	/*更新数据库表*/
	try{
		p_conn.CreateInstance("ADODB.Connection");//创建连接
		p_recordset.CreateInstance("ADODB.Recordset");//创建结果集,也就是实例化
		p_cmd.CreateInstance("ADODB.Command");

		p_conn->CursorLocation = adUseClient; //存储过程同时返回记录集和返回值
		p_conn->Open(_bstr_t(str_conn.c_str()), _bstr_t(userName.c_str()), _bstr_t(password.c_str()), adConnectUnspecified);
		p_cmd->ActiveConnection = p_conn;

		for (ci = 0; ci < count; ++ci)
		{
			p_recordset->Open(_bstr_t(sqlKC[ci].c_str()),//更新第二条
				p_conn.GetInterfacePtr(),
				adOpenStatic,
				adLockOptimistic,
				adCmdText);
		}
		p_recordset->Open(_bstr_t(sqlView.c_str()),//更新第二条
			p_conn.GetInterfacePtr(),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);		
	}
	catch (_com_error e){ return 0; cerr << "Err:"; }

	/*关闭查询*/
	::CoUninitialize();
	
	return 1;
}