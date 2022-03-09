//¼ÇÂ¼ÎÄ¼þrecord.txt (Óëexe±£´æÔÚÍ¬Ò»Ä¿Â¼ÏÂ£©£¬Ò»¸öÁ´±íÊµÏÖ 
//Ä¬ÈÏwhich £¬time £¬accessory £¬model ¼´¿ÉÈ·¶¨Ò»´Î½»Ò× 

#include "Yjh_1.h"

//#pragma warning(disabled:_CRT_SECURE_NO_WARNINGS)

//#define _CRT_SECURE_NO_WARNINGS
List insert_node_purch(List pointer,
	int which,
	const wchar_t *time,
	const wchar_t *accessory,
	const wchar_t *model,
	const wchar_t *manufacturer,
	double unit_price,
	double num,
	double total_price,
	const wchar_t *customer)
{
	List newnode = (List)malloc(sizeof(p));

	if (pointer->next == NULL)
	{
		pointer->next = newnode;
		newnode->next = NULL;
	}
	else
	{
	List tem = pointer->next;

	pointer->next = newnode;
	newnode->next = tem;
	}

	newnode->which = which;

	wcscpy_s(newnode->time, 20, time);
	wcscpy_s(newnode->accessory, 50, accessory);
	wcscpy_s(newnode->model, 20, model);
	wcscpy_s(newnode->manufacturer, 50, manufacturer);

	newnode->unit_price = unit_price;
	newnode->num = num;
	newnode->total_price = total_price;

	wcscpy_s(newnode->customer, 50, customer);

	return	newnode;
}

List init_purch_chain(List pointer)
{
	pointer = (List)malloc(sizeof(p));

	pointer->next = NULL;

	return pointer;
}
void destory_purch_chain(List pointer)
{
	while (pointer != NULL)
	{
		List tem = pointer;
		pointer = pointer->next;
		free(tem);
	}
}

void chain_to_file(FILE*fp, const List pointer)
{
	List poin = pointer;
	while (poin != NULL)
	{
		//_wsetlocale(0, L"chs");
		fwprintf_s(fp, L"%d ", poin->which);
		fwprintf_s(fp, L"%s ", poin->time);
		fwprintf_s(fp, L"%.2lf ", poin->unit_price);
		fwprintf_s(fp, L"%s ", poin->accessory);
		fwprintf_s(fp, L"%.0lf ", poin->num);
		fwprintf_s(fp, L"%s ", poin->model);
		fwprintf_s(fp, L"%.2lf ", poin->total_price);
		fwprintf_s(fp, L"%s ", poin->manufacturer);
		fwprintf_s(fp, L"%s ", poin->customer);
		fwprintf_s(fp, L"%c", '\n');
		poin = poin->next;
	}
}

List file_to_chain(FILE*fp, List pointer)
{
	List tem = pointer;
	int which = 0;

	while (feof(fp) == 0)
	{
		
		wchar_t time[20];
		wchar_t accessory[50];
		wchar_t model[20];
		wchar_t manufacturer[50];
		double unit_price = 0;
		double num = 0;
		double total_price = 0;
		wchar_t customer[50];

		if (fwscanf_s(fp, L"%d", &which) == EOF)
		{
			return tem;
		}
		fwscanf_s(fp, L"%s", time, 20);
		fwscanf_s(fp, L"%lf", &unit_price);
		fwscanf_s(fp, L"%s", accessory, 50);
		fwscanf_s(fp, L"%lf", &num);
		fwscanf_s(fp, L"%s", model, 20);
		fwscanf_s(fp, L"%lf", &total_price);
		fwscanf_s(fp, L"%s", manufacturer, 50);
		fwscanf_s(fp, L"%s", customer, 50);
		
		tem = insert_node_purch(pointer, which, time, accessory, model, manufacturer, 
			unit_price, num, total_price, customer);
	}

	return tem;
}

