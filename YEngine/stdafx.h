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

//resource head
#include "resource.h"

//general system def
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")//�ڹ���������������
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
