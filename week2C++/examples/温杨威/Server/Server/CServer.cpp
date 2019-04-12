

#include "CServer.h"
#include <iostream>
#include <WS2tcpip.h>

using namespace std;
#define SERVER_PORT 5000
#define MSG_BUF_SIZE 1024
ClIENTVECTOR clientvector;                  //�洢���׽���
CServer::CServer()
{
	//��ʼ��������
	cout << "Server ��ʼ��...\n";
	//��ַ����
	addr_len = sizeof(SOCKADDR_IN);
	//sin_familyָ��Э���壬��socket�����ֻ����AF_INET
	addr_server.sin_family = AF_INET;
	//sin_port�洢�˿ںţ�ʹ�������ֽ�˳�򣩣���ͨ���ֿ�����htons()����ת�����������ݸ�ʽ������)
	addr_server.sin_port = htons(SERVER_PORT);
	//sin_addr�洢IP��ַ��ʹ��in_addr������ݽṹ
	//address in network byte order��Internet address��
	//ADDR_ANY,�������е�ַ
	addr_server.sin_addr.S_un.S_addr = ADDR_ANY;
	//��buf_ip���г�ʼ��
	wmemset(buf_ip, 0, IP_BUF_SIZE);
	//WSAStartup,�ú�����һ������ΪWS2_32.DLL�汾��ͨ����ΪMAKEWORD(2,0)��
	//�ڶ�������Ϊһ��ָ��WSADATA��ָ�룬���ڷ���WS2_32.DLL��������Ϣ
	rec_val = WSAStartup(MAKEWORD(2, 0), &wsa_data);
	//�жϣ�����Ϊ0����WS2_32.DLL ��ʼ��ʧ��
	if (rec_val != 0)
	{
		cerr << "WSA ��ʼ��ʧ��!Error code: " << WSAGetLastError() << "\n";
		system("pause");
		exit(1);
	}
	//�������У�WS2_32.DLL ��ʼ���ɹ�
	cout << "WSA ��ʼ���ɹ�...\n";
	//�������ַΪAF_INET��TCP���ӣ�AF_INET���ַTCPЭ����׽���
	sock_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//������socket��INVALID_SOCKET��������socketʧ��
	if (sock_server == INVALID_SOCKET)
	{
		cerr << "����server socketʧ��!Error code: " << WSAGetLastError() << "\n";
		//�ͷ�WS2_32.DLL
		WSACleanup();
		system("pause");
		exit(1);
	}
	//����socket�ɹ�
	cout << "Server socket �����ɹ�...\n";
	//��socket
	rec_val = bind(sock_server, (SOCKADDR*)&addr_server, addr_len);
	if (rec_val != 0)
	{
		//��ʧ��
		cerr << "��server socketʧ��!Error code: " << WSAGetLastError() << "\n";
		WSACleanup();
		system("pause");
		exit(1);
	}
	//�󶨳ɹ�
	cout << "Server socket �󶨳ɹ�...\n";
	//����socket
	rec_val = listen(sock_server, SOMAXCONN);
	if (rec_val == SOCKET_ERROR)
	{
		//��������ʧ��
		cerr << "Server socket ��������ʧ��!Error code: " << WSAGetLastError() << "\n";
		WSACleanup();
		system("pause");
		exit(1);
	}
	//���������ɹ�����ʼ����
	cout << "Server socket ��ʼ����...\n";
	//�������ɹ�����
	cout << "Server �ɹ�����..." << endl;
}


CServer::~CServer()
{
	//�ر�server socket
	closesocket(sock_server);
	//�ر�client socket
	closesocket(sock_client);
	//�ͷ�WS2_32.DLL
	WSACleanup();
}
//���������ͻ����̺߳��������߳���ִ�е��̺߳�����ַ
DWORD WINAPI CreateClientThread(LPVOID lpParameter);

