#include "pch.h"
#include "savedata.h"

bool SaveData(pBookNode pHead)
{
	CString file_path;
	CString strText;
	pBookNode p = pHead;

	TCHAR szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; 
	file_path = szFilePath;
	file_path = file_path + "bookdata\\data.txt";

	//判断文件是否存在，存在则删除重建
	DWORD dwRe = GetFileAttributes(file_path);
	if (dwRe != (DWORD) - 1)
	{
		DeleteFile(file_path);
	}

	FILE* fp;
	fopen_s(&fp, file_path, "w");
	if (fp == NULL)
	{
		return false;
	}

	while (p->pNext != NULL)
	{
		p = p->pNext;
		
		fprintf_s(fp, "%s\t", p->book_name.c_str());

		fprintf_s(fp, "%s\t", p->book_ISBN.c_str());
		fprintf_s(fp, "%s\t", p->book_author.c_str());
		fprintf_s(fp, "%s\t", p->book_publish_house.c_str());
		fprintf_s(fp, "%s\t", p->book_publish_time.c_str());
		fprintf_s(fp, "%s\t", p->book_storage_time.c_str());
		fprintf_s(fp, "%d\t", p->book_num);
		fprintf_s(fp, "%d\t", p->book_borrow_num);
		fprintf_s(fp, "%d\t", p->book_borrow_num_time);

		//strText.Format(_T("%d"), p->book_num);
		//fprintf_s(fp, "%s\t", strText);

		//strText.Format(_T("%d"), p->book_borrow_num);
		//fprintf_s(fp, "%s\t", strText);

		fprintf_s(fp, "\n");
	}

	fclose(fp);
	return true;
}

bool ReadData(pBookNode pHead)
{
	CString file_path;
	CString strText;
	BookInfor book_infor;

	TCHAR szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	file_path = szFilePath;
	file_path = file_path + "bookdata\\data.txt";

	//判断文件是否存在
	DWORD dwRe = GetFileAttributes(file_path);
	if (dwRe == (DWORD)-1)
	{
		return false;
	}

	FILE* fp;
	fopen_s(&fp, file_path, "r");
	if (fp == NULL)
	{
		return false;
	}
	char ch[1024];
	while (fgets(ch, sizeof(ch), fp) != NULL)
	{
		string str = ch;
		string strText;
		string splint = "\t";
		int pos1, pos2;
		pos2 = str.find(splint, 0);
		pos1 = 0;
		int i = 0;
		string book[9];
		while (string::npos != pos2)
		{
			strText = str.substr(pos1, pos2 - pos1);
			pos1 = pos2 + splint.size();
			pos2 = str.find(splint, pos1);

			book[i] = strText;
			i++;
		}
		if (pos1 != str.length())
		{
			strText = str.substr(pos1);
		}
		book_infor.book_name = book[0];
		book_infor.book_ISBN = book[1];
		book_infor.book_author = book[2];
		book_infor.book_publish_house = book[3];
		book_infor.book_publish_time = book[4];
		book_infor.book_storage_time = book[5];
		book_infor.book_num = _ttoi(book[6].c_str());
		book_infor.book_borrow_num = _ttoi(book[7].c_str());
		book_infor.book_borrow_num_time = _ttoi(book[8].c_str());
		book_infor.pNext = NULL;

		AddListItem(pHead, book_infor);
	}

	fclose(fp);
	return true;
}
