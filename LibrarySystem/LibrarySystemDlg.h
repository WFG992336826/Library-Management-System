#pragma once
#include "booklist.h"
#include "savedata.h"

// CLibrarySystemDlg 对话框
class CLibrarySystemDlg : public CDialogEx
{
// 构造
public:
	CLibrarySystemDlg(CWnd* pParent = nullptr);	// 标准构造函数
	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIBRARYSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	//函数声明
	void InitListCtrl(); //list control 控件初始化
	
	DECLARE_MESSAGE_MAP()
public:
	//函数声明
	void DisplayAllBookInfor(pBookNode pHead, bool DisplayAll=true); //list control 插入数据
	BookInfor GetEditText();//获取编辑框的文字信息
	void DeleteEditText();//清空编辑框的文字信息
	void QueryBookInfor(pBookNode pHead, BookInfor book_infor);
	BookInfor GetListSelectBookInfor();
	void SetEditText(BookInfor book_infor);
	void CountBookNum(pBookNode pHead);
	//变量声明
	CListCtrl m_listctrl;
	CEdit m_book_name;
	CEdit m_book_ISBN;
	CEdit m_book_author;
	CEdit m_book_publish_house;
	CEdit m_book_publish_time;
	CEdit m_book_storage_time;
	CEdit m_book_storage_num;
	CEdit m_book_borrow_num;
	CEdit m_storage_all_num;
	CEdit m_borrow_all_num;

	pBookNode pHead;
	BookInfor book_infor;
	afx_msg void OnBnClickedButtonInsert();//插入书籍
	afx_msg void OnBnClickedButtonClear();//删除编辑框中的文字
	afx_msg void OnBnClickedButtonDisplayAllBooks();//在list中显示所有书籍
	afx_msg void OnBnClickedButtonChange();//修改已有书籍信息
	afx_msg void OnBnClickedButtonQurey();//查询图书
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLvnItemchangedListctrlBookInformation(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonBorrow();
	afx_msg void OnBnClickedButtonReturn();

	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonSortBookname();
	afx_msg void OnBnClickedButtonSaveBookInfor();

	afx_msg LRESULT OnClose(WPARAM wPara, LPARAM lPara);

};