void CServer::WaitForClient()
{
	while (true)
	{
		//������������
		sock_client = accept(sock_server, (SOCKADDR*)&addr_client, &addr_len);
		if (sock_client == INVALID_SOCKET)
		{
			//����ʧ��
			cerr << "Failed to accept client!Error code: " << WSAGetLastError() << "\n";
			WSACleanup();
			system("pause");
			exit(1);
		}
		//���ӳɹ����洢client����
		//CClient *pClient = new CClient(sock_client, addr_client);
		clientvector.insert(pair<SOCKET,bool>(sock_client,true));
		//ת��client ip��ַ
		InetNtop(addr_client.sin_family, &addr_client, buf_ip, IP_BUF_SIZE);
		//���wchar_t����
		wcout << "A new client connected...IP address: " << buf_ip << ", port number: " << ntohs(addr_client.sin_port) << endl;
		//�������߳�
		//h_thread = _beginthreadex(nullptr, 0, CreateClientThread, (LPVOID)sock_client, 0, nullptr);
		h_thread = CreateThread(nullptr, 0, CreateClientThread, (LPVOID)sock_client, 0, nullptr);
		if (h_thread == NULL)
		{
			//����ʧ��
			cerr << "Failed to create a new thread!Error code: " << ::WSAGetLastError() << "\n";
			WSACleanup();
			system("pause");
			exit(1);
		}
		//�ͷž��
		CloseHandle(h_thread);
	}
}

google::protobuf::uint32 readHdr(char *buf)
{
	google::protobuf::uint32 size;
	google::protobuf::io::ArrayInputStream ais(buf, 4);
	CodedInputStream coded_input(&ais);
	coded_input.ReadVarint32(&size);//Decode the HDR and get the size
	cout << "size of payload is " << size << endl;
	return size;
}
//���ݰ�����
void CServer::ReadMsg(SOCKET csock, google::protobuf::uint32 siz)
{
	int bytecount;
	log_packet payload;
	char *buffer = new char[siz + 4];//size of the payload and hdr
									 //Read the entire buffer including the hdr
	if ((bytecount = recv(csock, buffer, siz + 4, MSG_WAITALL)) == -1) {
		fprintf(stderr, "Error receiving data %d\n", errno);
	}
	cout << "Second read byte count is " << bytecount << endl;
	//Assign ArrayInputStream with enough memory 
	//google::protobuf::io::ArrayOutputStream
	google::protobuf::io::ArrayInputStream ais(buffer, siz+4);
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
	cout << "Message is " << payload.DebugString() << endl;
	//�㲥
	ClIENTVECTOR::iterator iter = clientvector.begin();
	while (iter != clientvector.end()) {
		//�����͸��Լ�
		if (csock != iter->first)
		{
			SendData(iter->first, payload);
		}
		iter++;
	}
}
void CServer::SendData(SOCKET client, log_packet payload)
{
	//�������л���װ
	int siz = payload.ByteSize() + 4;
	char *pkt = new char[siz];
	google::protobuf::io::ArrayOutputStream aos(pkt, siz);
	CodedOutputStream *coded_output = new CodedOutputStream(&aos);
	coded_output->WriteVarint32(payload.ByteSize());
	payload.SerializeToCodedStream(coded_output);

	//��������
	int bytecount = 0;
	if ((bytecount = send(client, pkt, siz, 0)) == -1) {
		fprintf(stderr, "Error sending data %d\n", errno);
		//closesocket(clientsocket);
	}
	printf("Sent bytes %d\n", bytecount);
}
DWORD WINAPI CreateClientThread(LPVOID lpParameter)
{
	SOCKET sock_clt = (SOCKET)lpParameter;
	char buf_msg[4];
	int ret_val = 0;
	int snd_result = 0;
	log_packet log;
	//ѭ������
	do
	{
		memset(buf_msg, 0, 4);
		//�����յ����ݸ�ֵ��buf_msg
		ret_val = recv(sock_clt, buf_msg, 4, MSG_PEEK);
		//�ж������Ƿ���ճɹ�
		if (ret_val > 0)
		{
			cout << "First read byte count is " << ret_val << endl;
			//���ճɹ��������ݽ��д���
			CServer::ReadMsg(sock_clt,readHdr(buf_msg));
			//CServer::SendData(sock_clt);
			//log.ParseFromArray(buf_msg, 1024);
			//send(sock_clt, buf_msg, 1024, MSG_PEEK);
			//cout << log.Utf8DebugString() << endl;
		}
		else if (ret_val == 0)
		{
			//�Ͽ�����
			cout << "connection closed..." << endl;
		}
		else
		{
			//���մ�������
			cerr << "Failed to receive message from client!Error code: " << GetLastError() << "\n";
		}
	} while (ret_val > 0);
	//�ر�socket
	ClIENTVECTOR::iterator key = clientvector.find(sock_clt);
	if (key != clientvector.end())
	{
		clientvector.erase(key);
	}
	closesocket(sock_clt);
	return 0;
}
