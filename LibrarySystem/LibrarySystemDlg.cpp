// LibrarySystemDlg.cpp: 实现文件
#include "pch.h"
#include "framework.h"
#include "LibrarySystem.h"
#include "LibrarySystemDlg.h"
#include "afxdialogex.h"
#include "booklist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define list_head_num 9

// CLibrarySystemDlg 对话框

CLibrarySystemDlg::CLibrarySystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIBRARYSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLibrarySystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTCTRL_BOOK_INFORMATION, m_listctrl);
	DDX_Control(pDX, IDC_EDIT_BOOK_NAME, m_book_name);
	DDX_Control(pDX, IDC_EDIT_BOOK_ISBN, m_book_ISBN);
	DDX_Control(pDX, IDC_EDIT_BOOK_AUTHOR, m_book_author);
	DDX_Control(pDX, IDC_EDIT_BOOK_PUBLISH, m_book_publish_house);
	DDX_Control(pDX, IDC_EDIT_BOOK_PUBLISH_TIME, m_book_publish_time);
	DDX_Control(pDX, IDC_EDIT_BOOK_STORAGE_TIME, m_book_storage_time);
	DDX_Control(pDX, IDC_EDIT_BOOK_STORAGE_NUM, m_book_storage_num);
	DDX_Control(pDX, IDC_EDIT_BOOK_BORROW_NUM, m_book_borrow_num);
	DDX_Control(pDX, IDC_EDIT_BOOK_STORAGE_ALL_NUM, m_storage_all_num);
	DDX_Control(pDX, IDC_EDIT_BOOK_BORROW_ALL_NUM, m_borrow_all_num);
}

BEGIN_MESSAGE_MAP(CLibrarySystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &CLibrarySystemDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CLibrarySystemDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_DISPLAY_ALL_BOOKS, &CLibrarySystemDlg::OnBnClickedButtonDisplayAllBooks)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CLibrarySystemDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_QUREY, &CLibrarySystemDlg::OnBnClickedButtonQurey)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL_BOOK_INFORMATION, &CLibrarySystemDlg::OnLvnItemchangedListctrlBookInformation)
	ON_BN_CLICKED(IDC_BUTTON_BORROW, &CLibrarySystemDlg::OnBnClickedButtonBorrow)
	ON_BN_CLICKED(IDC_BUTTON_RETURN, &CLibrarySystemDlg::OnBnClickedButtonReturn)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CLibrarySystemDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SORT_BOOKNAME, &CLibrarySystemDlg::OnBnClickedButtonSortBookname)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_BOOK_INFOR, &CLibrarySystemDlg::OnBnClickedButtonSaveBookInfor)
	ON_MESSAGE(WM_CLOSE, OnClose)
END_MESSAGE_MAP()


// CLibrarySystemDlg 消息处理程序

