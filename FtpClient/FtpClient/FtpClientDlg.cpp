
// FtpClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FtpClient.h"
#include "FtpClientDlg.h"
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


// CFtpClientDlg 对话框




CFtpClientDlg::CFtpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFtpClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_Address = _T("192.168.1.100");
	//m_Account = _T("test");
	//m_Password = _T("1");

	m_Address = _T("pop.163.com");
	m_Account = _T("18219111672@163.com");
	m_Password = _T("cjw18219111672");

	//m_Address = _T("pop.qq.com");
	//m_Account = _T("1047004324@qq.com");
	//m_Password = _T("snitiehdljzibbjc");

	m_Login = _T("");
	m_Directory = _T("");
}

void CFtpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_Address);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_Account);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_Password);
	DDX_Text(pDX, IDC_EDIT_LOGIN, m_Login);
	DDX_Text(pDX, IDC_EDIT_DIRECTORY, m_Directory);
}

BEGIN_MESSAGE_MAP(CFtpClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CFtpClientDlg::OnConnect)
	ON_BN_CLICKED(IDC_BTN_LIST, &CFtpClientDlg::OnList)
	ON_BN_CLICKED(IDC_BTN_QUIT, &CFtpClientDlg::OnQuit)
END_MESSAGE_MAP()


// CFtpClientDlg 消息处理程序

BOOL CFtpClientDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFtpClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFtpClientDlg::OnPaint()
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
HCURSOR CFtpClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



bool CFtpClientDlg::SendCommand(void)
{
	 int nSend;
   nSend=send(SocketControl,Command,strlen(Command),0);
   if (nSend==SOCKET_ERROR)
   {
      MessageBox("Socket发送失败！");
	  closesocket(SocketControl);
	  WSACleanup();
	  return false;
   }

   return true;
}


bool CFtpClientDlg::RecvRespond(void)
{
		int nRecv;
    memset(Respond,0,MAX_SIZE);
	nRecv=recv(SocketControl,Respond,MAX_SIZE,0);//通过连接接收响应
	if (nRecv==SOCKET_ERROR)
	{
       MessageBox("Socket接收失败！");
	   closesocket(SocketControl);
	   WSACleanup();
	   return false;
	}

	//从响应中解析响应码
	char* ReplyCodes=new char[3];
	memset(ReplyCodes,0,3);
	memcpy(ReplyCodes,Respond,3);
	RespondCode=atoi(ReplyCodes);
	return true;
}


bool CFtpClientDlg::DataConnect(void)
{
	 memset(Command,0,MAX_SIZE);
   //合成PASV命令
   memcpy(Command,"PASV",strlen("PASV"));
   memcpy(Command+strlen("PASV"),"\r\n",2);

   if (!SendCommand())
	   return false;
  
   if (!RecvRespond())
	   return false;
   else
   {
      //判断PASV响应码
	   if (RespondCode!=227)
	   {
         MessageBox("PASV响应错误！");
		 closesocket(SocketControl);
		 WSACleanup();
		 return false;
	   }
	   
   }


   char* part[6];
   //分离PASV应答信息
  if (strtok(Respond,"("))
     {
	   for (int i=0;i<5;i++)
	   {
          part[i]=strtok(NULL,",");
		  if (!part[i])
			  return false;
	   }
	   part[5]=strtok(NULL,")");
	  
	   if (!part[5])
		   return false;

   }
    else
		return false;

	
	unsigned short ServerPort;   //获取服务器数据端口
	ServerPort=unsigned short((atoi(part[4])<<8)+atoi(part[5]));
	SocketData=socket(AF_INET,SOCK_STREAM,0);
	if (SocketData==INVALID_SOCKET)
	{
      MessageBox("创建数据Socket失败！");
	  closesocket(SocketControl);
	  WSACleanup();
	  return false;
	}

	u_long IpAddress;
	IpAddress=inet_addr(m_Address);
	if (IpAddress==INADDR_NONE)
	{
      hostent* pHostent=gethostbyname(m_Address);
	  if (pHostent)
	  	 IpAddress=(*(in_addr*)pHostent->h_addr_list[0]).s_addr;	  
	}

	sockaddr_in serveraddr2;
	memset(&serveraddr2,0,sizeof(serveraddr2));
	serveraddr2.sin_family=AF_INET;
	serveraddr2.sin_port=htons(ServerPort);
	serveraddr2.sin_addr.s_addr=IpAddress;

	int nConnect=connect(SocketData,(sockaddr*)&serveraddr2,sizeof(serveraddr2));
	if (nConnect==SOCKET_ERROR)
	{
      MessageBox("数据连接失败！");
	  closesocket(SocketControl);
	  closesocket(SocketData);
	  WSACleanup();
	  return false;
	}

	return true;
}

