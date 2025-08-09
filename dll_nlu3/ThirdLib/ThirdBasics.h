/* ====================================================================
 * 作者-------  支叶认知
 * 创作时间---  20220403
 * 功能-------  语言功能基础定义
 * 运行环境---  长沙思知所提供的自然语运行环境
 */
//====================================================================
//#pragma once
#ifndef _THIRD_BASICS_
#define _THIRD_BASICS_

#include <stdio.h>
#include <stdint.h>
#include <windows.h>

//==============基础数据定义============================
typedef unsigned char   	u8;
typedef unsigned short   	u16;
typedef unsigned int   		u32;

//===================C++才能用到的内容===========================================
#ifdef __cplusplus
typedef unsigned short  	USTR;	//!< Define u16

#if defined(_WIN64) || defined(__LP64__)  
typedef double  INUM; //64位系统，双精度定义
#else
typedef float  	INUM;	
#endif

//------布尔三源定义---增加 反向(ANTI)-
#define ANTI  (-1)
/*
typedef enum
{
	FALSE	= 0,
	TRUE	= 1,
	ANTI	=-1,
}BOOL;
*/
//=======数据空间===space============
typedef enum
{
	SPACE_NULL=0,	//无
	SPACE_NAME=1,	//名称
	SPACE_POIT=2,	//指针
	SPACE_SUB=0x08,	//子集 
}SPACE_VAL;

//=======参数类型=========================
typedef enum
{
	TYPE_NULL,	//0 无
	TYPE_NUM,	//1数
	TYPE_DATA,	//2数据
	
	TYPE_FUNC,	//3C函数
	TYPE_SCR,	//4 脚本
	
	TYPE_SEPA,	//5分隔
}TYPE_VAL;
//--------类型值----------------------------
typedef enum
{
	NUM_NULL,
	NUM_BOOL,	//布尔
	NUM_NUM,	//浮点
	NUM_INT,	//整型
}TVAL_NUM;

typedef enum
{
	DATA_NULL,
	DATA_BUF,	// 连续数据
	DATA_STR,	// 字符串
}TVAL_DATA;


#pragma warning(disable : 4200)
//=================结构体申明================================
typedef struct _EXP_UNIT EXP_UNIT;
typedef struct _PAR_UNIT PAR_UNIT;
//=================函数定义================================
#define FUNC_TYPE_I					1
typedef struct _DefEnv DefEnv,*EnvP;
typedef int(*FUNC_ExpI)(EnvP,EXP_UNIT* &); //函数功能定义(环境参数,输入输出参数) 返回输入参数个数
typedef int(*FUNC_PLUS)(EnvP,EXP_UNIT*, EXP_UNIT*, EXP_UNIT*); //加强型函数功能定义(env,before,after,itself)
//==========连续字符=====================
typedef struct
{
	size_t Len;					//参数长度
	union
	{
		u8		pBuf[];	//缓冲字符号(tval==DATA_BUFF)
		char	pStr[];		//字符串(tval==DATA_STR)
	};
}DATA_BUFSTR;
//======数据基源(包括数据与逻辑关系)===============
struct _EXP_UNIT
{
	u8		space;		//空间类型，{@link SPACE_VAL}
	
