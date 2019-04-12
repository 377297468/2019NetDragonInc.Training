
// ClientDlg.h : ͷ�ļ�
//
#pragma once
#include <stdio.h>
#include <winsock2.h>
#include <string>
#include "afxwin.h"
#include "msg.pb.h"
#include "afxcmn.h"

#pragma comment(lib,"ws2_32.lib")
#define BUF_SIZE 1024					//���ݴ��仺������С
using namespace std;

// CClientDlg �Ի���
class CClientDlg : public CDialog
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

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

	HBRUSH m_brush;						//�޸ı���ɫ��ˢ
	void Socketinit();					//�׽��ֳ�ʼ������
	CString GetLocalIP();				//��ñ���IP����
public:
	SOCKET clientsocket;				//�ͻ����׽��ֶ���
	SOCKADDR_IN serveraddr;				//��������ַ�ṹ�����
	SOCKADDR_IN clientaddr;				//�ͻ��˵�ַ�ṹ�����
	CString m_content;					//������ʾ�ַ���
	CString m_sendmsg;					//���������ַ���
	afx_msg void OnBnClickedConnect();	//���ӷ�������ť�¼�
	HANDLE m_Threadrecv;				//���������߳̾��
	bool client_status;					//�ͻ���״̬��־
	afx_msg void OnBnClickedSendmsg();	//������Ϣ��ť�¼�
	afx_msg void OnBnClickedClose();	//�ͻ��˹رհ�ť�¼�
	//��CString���ֽڶ���ת��Ϊchar���ֽڶ�����
	void cstring2char(CString str, char c[]);
	CEdit m_recv;						//���ܱ༭�����
	CEdit m_send;						//���ͱ༭�����
	//�ı䱳��ɫ����
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton m_connect;					//���Ӱ�ť����
	void ProgressShow();				//��ʾ����������
	CIPAddressCtrl m_ip;				//IP��ַ�༭�����
};
DWORD WINAPI ThreadProcRecv(LPVOID lpParam);//���������̺߳�����ȫ�ֺ���