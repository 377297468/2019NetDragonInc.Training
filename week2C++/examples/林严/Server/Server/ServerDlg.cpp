
// ServerDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CServerDlg �Ի���
CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
	, m_content(_T("")), server_status(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTENT, m_text);
	DDX_Control(pDX, IDC_STARTSERVER, m_start);
	DDX_Control(pDX, IDC_STOPSERVER, m_stop);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTSERVER, &CServerDlg::OnBnClickedStartserver)
	ON_BN_CLICKED(IDC_STOPSERVER, &CServerDlg::OnBnClickedStopserver)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CServerDlg ��Ϣ�������

BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//�԰�ť��ʾ���г�ʼ�����򿪷�������ť���ã��رշ�������ť������
	m_start.EnableWindow(!server_status);
	m_stop.EnableWindow(server_status);
	//��ʼ���׽���
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	Socketinit();

	CRect rect;
	// ��ȡ�б���ͼ�ؼ���λ�úʹ�С   
	m_list.GetClientRect(&rect);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ����һ��   
	m_list.InsertColumn(0, _T("IP��ַ"), LVCFMT_CENTER, rect.Width() , 0);
	//��ʼ���ٽ�������
	InitializeCriticalSection(&m_clientlock);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//socket��ʼ������
void CServerDlg::Socketinit()
{
	WSADATA wsa;
	//��ʼ��WS2_32.DLL
	WSAStartup(MAKEWORD(2, 0), &wsa);
	//�����׽���
	if ((server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		AfxMessageBox(_T("�׽���socket����ʧ��!"));
		return ;
	}
	//�����׽��ַ�����ģʽ
	unsigned long ul = 1;
	int reVal = ioctlsocket(server, FIONBIO, (unsigned long*)&ul);
	if (SOCKET_ERROR == reVal)
		return;
	//����Э�飬IP���˿�
	serveraddr.sin_family = AF_INET;
	//���ü����˿�Ϊ6000
	serveraddr.sin_port = htons(6000);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//���׽���
	if (bind(server, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		AfxMessageBox(_T("�׽��ְ�ʧ��!"));
		return ;
	}
}
//�򿪷�������ť�¼�
void CServerDlg::OnBnClickedStartserver()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�����ͻ�������
	int retVal = listen(server, MAX_CLIENT_NUM);
	if (SOCKET_ERROR == retVal)
	{
		AfxMessageBox(_T("����ʧ��!"));
		return ;
	}
	//������״̬�޸�Ϊ��
	server_status = true;
	//�򿪷�������ť�����ã��رշ�������ť����
	m_start.EnableWindow(!server_status);
	m_stop.EnableWindow(server_status);
	//�����ӿͻ����߳�
	m_startThread = (HANDLE)_beginthreadex(0, 0, Thread, this, 0, NULL);
}
//�رշ�������ť�¼�
void CServerDlg::OnBnClickedStopserver()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//������״̬�޸�Ϊ�ر�
	server_status = false;
	//�򿪷�������ť���ã��رշ�������ť������
	m_start.EnableWindow(!server_status);
	m_stop.EnableWindow(server_status);
	//�ͷ��߳̾��
	CloseHandle(m_startThread);
	//��տͻ��˹�������
	if (!client.empty())
	{
		client.clear();
	}
	//�ͷ�WS2_32.DLL
	WSACleanup();
	CDialog::OnCancel();
}
//�����ͻ��������߳�
void CServerDlg::ThreadFun()
{
	SOCKET clientsoc;												//������ʱ�׽��ֱ���
	int len;
	len = sizeof(SOCKADDR_IN);
	struct sockaddr_in sa;
	int i = 0;
	while (server_status)
	{
		memset(&sa, 0, sizeof(sockaddr_in));						//��ʼ��
		clientsoc = accept(server, (sockaddr*)&clientaddr, &len);	//���ܿͻ�����
		if (INVALID_SOCKET == clientsoc)
		{
			int nErrCode = WSAGetLastError();
			if (nErrCode == WSAEWOULDBLOCK)							//�޷��������һ�����赲���׽��ֲ���
			{
				Sleep(500);											//�̵߳ȴ�ʱ��500ms
				continue;											//�����ȴ�
			}
			else
			{
				return ;											//�߳��˳�
			}

		}
		//���ܿͻ��˵�����
		else
		{
			getpeername(clientsoc, (struct sockaddr *)&sa, &len);	//��ÿͻ���ip��ַ
			m_socket = new MySocket();								//�����ڴ�
			m_socket->mysocket = clientsoc;
			m_socket->ip = CString(inet_ntoa(sa.sin_addr));
			current_socket = *m_socket;
			EnterCriticalSection(&m_clientlock);
			client.push_back(*m_socket);							//�������ӵĿͻ��˷������������
			UpdateList();											//�����б�
			LeaveCriticalSection(&m_clientlock);
			current_time = CTime::GetCurrentTime();
			mytime = current_time.Format("%Y��%m��%d��%X\r\n");
			m_content += mytime;									//��ӵ�ǰʱ��
			m_content += m_socket->ip;
			m_content += " �����Ϸ���������\r\n";
			m_text.SetWindowText(m_content);						//��ʾ�ͻ�����������Ϣ
			mymsg::msg connectmsg;									//protobufЭ���װ����
			char temp[BUF_SIZE];
			cstring2char((mytime + m_socket->ip + CString(" �����Ϸ���������\r\n")), temp);
			connectmsg.set_type(mymsg::msg::SENDMSG);				//������Ϣ����
			connectmsg.set_data(temp);								//������Ϣ����
			sendtoall(connectmsg);									//���ù㲥����
			//����һ�����������߳�
			m_hThread[i++] = CreateThread(NULL, 0, ThreadProc, this, 0, NULL);//�������߳�  
			CloseHandle(m_hThread[i - 1]);							//�ͷ��߳̾��
		}

	}
}
//��������ͻ������ݴ����߳�
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	CServerDlg *tmp = (CServerDlg *)lpParam;						
	MySocket mstmp = tmp->current_socket;							//�õ���ǰ���ӵĿͻ��˶���
	SOCKET clienttmp = mstmp.mysocket;
	char buf[BUF_SIZE];
	mymsg::msg message;
	while (true)
	{
		memset(&buf, 0, BUF_SIZE);
		int retVal = recv(clienttmp, buf, BUF_SIZE , 0);			//���տͻ��˷��͵���Ϣ
		if (retVal>0)
		{
			message.ParseFromArray(buf, BUF_SIZE);					//������յ�protobufЭ����з����л�
			//�����Ϣ�Ƿ��͸���һ���ͻ��˵Ļ����������Ϣ���͸���һ���ͻ���
			if (message.type() == mymsg::msg::SENDMSG)
			{
				tmp->current_time = CTime::GetCurrentTime();
				tmp->mytime = tmp->current_time.Format("%Y��%m��%d��%X\r\n");
				//�ַ���ƴ�ӣ�ʱ�� + ip + ˵ + ��Ϣ����
				tmp->m_content = tmp->m_content + tmp->mytime + CString(mstmp.ip) + CString(" ˵��") + message.data().c_str() + CString("\r\n");
				tmp->m_text.SetWindowText(tmp->m_content);
				//���ù㲥����������Ϣ
				CString str = (tmp->mytime + CString(mstmp.ip) + CString(" ˵��") + message.data().c_str() + CString("\r\n"));
				char temp[BUF_SIZE];
				tmp->cstring2char(str, temp);
				//��װprotobufЭ�鴫������
				message.set_data(temp);
				message.set_type(mymsg::msg::SENDMSG);
				//���ù㲥����
				tmp->sendtoall(message);
			}
			//�����Ϣ�ǿͻ��˹ر��ˣ���رյ�ǰ�߳�
			if (message.type() == mymsg::msg::DISCONNECT)
			{
				//�ر��׽���
				closesocket(clienttmp);
				//Ѱ�ҵ�ǰ�رտͻ��˶���ĵ���������
				vector<MySocket>::iterator itr = find(tmp->client.begin(), tmp->client.end(), mstmp);
				//�ͻ����������̹߳�����Դ��������Ҫ�����ٽ���
				EnterCriticalSection(&tmp->m_clientlock);
				//ɾ����ǰ�ͻ��˵��׽��ֶ���
				tmp->client.erase(itr);
				tmp->UpdateList();
				//�뿪�ٽ���
				LeaveCriticalSection(&tmp->m_clientlock);
				//�ַ���ƴ�ӣ�ʱ�� + ip + �Ͽ�����
				tmp->current_time = CTime::GetCurrentTime();
				tmp->mytime = tmp->current_time.Format("%Y��%m��%d��%X\r\n");
				tmp->m_content = tmp->m_content + tmp->mytime + CString(mstmp.ip) + CString(" �Ͽ���������\r\n");
				tmp->m_text.SetWindowText(tmp->m_content);
				char temp[BUF_SIZE];
				tmp->cstring2char(tmp->mytime + CString(mstmp.ip) + CString(" �Ͽ���������\r\n"), temp);
				//��װprotobufЭ�����
				message.set_data(temp);
				message.set_type(mymsg::msg::SENDMSG);
				tmp->sendtoall(message);
				break;
			}
		}
	}
	return 0;
}
//�㲥����
void CServerDlg::sendtoall(mymsg::msg &message)
{
	char temp[BUF_SIZE];
	memset(temp, 0, BUF_SIZE);
	//��������ͻ����������ٽ���
	EnterCriticalSection(&m_clientlock);
	for (int i = 0; i < client.size();i++)
	{
		//��protobufЭ��Ķ���������л�
		message.SerializeToArray(temp, BUF_SIZE);
		if (send(client[i].mysocket, temp, strlen(temp), 0) <= 0)
		{
			AfxMessageBox(_T("���ʹ���!"));
		}
	}
	//�뿪�ٽ���
	LeaveCriticalSection(&m_clientlock);
}
//��CString���ֽڶ���תΪchar���ֽڶ���ĺ���
void CServerDlg::cstring2char(CString str, char* c)
{
	TCHAR wTmp[BUF_SIZE / 2 - 1] = {};
	_tcscpy(wTmp, str.GetBuffer(0));
	int   nLen = wcslen(wTmp) + 1;
	WideCharToMultiByte(CP_ACP, 0, wTmp, nLen, c, 2 * nLen, NULL, NULL);
}
//�޸ı�����ɫ����
HBRUSH CServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (pWnd->GetDlgCtrlID() == IDC_CONTENT)
	{
		COLORREF clr_bk = RGB(140, 200, 85);	//�˴����ñ�����ɫ  
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
//�������߿ͻ����б�
void CServerDlg::UpdateList()
{
	//������б�����ӵ�ǰ���߿ͻ���
	m_list.DeleteAllItems();
	for (int i = 0; i < client.size(); i++)
	{
		m_list.InsertItem(i, client[i].ip);
	}
	UpdateWindow();
}