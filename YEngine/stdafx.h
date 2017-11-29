// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>
#include <windowsx.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
///////////////////////////////////////////////////////////////////////////////////////////////

//resource head
#include "resource.h"

//general system def
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")//在工程属性中添加亦可
using namespace Gdiplus;


//stl header
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
#include <thread>
using namespace std;

//general def
#include "GeneralDef.h"
