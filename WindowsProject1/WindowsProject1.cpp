// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ButtonAdd(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ButtonSelectFile(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ButtonSell(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ButtonModify(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ButtonModifyNew(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ButtonSearch(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ButtonSearchShow(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ButtonStatistic(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ButtonPresent(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ButtonTimeSh(HWND, UINT, WPARAM, LPARAM);


int sellstate = 0;
FILE * fp;
List PurForAll = NULL;
List pnew = NULL;
List purpresent = NULL;
Str * strmodify;
Str * recievetoshow;
Str * report;
Str * turnovertext;
Str * profittext;
Str * textfortimesearch;
Str * textforpresent;
wchar_t * textmodify;
wchar_t bufSearch[50];
double RecordSer;
double searchitem = 0;
int ModifyState = 0;
int presenttype = -1;
int DeleNum = 0;
int selectstate = 0;
Present presentforall[100];
int presentnum = 0;



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	//wchar_t shan[20];
	

	_wfopen_s(&fp, L"Default.txt", L"r+");

	//fwscanf_s(fps, L"%s", shan, 10);

	//MessageBox(NULL, shan, TEXT("shan"), MB_OK);
	PurForAll = init_purch_chain(PurForAll);
	presentnum = init_present(PurForAll, presentforall);
	
	//if (PurForAll == NULL)
	////{
		///MessageBox(NULL, TEXT("null2"), TEXT("null2"), MB_OK);
	//}
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	if (fp != NULL)
	{
		fclose(fp);
	}
	
	fp = NULL;
	_wfopen_s(&fp, L"Default.txt", L"w");

	fseek(fp, 0L, SEEK_SET);

	chain_to_file(fp, PurForAll->next);

	destory_purch_chain(PurForAll);

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      400, 100, 500, 500, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxChar, cyChar;

	char ch;
	
    switch (message)
    {
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		ch = fgetc(fp);

		if (ch != EOF)
		{
			fseek(fp, 0L, SEEK_SET);
			file_to_chain(fp, PurForAll);
		}
		
		for (int i = 0; i < NUM; i++)
		{
				hwndButton[i] = CreateWindowW(szAppNameButton,
				button[i].szText,
				WS_CHILD | WS_VISIBLE | button[i].iStyle,
				2 * cxChar + 25, cyChar*(1 + 3 * i),
				50 * cxChar, 7 * cyChar / 3,
				hWnd,
				(HMENU)i,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);
		}

		

    case WM_COMMAND:
		if ((HWND)lParam == hwndButton[0])
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGADD), hWnd, ButtonAdd);
			//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		}
		else if ((HWND)lParam == hwndButton[1])
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGMODIFY), hWnd, ButtonModify);
		}
		//else if ((HWND)lParam == hwndButton[2])
		//{
		//	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGSELECTFILE), hWnd, ButtonSelectFile);
		//}
		else if ((HWND)lParam == hwndButton[2])
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGSELL), hWnd, ButtonSell);
		}
		else if ((HWND)lParam == hwndButton[3])
		{
			selectstate = 1;
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGSELECTFILE), hWnd, ButtonSelectFile);
			if (PurForAll->next == NULL)
			{
				break;
			}
			//fseek(fp, 0L, SEEK_SET);
			//chain_to_file(fp, PurForAll->next);
			MessageBox(hWnd, TEXT("完成"), TEXT("完成"), MB_OK);
		}
		else if ((HWND)lParam == hwndButton[4])
		{
			selectstate = 2;
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGSELECTFILE), hWnd, ButtonSelectFile);
			//if (fp != NULL)
			//{
			//	fseek(fp, 0L, SEEK_SET);
			//	file_to_chain(fp, PurForAll);
			//}
			
			MessageBox(hWnd, TEXT("完成"), TEXT("完成"), MB_OK);
		}
		else if ((HWND)lParam == hwndButton[5])
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGSEARCH), hWnd, ButtonSearch);
		}
		else if ((HWND)lParam == hwndButton[6])
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGTJ), hWnd, ButtonStatistic);
		}
		else 
		{
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.



INT_PTR CALLBACK ButtonAdd(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	wchar_t time[20];
	wchar_t month[5];
	wchar_t day[5];
	wchar_t hour[5];
	wchar_t min[5];
	wchar_t accessory[50];
	wchar_t model[20];
	wchar_t manu[50];
	wchar_t uprice[8];
	wchar_t num[8];
	wchar_t customer[50];

	double UPrice, Num;

	wcscpy_s(time, L"\0");

	HWND hEditMonth,
		hEditDay,
		hEditHour,
		hEditMin,
		hEditAccessory, 
		hEditModel, 
		hEditManu, 
		hEditUprice, 
		hEditNum, 
		hEditCustomer;

	hEditMonth = GetDlgItem(hDlg, IDC_EDITADDMONTH);
	hEditDay = GetDlgItem(hDlg, IDC_EDITADDDAY);
	hEditHour = GetDlgItem(hDlg, IDC_EDITADDHOUR);
	hEditMin = GetDlgItem(hDlg, IDC_EDITADDMIN);
	hEditAccessory = GetDlgItem(hDlg, IDC_EDITACCESSORY);
	hEditModel = GetDlgItem(hDlg, IDC_EDITMODEL);
	hEditManu = GetDlgItem(hDlg, IDC_EDITMANU);
	hEditUprice = GetDlgItem(hDlg, IDC_EDITUPRICE);
	hEditNum = GetDlgItem(hDlg, IDC_EDITNUM);
	hEditCustomer = GetDlgItem(hDlg, IDC_EDITCUSTOMER);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON2:	
			GetWindowText(hEditMonth, month, 5);
			GetWindowText(hEditDay, day, 5);
			GetWindowText(hEditHour, hour, 5);
			GetWindowText(hEditMin, min, 5);
			GetWindowText(hEditAccessory, accessory, 50);
			GetWindowText(hEditModel, model, 20);
			GetWindowText(hEditManu, manu, 50);
			GetWindowText(hEditUprice, uprice, 8);
			GetWindowText(hEditNum, num, 8);
			GetWindowText(hEditCustomer, customer, 50);

			UPrice = _wtof(uprice);
			Num = _wtof(num);

			if (UPrice <= 0 || Num <= 0)
			{
				MessageBox(hDlg, TEXT("输入不能为负"), TEXT("警告"), MB_OK);
				break;
			}

			if (wcslen(month) != 2 || wcslen(min) != 2 || wcslen(hour)!=2||
				wcslen(day) != 2 )
			{
				MessageBox(hDlg, TEXT("所有输入应为两位"), TEXT("警告"), MB_OK);
				break;
			}

			wcscat_s(time, month);
			wcscat_s(time, L"-");
			wcscat_s(time, day);
			wcscat_s(time, L"-");
			wcscat_s(time, hour);
			wcscat_s(time, L"-");
			wcscat_s(time, min);

			if (PurForAll == NULL)
			{
				MessageBox(hDlg, TEXT("nullptr1"), TEXT("nullptr1"), MB_OK);
			}

			pnew = PurForAll;
			pnew = insert_node_purch(PurForAll, jinhuo, time, accessory,
				model, manu, UPrice, Num, UPrice*Num, customer);

			MessageBox(hDlg, TEXT("输入下一个"), TEXT("提示"), MB_OK);
			return (INT_PTR)TRUE;

		case IDOK2:
		case IDCANCEL:
		case IDCANCELE:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		default:
			return (INT_PTR)FALSE;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ButtonSelectFile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR buf[70];
	HWND hEdit;
	hEdit = GetDlgItem(hDlg, IDC_EDITSFILE);
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(hEdit, TEXT("Default.txt"));
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTONSFILE:
			//hEdit = GetDlgItem(hDlg, IDC_EDITSFILE);
			GetWindowText(hEdit, buf, 70);

			if (fp != NULL)
			{
				fclose(fp);
			}
			
			_wfopen_s(&fp, buf, L"r+");

			if (fp == NULL)
			{
				MessageBox(hDlg, TEXT("打开文件失败!"), TEXT("提示"), MB_OK);
				return (INT_PTR)TRUE;
			}

			MessageBox(hDlg, buf, TEXT("提示"), MB_OK);

			if (selectstate == 1)
			{
				if (PurForAll->next == NULL)
				{
					break;
				}
				fseek(fp, 0L, SEEK_SET);
				chain_to_file(fp, PurForAll->next);
			}
			else if (selectstate == 2)
			{
				if (fp != NULL)
				{
					fseek(fp, 0L, SEEK_SET);
					file_to_chain(fp, PurForAll);
				}
			}
			
			//MessageBox(hDlg, TEXT(""), TEXT("提示"), MB_OK);
			return (INT_PTR)TRUE;

		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		default:
			break;
		}

		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ButtonSell(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	wchar_t time[20],
		month[5],
		day[5],
		hour[5],
		min[5];
	wchar_t accessory[50];
	wchar_t model[20];
	wchar_t manu[50];
	wchar_t uprice[8];
	wchar_t num[8];
	wchar_t customer[50];
	wchar_t item[100];

	wcscpy_s(item, L"\0");
	wcscpy_s(time, L"\0");

	double UPrice, Num;

	HWND hEditMonth,
		hEditDay,
		hEditHour,
		hEditMin,
		hEditAccessory,
		hEditModel,
		hEditManu,
		hEditUprice,
		hEditNum,
		hEditCustomer;

	hEditMonth = GetDlgItem(hDlg, IDC_EDITSELLMONTH);
	hEditDay = GetDlgItem(hDlg, IDC_EDITSELLDAY);
	hEditHour = GetDlgItem(hDlg, IDC_EDITSELLHOUR);
	hEditMin = GetDlgItem(hDlg, IDC_EDITSELLMIN);

	hEditAccessory = GetDlgItem(hDlg, IDC_EDITACCESSORYS);
	hEditModel = GetDlgItem(hDlg, IDC_EDITMODELS);
	hEditManu = GetDlgItem(hDlg, IDC_EDITMANUS);
	hEditUprice = GetDlgItem(hDlg, IDC_EDITUPRICES);
	hEditNum = GetDlgItem(hDlg, IDC_EDITNUMS);
	hEditCustomer = GetDlgItem(hDlg, IDC_EDITCUSTOMERS);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTONS:
			GetWindowText(hEditMonth, month, 5);
			GetWindowText(hEditDay, day, 5);
			GetWindowText(hEditHour, hour, 5);
			GetWindowText(hEditMin, min, 5);

			GetWindowText(hEditAccessory, accessory, 50);
			GetWindowText(hEditModel, model, 20);
			GetWindowText(hEditManu, manu, 50);
			GetWindowText(hEditUprice, uprice, 8);
			GetWindowText(hEditNum, num, 8);
			GetWindowText(hEditCustomer, customer, 50);

			wcscat_s(item, accessory);
			wcscat_s(item, model);

			wcscat_s(time, month);
			wcscat_s(time, L"-");
			wcscat_s(time, day);
			wcscat_s(time, L"-");
			wcscat_s(time, hour);
			wcscat_s(time, L"-");
			wcscat_s(time, min);

			UPrice = _wtof(uprice);
			Num = _wtof(num);

			if (UPrice <= 0 || Num <= 0)
			{
				MessageBox(hDlg, TEXT("输入不能为负"), TEXT("警告"), MB_OK);
				break;
			}

			if (wcslen(month) != 2 || wcslen(min) != 2 || wcslen(hour) != 2 ||
				wcslen(day) != 2)
			{
				MessageBox(hDlg, TEXT("所有输入应为两位"), TEXT("警告"), MB_OK);
				break;
			}

			if (PurForAll == NULL)
			{
				MessageBox(hDlg, TEXT("nullptr1"), TEXT("nullptr1"), MB_OK);
			}
			if (sellstate == 0)
			{
				MessageBox(hDlg, TEXT("请先选择销售类型!"), TEXT("警告"), MB_OK);
				return (INT_PTR)TRUE;
			}
			if (!find_purch_node(PurForAll->next, item, Num))
			{
				MessageBox(hDlg, TEXT("请先进货!"), TEXT("警告"), MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			pnew = PurForAll;
			pnew = insert_node_purch(PurForAll, sellstate, time, accessory,
				model, manu, UPrice, Num, UPrice*Num, customer);

			if (sellstate == pifa)
			{
				if (UPrice * Num > threshold || Num > numthresgold)
				{
					purpresent = pnew;
					MessageBox(hDlg, TEXT("需要赠送赠品"), TEXT("提示"), MB_OK);
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGPRESENT), hDlg, ButtonPresent);
				}
			}
			
			MessageBox(hDlg, TEXT("输入下一个"), TEXT("提示"), MB_OK);
			return (INT_PTR)TRUE;

		case IDC_RADIOSPF:
			sellstate = pifa;
			MessageBox(hDlg, TEXT("批发"), TEXT("提示"), MB_OK);
			return (INT_PTR)TRUE;

		case IDC_RADIOSLSH:
			sellstate = lingshou;
			MessageBox(hDlg, TEXT("零售"), TEXT("提示"), MB_OK);
			return (INT_PTR)TRUE;

		case IDOK2S:
		case IDCANCEL:
		case IDCANCELES:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		default:
			return (INT_PTR)FALSE;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ButtonModify(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hEditMS, hEditSelectRec, hEditDS;
	wchar_t SRecordSer[10];
	wchar_t delenum[10];

	hEditMS = GetDlgItem(hDlg, IDC_EDITMS);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:	
		strmodify = chain_to_string(PurForAll->next, 409600);
		SetWindowText(hEditMS, strmodify->contains);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTONMQ:
			hEditSelectRec = GetDlgItem(hDlg, IDC_EDITMQ);
			GetWindowText(hEditSelectRec, SRecordSer, 10);
			RecordSer = _wtof(SRecordSer);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGMODIFYNEW), hDlg, ButtonModifyNew);
			return (INT_PTR)TRUE;

		case IDC_BUTTONDQ:
			hEditDS = GetDlgItem(hDlg, IDC_EDITDQ);
			GetWindowText(hEditDS, delenum, 10);
			DeleNum = _wtof(delenum);
			if (DeleNum <= 0)
			{								
				MessageBox(hDlg, TEXT("输入不能为负"), TEXT("警告"), MB_OK);
				break;
			}


			if (delete_node_purch(PurForAll, DeleNum))
			{
				MessageBox(hDlg, TEXT("删除成功"), TEXT("提示"), MB_OK);
			}
			//MessageBox(hDlg,TEXT(""))
			return (INT_PTR)TRUE;

		case IDOKM:
		case IDCANCELM:
		case IDCANCEL:
			free(strmodify);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		default:
			return (INT_PTR)FALSE;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ButtonModifyNew(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	List ListModify;
	ListModify = find_node_purch(PurForAll->next, RecordSer);

	ModifyState = ListModify->which;

	wchar_t timemn[20];
	wchar_t accessorymn[50];
	wchar_t modelmn[20];
	wchar_t manumn[50];
	wchar_t upricemn[18];
	wchar_t nummn[18];
	wchar_t customermn[50];

	double UPriceMN, NumMN;

	

	HWND hEditTimeMN,
		hEditAccessoryMN,
		hEditModelMN,
		hEditManuMN,
		hEditUpriceMN,
		hEditNumMN,
		hEditCustomerMN;

	hEditTimeMN = GetDlgItem(hDlg, IDC_EDITTIMEMN);
	hEditAccessoryMN = GetDlgItem(hDlg, IDC_EDITACCESSORYMN);
	hEditModelMN = GetDlgItem(hDlg, IDC_EDITMODELMN);
	hEditManuMN = GetDlgItem(hDlg, IDC_EDITMANUMN);
	hEditUpriceMN = GetDlgItem(hDlg, IDC_EDITUPRICEMN);
	hEditNumMN = GetDlgItem(hDlg, IDC_EDITNUMMN);
	hEditCustomerMN = GetDlgItem(hDlg, IDC_EDITCUSTOMERMN);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG:
		switch (ListModify->which)
		{
		case pifa:
			CheckDlgButton(hDlg, IDC_RADIOSPFMN, BST_CHECKED);
			break;

		case lingshou:
			CheckDlgButton(hDlg, IDC_RADIOSLSHMN, BST_CHECKED);
			break;

		case jinhuo:
			CheckDlgButton(hDlg, IDC_RADIOJINHUOMN, BST_CHECKED);
			break;

		default:
			break;
		}

		swprintf_s(upricemn, 18, L"%lf", ListModify->unit_price);
		swprintf_s(nummn, 18, L"%lf", ListModify->num);

		SetWindowText(hEditTimeMN, ListModify->time);
		SetWindowText(hEditAccessoryMN, ListModify->accessory);
		SetWindowText(hEditModelMN, ListModify->model);
		SetWindowText(hEditManuMN, ListModify->manufacturer);
		SetWindowText(hEditUpriceMN, upricemn);
		SetWindowText(hEditNumMN, nummn);
		SetWindowText(hEditCustomerMN, ListModify->customer);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTONMNSAVE:
			GetWindowText(hEditTimeMN, timemn, 20);
			GetWindowText(hEditAccessoryMN, accessorymn, 50);
			GetWindowText(hEditModelMN, modelmn, 20);
			GetWindowText(hEditManuMN, manumn, 50);
			GetWindowText(hEditUpriceMN, upricemn, 8);
			GetWindowText(hEditNumMN, nummn, 8);
			GetWindowText(hEditCustomerMN, customermn, 50);

			UPriceMN = _wtof(upricemn);
			NumMN = _wtof(nummn);

			if (UPriceMN <= 0 || NumMN <= 0)
			{
				MessageBox(hDlg, TEXT("输入不能为负"), TEXT("警告"), MB_OK);
				break;
			}

	

			if (PurForAll == NULL)
			{
				MessageBox(hDlg, TEXT("nullptr1"), TEXT("nullptr1"), MB_OK);
			}
			
			rewrite_node_purch(ListModify, ModifyState, timemn, accessorymn, modelmn,
				manumn, UPriceMN, NumMN, UPriceMN*NumMN, customermn);
			MessageBox(hDlg, TEXT("修改成功"), TEXT("提示"), MB_OK);
			return (INT_PTR)TRUE;

		case IDC_RADIOSPFMN:
			ModifyState = pifa;
			return (INT_PTR)TRUE;

		case IDC_RADIOSLSHMN:
			ModifyState = lingshou;
			return (INT_PTR)TRUE;

		case IDC_RADIOJINHUOMN:
			ModifyState = jinhuo;
			return (INT_PTR)TRUE;

		case IDOK2MN:
		case IDCANCEL:
		case IDCANCELEMN:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		default:
			return (INT_PTR)FALSE;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ButtonSearch(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	
	HWND hEditSearch;
	hEditSearch = GetDlgItem(hDlg, IDC_EDITSEARCH);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTONQDSEARCH:
			GetWindowText(hEditSearch, bufSearch, 50);

			recievetoshow = search_node_purch(PurForAll->next, bufSearch, searchitem);

			MessageBox(hDlg, bufSearch, TEXT("提示"), MB_OK);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGSEARCHSHOW), hDlg, ButtonSearchShow);
			return (INT_PTR)TRUE;

		case IDC_RADIOPJSCH:
			searchitem = searchpj;
			return (INT_PTR)TRUE;

		case IDC_RADIOGHSHSCH:
			searchitem = searchghsh;
			return (INT_PTR)TRUE;

		case IDC_RADIOCUSTSCH:
			searchitem = searchkehu;
			return (INT_PTR)TRUE;

		case IDCANCEL:
		case IDOKSCH:
		case IDCANCELESCH:
			//free(recievetoshow);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		default:
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ButtonSearchShow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hEditSS;
	hEditSS = GetDlgItem(hDlg, IDC_EDITSS);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(hEditSS, recievetoshow->contains);//recievetoshow->contains
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOKSS:
		case IDCANCEL:
		case IDCANCELESS:
			free(recievetoshow);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		default:
			return (INT_PTR)FALSE;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ButtonStatistic(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hEditReport;
	HWND hEditTurnover;
	HWND hEditProfit;
	HWND hEditMonthStart;
	HWND hEditDayStart;
	HWND hEditHourStart;
	HWND hEditMinStart;
	HWND hEditMonthEnd;
	HWND hEditDayEnd;
	HWND hEditHourEnd;
	HWND hEditMinEnd;
	HWND hEditPresent;

	wchar_t timestart[20];
	wchar_t timeend[20];
	
	wchar_t monthstart[5];
	wchar_t daystart[5];
	wchar_t hourstart[5];
	wchar_t minstart[5];
	wchar_t monthend[5];
	wchar_t dayend[5];
	wchar_t hourend[5];
	wchar_t minend[5];


	hEditReport = GetDlgItem(hDlg, IDC_EDITTJIVENTORYRP);
	hEditTurnover = GetDlgItem(hDlg, IDC_EDITTJTURNOVER);
	hEditProfit = GetDlgItem(hDlg, IDC_EDITPROFIT);

	hEditMonthStart = GetDlgItem(hDlg, IDC_EDITMONTHSTART);
	hEditDayStart = GetDlgItem(hDlg, IDC_EDITDAYSTART);
	hEditHourStart = GetDlgItem(hDlg, IDC_EDITHOURSTART);
	hEditMinStart = GetDlgItem(hDlg, IDC_EDITMINSTART);
	hEditMonthEnd = GetDlgItem(hDlg, IDC_EDITMONTHEND);
	hEditDayEnd = GetDlgItem(hDlg, IDC_EDITDAYEND);
	hEditHourEnd = GetDlgItem(hDlg, IDC_EDITHOUREND);
	hEditMinEnd = GetDlgItem(hDlg, IDC_EDITMINEND);
	hEditPresent = GetDlgItem(hDlg, IDC_EDITPRESENTINFO);

	wcscpy_s(timestart, L"\0");
	wcscpy_s(timeend, L"\0");

	

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		//recievetoshow->contains
		turnovertext = get_turnover_purch(PurForAll->next);
		report = create_inventory_report(PurForAll->next);
		profittext = get_profit_value(PurForAll->next);

		textforpresent = text_present_static(PurForAll->next);

		SetWindowText(hEditReport, report->contains);
		SetWindowText(hEditTurnover, turnovertext->contains);
		SetWindowText(hEditProfit, profittext->contains);
		SetWindowText(hEditPresent, textforpresent->contains);

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTONTJQD:
			
			GetWindowText(hEditMonthStart, monthstart, 5);
			GetWindowText(hEditMonthEnd, monthend, 5);
			GetWindowText(hEditDayStart, daystart, 5);
			GetWindowText(hEditDayEnd, dayend, 5);
			GetWindowText(hEditMinStart, minstart, 5);
			GetWindowText(hEditMinEnd, minend, 5);
			GetWindowText(hEditHourStart, hourstart, 5);
			GetWindowText(hEditHourEnd, hourend, 5);

			if (wcslen(monthstart) != 2 || wcslen(monthend) != 2 || wcslen(daystart) != 2
				|| wcslen(dayend) != 2 || wcslen(hourstart) != 2 || wcslen(hourend) != 2
				|| wcslen(minstart) != 2 || wcslen(minend) != 2)
			{
				MessageBox(hDlg, TEXT("所有输入应为两位"), TEXT("警告"), MB_OK);
				break;
			}

			wcscat_s(timestart, monthstart);
			wcscat_s(timestart, L"-");

			wcscat_s(timeend, monthend);
			wcscat_s(timeend, L"-");

			wcscat_s(timestart, daystart);
			wcscat_s(timestart, L"-");

			wcscat_s(timeend, dayend);
			wcscat_s(timeend, L"-");

			wcscat_s(timestart, hourstart);
			wcscat_s(timestart, L"-");

			wcscat_s(timeend, hourstart);
			wcscat_s(timeend, L"-");

			wcscat_s(timestart, minstart);
			wcscat_s(timeend, minend);

			textfortimesearch = search_time(PurForAll->next, timestart, timeend);

			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGTIMESH), hDlg, ButtonTimeSh);

			return (INT_PTR)TRUE;

		case IDOKTJ:
		case IDCANCEL:
		//case IDCANCELESS:
			free(report);
			free(profittext);
			free(turnovertext);
			free(textforpresent);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		default:
			return (INT_PTR)FALSE;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ButtonPresent(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hEditPresent1, hEditPresent2, hEditPresent3;
	hEditPresent1 = GetDlgItem(hDlg, IDC_EDITPRESENT1);
	hEditPresent2 = GetDlgItem(hDlg, IDC_EDITPRESENT2);
	hEditPresent3 = GetDlgItem(hDlg, IDC_EDITPRESENT3);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		srand(time(NULL));
		presenttype = rand() % PRESENTNUM;
		while (presenttype > PRESENTNUM - 2)
		{
			presenttype = rand() % PRESENTNUM;
		}

		SetWindowText(hEditPresent1, pres[presenttype].presentname);
		SetWindowText(hEditPresent2, pres[presenttype+1].presentname);
		SetWindowText(hEditPresent3, pres[presenttype+2].presentname);//recievetoshow->contains
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTONPRE1:
			MessageBox(hDlg, pres[presenttype].presentname, TEXT("赠品"), MB_OK);
			//presentforall[presentnum] = pres[presenttype];
			//wcscpy_s(presentforall[presentnum].customer, purpresent->customer);
			insert_node_purch(PurForAll, 4, purpresent->time, pres[presenttype].presentname,
				L"present", L"present", pres[presenttype].price, 1, 
				pres[presenttype].price, purpresent->customer);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		case IDC_BUTTONPRE2:
			MessageBox(hDlg, pres[presenttype+1].presentname, TEXT("赠品"), MB_OK);
			//presentforall[presentnum] = pres[presenttype];
			//wcscpy_s(presentforall[presentnum].customer, purpresent->customer);
			insert_node_purch(PurForAll, 4, purpresent->time, pres[presenttype+1].presentname,
				L"present", L"present", pres[presenttype].price, 1, 
				pres[presenttype].price, purpresent->customer);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		case IDC_BUTTONPRE3:
			MessageBox(hDlg, pres[presenttype+2].presentname, TEXT("赠品"), MB_OK);
			//presentforall[presentnum] = pres[presenttype];
			//wcscpy_s(presentforall[presentnum].customer, purpresent->customer);
			insert_node_purch(PurForAll, 4, purpresent->time, pres[presenttype+2].presentname,
				L"present", L"present", pres[presenttype].price, 1, 
				pres[presenttype].price, purpresent->customer);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		case IDOKPRESENT:
		case IDCANCEL:
			//free(recievetoshow);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		default:
			return (INT_PTR)FALSE;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ButtonTimeSh(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hEditTimeSh;
	hEditTimeSh = GetDlgItem(hDlg, IDC_EDITTIMESH);

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(hEditTimeSh, textfortimesearch->contains);//recievetoshow->contains
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOKTIMESH:
			//case IDCANCEL:
		case IDCANCEL:
			free(textfortimesearch);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;

		default:
			return (INT_PTR)FALSE;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}