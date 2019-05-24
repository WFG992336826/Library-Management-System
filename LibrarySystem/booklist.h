#pragma once
#include "pch.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string>

using namespace std;

//����һ���������ݽṹ
typedef struct NODE
{
	//������
	string book_name;
	string book_ISBN;//���ʱ�׼ͼ����
	string book_author;
	string book_publish_house;
	string book_publish_time;
	string book_storage_time;
	int book_num;
	int book_borrow_num;
	int book_borrow_num_time;
	struct NODE* pNext;//ָ����
}BookInfor, * pBookNode;

//��������
pBookNode CreatList(void);
void InitList(pBookNode pHead);
BookInfor CountAllBook(pBookNode pHead);
bool is_empty_list(pBookNode pHead);
int length_list(pBookNode pHead);
bool insert_list(pBookNode pHead, int pos, int val);
bool AddListItem(pBookNode pHead, BookInfor book_infor);
bool delete_list(pBookNode pHead, int pos, int* val);
void sort_list(pBookNode pHead);
bool ChangeBookInfor(pBookNode pHead, BookInfor book_infor);
pBookNode MatchBookInfor(pBookNode pHead, BookInfor book_infor);
bool DeleteListItem(pBookNode pHead, BookInfor book_infor);
void SortListBookNume(pBookNode pHead);

BookInfor pBookNode2BookInfor(pBookNode p);

pBookNode BookInfor2pBookNode(BookInfor book_infor, pBookNode p);