Str* chain_to_string(List pointer, int size)
{
	List poin = pointer;
	int num = 1;
	wchar_t UPrice[20], Num[10], SNum[10], SellState[20];
	
	Str * text = (Str*)malloc(sizeof(Str));
	wcscpy_s(text->contains, L"\0");

	wcscat_s(text->contains, size, L"序号");
	wcscat_s(text->contains, size, L".\t\t\t");
	wcscat_s(text->contains, size, L"货物类型");
	wcscat_s(text->contains, size, L".\t\t");
	wcscat_s(text->contains, size, L"时间");
	wcscat_s(text->contains, size, L".\t\t\t");
	wcscat_s(text->contains, size, L"配件名称");
	wcscat_s(text->contains, size, L".\t\t");
	wcscat_s(text->contains, size, L"配件型号");
	wcscat_s(text->contains, size, L".\t\t");
	wcscat_s(text->contains, size, L"制造商");
	wcscat_s(text->contains, size, L".\t\t\t");
	wcscat_s(text->contains, size, L"单价(元)");
	wcscat_s(text->contains, size, L".\t\t");
	wcscat_s(text->contains, size, L"数量(个)");
	wcscat_s(text->contains, size, L".\t\t");
	wcscat_s(text->contains, size, L"供货商");
	wcscat_s(text->contains, size, L".\r\n");

	while (poin != NULL)
	{
		if (poin->which == 1)
		{
			wcscpy_s(SellState, L"jinhuo");
		}
		else if (poin->which == 2)
		{
			wcscpy_s(SellState, L"pifa");
		}
		else if(poin->which == 3)
		{
			wcscpy_s(SellState, L"lingshou");
		}
		else if(poin->which == 4)
		{
			wcscpy_s(SellState, L"zengpin");
		}
		else
		{
			wcscpy_s(SellState, L"NULL");
		}
		swprintf_s(UPrice, 20, L"%.2lf", poin->unit_price);
		swprintf(Num, 10, L"%.0lf", poin->num);
		swprintf(SNum, 20, L"%d", num);

		wcscat_s(text->contains, size, SNum);
		wcscat_s(text->contains, size, L".\t\t\t");
		wcscat_s(text->contains, size, SellState);
		wcscat_s(text->contains, size, L".\t\t\t");

		wcscat_s(text->contains, size, poin->time);
		if (wcslen(poin->time) > tabb)
		{
			wcscat_s(text->contains, size, L".\t\t");
		}
		else
		{
			wcscat_s(text->contains, size, L".\t\t\t");
		}

		wcscat_s(text->contains, size, poin->accessory);
		if (wcslen(poin->accessory) > tabb)
		{
			wcscat_s(text->contains, size, L".\t\t");
		}
		else
		{
			wcscat_s(text->contains, size, L".\t\t\t");
		}

		wcscat_s(text->contains, size, poin->model);
		if (wcslen(poin->model) > tabb)
		{
			wcscat_s(text->contains, size, L".\t\t");
		}
		else
		{
			wcscat_s(text->contains, size, L".\t\t\t");
		}

		wcscat_s(text->contains, size, poin->manufacturer);
		if (wcslen(poin->manufacturer) > tabb)
		{
			wcscat_s(text->contains, size, L".\t\t");
		}
		else
		{
			wcscat_s(text->contains, size, L".\t\t\t");
		}

		wcscat_s(text->contains, size, UPrice);
		if (wcslen(UPrice) > tabb)
		{
			wcscat_s(text->contains, size, L".\t\t");
		}
		else
		{
			wcscat_s(text->contains, size, L".\t\t\t");
		}

		wcscat_s(text->contains, size, Num);
		if (wcslen(Num) > tabb)
		{
			wcscat_s(text->contains, size, L".\t\t");
		}
		else
		{
			wcscat_s(text->contains, size, L".\t\t\t");
		}

		wcscat_s(text->contains, size, poin->customer);
		wcscat_s(text->contains, size, L". \r\n");

		poin = poin->next;

		num++;
	}
	//wcscpy_s(text->contains, L"jinhuo");
	//wcscat_s(text->contains, size, L"asdf");

	return text;
}

void rewrite_node_purch(List pointer,
	int which,
	const wchar_t *time,
	const wchar_t *accessory,
	const wchar_t *model,
	const wchar_t *manufacturer,
	double unit_price,
	double num,
	double total_price,
	const wchar_t *customer)
{
	pointer->which = which;
	wcscpy_s(pointer->time, time);
	wcscpy_s(pointer->accessory, accessory);
	wcscpy_s(pointer->model, model);
	wcscpy_s(pointer->manufacturer, manufacturer);
	wcscpy_s(pointer->customer, customer);
	pointer->unit_price = unit_price;
	pointer->num = num;
	pointer->total_price = num * unit_price;

}

List find_node_purch(List pointer, double n)
{
	int i = 1;
	List tem = pointer;
	while (i < n)
	{
		tem = tem->next;
		if (tem == NULL)
		{
			return NULL;
		}
		i++;
	}
	return tem;
}

