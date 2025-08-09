------

# UI Component Library ui.dll Usage Guide

Z-Language Interface Specification

------

### 1: Basic Interfaces

##### 1.1: Get Image Data

| Interface | `gmap`     | Retrieves image data                 |
| --------- | ---------- | ------------------------------------ |
| Parameter | `pathName` | File path                            |
| Returns   | `mapdata`  | Success: image data Failure: `false` |

```
buf gmap(pathName) // Example: mapdata = gmap("test.png")  
```

##### 1.2: Save Image Data

| Interface  | `smap`               | Saves image data to file                  |
| ---------- | -------------------- | ----------------------------------------- |
| Parameters | `pathName` `mapdata` | File path Image data                      |
| Returns    | `int`                | Success: saved file size Failure: `false` |

```
int smap(pathName, mapdata) // Example: smap("test2.png", mapdata)  
```

##### 1.3: Display Image Data

| Interface | `dmap`    | Displays image in a window       |
| --------- | --------- | -------------------------------- |
| Parameter | `mapdata` | Image data                       |
| Returns   | `bool`    | Success: `true` Failure: `false` |

```
bool dmap(mapdata) // Example: dmap(mapdata) OR dmap(gmap("test.png"))  
```

------

### 2: Advanced Interfaces

*^(Supports multi-window, scroll wheel, cursor customization)*

##### 2.1: Create Window

| Interface  | `openwd`       | Creates display window                  |
| ---------- | -------------- | --------------------------------------- |
| Parameters | `w` `h` `name` | Window width Window height Window title |
| Returns    | `fd`           | Success: window handle Failure: `false` |

```
bool openwd(w, h, name) // Example: fd = openwd(640, 480, "test")  
```

##### 2.2: Close Window

| Interface | `closewd` | Closes window                    |
| --------- | --------- | -------------------------------- |
| Parameter | `fd`      | Window handle                    |
| Returns   | `bool`    | Success: `true` Failure: `false` |

```
bool closewd(fd) // Example: closewd(fd)  
```

##### 2.3: Fill Window

| Interface  | `fillwd`             | Fills window with color                                      |
| ---------- | -------------------- | ------------------------------------------------------------ |
| Parameters | `fd` `colour` `flag` | Window handle Color (0xRRGGBB format) Blending mode: ¬- `flag=1`: Additive ¬- `flag=-1`: Subtractive ¬- `flag=2/±2`: Alpha blending |
| Returns    | `bool`               | Success: `true` Failure: `false`                             |

```
bool fillwd(fd, colour, flag) // Examples:<br>fillwd(fd, 0xFF0000, 2) // Red window<br>fillwd(fd, 0x800000FF, 2) // Add 50% blue  
```

##### 2.4: Draw to Window

| Interface  | `pushwd`                   | Draws image to window                                     |
| ---------- | -------------------------- | --------------------------------------------------------- |
| Parameters | `fd` `mapdata` `left, top` | Window handle Image data Start coordinates (default: 0,0) |
| Returns    | `bool`                     | Success: `true` Failure: `false`                          |

```
bool pushwd(fd, mapdata, left, top) // Examples:<br>pushwd(fd, mapdata) // Draw at (0,0)<br>pushwd(fd, mapdata, 20, 10) // Draw at (20,10)  
```

##### 2.5: Backup Window

| Interface  | `backupwd`     | Backs up window region                                       |
| ---------- | -------------- | ------------------------------------------------------------ |
| Parameters | `fd` `x,y,w,h` | Window handle Region coordinates (optional)                  |
| Returns    | `mapdata/bool` | With region: image data Without region: `true` Failure: `false` |

```
// Full window backup:<br>backupwd(fd)<br>// Partial backup:<br>md = backupwd(fd, 20, 10, 80, 100)  
```

##### 2.6: Restore Window

| Interface  | `recoverywd`   | Restores backup data                    |
| ---------- | -------------- | --------------------------------------- |
| Parameters | `fd` `x,y,w,h` | Window handle Restore region (optional) |
| Returns    | `bool`         | Success: `true` Failure: `false`        |

```
// Full restore:<br>recoverywd(fd)<br>// Partial restore:<br>recoverywd(fd, 20, 10, 80, 100)  
```

##### 2.7: Save Window

| Interface  | `savewd`       | Saves window to image file  |
| ---------- | -------------- | --------------------------- |
| Parameters | `fd` `mapname` | Window handle Filename      |
| Returns    | `bool`         | Success: `1` Failure: other |

```
bool savewd(fd, mapname) // Example: savewd(fd, "mapwd.png")  
```

##### 2.8: Set Cursor Style

| Interface  | `cursorwd`   | Sets cursor style                                            |
| ---------- | ------------ | ------------------------------------------------------------ |
| Parameters | `fd` `index` | Window handle Cursor ID: ¬- 32649: Hand pointer ¬- 32512: Arrow pointer |
| Returns    | `bool`       | Success: `true` Failure: `false`                             |

```
bool cursorwd(fd, index) // Examples:<br>cursorwd(fd, 32649) // Hand cursor<br>cursorwd(fd, 32512) // Arrow cursor  
```

##### 2.9: Get Window Core API

| Interface | `getwd`       | Gets low-level window API |
| --------- | ------------- | ------------------------- |
| Returns   | `UI_FuncBase` | Core API structure        |

```
UI_FuncBase getwd() // For direct C/C++ development  
```

##### 2.10: Get Window Control Handle

| Interface | `pullwd`         | Gets window control handle               |
| --------- | ---------------- | ---------------------------------------- |
| Parameter | `fd`             | Window handle                            |
| Returns   | `UI_FuncSynPlus` | Control structure (see definition below) |

```
UI_FuncSynPlus pullwd(fd) // Usage in Zhiye: getuibase(pullwindow())  
```

------

### Data Structures & Implementation

```
// ===================== C Program Reference Definitions =====================  

// Bitmap structure  
typedef struct {  
    BYTE b;  
    BYTE g;  
    BYTE r;  
    BYTE a;  
} rgba_t;  

typedef union {  
    rgba_t t;  
    DWORD  rgba;  
} bitmap_trgb;  

typedef struct {  
    DWORD w;  
    DWORD h;  
    bitmap_trgb* data;  
} bitmap_t;  

// Window control structure  
typedef struct {  
    void* fd;  
    WindowBase* (*LockWindow)(void* fd);  
    bitmap_t ui;  
    void (*push)(WindowBase* pWd);  
    void (*loadKeyMouse)(WindowBase* pWd, FUNC_Keyboard pKeybd, ...);  
    void (*UnLockWindow)(WindowBase* pWd);  
} UI_FuncSynPlus;  

// Mouse/Keyboard callback definitions  
typedef int (*FUNC_MouseLdown)(bitmap_t&, int x, int y);     // Left click  
typedef int (*FUNC_MouseRdown)(bitmap_t&, int x, int y);     // Right click  
typedef int (*FUNC_MouseMove)(bitmap_t&, int type, int x, int y);  // Move  
typedef int (*FUNC_MouseWheel)(bitmap_t&, int updown);       // Wheel  
typedef int (*FUNC_Keyboard)(bitmap_t&, int down, int key, int timems); // Key events  
#define WM_WD_REFRESH 'P'  // Refresh required if bitmap modified  

```

**Full Implementation Guide**:
 [Natural Language Understanding NLU - Third-party Integration](https://gitee.com/kebo521/nlu3)

