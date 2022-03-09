#pragma once

#include "stdafx.h"
#include <stdbool.h>

#define tabb 7

typedef struct Purchase {
	int which;
	int state = 0;//which==1�����ۣ�which==2��������which==3������ 
	wchar_t time[20];//ʱ���������ʱ��03221428�����¶�ʮ����ʮ�ĵ��ʮ�˷� 
	wchar_t accessory[50];//�������
	wchar_t model[20];//�ͺ� 
	wchar_t manufacturer[50];//������ 
	double unit_price;//1���� ��2�������ۣ�3���۵��� 
	double num;//���� 
	double total_price;//�ܼ� 
	wchar_t customer[50];//����ʱ����Ϊ1������ ���ۺ�����ʱ���۴���Ϊ2 3�ͻ���Ϣ 
	struct Purchase *next;//ָ�� 
}p, *List;

typedef struct str {
	wchar_t contains[409600];
}Str;

typedef struct present
{
	double price = 0;
	wchar_t customer[50];
	wchar_t presentname[50];
}Present;

List insert_node_purch(List pointer,
	int which,
	const wchar_t *time,
	const wchar_t *accessory,
	const wchar_t *model,
	const wchar_t *manufacturer,
	double unit_price,
	double num,
	double total_price,
	const wchar_t *customer);

List init_purch_chain(List pointer);

void destory_purch_chain(List pointer);

void chain_to_file(FILE*fp, const List pointer);

List file_to_chain(FILE*fp, List pointer);

Str* chain_to_string(List pointer, int size);

void rewrite_node_purch(List pointer,
	int which,
	const wchar_t *time,
	const wchar_t *accessory,
	const wchar_t *model,
	const wchar_t *manufacturer,
	double unit_price,
	double num,
	double total_price,
	const wchar_t *customer);

List find_node_purch(List pointer, double n);

Str * search_node_purch(List pointer, wchar_t*, double item);

Str * create_inventory_report(List pointer);

Str * get_turnover_purch(List pointer);

Str * get_profit_value(List pointer);

Str * search_time(List pointer, wchar_t * start, wchar_t * end);

bool delete_node_purch(List pointer, double num);

bool find_purch_node(List pointer, wchar_t * item, double num);

Str * present_static(Present * pres, int num);

Str * text_present_static(List pointer);

int init_present(List pointer, Present * pres);




List add_list(List headpointer,
		int which,
		const wchar_t *time,
		const wchar_t *accessory,
		const wchar_t *model,
		const wchar_t *manufacturer,
		double unit_price,
		int num,
		double total_price,
		const wchar_t *customer);

void find_list_del(List headpointer, 
		int which,
		wchar_t *time, 
		wchar_t *accessory, 
		wchar_t *model);

List add(List headpointer,
	int which,
	const wchar_t *time,
	const wchar_t *accessory,
	const wchar_t *model,
	const wchar_t *manufacturer,
	double unit_price,
	int num,
	double total_price,
	const wchar_t *customer);





void del(List headpointer, int which, wchar_t *time, wchar_t *accessory, wchar_t *model);

void read_new(List headpointer);

void correct(List headpointer, int which, wchar_t *time, wchar_t *accessory, wchar_t *model);