BOOL CLibrarySystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	WM_CLOSE;

	// TODO: 在此添加额外的初始化代码
	InitListCtrl();
	pHead = CreatList();
	InitList(pHead);
	//SaveData(pHead);
	CountBookNum(pHead);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLibrarySystemDlg::InitListCtrl()
{
	//int num = 9;//表头数目
	//设置Listctrl为报表形式
	CListCtrl* pmyListCtrl = (CListCtrl*)GetDlgItem(IDC_LISTCTRL_BOOK_INFORMATION);
	DWORD dwStyle = GetWindowLong(pmyListCtrl->m_hWnd, GWL_STYLE);
	SetWindowLong(pmyListCtrl->m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT);

	//设置listctrl可以整行选择和网格条纹
	DWORD styles = pmyListCtrl->GetExtendedStyle();
	pmyListCtrl->SetExtendedStyle(styles | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//给listctrl设置8个标题栏
	TCHAR rgtsz[list_head_num][100] = { _T("书籍名称"), _T("ISBN"), _T("作者"), _T("出版社"), _T("出版时间"), _T("入库时间"), _T("书籍总量/本"), _T("借阅数量/本"), _T("借阅总次数") };

	//修改数组大小，可以确定分栏数和没栏长度，如果修改下面的数据（蓝色部分）也要跟着改变
	LV_COLUMN lvcolumn;
	CRect rect;
	pmyListCtrl->GetWindowRect(&rect);
	for (int i = 0; i < list_head_num; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT
			| LVCF_WIDTH | LVCF_ORDER;
		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.pszText = rgtsz[i];
		lvcolumn.iSubItem = i;
		lvcolumn.iOrder = i;
		lvcolumn.cx = rect.Width() / list_head_num;
		pmyListCtrl->InsertColumn(i, &lvcolumn);
	}
	
}

void CLibrarySystemDlg::DisplayAllBookInfor(pBookNode pHead, bool DisplayAll)
{
	CString strText;
	int n = 0;
	pBookNode p = pHead;

	if (DisplayAll)
	{
		m_listctrl.DeleteAllItems();

		while (NULL != p->pNext)
		{
			p = p->pNext;
			// Insert the item, select every other item.
			n = m_listctrl.InsertItem(0, p->book_name.c_str());
			m_listctrl.SetItemText(n, 1, p->book_ISBN.c_str());
			m_listctrl.SetItemText(n, 2, p->book_author.c_str());
			m_listctrl.SetItemText(n, 3, p->book_publish_house.c_str());
			m_listctrl.SetItemText(n, 4, p->book_publish_time.c_str());
			m_listctrl.SetItemText(n, 5, p->book_storage_time.c_str());
			strText.Format(_T("%d"), p->book_num);
			m_listctrl.SetItemText(n, 6, strText);
			strText.Format(_T("%d"), p->book_borrow_num);
			m_listctrl.SetItemText(n, 7, strText);
			strText.Format(_T("%d"), p->book_borrow_num_time);
			m_listctrl.SetItemText(n, 8, strText);
		}
	}
	else
	{
		// Insert the item, select every other item.
		n = m_listctrl.InsertItem(0, p->book_name.c_str());
		m_listctrl.SetItemText(n, 1, p->book_ISBN.c_str());
		m_listctrl.SetItemText(n, 2, p->book_author.c_str());
		m_listctrl.SetItemText(n, 3, p->book_publish_house.c_str());
		m_listctrl.SetItemText(n, 4, p->book_publish_time.c_str());
		m_listctrl.SetItemText(n, 5, p->book_storage_time.c_str());
		strText.Format(_T("%d"), p->book_num);
		m_listctrl.SetItemText(n, 6, strText);
		strText.Format(_T("%d"), p->book_borrow_num);
		m_listctrl.SetItemText(n, 7, strText);
		strText.Format(_T("%d"), p->book_borrow_num_time);
		m_listctrl.SetItemText(n, 8, strText);
	}
	
}

BookInfor CLibrarySystemDlg::GetEditText()
{
	CString strText;
	m_book_name.GetWindowTextA(strText);
	book_infor.book_name = strText;

	m_book_ISBN.GetWindowTextA(strText);
	book_infor.book_ISBN = strText;

	m_book_author.GetWindowTextA(strText);
	book_infor.book_author = strText;

	m_book_publish_house.GetWindowTextA(strText);
	book_infor.book_publish_house = strText;

	m_book_publish_time.GetWindowTextA(strText);
	book_infor.book_publish_time = strText;

	m_book_storage_time.GetWindowTextA(strText);
	book_infor.book_storage_time = strText;

	m_book_storage_num.GetWindowTextA(strText);
	book_infor.book_num = _ttoi(strText);

	m_book_borrow_num.GetWindowTextA(strText);
	book_infor.book_borrow_num = _ttoi(strText);

	return book_infor;
}

void CLibrarySystemDlg::SetEditText(BookInfor book_infor)
{
	CString strText;
	m_book_name.SetWindowTextA(book_infor.book_name.c_str());
	m_book_ISBN.SetWindowTextA(book_infor.book_ISBN.c_str());
	m_book_author.SetWindowTextA(book_infor.book_author.c_str());
	m_book_publish_house.SetWindowTextA(book_infor.book_publish_house.c_str());
	m_book_publish_time.SetWindowTextA(book_infor.book_publish_time.c_str());
	m_book_storage_time.SetWindowTextA(book_infor.book_storage_time.c_str());

	strText.Format(_T("%d"), book_infor.book_num);
	m_book_storage_num.SetWindowTextA(strText);

	strText.Format(_T("%d"), book_infor.book_borrow_num);
	m_book_borrow_num.SetWindowTextA(strText);
}

void CLibrarySystemDlg::DeleteEditText()
{
	m_book_name.SetWindowTextA(_T(""));
	m_book_ISBN.SetWindowTextA(_T(""));
	m_book_author.SetWindowTextA(_T(""));
	m_book_publish_house.SetWindowTextA(_T(""));
	m_book_publish_time.SetWindowTextA(_T(""));
	m_book_storage_time.SetWindowTextA(_T(""));
	m_book_storage_num.SetWindowTextA(_T(""));
	m_book_borrow_num.SetWindowTextA(_T(""));
}

void CLibrarySystemDlg::QueryBookInfor(pBookNode pHead, BookInfor book_infor)
{
	pBookNode p = pHead;

	m_listctrl.DeleteAllItems();

	while (NULL != p->pNext)
	{
		p = p->pNext;
		/*p->book_publish_time == book_infor.book_publish_time ||
		p->book_storage_time == book_infor.book_storage_time ||
		p->book_num == book_infor.book_num ||
		p->book_borrow_num == book_infor.book_borrow_num*/
		if (p->book_name == book_infor.book_name ||
			p->book_ISBN == book_infor.book_ISBN ||
			p->book_author == book_infor.book_author ||
			p->book_publish_house == book_infor.book_publish_house)
		{
			DisplayAllBookInfor(p, false);
		}
	}
}

BookInfor CLibrarySystemDlg::GetListSelectBookInfor()
{
	CString strText;
	POSITION pos = m_listctrl.GetFirstSelectedItemPosition(); //pos选中的首行位置
	if (pos != NULL)
	{
		while (pos)   //如果你选择多行
		{
			int nIdx = -1;
			nIdx = m_listctrl.GetNextSelectedItem(pos);

			if (nIdx >= 0 && nIdx < m_listctrl.GetItemCount())
			{
				book_infor.book_name = m_listctrl.GetItemText(nIdx, 0);
				book_infor.book_ISBN = m_listctrl.GetItemText(nIdx, 1);
				book_infor.book_author = m_listctrl.GetItemText(nIdx, 2);
				book_infor.book_publish_house = m_listctrl.GetItemText(nIdx, 3);
				book_infor.book_publish_time = m_listctrl.GetItemText(nIdx, 4);
				book_infor.book_storage_time = m_listctrl.GetItemText(nIdx, 5);
				strText = m_listctrl.GetItemText(nIdx, 6);
				book_infor.book_num = _ttoi(strText);
				strText = m_listctrl.GetItemText(nIdx, 7);
				book_infor.book_borrow_num = _ttoi(strText);
				strText = m_listctrl.GetItemText(nIdx, 8);
				book_infor.book_borrow_num_time = _ttoi(strText);

				SetEditText(book_infor);
			}
		}
	}
	return book_infor;
}

void CLibrarySystemDlg::CountBookNum(pBookNode pHead)
{
	CString strText;

	int borrow_num = 0, storage_num = 0;
	pBookNode p = pHead->pNext;
	while (NULL != p)
	{
		borrow_num += p->book_borrow_num;
		storage_num += p->book_num;
		p = p->pNext;
	}

	strText.Format(_T("%d"), storage_num);
	m_storage_all_num.SetWindowTextA(strText);

	strText.Format(_T("%d"), borrow_num);
	m_borrow_all_num.SetWindowTextA(strText);
}

void CLibrarySystemDlg::OnBnClickedButtonInsert()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flag = false;
	book_infor = GetEditText();
	if (book_infor.book_name == "" ||
		book_infor.book_author == "" ||
		book_infor.book_publish_house == "" ||
		book_infor.book_publish_time == "" ||
		book_infor.book_storage_time == ""
		)
	{
		MessageBox("所有图书信息不能为空！请补全信息");
	}
	else
	{
		flag = AddListItem(pHead, book_infor);

		if (true == flag)
		{
			MessageBox("录入图书成功");
			CountBookNum(pHead);
		}
		else
		{
			MessageBox("录入图书重复，若要修改图书信息请点击 修改 按钮");
		}
	}

}

void CLibrarySystemDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteEditText();
}

void CLibrarySystemDlg::OnBnClickedButtonDisplayAllBooks()
{
	// TODO: 在此添加控件通知处理程序代码
	DisplayAllBookInfor(pHead);
}

void CLibrarySystemDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flag = false;
	book_infor = GetEditText();
	flag = ChangeBookInfor(pHead, book_infor);
	if (true == flag)
	{
		MessageBox("修改成功");
		CountBookNum(pHead);
	}
	else
	{
		MessageBox("修改失败！书籍ISBN不同或者书库中没有此本图书");
	}
}

void CLibrarySystemDlg::OnBnClickedButtonQurey()
{
	// TODO: 在此添加控件通知处理程序代码
	book_infor = GetEditText();
	QueryBookInfor(pHead, book_infor);
}

BOOL CLibrarySystemDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	//屏蔽ESC按钮
	/*if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;*/

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CLibrarySystemDlg::OnLvnItemchangedListctrlBookInformation(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	GetListSelectBookInfor();
}

void CLibrarySystemDlg::OnBnClickedButtonBorrow()
{
	// TODO: 在此添加控件通知处理程序代码
	pBookNode p;
	book_infor = GetListSelectBookInfor();
	p = MatchBookInfor(pHead, book_infor);
	if (NULL != p)
	{
		if (p->book_num == p->book_borrow_num)
		{
			MessageBox("书籍全部被借阅！");
		}
		else
		{
			MessageBox("借书成功");
			p->book_borrow_num++;
			p->book_borrow_num_time++;
			book_infor.book_borrow_num = p->book_borrow_num;
			SetEditText(book_infor);
			DisplayAllBookInfor(pHead);

			CountBookNum(pHead);
		}
	}
}

