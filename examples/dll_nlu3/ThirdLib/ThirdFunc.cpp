/* ====================================================================
 * 作者-------  支叶认知
 * 创作时间---  20220403
 * 功能-------  第三方接口示例（ThirdLib.c 定义应用程序的导出函数）
 * 运行环境---  长沙思知所提供的自然语运行环境
 */
//====================================================================

#include "ThirdBasics.h"

//=======初次调用库被执行函数=======================
void Thirdlib_Init(void *p)
{
	printf("Thirdlib_Init\n");
}

//=======结束库被调执行函数===========================
void Thirdlib_DeInit(void *p)
{
	printf("Thirdlib_DeInit\n");
}

//==========================================================
void LoadBoolInUnit(EXP_UNIT* &pUnit, int result)
{
	if(pUnit)
		BAS_CleanUnitData(pUnit);
	else
		pUnit = BAS_CreateUnit();
	pUnit->type = TYPE_NUM;
	pUnit->tval = NUM_BOOL;
	pUnit->Result = result;
}

void LoadNumInUnit(EXP_UNIT* &pUnit,INUM iNum)
{
	if(pUnit)
		BAS_CleanUnitData(pUnit);
	else
		pUnit = BAS_CreateUnit();
	pUnit->type = TYPE_NUM;
	pUnit->tval = NUM_NUM;
	pUnit->iNum = iNum;
}

void LoadDataInUnit(EXP_UNIT* &pUnit, int tval,const void *pBuf, size_t bLen)
{
	DATA_BUFSTR *pData = (DATA_BUFSTR *)gMalloc(sizeof(DATA_BUFSTR) + bLen + 1);
	memcpy(pData->pBuf, pBuf, bLen);
	pData->pBuf[bLen] = 0;
	pData->Len = bLen;
	if(pUnit)
		BAS_CleanUnitData(pUnit);
	else
		pUnit = BAS_CreateUnit();
	pUnit->type = TYPE_DATA;
	pUnit->tval = tval;
	pUnit->pBfS = pData;
}
//=============函数接口区============================
int FunTest1(EnvP pENV, EXP_UNIT* &pInOutPar)
{
	EXP_UNIT *pPar = BAS_ParsingUnit(pInOutPar);
	if (pPar == NULL) return -5;
	//---------执行模块--------------------
	LG("FunTest1\r\n");
	//--------显示所有属性---------------
	
	//--------填充返回结果------------------------
	LoadBoolInUnit(pInOutPar,TRUE);
	return 1;	//只返回一个参数
}


int FunTest2(EnvP pENV, EXP_UNIT* &pInOutPar)
{
	EXP_UNIT *pPar = BAS_ParsingUnit(pInOutPar);
	if (pPar == NULL) return -5;
	//---------执行模块--------------------
	if(pPar== NULL) return -1;	//没有输入参数不执行
	if(pPar->type != TYPE_DATA) return -1; //不是buff不执行
	LG("FunTest2 输入字符串[%s]\r\n", pPar->pBfS->pStr);


	
	//--------填充返回结果------------------------
	const char *pOutMsg = "这里是输出字符串";
	LoadDataInUnit(pInOutPar,DATA_STR,pOutMsg,strlen(pOutMsg));
	return 1;	//只返回一个参数
}

int FunTestOut3(EnvP pENV, EXP_UNIT* &pInOutPar)
{
	if (pInOutPar == NULL)
		pInOutPar = BAS_CreateUnit();	//无输入参数，就没有参数空间，所以创建参数空间来存放返回参数
	else
		BAS_CleanUnitData(pInOutPar); //有输入参数，清理参数空间，存放返回参数


	const char *pOutMsg = "输出字符串哈哈哈";
	LoadDataInUnit(pInOutPar, DATA_STR, pOutMsg, strlen(pOutMsg));	
	return 1; //返回1个参数
}

int FunSquare(EnvP pENV, EXP_UNIT* &pInOutPar)
{
	EXP_UNIT *pPar = BAS_ParsingUnit(pInOutPar);
	if (pPar == NULL) return -5;
	//---------执行模块--------------------
	if (pPar->type != TYPE_NUM) return -1;	//不是数字不能执行
	pInOutPar->iNum = pPar->iNum * pPar->iNum;
	pInOutPar->type = pPar->type;
	return 1;
}
//=====================配置==================================================
//=========函数对应表(名称,功能，使用规则，最后以NULL结束)=================
const DEF_FUNC_Tbl gFuncTbl =
{
	FUNC_TYPE_I,	1,
	1,
	"test",
	{
		"fun1",		FunTest1,
		"功能2",	FunTest2,
		"fout3",	FunTestOut3,
		"平方",		FunSquare,
		NULL,		NULL,	//结束行
	}
};
//注：调用方式为：test.fun1(参数1,参数2,参数3,...),当TbName为NULL时，表示不需要表名，直接调用函数名即可。

/*
开发者信息(JSON格式{id:var,id2:var2,....})说明：
ID 	：已注册的开发者编号（版权依据，贡献依据，收益凭证），没有可以无此项
公司	：个人开发者不需要填此项
作者	：开发者姓名
手机	：开发者手机号（当无开发者编号时，也可以作为贡献版权依据）
*/
const char sDeveloperInfo[] = \
"{\"ID\":\"00000001-0001-0001\","\
"\"Corp\":\"长沙思知\","        \
"\"Auth\":\"支叶\","             \
"\"Mob\":\"138****8888\"}";

//const char sDeveloperCert[]

//==============导出总接口：gTotalInterSet==================
extern const TOTAL_INTERFACE gTotalInterSet =
{
	sDeveloperInfo,
	NULL, //开发者证书
	{
		&gFuncTbl,
		NULL,	//结束行
	}
};