Str * search_node_purch(List pointer, wchar_t * itemname, double item)
{
	Str * retval = (Str*)malloc(sizeof(Str));
	List point = pointer;
	int num = 1;
	int size = 409600;
	wcscpy_s(retval->contains, L"\0");

	wchar_t UPrice[20], Num[10], SNum[10], SellState[20];

	wcscat_s(retval->contains, size, L"序号");
	wcscat_s(retval->contains, size, L".\t\t\t");
	wcscat_s(retval->contains, size, L"货物类型");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"时间");
	wcscat_s(retval->contains, size, L".\t\t\t");
	wcscat_s(retval->contains, size, L"配件名称");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"配件型号");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"制造商");
	wcscat_s(retval->contains, size, L".\t\t\t");
	wcscat_s(retval->contains, size, L"单价(元)");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"数量(个)");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"供货商");
	wcscat_s(retval->contains, size, L".\r\n");
	
	if (item == 1)
	{
		while (point != NULL)
		{
			wchar_t peijianzhonglei[100];
			wcscpy_s(peijianzhonglei, L"\0");

			wcscat_s(peijianzhonglei, 100, point->accessory);
			wcscat_s(peijianzhonglei, 100, point->model);

			if (wcscmp(peijianzhonglei, itemname) != 0)
			{
				point = point->next;
				continue;
			}
			if (point->which == 1)
			{
				wcscpy_s(SellState, L"进货");
			}
			else if (point->which == 2)
			{
				wcscpy_s(SellState, L"批发");
			}
			else if (point->which == 3)
			{
				wcscpy_s(SellState, L"零售");
			}
			else
			{
				wcscpy_s(SellState, L"赠品");
			}
			swprintf_s(UPrice, 20, L"%.2lf", point->unit_price);
			swprintf(Num, 10, L"%.0lf", point->num);
			swprintf(SNum, 20, L"%d", num);

			wcscat_s(retval->contains, size, SNum);
			if (wcslen(SNum) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, SellState);
			if (wcslen(SellState) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, point->time);
			if (wcslen(point->time) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->accessory);
			if (wcslen(point->accessory) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->model);
			if (wcslen(point->model) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->manufacturer);
			if (wcslen(point->manufacturer) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, UPrice);
			if (wcslen(UPrice) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, Num);
			if (wcslen(Num) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->customer);
			wcscat_s(retval->contains, size, L".\r\n");

			point = point->next;
			num++;
		}
	}
	else if (item == 2)//gonghuoshang
	{
		while (point != NULL)
		{
			if (wcscmp(point->customer, itemname) != 0)
			{
				point = point->next;
				continue;
			}
			if (point->which == 1)
			{
				wcscpy_s(SellState, L"进货");
			}
			else if (point->which == 2)
			{
				wcscpy_s(SellState, L"批发");
			}
			else if (point->which == 3)
			{
				wcscpy_s(SellState, L"零售");
			}
			else
			{
				wcscpy_s(SellState, L"赠品");
			}
			if (point->which != 1)
			{
				point = point->next;
				continue;
			}
			swprintf_s(UPrice, 20, L"%.2lf", point->unit_price);
			swprintf(Num, 10, L"%.0lf", point->num);
			swprintf(SNum, 20, L"%d", num);

			wcscat_s(retval->contains, size, SNum);
			if (wcslen(SNum) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, SellState);
			if (wcslen(SellState) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, point->time);
			if (wcslen(point->time) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->accessory);
			if (wcslen(point->accessory) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->model);
			if (wcslen(point->model) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->manufacturer);
			if (wcslen(point->manufacturer) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, UPrice);
			if (wcslen(UPrice) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, Num);
			if (wcslen(Num) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->customer);
			wcscat_s(retval->contains, size, L".\r\n");

			point = point->next;
			num++;
		}
	}
	else if (item == 3)
	{
		while (point != NULL)
		{
			if (wcscmp(point->customer, itemname) != 0)
			{
				point = point->next;
				continue;
			}
			if (point->which == 1)
			{
				wcscpy_s(SellState, L"进货");
			}
			else if (point->which == 2)
			{
				wcscpy_s(SellState, L"批发");
			}
			else if (point->which == 3)
			{
				wcscpy_s(SellState, L"零售");
			}
			else
			{
				wcscpy_s(SellState, L"赠品");
			}
			if (point->which == 1)
			{
				point = point->next;
				continue;
			}
			swprintf_s(UPrice, 20, L"%.2lf", point->unit_price);
			swprintf(Num, 10, L"%.0lf", point->num);
			swprintf(SNum, 20, L"%d", num);

			wcscat_s(retval->contains, size, SNum);
			if (wcslen(SNum) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, SellState);
			if (wcslen(SellState) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, point->time);
			if (wcslen(point->time) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->accessory);
			if (wcslen(point->accessory) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->model);
			if (wcslen(point->model) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->manufacturer);
			if (wcslen(point->manufacturer) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, UPrice);
			if (wcslen(UPrice) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, Num);
			if (wcslen(Num) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}
			wcscat_s(retval->contains, size, point->customer);
			wcscat_s(retval->contains, size, L".\r\n");

			point = point->next;
			num++;
		}
	}
		/*
												while (point != NULL)
													{
							if (point->which == 1)
			{
				wcscpy_s(SellState, L"jinhuo");
			}
			else if (point->which == 2)
			{
				wcscpy_s(SellState, L"pifa");
			}
			else
			{
				wcscpy_s(SellState, L"lingshou");
			}
			swprintf_s(UPrice, 20, L"%lf", point->unit_price);
			swprintf(Num, 10, L"%lf", point->num);
			swprintf(SNum, 20, L"%d", num);

			wcscat_s(retval->contains, size, SNum);
			wcscat_s(retval->contains, size, L".\t\t");
			wcscat_s(retval->contains, size, SellState);
			wcscat_s(retval->contains, size, L".\t\t");
			wcscat_s(retval->contains, size, point->time);
			wcscat_s(retval->contains, size, L".\t\t");
			wcscat_s(retval->contains, size, point->accessory);
			wcscat_s(retval->contains, size, L".\t\t");
			wcscat_s(retval->contains, size, point->model);
			wcscat_s(retval->contains, size, L".\t\t");
			wcscat_s(retval->contains, size, point->manufacturer);
			wcscat_s(retval->contains, size, L".\t\t");
			wcscat_s(retval->contains, size, UPrice);
			wcscat_s(retval->contains, size, L".\t\t");
			wcscat_s(retval->contains, size, Num);
			wcscat_s(retval->contains, size, L".\t\t");
			wcscat_s(retval->contains, size, point->customer);
			wcscat_s(retval->contains, size, L". \r\n");

			point = point->next;

			num++;
		}*/

	return retval;
}

