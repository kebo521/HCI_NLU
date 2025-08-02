# UI 组件库 ui.dll 使用说明

Z语言接口使用说明



### 1：基础接口

##### 1.1：获取图像数据

| 接口 | gmap     | 获取图像数据                      |
| ---- | -------- | --------------------------------- |
| 入参 | pathName | 文件路径名                        |
| 返回 | mapdata  | 成功返回 图形数据，失败返回 false |

```c
buf gmap(pathName) // mapdata=gmap("test.png")
```



##### 1.2：保存图像数据

| 接口 | smap     | 将图像数据存入文件                        |
| ---- | -------- | ----------------------------------------- |
| 入参 | pathName | 文件路径名                                |
| 入参 | mapdata  | 图形数据                                  |
| 返回 | int      | 成功返回 所存文件数据长度，失败返回 false |

```c
int smap(pathName,mapdata) // smap("test2.png",mapdata) 
```



##### 1.3：显示图像数据

| 接口 | dmap    | 在显示屏上创建窗口显示图像数据 |
| ---- | ------- | ------------------------------ |
| 入参 | mapdata | 图形数据                       |
| 返回 | bool    | 成功返回 true，失败返回 false  |

```c
bool dmap(mapdata) // dmap(mapdata)  or   dmap(gmap("test.png"))
```



### 2：高级接口

[^（增加多窗口功能，滚轮功能，光标设置功能）]: 

##### 2.1：打开画窗

| 接口 | openwd | 在显示屏上 创建并显示画窗         |
| ---- | ------ | --------------------------------- |
| 入参 | w      | 画窗高度                          |
| 入参 | h      | 画窗宽度                          |
| 入参 | name   | 窗口名称                          |
| 返回 | fd     | 成功返回 画窗句柄，失败返回 false |

```c
bool openwd(w,h,name) // fd=openwd(640,480,"test") 
```



##### 2.2：关闭画窗

| 接口 | closewd | 关闭openwindow打开的画窗      |
| ---- | ------- | ----------------------------- |
| 入参 | fd      | 窗口句柄                      |
| 返回 | bool    | 成功返回 true，失败返回 false |

```c
bool closewd(fd) // closewd(fd) 
```



##### 2.3：填充画窗

| 接口 | fillwd | 将指定颜色填充到画窗                                         |
| ---- | ------ | ------------------------------------------------------------ |
| 入参 | fd     | 窗口句柄                                                     |
| 入参 | colour | 填充色彩,参数16进制格式为 0xRRGGBB（如需要更强大控制：0xaaRRGGBB,aa为透明度，00不透明） |
| 入参 | flag   | 当此参数不存在时，只填充不显示<br />（当aa>0时，flag==1色彩添加 (256-aa)/256,当flag==-1 色彩减少，2与-2对应以上的显示） |
| 返回 | bool   | 成功返回 true，失败返回 false                                |

```c
bool fillwd(fd,colour,flag) // fillwd(fd,0xFF0000,2) 画窗为全红；fillwd(fd,0x800000FF,2) 画窗增加50%蓝色
```



##### 2.4：绘制画窗

| 接口 | pushwd   | 将图像数据填入画窗并显示                |
| ---- | -------- | --------------------------------------- |
| 入参 | fd       | 窗口句柄                                |
| 入参 | mapdata  | 图形数据（以上 gmap 获取的图像数据）    |
| 入参 | left,top | 起点位置，当参数不存在时，默认0,0起点。 |
| 返回 | bool     | 成功返回 true，失败返回 false           |

```c
bool pushwd(fd,mapdata,left,top) 
// pushwd(fd,mapdata) 在起点绘制mapdata图形；pushwd(fd,mapdata,20,10) 以20,10为起点绘制mapdata图形
```



##### 2.5：备份画窗

| 接口 | backupwd     | 备份当前画窗图像数据                                         |
| ---- | ------------ | ------------------------------------------------------------ |
| 入参 | fd           | 窗口句柄                                                     |
| 入参 | x,y,w,h      | 对应用画窗上的图形区域，当这组参数不存时备份整个画窗存于内部 |
| 返回 | mapdata/bool | 当有区域参数时成功返回mapdata，当没有区域参数时成功返回true，所有的失败返回false |

```c
bool backupwd(fd) \ mapdata backupwd(fd,x,y,w,h)
// backupwd(fd) 备份整个画窗存于内部；
// md=backupwd(fd,20,10,80,100) 以20,10为起，在当前画窗上取80*100的mapdata图形数据，
// 前面返回的md参数可以用于pushwd，也可以用于smap输出图片文件
```



##### 2.6：恢复画窗

