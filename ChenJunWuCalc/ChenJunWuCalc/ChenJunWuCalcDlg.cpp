
// ChenJunWuCalcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChenJunWuCalc.h"
#include "ChenJunWuCalcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChenJunWuCalcDlg �Ի���




CChenJunWuCalcDlg::CChenJunWuCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChenJunWuCalcDlg::IDD, pParent)
	, first(_T(""))
	, second(_T(""))
	, answer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChenJunWuCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPERA, m_comboOpera);
	DDX_Text(pDX, IDC_FIRST, first);
	DDX_Text(pDX, IDC_SECOND, second);
	DDX_Text(pDX, IDC_EDIT3, answer);
}

BEGIN_MESSAGE_MAP(CChenJunWuCalcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_OPERA, &CChenJunWuCalcDlg::OnCbnSelchangeOpera)
	ON_EN_CHANGE(IDC_FIRST, &CChenJunWuCalcDlg::OnEnChangeFirst)
	ON_BN_CLICKED(IDOK, &CChenJunWuCalcDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_SECOND, &CChenJunWuCalcDlg::OnEnChangeSecond)
END_MESSAGE_MAP()


// CChenJunWuCalcDlg ��Ϣ�������

BOOL CChenJunWuCalcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// Ϊ��Ͽ�ؼ����б������б�������ס�   
    m_comboOpera.AddString(_T("-"));   
    // Ϊ��Ͽ�ؼ����б������б���ٶȡ�   
    m_comboOpera.AddString(_T("*"));   
    // ����Ͽ�ؼ����б��������Ϊ1��λ�ò����б�����ˡ�   
    m_comboOpera.InsertString(1, _T("/"));   
  
    // Ĭ��ѡ���һ��   
    m_comboOpera.SetCurSel(0);   
    // �༭����Ĭ����ʾ��һ������֡������ס�   
    SetDlgItemText(IDC_OPERA, _T("+")); 


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChenJunWuCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChenJunWuCalcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChenJunWuCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChenJunWuCalcDlg::OnCbnSelchangeOpera()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;   
    int nSel;

	// ��ȡ��Ͽ�ؼ����б����ѡ���������   
    nSel = m_comboOpera.GetCurSel();   
    // ����ѡ����������ȡ�����ַ���   
    m_comboOpera.GetLBText(nSel, str);   
    // ����Ͽ���ѡ�е��ַ�����ʾ��IDC_SEL_WEB_EDIT�༭����   
    SetDlgItemText(IDC_OPERA, str);

}


void CChenJunWuCalcDlg::OnLbnSelchangeList2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CChenJunWuCalcDlg::OnEnChangeFirst()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	_first = first;
}


void CChenJunWuCalcDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CChenJunWuCalcDlg::OnEnChangeSecond()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	_second = second;
}
