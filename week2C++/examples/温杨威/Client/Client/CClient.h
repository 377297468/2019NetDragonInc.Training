#pragma once
#include <iostream>
#include <winsock2.h>
#include <process.h>
#include "log_packet.pb.h"
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#pragma comment(lib, "WS2_32.lib")
using namespace google::protobuf::io;
using namespace std;

class CClient
{
public:
	CClient();
	~CClient();
public:
	//��������
	BOOL ConnectServer(void);           //���ӷ�����
	bool sendData(SOCKET s, char* str, int size); //��������
	BOOL	CreateSendAndRecvThread(void);
public:
	SOCKADDR_IN serveraddr;
	SOCKET  sClient;
	WSADATA wsa;
};