Str * create_inventory_report(List pointer)
{
	Str * retval = (Str*)malloc(sizeof(str));
	wchar_t tem[20];
	List point = pointer;
	List pointi = pointer;
	List pointj = pointer;
	int size = 409600;

	wcscpy_s(tem, L"\0");
	wcscpy_s(retval->contains, L"\0");

	wcscat_s(retval->contains, size, L"配件名称");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"配件型号");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"数量(个)");
	wcscat_s(retval->contains, size, L".\r\n");

	while (point != NULL)
	{
		if (point->state == 1 || point->which == 4)
		{
			point = point->next;
			continue;
		}
		wchar_t bufm[270];
		int num = 0;
		wcscpy_s(bufm, L"\0");
		wcscat_s(bufm, 270, point->accessory);
		wcscat_s(bufm, 270, point->model);

		wcscat_s(retval->contains, 409600, point->accessory);
		if (wcslen(point->accessory) > tabb)
		{
			wcscat_s(retval->contains, size, L".\t\t");
		}
		else
		{
			wcscat_s(retval->contains, size, L".\t\t\t");
		}

		wcscat_s(retval->contains, 409600, point->model);

		for (pointi = point; pointi != NULL; pointi = pointi->next)
		{
			wchar_t bufa[270];
			wcscpy_s(bufa, L"\0");
			wcscat_s(bufa, 270, pointi->accessory);
			wcscat_s(bufa, 270, pointi->model);
			if (wcscmp(bufm, bufa) == 0)
			{
				if (pointi->which == 1)
				{
					num += pointi->num;
				}
				else if (pointi->which == 4)
				{
					;
				}
				else if (pointi->which != 1)
				{
					num -= pointi->num;
				}
				pointi->state = 1;
			}
		}//for
		swprintf(tem, 20, L"%d", num);
		if (wcslen(tem) > tabb)
		{
			wcscat_s(retval->contains, size, L".\t\t");
		}
		else
		{
			wcscat_s(retval->contains, size, L".\t\t\t");
		}
		wcscat_s(retval->contains, tem);
		wcscat_s(retval->contains, 4096, L"\r\n");
		point = point->next;
	}//while
	while (pointj != NULL)
	{
		pointj->state = 0;
		pointj = pointj->next;
	}
	return retval;
}

Str * get_turnover_purch(List pointer)//yingyee
{
	List point = pointer;
	Str * retval = (Str*)malloc(sizeof(str));
	double doubleretval = 0;
	while (point != NULL)
	{
		if (point->which == 1 || point->which == 4)
		{
			point = point->next;
			continue;
		}
		doubleretval += (point->num) * (point->unit_price);
		point = point->next;
	}
	swprintf(retval->contains, 409600, L"%.2lf", doubleretval);
	return retval;
}

Str * get_profit_value(List pointer)
{
	List point = pointer;
	Str * retval = (Str*)malloc(sizeof(str));

	double doubleretval = 0;
	double doubleturnovervalue = 0;
	double doublepurchasprice = 0;

	doubleturnovervalue = _wtof(get_turnover_purch(point)->contains);

	while (point != NULL)
	{
		if (point->which == 2 || point->which == 3)
		{
			point = point->next;
			continue;
		}
		doublepurchasprice += (point->num) * (point->unit_price);
		point = point->next;
	}

	swprintf(retval->contains, 409600, L"%.2lf", doubleturnovervalue - doublepurchasprice);
	return retval;
}

