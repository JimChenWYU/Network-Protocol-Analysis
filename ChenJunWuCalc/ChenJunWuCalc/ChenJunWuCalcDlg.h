
// ChenJunWuCalcDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CChenJunWuCalcDlg 对话框
class CChenJunWuCalcDlg : public CDialogEx
{
// 构造
public:
	CChenJunWuCalcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHENJUNWUCALC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeOpera();
	afx_msg void OnLbnSelchangeList2();
	CComboBox m_comboOpera;
	afx_msg void OnEnChangeFirst();
	CString first;
	CString second;
	CString answer;

	CString _first;
	CString _second;
	CString _answer;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeSecond();
};
