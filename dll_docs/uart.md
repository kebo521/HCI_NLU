------

# UART Component Library uart.dll Usage Guide

Z-Language Interface Specification

------

### 1.1: Open Serial Port

| Interface  | `uopen`                      | Opens a serial port                                          |
| ---------- | ---------------------------- | ------------------------------------------------------------ |
| Parameters | `commName` `baudrate` `flag` | Port name (e.g., COM1) Baud rate Optional mode flag: - `"s"`: String mode - Default: Binary buffer mode |
| Returns    | Handle                       | Success: Port handle Failure: `false`                        |

```
hd uopen(commName, baudrate, flag) // Example: fd = uopen("com3", 9600, "s")  
```

### 1.2: Send Data

| Interface  | `usend`     | Transmits data                              |
| ---------- | ----------- | ------------------------------------------- |
| Parameters | `hd` `data` | Port handle Data to send (string or buffer) |
| Returns    | `int`       | Success: Bytes transmitted Failure: `false` |

```
int usend(hd, data) // Example: usend(fd, "\x02testdata123456789\x03")  
```

### 1.3: Receive Data

| Interface | `urecv` | Receives data                           |
| --------- | ------- | --------------------------------------- |
| Parameter | `hd`    | Port handle                             |
| Returns   | `buf`   | Success: Received data Failure: `false` |

```
buf urecv(hd) // Example: data = urecv(fd)  
```

### 1.4: Close Port

| Interface | `uclose` | Closes port                      |
| --------- | -------- | -------------------------------- |
| Parameter | `hd`     | Port handle                      |
| Returns   | `bool`   | Success: `true` Failure: `false` |

```
bool uclose(hd) // Example: uclose(fd)  
```

### 1.5: Threaded Receive

| Interface | `ucrecv` | Enables background reception     |
| --------- | -------- | -------------------------------- |
| Parameter | `hd`     | Port handle                      |
| Returns   | `bool`   | Success: `true` Failure: `false` |

```
bool ucrecv(hd) // Starts background thread that prints received data to console  
```

### 1.6: Scan Ports

| Interface | `uscan` | Discovers available ports                     |
| --------- | ------- | --------------------------------------------- |
| Parameter | `tag`   | Optional filter pattern                       |
| Returns   | `str{}` | Success: Array of port names Failure: `false` |

```
strname uscan(tag) // Examples:<br>ports = uscan() // All ports<br>fd = uopen(uscan("MI_????")) // Filtered ports  
```

### 1.7: Get C/C++ Interface

| Interface | `ugetapi` | Exports native C/C++ API |
| --------- | --------- | ------------------------ |
| Returns   | `bufApi`  | Pointer to API structure |

```
bufApi ugetapi() // Example: ugetapi()  
//----------- Structure Definition ----------------------  
typedef struct _HD_UART *PT_UART;  

typedef struct {  
    int (*scan)(char*, int, const char*);   // Scan ports  
    PT_UART (*open)(const char*, DWORD);     // Open port  
    int (*send)(PT_UART, u8*, int);          // Send data  
    int (*recv)(PT_UART, u8*, int, int);     // Receive data  
    void (*close)(PT_UART);                  // Close port  
} FT_UART_API;  

static FT_UART_API func_uart_api = {NULL};  

bool import_uart_api(void* pBuf, int size) {  
    if(size == sizeof(func_uart_api)) {  
        memcpy(&func_uart_api, pBuf, size);  
        return true;  
    }  
    return false;  
}  
```

**C Implementation Reference**:
 [Natural Language Understanding NLU - Third-party Integration](https://github.com/kebo521/HCI_NLU/dll_nlu3)