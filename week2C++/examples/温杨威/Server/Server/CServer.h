#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include "log_packet.pb.h"
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#pragma comment(lib, "ws2_32.lib")
using namespace google::protobuf::io;
using namespace std;
#define IP_BUF_SIZE 129
typedef map<SOCKET,bool> ClIENTVECTOR;		//��������
class CServer
{
public:
	CServer();
	~CServer();
public:
	//�ȴ��ͻ���
	void WaitForClient();
	//���ݰ�����
	void static ReadMsg(SOCKET csock, google::protobuf::uint32 siz);
	void static SendData(SOCKET client, log_packet msg);
private:
	//�洢��WSAStartup�������ú󷵻ص�Windows Sockets����
	WSADATA wsa_data;
	//����server�׽���
	SOCKET sock_server;
	//����client�׽���
	SOCKET sock_client;
	//�������������߳�
	HANDLE h_thread;
	//����server��ַ�Ͷ˿�
	SOCKADDR_IN addr_server;
	//����client��ַ�Ͷ˿�
	SOCKADDR_IN addr_client;
	//���溯������ֵ��������֤�����Ƿ����гɹ�
	int rec_val;
	//�����ַ����
	int addr_len;
	//����ip��ַ
	wchar_t buf_ip[IP_BUF_SIZE];
};