| 接口 | recoverywd | 将之前的内部备份数据恢复到当前画窗并显示             |
| ---- | ---------- | ---------------------------------------------------- |
| 入参 | fd         | 窗口句柄                                             |
| 入参 | x,y,w,h    | 对应用画窗上的恢复区域，当这组参数不存时恢复整个画窗 |
| 返回 | bool       | 成功返回true，失败返回false                          |

```c
bool recoverywd(fd) \ bool recoverywd(fd,x,y,w,h)
//（执行recoverywd 前，先要执行一次 backupwd(fd)）
// recoverywd(fd) 恢复整个画窗；recoverywd(fd,20,10,80,100) 以20,10为起，恢复画窗上80*100的区域
```



##### 2.7：保存画窗

| 接口 | savewd  | 将当前画窗数据保存在图片文件 |
| ---- | ------- | ---------------------------- |
| 入参 | fd      | 窗口句柄                     |
| 入参 | mapname | 图片文件名                   |
| 返回 | bool    | 成功返回1，失败返回其它      |

```c
bool savewd(fd,mapname)
// savewd(fd,"mapwd.png")  // 将fd画窗图形数据保存到mapwd.png文件中
```



##### 2.8：设置光标样式

| 接口 | pushwd | 将图像数据填入画窗并显示                 |
| ---- | ------ | ---------------------------------------- |
| 入参 | fd     | 窗口句柄                                 |
| 入参 | index  | 光标参数（32649手指指针，32512普通指针） |
| 返回 | bool   | 成功返回 true，失败返回 false            |

```c
bool cursorwd(fd,index) 
// cursorwd(fd,32649) 手指指针；cursorwd(fd,32512) 普通指针
```



##### 2.9：获取图形窗口底层接口

| 接口 | getwd       | 获取图形窗口底层接口（相比openwd不需要通过Y语言，只接在C语言内部创建窗口） |
| ---- | ----------- | ------------------------------------------------------------ |
| 返回 | UI_FuncBase | 返回内部接口UI_FuncBase数据                                  |

```
UI_FuncBase getwd() //获取图形底层接口，用于C/C++直接开发，UI_FuncBase 定义参照《C程序引用方法定义2》
```



##### 2.10：获取图形窗口控制信息

| 接口 | pullwd         | 获取图形窗口控制信息，以便在其它库中直接用C程序控制窗口      |
| ---- | -------------- | ------------------------------------------------------------ |
| 入参 | fd             | 窗口句柄                                                     |
| 返回 | UI_FuncSynPlus | 成功UI_FuncSynPlus数据（参考以下：《C 程序引用方法定义2》），失败返回 false |

```c
UI_FuncSynPlus pullwd(fd) //如在以下示例实现getuibase功能，在支叶对话窗口输入：getuibase(pullwindow());
```