void CLibrarySystemDlg::OnBnClickedButtonReturn()
{
	// TODO: 在此添加控件通知处理程序代码
	pBookNode p;
	book_infor = GetListSelectBookInfor();
	p = MatchBookInfor(pHead, book_infor);
	if (NULL != p)
	{
		if (p->book_borrow_num == 0)
		{
			MessageBox("书籍没有外接记录！请确认归还书籍信息");
		}
		else
		{
			MessageBox("还书成功");
			p->book_borrow_num--;
			book_infor.book_borrow_num = p->book_borrow_num;
			SetEditText(book_infor);
			DisplayAllBookInfor(pHead);

			CountBookNum(pHead);
		}
	}
}

void CLibrarySystemDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	bool flag = false;
	book_infor = GetListSelectBookInfor();
	flag = DeleteListItem(pHead, book_infor);

	if (true == flag)
	{
		MessageBox("删除成功");
		CountBookNum(pHead);
		DisplayAllBookInfor(pHead);
	}
	else
	{
		MessageBox("删除失败！请确认输入的书籍信息是否正确");
	}
}

void CLibrarySystemDlg::OnBnClickedButtonSortBookname()
{
	// TODO: 在此添加控件通知处理程序代码
	SortListBookNume(pHead);
	DisplayAllBookInfor(pHead);
}

void CLibrarySystemDlg::OnBnClickedButtonSaveBookInfor()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveData(pHead);
}

afx_msg LRESULT CLibrarySystemDlg::OnClose(WPARAM wPara, LPARAM lPara)
{
	if (IDNO == MessageBox("请再次确认退出", NULL, MB_YESNO))
	{
		return 0;
	}
	else
	{
		SaveData(pHead);
		CDialog::OnClose();
	}
	return 0;
}