	u8		type;		//参数类型，{@link TYPE_VAL}
	u8		funt;		//功能	，
	u8		tval:4;		//类型值，
	u8		fval:4;		//分类
	union
	{
		DATA_BUFSTR *pBfS;		//字符串(Type==TYPE_DATA)
		INUM iNum;				//数值 (Type==TYPE_NUM)
		intptr_t iVal;		//有符号数值(Type==NUM_INT)
		intptr_t Result;		//返回结果1和0(Type==NUM_BOOL)
		EXP_UNIT* pUNIT;		// 对应 space==SPACE_POIT或space==SPACE_SUB 时使用
	};
	union
	{
		INUM	multiple;	//倍数,为SPACE_POIT,SPACE_SUB 时有效果。
		intptr_t offset;	//偏移量
	};
	EXP_UNIT* pAttr;	//属性，也可以表关系
	//------------------------------------------------------------
	EXP_UNIT* pNext;	//下一条
};
//====================基本功能====================================================
extern void* gMalloc(unsigned size);
extern void gFree(void* p);
extern EXP_UNIT* BAS_CreateUnit(void);
extern void BAS_FreeUnitAll(EXP_UNIT* pStar);
extern void BAS_CleanUnitData(EXP_UNIT* pUnit);
extern void BAS_FreeCurrParAndNext(EXP_UNIT* pStar,int Num);
extern EXP_UNIT* BAS_FreeUNIT(EXP_UNIT* pStar,int Num);
extern EXP_UNIT* BAS_SetUnitLose(EXP_UNIT* pStar,int Num);
extern void BAS_FreeNext(EXP_UNIT* pStar,int Num);
extern void BAS_AddNext(EXP_UNIT* pStar,EXP_UNIT* pAdd);
extern EXP_UNIT* BAS_ParsingUnit(EXP_UNIT* pUNIT);
extern int BAS_GetUnitResult(EXP_UNIT* pUNIT);
extern void BAS_GetUnitResult(char *pTitle, u8 NoSpace, EXP_UNIT* pUnit);
extern int BAS_StrFun(EnvP pEnv,const char *pStrFun,EXP_UNIT* par);
extern DATA_BUFSTR* BAS_ReadFile(const char* pathName);
extern int BAS_SaveFile(const char* pathName, DATA_BUFSTR* pBfS);
extern int BAS_Input(const char *title, char *pOut, int oSize);
//------------Tcp---------------------------------------------------
extern int BAS_TcpConnect(const char* host, const char* port, int proto);
extern int BAS_TcpSend(int fd, const unsigned char* buf, size_t len);
extern int BAS_TcpRecv(int fd, unsigned char* buf, size_t len);
extern int BAS_TcpRecvTimeout(int fd, unsigned char* buf, size_t len, u32 timeout);
extern int BAS_TcpBind(const char* bind_ip, const char* port, int proto);
extern int BAS_TcpAccept(int* bind_fd, int* client_fd, void* client_ip, size_t buf_size, size_t* ip_len);
extern void BAS_TcpFree(int fd);
//-----------------------NET-------------------------------------------------------------------
typedef struct _NET_CTX NET_CTX;
extern NET_CTX* App_NetConnect(const char* pHost, const char* pPort, int proto); //-proto:0为TCP，1为UDP，|0x10为SSL---
extern int App_NetSend(NET_CTX* pNet, char* pIn, int iLen);
extern int App_NetRecv(NET_CTX* pNet, char* pOut, int oSize, int timeOutMs);
extern int App_NetDisconnect(NET_CTX* pNet);
//==========================I型函数对应结构================================================
typedef struct
{
	const char*	pFunName;		//函数名，对外名称
	const FUNC_ExpI	pFunExp;	//处理功能
}FUNC_MatchI;

typedef struct
{
	u8	type,Priority;
	u16	ver;					//接口版本
	const FUNC_MatchI ArrayI[];	//以NULL结束
}DEF_FUNC_Tbl;
//==========================对外总结构定义===============================
typedef struct
{
	const char* Info;			//开发者信息
	const char* certificate;	//开发者授权证书(未注册无证书为NULL)
	const DEF_FUNC_Tbl* gAll[];	//以NULL结束
}TOTAL_INTERFACE;
#endif
//======================日志输出=================================================
#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
	LOG_DEBUG, //显示调试信息
	LOG_INFO, //显示提示信息
	LOG_WARN, //显示警告信息
	LOG_ERROR, //显示错误信息
	LOG_NULL,	//无调试信息
} LOG_T;
typedef void (*DefOsLog)(LOG_T,const char*, ...);
typedef void(*DefOsLogHex)(LOG_T,const char*, void *, int);
extern DefOsLog OsLog;
extern DefOsLogHex OsLogHex;
#ifdef __cplusplus
}
#endif
#define LOG(t,...)						OsLog(t, ## __VA_ARGS__)
#define LOG_HEX(t,msg,pBuf,Len)		OsLogHex(t,msg,pBuf,Len)
#define LG(...)							OsLog(LOG_INFO, ## __VA_ARGS__)
#define LG_HEX(msg,pBuf,Len)			OsLogHex(LOG_INFO,msg,pBuf,Len)


#endif
