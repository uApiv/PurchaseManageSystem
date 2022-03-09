#pragma once

#include "resource.h"
#include <windows.h>
#include <time.h>
#include "Yjh_1.h"
struct
{
	int iStyle;
	TCHAR szText[50];
}
button[] =
{
	BS_DEFPUSHBUTTON, TEXT("增加进货记录"),
	BS_DEFPUSHBUTTON, TEXT("修改"),
	//BS_DEFPUSHBUTTON, TEXT("选择文件"),
	BS_DEFPUSHBUTTON, TEXT("增加销售记录"),
	BS_DEFPUSHBUTTON, TEXT("选择其他文件储存"),
	BS_DEFPUSHBUTTON, TEXT("从文件导入"),
	BS_DEFPUSHBUTTON, TEXT("查询"),
	BS_DEFPUSHBUTTON, TEXT("统计"),
};


Present pres[] =
{
	50, L"\0", L"UPan",
	20, L"\0", L"USB DataLine",
	100, L"\0", L"RAM",
	50, L"\0", L"Power",
	50, L"\0", L"Mouse",
	80, L"\0", L"Computer Case",
	50, L"\0", L"Kerboard",
	80, L"\0", L"Hard Disk",
	50, L"\0", L"Power",
	100, L"\0", L"MotherBoard",
	50, L"\0", L"UPan",
	80, L"\0", L"Hard Disk",
	20, L"\0", L"Fan",
	80, L"\0", L"Hard Disk",
	50, L"\0", L"UPan",
	20, L"\0", L"USB DataLine",
	50, L"\0", L"Power",
};

#define PRESENTNUM (sizeof(pres)/sizeof(pres[0]))

#define NUM (sizeof button / sizeof button[0])
HWND hwndButton[NUM];
TCHAR szAppNameButton[] = TEXT("button");

#define jinhuo 1
#define pifa 2
#define lingshou 3

#define searchpj 1
#define searchghsh 2;
#define searchkehu 3

double initial_data = 5000000;
double threshold = 200;//zengpinyuzhi
double numthresgold = 20;