# Library-Management-System

### 环境：Visual Studio 2019 + MFC

1. 图书管理系统图形交互界面设计完成 2019-05-15

2. 添加链表的各种操作函数模型（待修改）2019-05-16

3. 实现录入图书信息功能 2019-05-17

4. 添加清除编辑框内容按钮及功能 2019-05-18

5. 实现修改图书信息功能 2019-05-18

6. 实现显示全部图书信息功能 2019-05-18

7. 实现书籍查询功能 2019-05-18

8. 实现借书和还书功能 2019-05-18

9. 实现统计借出书籍和库存书籍的总量功能 2019-05-18

10. 实现删除书籍功能 2019-05-19

11. 实现按照书名排序功能 2019-05-19

12. 实现导出和读取TXT文件功能 2019-05-20

13. 实现退出时弹出提示功能 2019-05-20

14. 添加了统计每本书籍被借出次数 2019-05-21

    ### 编程中遇到的问题

    1. LPCTSTR  string 转换；

       解决方法：**项目-属性-属性配置-常规-字符集，修改为：多字节显示**

    2. MFC窗口退出时，弹出提示框

       解决方法：新建消息映射

       BEGIN_MESSAGE_MAP(CLibrarySystemDlg, CDialogEx)

       ​       **ON_MESSAGE(WM_CLOSE, OnClose)**

       END_MESSAGE_MAP()

       

       定义相关联函数 OnClose();

       **afx_msg LRESULT OnClose(WPARAM wPara, LPARAM lPara)**

    3. Edit控件，按回车键会退出程序

       参考博客：https://www.cnblogs.com/dupengcheng/p/5618286.html

