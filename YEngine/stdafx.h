// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

//#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>
#include <windowsx.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
///////////////////////////////////////////////////////////////////////////////////////////////
#pragma warning(disable: 4996)


//resource head
#include "resource.h"

//general system def
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")//�ڹ���������������
using namespace Gdiplus;

#pragma comment(lib, "Msimg32.lib")  //alphabend function needs this!

//stl header
#include <list>
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
#include <thread>
#include <iostream>
#include <functional>
#include <map>
using namespace std;

//general def
#include "GeneralDef.h"
#include "GlobalFunc.h"