```c
//=====================《C 程序引用方法定义2》=============================
//先下载 “第三方功能接入”代码，在代码中添加下面内容，编译输入dll文件，在支叶中用loadlib加载此dll文件。
typedef struct _WindowBase WindowBase;
//================按键与鼠标功能回调函数定义=========================================
typedef void (*FUNC_MouseLdown)(int x, int y); //左击 x,y 在窗体上的坐标
typedef void (*FUNC_MouseRdown)(int x, int y); //右击 x,y 在窗体上的坐标
typedef void (*FUNC_MouseMove)(int type, int x, int y); //type = 0 ,只是移动，type=1 按左键移动，type=2，按右键移动
typedef void (*FUNC_MouseWheel)(int updown); //正数向下，负数向上
typedef void (*FUNC_Keyboard)(int down, int key, int timems); //键盘l输入回调，down为true按下，

//========================图形数据结构定义=====================================
//BEGIN_C_DECLS
typedef struct {
	BYTE b;
	BYTE g;
	BYTE r;
	BYTE a;
} rgba_t;

typedef union {
  rgba_t 	t;
  DWORD		rgba;
}bitmap_trgb;

typedef struct{
	DWORD w;
	DWORD h;
	bitmap_trgb* data;
} bitmap_t;

//==================  pullwindow 返回结构定义========================
typedef struct
{
	void* fd;
	WindowBase* (*LockWindow)(void* fd); //用于ui操作锁，避免信息不同步问题,当返回NULL时，窗口已经被释放
	bitmap_t ui;
	void (*push)(WindowBase* pWd);			//推送屏显示，
	void (*loadKeyMouse)(WindowBase* pWd,FUNC_Keyboard pKeybd, FUNC_MouseLdown pLdow, FUNC_MouseRdown pRdown, FUNC_MouseWheel pWheel, FUNC_MouseMove pMove); //按键与鼠标回调
	void (*UnLockWindow)(WindowBase* pWd);//解除锁
}UI_FuncSynPlus;

//在代码中添加画窗操作参数tSysBaseUi
UI_FuncSynPlus tSysBaseUi = { 0 }; 

//=====下载“自然语言理解NLU-第三方功能接入” https://gitee.com/kebo521/nlu3
void Keyboard(int down, int key, int timems)
{
    if(down) { //有按键按下
        //key,timems      
    }
    else {
        if(key == 0) {	
            //窗口关闭，bitmap_t ui已经释放，后面不能再往 ui.data 写数据       
        }
        
        
    }
}
//----如果需要鼠标功能定义以下函数（根据需求选定）-----------------
void MouseLdown(int x, int y) //左击 x,y 在窗体上的坐标
{
	//处理鼠标左击代码
}
void MouseRdown(int x, int y) //右击 x,y 在窗体上的坐标
{
	//处理鼠标右击代码
}
void MouseMove(int type, int x, int y) //type = 0 ,只是移动，type=1 按左键移动，type=2，按右键移动
{
	//处理鼠标移动代码
}
void MouseWheel(int updown) 	//正数向下，负数向上
{
	if(updown > 0) {   
    }
	else {   
    }
}
//----------Y语言引用函数定义---------------------------------
int FunPullUiBase(EnvP pENV, EXP_UNIT*& pInOutPar)	//(&UiBase)
{
	EXP_UNIT* pData = BAS_ParsingUnit(pInOutPar);
	if (pData == NULL || pData->type != TYPE_DATA || pData->tval != DATA_BUF) return -5;
	if (pData->pBfS->Len < sizeof(UI_FuncSyn)) {
		LoadBoolInUnit(pInOutPar, false);
		return 1;
	}
	UI_FuncSynPlus* pSyn = (UI_FuncSynPlus*)pData->pBfS->pBuf;
	tSysBaseUi.ui.fd = pSyn->fd;
	tSysBaseUi.LockWindow = pSyn->LockWindow;
	tSysBaseUi.UnLockWindow = pSyn->UnLockWindow;
	tSysBaseUi.ui.w = pSyn->ui.w;
	tSysBaseUi.ui.h = pSyn->ui.h;
	tSysBaseUi.ui.data = pSyn->ui.data;  //后面通过 tSysBaseUi.ui.data 修改显示内容
	tSysBaseUi.push = pSyn->push; //后面 通过 执行 ：tSysBaseUi.push(pWd)推动显示刷新
	//------需要键盘或鼠标功能需要执行回调反向加载---------------
	WindowBase* pWd = tSysBaseUi.LockWindow(tSysBaseUi.fd);
	if(pWd) {
		(*pSyn->loadKeyMouse)(pWd,Keyboard,MouseLdown, MouseRdown, MouseMove);
		tSysBaseUi.UnLockWindow(pWd);
		LoadBoolInUnit(pInOutPar, true);
	}
	else {
		LoadBoolInUnit(pInOutPar, false);    
	}
	//-----------------------------------------------------
	return 1;	//只返回一个参数
}
/* 全窗口刷新示例
	WindowBase* pWd = tSysBaseUi.LockWindow(tSysBaseUi.fd);//检查与锁定窗口
	if (pWd == NULL) return -1; //窗口不存了，直接返回
	register bitmap_trgb* pIn = tSysBaseUi.ui.data;
	register int max = tSysBaseUi.ui.w * tSysBaseUi.ui.h;
	while (max--) {
		pIn->t.r = 255;
		pIn->t.g = 255;
		pIn->t.b = 255;
		//pIn->rgba = 0xFFFFFF;
		pIn++;
	}
	tSysBaseUi.push(pWd); //推送刷新
	tSysBaseUi.UnLockWindow(pWd); //解除窗口锁
*/
//-------------将 FunPullUiBase 放入gFuncTbl引用表-----------------
const DEF_FUNC_Tbl gFuncTbl =
{
	FUNC_TYPE_I,	1,
	1,
	{
		......
		"getuibase",	FunPullUiBase,
		NULL,			NULL,	//结束
	}
};

//====================底层画布窗口接口（开放）================================================
typedef struct
{
	void* (*CreateWd)(int, int, const char*); //CreateWindow(WORD width, WORD height, const char* pName);
	int (*PullUi)(void*, UI_FuncSyn*); //(void* fd, UI_FuncSyn* pUiSyn)
	int (*CloseWd)(void*);	//CloseWindow(void* fd);
}UI_FuncBase;

loadwdapi(getwd()); //三方库实现loadwdapi来接受UI_FuncBase数据。同：pullwd 方式

```

完成以上函数编译，支叶中loadlib加载，先创建窗口fd=openwd(640,480,"test") ，然后就可以使用getuibase(pullwd(fd)) 获得UI的操作参数。

##### C 程序引用方法定义基础代码：**[自然语言理解NLU-第三方功能接入](https://gitee.com/kebo521/nlu3)**