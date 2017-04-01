
// ChenJunWuCalcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChenJunWuCalc.h"
#include "ChenJunWuCalcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CChenJunWuCalcDlg 对话框




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


// CChenJunWuCalcDlg 消息处理程序

BOOL CChenJunWuCalcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 为组合框控件的列表框添加列表项“鸡啄米”   
    m_comboOpera.AddString(_T("-"));   
    // 为组合框控件的列表框添加列表项“百度”   
    m_comboOpera.AddString(_T("*"));   
    // 在组合框控件的列表框中索引为1的位置插入列表项“新浪”   
    m_comboOpera.InsertString(1, _T("/"));   
  
    // 默认选择第一项   
    m_comboOpera.SetCurSel(0);   
    // 编辑框中默认显示第一项的文字“鸡啄米”   
    SetDlgItemText(IDC_OPERA, _T("+")); 


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChenJunWuCalcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChenJunWuCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChenJunWuCalcDlg::OnCbnSelchangeOpera()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;   
    int nSel;

	// 获取组合框控件的列表框中选中项的索引   
    nSel = m_comboOpera.GetCurSel();   
    // 根据选中项索引获取该项字符串   
    m_comboOpera.GetLBText(nSel, str);   
    // 将组合框中选中的字符串显示到IDC_SEL_WEB_EDIT编辑框中   
    SetDlgItemText(IDC_OPERA, str);

}


void CChenJunWuCalcDlg::OnLbnSelchangeList2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CChenJunWuCalcDlg::OnEnChangeFirst()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	_first = first;
}


void CChenJunWuCalcDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CChenJunWuCalcDlg::OnEnChangeSecond()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	_second = second;
}
