#include "pch.h"
#include "LibrarySystemDlg.h"
#include "booklist.h"

pBookNode CreatList(void)
{
	//int len, val;
	pBookNode pHead = (pBookNode)malloc(sizeof(NODE));
	if (NULL == pHead)
	{
		printf("分配失败，程序终止\n");
		exit(-1);
	}

	pBookNode pTail = pHead;
	pTail->pNext = NULL;

	/*printf("请输入生成链表结点的个数： len = ");
	scanf_s("%d", &len);
	for (int i = 0; i < len; i++)
	{
		printf("请输入第%d个结点的值：", i + 1);
		scanf_s("%d", &val);

		pBookNode pNew = (pBookNode)malloc(sizeof(NODE));
		if (NULL == pNew)
		{
			printf("分配失败，程序终止\n");
			exit(-1);
		}
		pNew->book_num = val;
		pTail->pNext = pNew;
		pNew->pNext = NULL;
		pTail = pNew;
	}*/

	return pHead;
}

void InitList(pBookNode pHead)
{
	ReadData(pHead);
}

BookInfor CountAllBook(pBookNode pHead)
{
	BookInfor book_infor;
	book_infor.book_borrow_num = 0;
	book_infor.book_num = 0;
	pBookNode p = pHead->pNext;
	while (NULL != p)
	{
		book_infor.book_borrow_num += p->book_borrow_num;
		book_infor.book_num += p->book_num;
		p = p->pNext;
	}
	return book_infor;
}

bool is_empty_list(pBookNode pHead)
{
	if (pHead->pNext == NULL)
	{
		printf("数组为空\n");
		return true;
	}
	else
	{
		printf("数组不为空\n");
		return false;
	}
}

int length_list(pBookNode pHead)
{
	pBookNode p = pHead->pNext;
	int len = 0;
	while (NULL != p)
	{
		len++;
		p = p->pNext;
	}
	return len;
}

void sort_list(pBookNode pHead)
{
	int t;
	pBookNode p = pHead;
	pBookNode q = pHead;
	for (p = p->pNext; p != NULL; p = p->pNext)
	{
		for (q = p; q != NULL; q = q->pNext)
		{
			if (p->book_num > q->book_num)   //a[i] > a[j]
			{
				t = p->book_num;         //t = a[i];
				p->book_num = q->book_num;   //a[i] = a[j];
				q->book_num = t;         //a[j] = t;
			}
		}
	}
}

bool insert_list(pBookNode pHead, int pos, int val)
{
	pBookNode p = pHead;
	int i = 0;
	while (p != NULL && i < pos - 1)
	{
		p = p->pNext;
		i++;
	}
	if (i > pos - 1 || p == NULL)
	{
		return false;
	}

	//pBookNode pNew = (pBookNode)malloc(sizeof(NODE));
	pBookNode pNew = new NODE;

	if (NULL == pNew)
	{
		printf("分配失败，程序终止\n");
		exit(-1);
	}
	pNew->book_num = val;
	pNew->pNext = p->pNext;
	p->pNext = pNew;

	return true;
}

bool AddListItem(pBookNode pHead, BookInfor book_infor)
{
	pBookNode p = pHead;
	bool flag_same_book = false;
	while (NULL != p->pNext)
	{
		p = p->pNext;
		if (book_infor.book_ISBN == p->book_ISBN)
		{
			flag_same_book = true;
			break;
		}
	}

	//pBookNode pNew = (pBookNode)malloc(sizeof(NODE));
	pBookNode pNew = new NODE;
	if (NULL == pNew)
	{
		printf("分配失败，程序终止\n");
		exit(-1);
	}

	if (!flag_same_book)
	{
		pNew->book_name = book_infor.book_name;
		pNew->book_ISBN = book_infor.book_ISBN;
		pNew->book_author = book_infor.book_author;
		pNew->book_publish_house = book_infor.book_publish_house;
		pNew->book_publish_time = book_infor.book_publish_time;
		pNew->book_storage_time = book_infor.book_storage_time;
		pNew->book_num = book_infor.book_num;
		pNew->book_borrow_num = book_infor.book_borrow_num;
		pNew->book_borrow_num_time = book_infor.book_borrow_num_time;
		p->pNext = pNew;
		pNew->pNext = NULL;
		return true;
	}
	else
	{
		return false;
	}
	
}

bool delete_list(pBookNode pHead, int pos, int* val)
{
	pBookNode p = pHead;
	int i = 0;
	while (p != NULL && i < pos - 1)
	{
		p = p->pNext;
		i++;
	}
	if (i > pos - 1 || p == NULL)
	{
		return false;
	}

	pBookNode pNew = p->pNext;
	*val = pNew->book_num;
	p->pNext = p->pNext->pNext;
	free(pNew);
	return true;
}

bool ChangeBookInfor(pBookNode pHead, BookInfor book_infor)
{
	pBookNode p = pHead;
	while (NULL != p->pNext)
	{
		p = p->pNext;
		if (p->book_ISBN == book_infor.book_ISBN)
		{
			if (p->book_name != book_infor.book_name ||
				p->book_author != book_infor.book_author ||
				p->book_publish_house != book_infor.book_publish_house ||
				p->book_publish_time != book_infor.book_publish_time ||
				p->book_storage_time != book_infor.book_storage_time ||
				p->book_num != book_infor.book_num ||
				p->book_borrow_num != book_infor.book_borrow_num)
			{
				p->book_name = book_infor.book_name;
				p->book_ISBN = book_infor.book_ISBN;
				p->book_author = book_infor.book_author;
				p->book_publish_house = book_infor.book_publish_house;
				p->book_publish_time = book_infor.book_publish_time;
				p->book_storage_time = book_infor.book_storage_time;
				p->book_num = book_infor.book_num;
				p->book_borrow_num = book_infor.book_borrow_num;
				p->book_borrow_num_time = book_infor.book_borrow_num_time;
			}
			return true;
		}
	}
	return false;
}

