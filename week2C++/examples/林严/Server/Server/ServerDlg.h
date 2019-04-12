
// ServerDlg.h : ͷ�ļ�
//

#pragma once
#include "msg.pb.h"
#include <stdio.h>
#include <winsock2.h>
#include <vector>
#include <string>
#include "afxwin.h"
#include <afxmt.h>
#include "afxcmn.h"
#include "afx.h"

#pragma comment(lib,"ws2_32.lib")
#define MAX_CLIENT_NUM 5				//�ͻ��������������
#define BUF_SIZE 1024					//���ݴ����buf��С
using namespace std;

//��������׽��ֶ���Ľṹ��
class MySocket
{
public:
	//����==����������find���������׽���
	bool operator==(const MySocket &S) const
	{ 
		if (this->ip == S.ip)
		{
			return true;
		}
		return false;
	 }
	SOCKET mysocket;					//�׽���
	CString ip;							//�׽��ֶ�Ӧ��ip
};
// CServerDlg �Ի���
class CServerDlg : public CDialog
{
// ����
public:
	CServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void Socketinit();						//��ʼ���׽��ֺ���
	SOCKET server;							//�������׽��ֶ���
	SOCKADDR_IN serveraddr;					//��������ַ�ṹ�����
	SOCKADDR_IN clientaddr;					//�ͻ��˵�ַ�ṹ�����
	HANDLE m_hThread[MAX_CLIENT_NUM];		//ÿ���ͻ������ݴ����߳̾��
	HANDLE m_startThread;					//�����������ͻ����߳̾��
	bool server_status;						//������״̬��־
	HBRUSH m_brush;							//��ˢ
public:
	CString m_content;						//���ڷ�������ͻ���֮���������ݵ���ʾ
	vector<MySocket> client;				//�����׽�������
	CEdit m_text;							//��ʾ��Ϣ��Edit�ؼ�����
	MySocket *m_socket;						//���ٴ���������׽����ڴ�
	MySocket current_socket;				//��ǰ�����׽���
	CButton m_start;						//������������ť�ؼ�
	CButton m_stop;							//�رշ�������ť�ؼ�
	CRITICAL_SECTION m_clientlock;			//�ٽ������������̵߳Ļ���
	CListCtrl m_list;						//�б����������ʾ��ǰ�ͻ����б�
	CTime current_time;						//��ȡϵͳʱ�����
	CString mytime;							//��ȡϵͳʱ���ַ���
	afx_msg void OnBnClickedStartserver();	//������������ť�¼�
	afx_msg void OnBnClickedStopserver();	//�رշ�������ť�¼�
	//�޲��̺߳���
	static unsigned __stdcall Thread(LPVOID lpParm)
	{
		((CServerDlg*)lpParm)->ThreadFun();
		return 0;
	}
	void ThreadFun(void);
	//������Ϣ�����пͻ��˵ĺ���
	void sendtoall(mymsg::msg &message);
	//��CString���ֽڶ���תΪchar���ֽڶ���ĺ���
	void cstring2char(CString str, char c[]);
	//�޸Ŀؼ�����ɫ����
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//�����б���
	void CServerDlg::UpdateList();
};
DWORD WINAPI ThreadProc(LPVOID lpParam);	//��������ͻ������ݴ����̺߳�����ȫ�ֺ���