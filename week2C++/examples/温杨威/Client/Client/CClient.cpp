#include "CClient.h"

//����
SOCKET  sClient1;
HANDLE	hThreadRecv;						//���������߳�
BOOL	bConnecting;						//�������������״̬
HANDLE	arrThread[1];						//���߳�����

CClient::CClient()
{
	sClient = INVALID_SOCKET;	//�׽���
	sClient1 = INVALID_SOCKET;	//�׽���
	hThreadRecv = NULL;			//���������߳̾��
	bConnecting = FALSE;		//Ϊ����״̬

								//��ʼ�����ݻ�����
	memset(arrThread, 0, 2);
}


CClient::~CClient()
{
	CloseHandle(hThreadRecv);
	closesocket(sClient);
	WSACleanup();
}
//���ӷ�����
BOOL CClient::ConnectServer(void)
{
	WSAStartup(MAKEWORD(2, 0), &wsa);	//��ʼ��WS2_32.DLL

	//�����׽���
	if ((sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		printf("�׽���socket����ʧ��!\n");
		return false;
	}
	sClient1 = sClient;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(5000);
	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//��������
	printf("����������...\n");
	if (connect(sClient, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		printf("����ʧ��!\n");
		return false;
	}
	printf("���ӳɹ�!\n");
	bConnecting = TRUE;
	return true;
}

bool CClient::sendData(SOCKET s, char * str, int size)
{
	//��������
	int bytecount = 0;
	if ((bytecount = send(sClient, str, size, 0)) == -1) {
		fprintf(stderr, "Error sending data %d\n", errno);
		//closesocket(clientsocket);
		return false;
	}
	printf("Sent bytes %d\n", bytecount);
	return true;
}

google::protobuf::uint32 readHdr(char *buf)
{
	google::protobuf::uint32 size;
	google::protobuf::io::ArrayInputStream ais(buf, 4);
	CodedInputStream coded_input(&ais);
	coded_input.ReadVarint32(&size);//Decode the HDR and get the size
	//cout << "size of payload is " << size << endl;
	return size;
}
//���ݰ�����
void ReadMsg(SOCKET csock, google::protobuf::uint32 siz)
{
	int bytecount;
	log_packet payload;
	char *buffer = new char[siz + 4];//size of the payload and hdr
									 //Read the entire buffer including the hdr
	if ((bytecount = recv(csock, buffer, siz + 4, MSG_WAITALL)) == -1) {
		fprintf(stderr, "Error receiving data %d\n", errno);
	}
	//cout << "Second read byte count is " << bytecount << endl;
	//Assign ArrayInputStream with enough memory 
	//google::protobuf::io::ArrayOutputStream
	google::protobuf::io::ArrayInputStream ais(buffer, siz + 4);
	CodedInputStream coded_input(&ais);
	//Read an unsigned integer with Varint encoding, truncating to 32 bits.
	coded_input.ReadVarint32(&siz);
	//After the message's length is read, PushLimit() is used to prevent the CodedInputStream 
	//from reading beyond that length.Limits are used when parsing length-delimited 
	//embedded messages
	google::protobuf::io::CodedInputStream::Limit msgLimit = coded_input.PushLimit(siz);
	//De-Serialize
	payload.ParseFromCodedStream(&coded_input);
	//Once the embedded message has been parsed, PopLimit() is called to undo the limit
	coded_input.PopLimit(msgLimit);
	//Print the message
	cout << "���յ����ݣ� " << endl;
	cout << payload.DebugString() << endl;
}

DWORD WINAPI RecvDataThread(void * pParam)
{
	int		reVal;				    //����ֵ
	char    bufRecv[4];   //�������ݻ�����

	while (bConnecting)			    //����״̬
	{
		memset(bufRecv, 0, 4);
		reVal = recv(sClient1, bufRecv, 4, MSG_PEEK);//��������
		if (SOCKET_ERROR == reVal)
		{
			int nErrCode = WSAGetLastError();
			if (WSAEWOULDBLOCK == nErrCode)			//�������ݻ�����������
			{
				continue;							//������������
			}
			else {
				bConnecting = FALSE;
				return 0;							//�߳��˳�
			}
		}

		if (reVal == 0)							//�������ر�������
		{
			bConnecting = FALSE;
			return 0;								//�߳��˳�
		}
		if (reVal > 0)
		{
			ReadMsg(sClient1, readHdr(bufRecv));
		}
	}
	return 0;
}


BOOL CClient::CreateSendAndRecvThread(void)
{
	// �����������ݵ��߳�
	unsigned long ulThreadId;
	hThreadRecv = CreateThread(NULL, 0, RecvDataThread, NULL, 0, &ulThreadId);
	if (NULL == hThreadRecv)
		return FALSE;

	//��ӵ��߳�����
	arrThread[0] = hThreadRecv;
	return TRUE;
}