Str * search_time(List pointer, wchar_t * start, wchar_t * end)
{
	if (wcscmp(start, end) >= 0)
	{
		MessageBox(NULL, TEXT("起始时间大于截止时间"), TEXT("警告"), MB_OK);
		return NULL;
	}

	Str * retval = (Str*)malloc(sizeof(Str));
	List point = pointer;
	int num = 1;
	int size = 409600;
	wcscpy_s(retval->contains, L"\0");

	wchar_t UPrice[20], Num[10], SNum[10], SellState[20];

	wcscat_s(retval->contains, size, L"序号");
	wcscat_s(retval->contains, size, L".\t\t\t");
	wcscat_s(retval->contains, size, L"货物类型");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"时间");
	wcscat_s(retval->contains, size, L".\t\t\t");
	wcscat_s(retval->contains, size, L"配件名称");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"配件型号");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"制造商");
	wcscat_s(retval->contains, size, L".\t\t\t");
	wcscat_s(retval->contains, size, L"单价(元)");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"数量(个)");
	wcscat_s(retval->contains, size, L".\t\t");
	wcscat_s(retval->contains, size, L"供货商");
	wcscat_s(retval->contains, size, L".\r\n");

	while (point != NULL)
	{

		if (wcscmp(point->time, start) < 0 || wcscmp(point->time, end) > 0)
		{
			point = point->next;
			continue;
		}
			wchar_t peijianzhonglei[100];
			wcscpy_s(peijianzhonglei, L"\0");
			wcscat_s(peijianzhonglei, 100, point->accessory);
			wcscat_s(peijianzhonglei, 100, point->model);

			if (point->which == 1)
			{
				wcscpy_s(SellState, L"进货");
			}
			else if (point->which == 2)
			{
				wcscpy_s(SellState, L"批发");
			}
			else if (point->which == 3)
			{
				wcscpy_s(SellState, L"零售");
			}
			else
			{
				wcscpy_s(SellState, L"赠品");
			}
			swprintf_s(UPrice, 20, L"%.2lf", point->unit_price);
			swprintf(Num, 10, L"%.0lf", point->num);
			swprintf(SNum, 20, L"%d", num);

			wcscat_s(retval->contains, size, SNum);
			if (wcslen(SNum) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, SellState);
			if (wcslen(SellState) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, point->time);
			if (wcslen(point->time) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, point->accessory);
			if (wcslen(point->accessory) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, point->model);
			if (wcslen(point->model) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, point->manufacturer);
			if (wcslen(point->manufacturer) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, UPrice);
			if (wcslen(UPrice) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, Num);
			if (wcslen(Num) > tabb)
			{
				wcscat_s(retval->contains, size, L".\t\t");
			}
			else
			{
				wcscat_s(retval->contains, size, L".\t\t\t");
			}

			wcscat_s(retval->contains, size, point->customer);
			wcscat_s(retval->contains, size, L".\r\n");

			point = point->next;
			num++;
	}
	return retval;
}


bool delete_node_purch(List pointer, double num)
{
	List prepoint = pointer;
	List curpoint = prepoint->next;
	double n = num;
	int i = 1;

	while (i < n)
	{
		prepoint = prepoint->next;
		curpoint = curpoint->next;
		if (curpoint == NULL)
		{
			return FALSE;
		}
		i++;
	}

	prepoint->next = curpoint->next;
	free(curpoint);

	return TRUE;
}

bool find_purch_node(List pointer, wchar_t * item, double num)
{
	List point = pointer;
	double numhas = 0;

	while (point != NULL)
	{
		wchar_t itemhas[100];

		wcscpy_s(itemhas, L"\0");
		if (point->which == 1)
		{
			wcscmp(itemhas, point->accessory);
			wcscmp(itemhas, point->model);
			if (wcscmp(item, itemhas))
			{
				numhas += point->num;
			}
		}
		point = point->next;
	}
	if (numhas < num)
	{
		return FALSE;
	}
	return TRUE;
}


Str * present_static(Present * pres, int num)
{
	int i = 0;
	Str * retval = (Str *)malloc(sizeof(Str));
	wcscpy_s(retval->contains, L"\0");

	wcscat_s(retval->contains, L"礼物名称");
	wcscat_s(retval->contains, L"\t\t");
	wcscat_s(retval->contains, L"客户名称");
	wcscat_s(retval->contains, L"\r\n");

	while (i<=num)
	{
		//wcscmp(pres[i].customer, L"\0");
		wcscat_s(retval->contains, pres[i].presentname);
		if (wcslen(pres[i].presentname) > tabb)
		{
			wcscat_s(retval->contains, 409600, L".\t\t");
		}
		else
		{
			wcscat_s(retval->contains, 409600, L".\t\t\t");
		}
		wcscat_s(retval->contains, pres[i].customer);
		wcscat_s(retval->contains, L"\r\n");
		i++;
	}
	return retval;
}

int init_present(List pointer, Present * pres)
{
	List point = pointer;
	int n = 0;
	while (point != NULL)
	{
		if (point->which == 4)
		{
			pres[n].price = point->unit_price;
			wcscpy_s(pres[n].presentname, point->accessory);
			wcscpy_s(pres[n].customer, point->customer);
			n++;
		}
		point = point->next;
	}
	return n;
}

