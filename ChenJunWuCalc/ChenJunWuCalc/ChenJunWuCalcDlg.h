
// ChenJunWuCalcDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CChenJunWuCalcDlg �Ի���
class CChenJunWuCalcDlg : public CDialogEx
{
// ����
public:
	CChenJunWuCalcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHENJUNWUCALC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
