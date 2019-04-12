
// ClientDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
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

// CClientDlg �Ի���
CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
	, m_content(_T(""))
	, m_sendmsg(_T(""))
	, client_status(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTENT, m_recv);
	DDX_Control(pDX, IDC_MSG, m_send);
	DDX_Control(pDX, IDC_CONNECT, m_connect);
	DDX_Control(pDX, IDC_IP, m_ip);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_SENDMSG, &CClientDlg::OnBnClickedSendmsg)
	ON_BN_CLICKED(IDC_CLOSE, &CClientDlg::OnBnClickedClose)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	//�׽��ֳ�ʼ��
	Socketinit();
	//���öԻ������Ϊclient + ip
	this->SetWindowText(CString("Client:") + GetLocalIP());
	//��ʼ��ip��ַ�ؼ�
	m_ip.SetAddress(192, 168, 18, 128);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//��ʼ���׽��ֺ���
void CClientDlg::Socketinit()
{
	WSADATA wsa;
	//��ʼ��WS2_32.DLL
	WSAStartup(MAKEWORD(2, 0), &wsa);
	//�����׽���
	if ((clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		AfxMessageBox(_T("�׽���socket����ʧ��!\n"));
		return ;
	}
	serveraddr.sin_family = AF_INET;
	//���ö˿ں�
	serveraddr.sin_port = htons(6000);
}
//���ӷ�������ť�¼�
void CClientDlg::OnBnClickedConnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString   strIP;
	//��ÿؼ��е�ip��ַ
	GetDlgItemText(IDC_IP, strIP);
	char ip[BUF_SIZE];
	cstring2char(strIP, ip);
	//��������ip����Ϊ�ؼ��е�ip��ַ
	serveraddr.sin_addr.S_un.S_addr = inet_addr(ip);
	//�����ӿͻ����߳�
	if (connect(clientsocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		AfxMessageBox(_T("����ʧ�ܣ�\n"));
		return;
	}
	//��ʾ���ӷ�����������
	ProgressShow();
	//�����Ӱ�ť����Ϊ������
	m_connect.EnableWindow(FALSE);
	//���ͻ���״̬����Ϊ��
	client_status = true;
	//�������ܷ����������߳�
	m_Threadrecv = CreateThread(NULL, 0, ThreadProcRecv, this, 0, NULL);//�������߳�  
	//�ر��߳̾��
	CloseHandle(m_Threadrecv);
}
//���ܷ�������Ϣ�̺߳���
DWORD WINAPI ThreadProcRecv(LPVOID lpParam)
{
	CClientDlg *tmp = (CClientDlg *)lpParam;
	char buf[BUF_SIZE];
	mymsg::msg message;
	while (tmp->client_status)
	{
		memset(&buf, 0, BUF_SIZE);
		int retVal = recv(tmp->clientsocket, buf, BUF_SIZE, 0);
		if (retVal>0)
		{
			//�����ܵ�protobufЭ�鷴���л�
			message.ParseFromArray(buf, BUF_SIZE);
			tmp->m_content += message.data().c_str();
			tmp->m_recv.SetWindowText(tmp->m_content);
		}
	}
	return 0;
}

void CClientDlg::OnBnClickedSendmsg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	mymsg::msg message;
	char temp[BUF_SIZE];
	memset(temp, 0, BUF_SIZE);
	if (client_status)
	{
		//��ȡ���ͱ༭���е��ַ���
		m_send.GetWindowText(m_sendmsg);
		//����ϢΪ�գ��򲻷��Ͳ���ʾ
		if (m_sendmsg == "")
		{
			AfxMessageBox(_T("���͵���Ϣ����Ϊ�գ�"));
			return;
		}
		cstring2char(m_sendmsg, temp);
		//���÷��͵�protobufЭ�����
		message.set_data(temp);
		message.set_type(mymsg::msg::SENDMSG);
		//�����ݶ������л�
		message.SerializeToArray(temp, BUF_SIZE);
		if (send(clientsocket,temp, strlen(temp), 0) <= 0)
		{
			m_content += CString("���ʹ���!\r\n");
		}
		//���ͳɹ��󽫷��ͱ༭����ղ���ý����Ա��´η���
		m_sendmsg = "";
		m_send.SetWindowText(_T(""));
		m_send.SetFocus();
	}
}
//��CString���ֽڶ���ת��Ϊchar���ֽڶ�����
void CClientDlg::cstring2char(CString str, char c[])
{
	TCHAR wTmp[BUF_SIZE/2-1] = {};
	_tcscpy(wTmp, str.GetBuffer(0));
	int   nLen = wcslen(wTmp) + 1;
	WideCharToMultiByte(CP_ACP, 0, wTmp, nLen, c, 2 * nLen, NULL, NULL);
}
//�رտͻ��˰�ť�¼�
void CClientDlg::OnBnClickedClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	mymsg::msg message;
	char temp[BUF_SIZE];
	if (client_status)
	{
		cstring2char(CString(" "), temp);
		//����protobufЭ�������Ϣ����Ϊ�Ͽ�����
		message.set_data(temp);
		message.set_type(mymsg::msg::DISCONNECT);
		//�����ݽ������л�
		message.SerializeToArray(temp, BUF_SIZE);
		if (send(clientsocket, temp, strlen(temp), 0) <= 0)
		{
			m_content += CString(" ����ʧ������\r\n");
		}
	}
	//���ͻ���״̬����Ϊ�ر�
	client_status = false;
	//�رտͻ����׽���
	closesocket(clientsocket);
	//�ͷ�WS2_32.DLL
	WSACleanup();
	CDialog::OnCancel();
}
//���ñ༭�򱳾�ɫ����
HBRUSH CClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_CONTENT)
	{ 
		COLORREF clr_bk = RGB(140, 200, 85);	//���ñ�����ɫ  
		pDC->SetBkColor(clr_bk);
		m_brush = ::CreateSolidBrush(clr_bk);
		return m_brush;
	}
	else if (pWnd->GetDlgCtrlID() == IDC_MSG)
	{
		COLORREF clr_bk = RGB(160, 160, 230);	//���ñ�����ɫ  
		pDC->SetBkColor(clr_bk);
		m_brush = ::CreateSolidBrush(clr_bk);
		return m_brush;
	}
	else
	{
		HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		return hbr;
	}
}
CString CClientDlg::GetLocalIP()
{
	char szHostName[MAX_PATH + 1];
	gethostname(szHostName, MAX_PATH);			//�õ��������
	hostent *p = gethostbyname(szHostName);		//�Ӽ�������õ�������Ϣ
	CString m_strName;
	m_strName = szHostName;						//����������  
	int nCount = 0;								//����������ַ
	//��32λIPת��Ϊ�ַ���IP
	char *pIP = inet_ntoa(*(in_addr *)p->h_addr_list[0]);  
	CString m_strAddr;
	m_strAddr = pIP;							//��������IP��ַ 
	return m_strAddr;
}
//��ʾ����������
void CClientDlg::ProgressShow()
{
	CProgressCtrl myProCtrl;
	CRect rect, proRect;
	//��õ�ǰ�ͻ��˴�С
	GetClientRect(&rect);
	//���ý�������С
	proRect.left = rect.left + rect.Width() / 2 - 100;
	proRect.top = rect.top + rect.Height() / 2 - 10;
	proRect.right = rect.right - rect.Width() / 2 + 100;
	proRect.bottom = rect.bottom - rect.Height() / 2 + 10;
	//����λ�á���С
	myProCtrl.Create(WS_VISIBLE, proRect, this, 99);
	myProCtrl.SetRange(0, 100);
	int i;
	for (i = 0; i < 100; i++)
	{
		myProCtrl.OffsetPos(1);
		Sleep(20);
	}
	return;
}