Str * text_present_static(List pointer)
{
	List point = pointer;

	Str * retval = (Str *)malloc(sizeof(Str));
	wcscpy_s(retval->contains, L"\0");

	wcscat_s(retval->contains, L"礼物名称");
	wcscat_s(retval->contains, L"\t\t");
	wcscat_s(retval->contains, L"客户名称");
	wcscat_s(retval->contains, L"\r\n");
	while (point != NULL)
	{
		if (point->which == 4)
		{
			wcscat_s(retval->contains, point->accessory);
			wcscat_s(retval->contains, L"\t\t\t");
			wcscat_s(retval->contains, point->customer);
			wcscat_s(retval->contains, L"\r\n");
		}
		point = point->next;
	}
	return retval;
}
/*
List add_list(List headpointer, 
		int which, 
		const wchar_t *time, 
		const wchar_t *accessory, 
		const wchar_t *model,
		const wchar_t *manufacturer,
		double unit_price,
		int num,
		double total_price,
		const wchar_t *customer)
{
	List creat_headpointer = NULL;									//ÓÐÍ·½áµã£¬Í·½áµã²»´æÊý¾Ý 
	List new_node = NULL;

	new_node = (List)malloc(sizeof(p));

	new_node->which = which;

	wcscpy_s(new_node->time, time);
	wcscpy_s(new_node->accessory, accessory);
	wcscpy_s(new_node->model, model);
	wcscpy_s(new_node->manufacturer, manufacturer);

	new_node->unit_price = unit_price;
	new_node->num = num;
	new_node->total_price = total_price;

	wcscpy_s(new_node->customer, customer);

	if (headpointer != NULL) 
	{
		new_node->next = headpointer->next;
		headpointer->next = new_node;
		return headpointer;
	} 
	else 
	{
		creat_headpointer->next = new_node;
		new_node->next = NULL;
		return creat_headpointer;
	}
}*/
/*
void find_list_del(List headpointer, int which, 
		wchar_t *time, wchar_t *accessory, wchar_t *model) 
{

	List prepointer = headpointer;
	List thispointer = prepointer->next;
	List freepointer = NULL;

	while (thispointer != NULL) {
		if (thispointer->which == which && 
			!_tcscmp(thispointer->time, time) && 
			!_tcscmp(thispointer->accessory, accessory) && 
			!_tcscmp(thispointer->model, model)) 
		{//ÔÚÁ´±íÖÐÕÒµ½·ûºÏµÄÊý¾Ý 

			if (thispointer->next != NULL) 
			{
				freepointer = thispointer;
				thispointer = thispointer->next;
				prepointer->next = thispointer;
				free(freepointer);
			} 
			else 
			{
				prepointer = NULL;
				freepointer = thispointer;
				free(freepointer);
			}
		}
		else 
		{//´Ë½ÚµãÊý¾Ý²»·ûºÏ£¬¼ÌÐø±éÀúÁ´±í 
			prepointer = thispointer;
			thispointer = thispointer->next;
		}
	}
}*/
/*
List add(List headpointer,
	int which,
	const wchar_t *time,
	const wchar_t *accessory,
	const wchar_t *model,
	const wchar_t *manufacturer,
	double unit_price,
	int num,
	double total_price,
	const wchar_t *customer)
{//ÊÖ¶¯Ìí¼ÓÊý¾Ý 
	FILE *fp;
	p p1;		 //p1ÓÃÓÚÔÝÊ±´¢´æ½ø»õÊý¾Ý 

	//printf("ÇëÑ¡ÔñÄúÒªÊÖ¶¯Â¼ÈëµÄ¼ÇÂ¼£º1.½ø»õ¼ÇÂ¼£¬2.Åú·¢ÏúÊÛ¼ÇÂ¼£¬3.ÁãÊÛÏúÊÛ¼ÇÂ¼\n");
	//printf("²¢ÒÀ´ÎÊäÈëÊ±¼ä,Åä¼þÃû³Æ,ÐÍºÅ,ÖÆÔìÉÌ,µ¥¼Û,ÊýÁ¿,×Ü¼Û£¬¹©»õÉÌ£¨Ã¿ÊäÈëÒ»Ïî°´Ò»´Î»Ø³µ£©£¬Ê¾Àý:\n1\n03221428\nkeyboard\nA\nJACK\n88.8\n100\n8880\nMARRY\n");

		p1.which = which;
		wcscpy_s(p1.time, time);
		wcscpy_s(p1.accessory, accessory);
		wcscpy_s(p1.model, model);
		wcscpy_s(p1.manufacturer, manufacturer);
		p1.unit_price = unit_price;
		p1.num = num;
		p1.total_price = total_price;
		wcscpy_s(p1.customer, customer);

	if ((fopen_s(&fp, "record", "a")) == NULL) 
	{
		//printf("´ò¿ª¼ÇÂ¼ÎÄ¼þÊ§°Ü");
		return NULL;//·µ»ØNULL±íÊ¾´ò¿ªÎÄ¼þÊ§°Ü 
	}
	else 
	{
		fwprintf(fp, L"%d %d %s %s %s %s %f %d %f %s\n", 
			p1.which, 
			p1.time, 
			p1.accessory, 
			p1.model, 
			p1.manufacturer, 
			p1.unit_price, 
			p1.num, 
			p1.total_price, 
			p1.customer);

		fclose(fp);

		return add_list(headpointer, 
			p1.which, 
			p1.time, 
			p1.accessory, 
			p1.model, 
			p1.manufacturer, 
			p1.unit_price, 
			p1.num, 
			p1.total_price, 
			p1.customer);
	}
}*/
/*
void del(List headpointer, int which, wchar_t *time, wchar_t *accessory, wchar_t *model)

{//which¼´1½ø»õ2Åú·¢3ÁãÊÛ£¬time¼´Ê±¼ä£¬accessory¼´Åä¼þÃû³Æ£¬model¼´ÐÍºÅ  £¨Ç°Èý¸ö¶¼ÐèÒªÔÚÊý×éÄ©Î²¼ÓÉÏ¿Õ¸ñ £© ~ÏÈÊäÈëºóµ÷ÓÃ
	FILE *fp1, *fp0;

	wchar_t a[1000];//´ÓÔ­ÎÄ¼þÖÐ¶ÁÈ¡Êý¾ÝÔÝÊ±´¢´æÓÚa
	wchar_t dela[1000];//ÐèÒªÉ¾³ýµÄ¼ÇÂ¼µÄÊý¾Ý 
	wchar_t b[1000]; //bÓÃÓÚ½ØÈ¡dela³¤¶ÈµÄa 

	dela[0] = which;
	dela[1] = ' ';
	wcscat_s(dela, time);
	wcscat_s(dela, L" ");//¼Ó¿Õ¸ñ¹æ·¶¸ñÊ½
	wcscat_s(dela, accessory);
	wcscat_s(dela, L" ");//¼Ó¿Õ¸ñ¹æ·¶¸ñÊ½
	wcscat_s(dela, model);
	wcscat_s(dela, L" \0");//¼Ó¿Õ¸ñ²¢½áÊø

	if ((fopen_s(&fp1, "record", "r")) == NULL && (fopen_s(&fp0, "record0", "w")) == NULL)
		printf("´ò¿ªÎÄ¼þÊ§°Ü\n");//´ò¿ª½ø»õ¼ÇÂ¼ÎÄ¼þ»òÓÃÓÚ¸´ÖÆµÄÎÄ¼þÊ§°Ü 

	else if ((fopen_s(&fp1, "record", "r")) == NULL && (fopen_s(&fp0, "record0", "w")) != NULL) 
	{
		printf("´ò¿ªÎÄ¼þÊ§°Ü\n");
		fclose(fp0);
	}
	else if ((fopen_s(&fp1, "record", "r")) != NULL && (fopen_s(&fp0, "record0", "w")) == NULL) 
	{
		printf("´ò¿ªÎÄ¼þÊ§°Ü\n");
		fclose(fp1);
	}
	else 
	{
		while (_fgetts(a, 1000, fp1)) 
		{				//Èç¹ûÃ»ÕÒµ½Êý¾ÝÔõÃ´°ìÄØ£¿ <<<<<<<<<<<<<<
			wcscpy_s(b, a);
			b[_tcsclen(dela)] = '\0';
			if (_tcscmp(b, dela))//Èç¹ûÕâÒ»ÐÐÎÄ¼þÊý¾Ý²»·ûºÏÌõ¼þ 
				_fputts(a, fp0);//¸´ÖÆÕâÐÐÊý¾Ýµ½ÐÂÎÄ¼þÀï 
			else 
			{			//·ñÔòÕâÐÐÊý¾Ý¼´ÊÇÐèÒª±»É¾µôµÄÊý¾Ý£¬²»¸´ÖÆµ½ÐÂÎÄ¼þÀï£¬½øÐÐÁ´±í²Ù×÷ 
				find_list_del(headpointer, which, time, accessory, model);//Õâ¸öº¯Êý²»¶ÔÍ·Ö¸Õë½øÐÐ²Ù×÷	
			}
			fclose(fp1);
			fclose(fp0);
			remove("record");
			rename("record0", "record");
		}
	}
}*/
/*
void read_new(List headpointer) 
{//ÎÄ¼þÖÐ¶ÁÈëÊý¾Ý

	FILE *fnew, *fo;//´Ó fnew¶ÁÈëÊý¾Ý´æµ½ foÖÐ 
	int num;
	p temp;//ÔÝ´æÊý¾Ý 
	wchar_t n[1000];
	wchar_t filename[1000];

	printf("ÇëÊäÈëÐèÒª¶ÁÈ¡µÄÎÄ¼þµÄÎÄ¼þÃû£¨°üÀ¨Â·¾¶£¬Èç¡°E:\\hello\\filename¡±,¸ñÊ½Îªtxt£¬ÎÄ¼þÖÐÃ¿Ìõ¼ÇÂ¼Ó¦µ¥¶À³ÉÐÐÇÒºÏºõ¹æ·¶£©\n");
	_getts_s(filename, 1000);

	if ((fopen_s(&fnew, "filename", "r")) == NULL && (fopen_s(&fo, "record", "a")) == NULL)
		printf("´ò¿ªÎÄ¼þÊ§°Ü\n");

	else if ((fopen_s(&fnew, "filename", "r")) != NULL && (fopen_s(&fo, "record", "a")) == NULL)
	{
		printf("´ò¿ªÎÄ¼þÊ§°Ü\n");
		fclose(fnew);
	}
	else if ((fopen_s(&fnew, "filename", "r")) != NULL && (fopen_s(&fo, "record", "a")) == NULL)
	{
		printf("´ò¿ªÎÄ¼þÊ§°Ü\n");
		fclose(fo);
	}
	else 
	{
		while (fscanf(fnew, "%d %s %s %s %s %lf %d %lf %s", &temp.which, temp.time, temp.accessory, 
			temp.model, temp.manufacturer, &temp.unit_price, &temp.num, &temp.total_price, temp.customer)) 
		{
			add_list(headpointer, temp.which, temp.time, temp.accessory, temp.model, 
				temp.manufacturer, temp.unit_price, temp.num, temp.total_price, temp.customer);

			fprintf(fo, "%d %s %s %s %s %lf %d %lf %s\n", temp.which, temp.time, temp.accessory, 
				temp.model, temp.manufacturer, temp.unit_price, temp.num, temp.total_price, temp.customer);
		}
		fclose(fo);
		fclose(fnew);

	}
}
void correct(List headpointer, int which, wchar_t *time, wchar_t *accessory, wchar_t *model) {//which¼´1½ø»õ2Åú·¢3ÁãÊÛ£¬time¼´Ê±¼ä£¬accessory¼´Åä¼þÃû³Æ£¬model¼´ÐÍºÅ
	FILE *fp, *fp0;
	wchar_t reserve[1000];//´ÓÔ­ÎÄ¼þÖÐ¶ÁÈ¡Êý¾ÝÔÝÊ±´¢´æÓÚreserve
	wchar_t dela[1000];//ÐèÒªÉ¾³ýµÄÊý¾Ý  µÄÌØÕ÷ 
	wchar_t len[1000]; //lenÓÃÓÚ½ØÈ¡dela³¤¶ÈµÄreserve
	p temp;//ÔÝ´æÕýÈ·µÄÊý¾Ý 

	find_list_del(headpointer, which, time, accessory, model);//ÏÈ´ÓÁ´±íÖÐÉ¾³ýÕâÌõ´íÎóµÄÊý¾Ý£¬Ö®ºóÔÙÌí¼ÓÕýÈ·µÄÊý¾Ý 

	wcscat_s(dela, time);
	wcscat_s(dela, L" ");//¼Ó¿Õ¸ñ¹æ·¶¸ñÊ½
	wcscat_s(dela, accessory);
	wcscat_s(dela, L" ");//¼Ó¿Õ¸ñ¹æ·¶¸ñÊ½
	wcscat_s(dela, model);
	wcscat_s(dela, L" \0"); //¼Ó¿Õ¸ñ²¢½áÊø 

	if ((fopen_s(&fp, "record", "r")) == NULL || (fopen_s(&fp0, "record0", "w")) == NULL)
		printf("´ò¿ªÎÄ¼þÊ§°Ü");//´ò¿ª¼ÇÂ¼ÎÄ¼þ»òÓÃÓÚ¸´ÖÆµÄÎÄ¼þÊ§°Ü 

	else 
	{
		while (_fgetts(reserve, 1000, fp)) 
		{
			wcscpy_s(len, reserve);
			len[_tcsclen(dela)] = '\0';
			if (_tcscmp(len, dela))
				_fputts(reserve, fp0);

			else 
			{
				if (which == 1)
					printf("ÇëÒÀ´ÎÊäÈëÕýÈ·µÄÊ±¼ä,Åä¼þÃû³Æ,ÐÍºÅ,ÖÆÔìÉÌ,µ¥¼Û,ÊýÁ¿,×Ü¼Û£¬¹©»õÉÌ£¨Ã¿ÊäÈëÒ»Ïî°´Ò»´Î¿Õ¸ñ£¬×îºó°´Ò»ÏÂ»Ø³µ£©£¬Ê¾Àý:\n03221428 keyboard A JACK 88.8 100 8880 MARRY \n");
				else if (which == 2)
					printf("ÇëÒÀ´ÎÊäÈëÕýÈ·µÄÊ±¼ä,Åä¼þÃû³Æ,ÐÍºÅ,ÖÆÔìÉÌ,Åú·¢µ¥¼Û,ÊýÁ¿,×Ü¼Û£¬¿Í»§ÐÅÏ¢£¨Ã¿ÊäÈëÒ»Ïî°´Ò»´Î¿Õ¸ñ£¬×îºó°´Ò»ÏÂ»Ø³µ£©£¬Ê¾Àý:\n03221428 keyboard A JACK 88.8 100 8880 MARRY \n");
				else
					printf("ÇëÒÀ´ÎÊäÈëÕýÈ·µÄÊ±¼ä,Åä¼þÃû³Æ,ÐÍºÅ,ÖÆÔìÉÌ,ÁãÊÛµ¥¼Û,ÊýÁ¿,×Ü¼Û£¬¿Í»§ÐÅÏ¢£¨Ã¿ÊäÈëÒ»Ïî°´Ò»´Î¿Õ¸ñ£¬×îºó°´Ò»ÏÂ»Ø³µ£©£¬Ê¾Àý:\n03221428 keyboard A JACK 88.8 100 8880 MARRY \n");

				scanf("%s%s%s%s%lf%d%lf%s", temp.time, temp.accessory, temp.model, temp.manufacturer, &temp.unit_price, &temp.num, &temp.total_price, temp.customer);
				add_list(headpointer, which, temp.time, temp.accessory, temp.model, temp.manufacturer, temp.unit_price, temp.num, temp.total_price, temp.customer);
				fprintf(fp0, "%d %s %s %s %s %lf %d %lf %s\n", which, temp.time, temp.accessory, temp.model, temp.manufacturer, temp.unit_price, temp.num, temp.total_price, temp.customer);
			}
		}
		fclose(fp);
		fclose(fp0);
		remove("record");
		rename("record0", "record");
	}

}
*/