void CFtpClientDlg::OnConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	  UpdateData(TRUE);
	
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2,2),&WSAData)!=0)//建立套接字绑定
	{
		MessageBox("初始化Winsock失败！");
		return;
	}

	SocketControl=socket(AF_INET,SOCK_STREAM,0);//创建连接套接字
	if (SocketControl==INVALID_SOCKET)
	{
      MessageBox("创建控制Socket失败！");
	  WSACleanup();
	  return;
	}

	
	u_long IpAddress; //判断域名或IP地址
	IpAddress=inet_addr(m_Address);
	if (IpAddress==INADDR_NONE)
	{
		hostent* pHostent=gethostbyname(m_Address);
		if (pHostent)
			IpAddress=(*(in_addr*)pHostent->h_addr_list[0]).s_addr;

	}

	sockaddr_in serveraddr;  //定义套接字地址
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(110);
	serveraddr.sin_addr.s_addr=IpAddress;

	m_Login+=m_Address;
	m_Login+="...\r\n";
	int nConnect;
	nConnect=connect(SocketControl,(sockaddr*)&serveraddr,sizeof(serveraddr));//建立FTP控制连接
	if (nConnect==SOCKET_ERROR)
	{
        MessageBox("控制连接建立失败！");
		closesocket(SocketControl);
		WSACleanup();
		return;
	}

	if (!RecvRespond())
		return;
    else
	{//判断连接应答码
      if (RespondCode==220)
	  {
         m_Login+="Server:  ";
		 m_Login+=Respond;
	  }
	  else
	  {
		  MessageBox("控制连接响应错误！");
		  closesocket(SocketControl);
		  WSACleanup();
		  return;
	  }

	}

	
	memset(Command,0,MAX_SIZE);
	//合成USER命令
	memcpy(Command,"USER ",strlen("USER "));
	memcpy(Command+strlen("USER "),m_Account,strlen(m_Account));
	memcpy(Command+strlen("USER ")+strlen(m_Account),"\r\n",2);
	if (!SendCommand())
		return;

	m_Login+="Client:  ";
	m_Login+=Command;

	if (!RecvRespond())
		return;
	else
	{//判断USER应答码
       if (RespondCode==220 || RespondCode==331)
	   {
          m_Login+="Server: ";
		  m_Login+=Respond;
	   }
	   else
	   {
          MessageBox("USER响应错误！");
		  closesocket(SocketControl);
		  WSACleanup();
		  return;
	   }
	}

	if (RespondCode==331)//User name okay,need password
	{ //合成PASS命令
		memset(Command,0,MAX_SIZE);
		memcpy(Command,"PASS ",strlen("PASS "));
		memcpy(Command+strlen("PASS "),m_Password,strlen(m_Password));
		memcpy(Command+strlen("PASS ")+strlen(m_Password),"\r\n",2);
		if (!SendCommand())
			return;
		m_Login+="Client: PASS ******\r\n";

		if (!RecvRespond())
			return;
		else
		{//判断PASS响应码
			if (RespondCode==230)
            {
               m_Login+="Server: ";
			   m_Login+=Respond;
			}
			else
			{
               MessageBox("PASS响应错误！");
			   closesocket(SocketControl);
			   WSACleanup();
			   return;
			}
		}

	}

	UpdateData(false);
}


void CFtpClientDlg::OnList()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!DataConnect())
		return;

	memset(Command,0,MAX_SIZE);
	//合成LIST命令
	memcpy(Command,"LIST",strlen("LIST"));
    memcpy(Command+strlen("LIST"),"\r\n",2);
	if (!SendCommand())
		return;

	m_Login+="Client: ";
	m_Login+=Command;
	if (!RecvRespond())
		return;
	else
	{
		if (RespondCode==125 || RespondCode==150 || RespondCode==226)
		{
          m_Login+="Server: ";
		  m_Login+=Respond;
		}
		else
		{
           MessageBox("LIST响应错误！");
		   closesocket(SocketControl);
		   WSACleanup();
		   return;
		}
	}
    
	m_Login+="Client: ......\r\n";
	while (true)
	{
      char ListBuf[MAX_SIZE];
	  memset(ListBuf,0,MAX_SIZE);
	  int nRecv;
	  nRecv=recv(SocketData,ListBuf,MAX_SIZE,0);//读取目录信息
	  if (nRecv==SOCKET_ERROR)
	  {
		  MessageBox("LIST接收错误！");
		  closesocket(SocketData);
		  WSACleanup();
		  return;
	  }
	  if (nRecv<=0) break;
      
	  m_Directory=ListBuf;//显示目录信息
	} 

	closesocket(SocketData);
	if (!RecvRespond())
		return;
	else
	{
		if (RespondCode==226)
		{
          m_Login+="Server: ";
		  m_Login+=Respond;
		}
		else
		{
           MessageBox("LIST响应错误！");
		   closesocket(SocketControl);
		   WSACleanup();
		   return;
		}
	}

	UpdateData(false);
}


void CFtpClientDlg::OnQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	memset(Command,0,MAX_SIZE);
	//合成QUIT命令
	memcpy(Command,"QUIT",strlen("QUIT"));
    memcpy(Command+strlen("QUIT"),"\r\n",2);
	if (!SendCommand())
		return;
    
	m_Login+="Client: ";
	m_Login+=Command;
	if (!RecvRespond())
		return;
	else
	{
      if (RespondCode==221)
	  {
         m_Login+="Server: ";
		 m_Login+=Respond;
		 m_Directory="";
	  }
	  else
	  {
        MessageBox("QUIT响应错误！");
		closesocket(SocketControl);
		WSACleanup();
		return;
	  }
	}

	UpdateData(false);
	closesocket(SocketControl);
	WSACleanup();
}
