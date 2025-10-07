# 串口 组件库 uart.dll 使用说明

Z语言接口使用说明



#### 1、串口通信基本操作接口（组名"uart",用 out uart 命令可以显示全部子集接口）

```apl
---<out uart 
[uart].sub(close crecv recv send open scan getapi )
```

------



##### 1.1：打开串口

| 接口              | uart.open    | 打开串口                               |
| ----------------- | ------------ | -------------------------------------- |
| 入参              | commName     | 串口名                                 |
| 入参              | baudrate     | 波特率                                 |
| ("comx",9600,"s") | 交互参数格式 | “s”表示以字符串方式交互，默认为buf方式 |
| 返回              | 操作句柄     | 成功返回 串口句柄，失败返回 false      |

```c
hd uart.open(commName,baudrate,flag/null) // fd=uart.open("comx",9600,"s")
```



##### 1.2：串口发送数据

| 接口 | uart.send | 发送数据                              |
| ---- | --------- | ------------------------------------- |
| 入参 | hd        | uopen 成功返回的句柄                  |
| 入参 | data      | 要发送的数据（字符串或buf)            |
| 返回 | int       | 成功返回 已发送的长度，失败返回 false |

```c
int uart.send(hd,data) // uart.send(fd,"\x02testdata123456789\x03")
```



##### 1.3：串口接收数据

| 接口 | uart.recv | 接收数据                                |
| ---- | --------- | --------------------------------------- |
| 入参 | hd        | uopen 成功返回的句柄                    |
| 返回 | buff      | 成功返回 已经收到的数据，失败返回 false |

```c
buf uart.recv(hd) // data=uart.recv(fd)
```



##### 1.4：串口关闭

| 接口 | uart.close | 关闭串口                      |
| ---- | ---------- | ----------------------------- |
| 入参 | hd         | uopen 成功返回的句柄          |
| 返回 | bool       | 成功返回 true，失败返回 false |

```c
bool uart.close(hd) // uart.close(fd)
```



##### 1.5：扩展线程接收

| 接口 | uart.crecv | 线程接收                      |
| ---- | ---------- | ----------------------------- |
| 入参 | hd         | uopen 成功返回的句柄          |
| 返回 | bool       | 成功返回 true，失败返回 false |

```c
bool uart.crecv(hd) // uart.crecv(fd) 创建一个线程独立收串口数据，将收到的数据直接打印到平台，键盘输入数据回转车可以发送数据，相当于时实交互。
```



##### 1.6：扫描串口

| 接口 | uart.scan | 扫描本机所有串口返回符合tag特征的串口名           |
| ---- | --------- | ------------------------------------------------- |
| 入参 | tag       | 特征名或不输入                                    |
| 返回 | str{}     | 成功返回 串口名(多个为给一个集合)，失败返回 false |

```c
strname uart.scan(tag/null) // 
/* sname=uart.scan() 返回机器上的所有串口我赋值给sname,如“COM1 COM2 COM5”
   fd=uart.open(uscan("MI_????"))  ;
```



##### 1.7：获取C/C++程序使用的接口

| 接口 | uart.getapi | 从库中导出能在C/C++中使用的接口 |
| ---- | ----------- | ------------------------------- |
| 返回 | buf         | 返回接口地址组                  |

```c
bufApi uart.getapi() // uart.getapi();
//-----------结构定义----------------------  
typedef struct _HD_UART *PT_UART;
typedef struct
{
	int (*scan)(char*,int,const char*);	//(char* pOutName, int oSize,const char *pTag)->num
	PT_UART (*open)(const char*,DWORD); //(const char* pComName,DWORD BaudRate) ->pFd
	int (*send)(PT_UART,u8*, int);	//(PT_UART pFd,u8* pBuf, int bLen)->slen
	int (*recv)(PT_UART,u8*, int,int);	//(PT_UART pFd,u8* pBuf, int bSize,int timeOutMs)->rlen
	void (*close)(PT_UART);	//(PT_UART pFd)
} FT_UART_API;   
static FT_FONT_API func_uart_api={NULL}; 

bool import_uart_api(void* pBuf,int size)
{
	if(size == sizeof(func_uart_api)) {
		memcpy(&func_uart_api,pBuf,size);
		return true;
	}
	return false;
}
    
```



C 程序引用方法定义基础代码：**[自然语言理解NLU-第三方功能接入](https://gitee.com/kebo521/nlu3)**