pBookNode MatchBookInfor(pBookNode pHead, BookInfor book_infor)
{
	pBookNode p = pHead;
	while (NULL != p->pNext)
	{
		p = p->pNext;
		/*p->book_publish_time == book_infor.book_publish_time ||
		p->book_storage_time == book_infor.book_storage_time ||
		p->book_num == book_infor.book_num ||
		p->book_borrow_num == book_infor.book_borrow_num*/
		if (p->book_name == book_infor.book_name &&
			p->book_ISBN == book_infor.book_ISBN &&
			p->book_author == book_infor.book_author &&
			p->book_publish_house == book_infor.book_publish_house &&
			p->book_publish_time == book_infor.book_publish_time &&
			p->book_storage_time == book_infor.book_storage_time)
		{
			return p;
		}
	}
	return NULL;
}

bool DeleteListItem(pBookNode pHead, BookInfor book_infor)
{
	pBookNode p = pHead;
	while (p->pNext != NULL)
	{
		if (p->pNext->book_ISBN == book_infor.book_ISBN)
		{
			pBookNode pNew = p->pNext;
			p->pNext = p->pNext->pNext;
			free(pNew);
			return true;
		}
		p = p->pNext;
	}
	
	return false;
}

void SortListBookNume(pBookNode pHead)
{
	pBookNode p = pHead;
	pBookNode q = pHead;
	BookInfor book_infor1;
	BookInfor book_infor2;
	for (p = p->pNext; p != NULL; p = p->pNext)
	{
		for (q = p; q != NULL; q = q->pNext)
		{
			if (p->book_name < q->book_name)
			{
				book_infor1 = pBookNode2BookInfor(p);
				book_infor2 = pBookNode2BookInfor(q);

				p->book_name = book_infor2.book_name;
				p->book_ISBN = book_infor2.book_ISBN;
				p->book_author = book_infor2.book_author;
				p->book_publish_house = book_infor2.book_publish_house;
				p->book_publish_time = book_infor2.book_publish_time;
				p->book_storage_time = book_infor2.book_storage_time;
				p->book_num = book_infor2.book_num;
				p->book_borrow_num = book_infor2.book_borrow_num;
				p->book_borrow_num_time = book_infor2.book_borrow_num_time;

				q->book_name = book_infor1.book_name;
				q->book_ISBN = book_infor1.book_ISBN;
				q->book_author = book_infor1.book_author;
				q->book_publish_house = book_infor1.book_publish_house;
				q->book_publish_time = book_infor1.book_publish_time;
				q->book_storage_time = book_infor1.book_storage_time;
				q->book_num = book_infor1.book_num;
				q->book_borrow_num = book_infor1.book_borrow_num;
				q->book_borrow_num_time = book_infor1.book_borrow_num_time;

			}
		}
	}

	/*pBookNode t = NULL;
	pBookNode p = pHead;
	pBookNode q = pHead;
	for (p = p->pNext; p->pNext != NULL; p = p->pNext)
	{
		for (q = p; q->pNext->pNext != NULL; q = q->pNext)
		{
			if (p->pNext->book_name < q->pNext->book_name)
			{
				t = p->pNext->pNext;
				p->pNext->pNext = q->pNext->pNext;
				q->pNext->pNext = t;

				t = p->pNext;
				p->pNext = q->pNext;
				q->pNext = t;
			}
		}
	}
	p = pHead;
	while (p->pNext->pNext != NULL)
	{
		p = p->pNext;
	}

	for (q = pHead; q->pNext->pNext != NULL; q = q->pNext)
	{
		if (p->pNext->book_name < q->pNext->book_name)
		{
			//p->pNext->pNext = q->pNext;
			//q->pNext = p->pNext;
			//p->pNext = NULL;

			//break;

			t = p->pNext->pNext;
			p->pNext->pNext = q->pNext->pNext;
			q->pNext->pNext = t;

			t = p->pNext;
			p->pNext = q->pNext;
			q->pNext = t;

			t = NULL;
		}
	}*/

}

BookInfor pBookNode2BookInfor(pBookNode p)
{
	BookInfor book_infor;
	book_infor.book_name = p->book_name;
	book_infor.book_ISBN = p->book_ISBN;
	book_infor.book_author = p->book_author;
	book_infor.book_publish_house = p->book_publish_house;
	book_infor.book_publish_time = p->book_publish_time;
	book_infor.book_storage_time = p->book_storage_time;
	book_infor.book_num = p->book_num;
	book_infor.book_borrow_num = p->book_borrow_num;
	book_infor.book_borrow_num_time = p->book_borrow_num_time;

	return book_infor;
}

pBookNode BookInfor2pBookNode(BookInfor book_infor, pBookNode p)
{
	p->book_name = book_infor.book_name;
	p->book_ISBN = book_infor.book_ISBN;
	p->book_author = book_infor.book_author;
	p->book_publish_house = book_infor.book_publish_house;
	p->book_publish_time = book_infor.book_publish_time;
	p->book_storage_time = book_infor.book_storage_time;
	p->book_num = book_infor.book_num;
	p->book_borrow_num = book_infor.book_borrow_num;
	p->book_borrow_num_time = book_infor.book_borrow_num_time;

	return p;
}
