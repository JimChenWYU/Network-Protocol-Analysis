#include "Server.h"

using namespace std;

namespace server {

	Server::Server(void)
	{
		versionRequired = MAKEWORD(1, 1);
		err = WSAStartup(versionRequired, &wsaData);

		OpenMsg(err);
	}

	Server::~Server(void)
	{
		closesocket(socketMsg);
		closesocket(socketListen);
		WSACleanup();
	}

	void Server::OpenMsg(int err)
	{
		if(!err) {
			cout<<"����˴򿪳ɹ���"<<endl;
		} else{
			cout<<"����˴�ʧ�ܣ�"<<endl;
			exit(-1);
		}
	}

	Server Server::Socket(void)
	{
		socketListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (socketListen == INVALID_SOCKET)
		{
			cout<<"socket ����";
			exit(-1);
		}
		return *this;
	}

	Server Server::GetAddrInfo(void)
	{
		addrServer.sin_addr.S_un.S_addr=inet_addr(SERVER_IP);
		addrServer.sin_family=AF_INET;
		addrServer.sin_port=htons(SERVER_PORT);
		len=sizeof(sockaddr);

		return *this;

	}

	Server Server::Bind(void)
	{
		iResult = bind(socketListen, (sockaddr*) &addrServer, len);

		if (iResult == SOCKET_ERROR)
		{
			cout<<"bind ����"<<endl;
			exit(-1);
		}

	}

	Server Server::Listen(void)
	{
		iResult = listen(socketListen, 1);
		if (iResult == SOCKET_ERROR)
		{
			cout<<"listen ����"<<endl;
			exit(-1);
		}

		cout<<"�����ip��"<<SERVER_IP<<"  "<<"����˶˿ڣ�"<<SERVER_PORT<<endl;
		cout<<"�����������ɹ������ڼ���..."<<endl;
		return *this;
	}

	Server Server::Accept(void)
	{
		len = sizeof(sockaddr);
		socketMsg = accept(socketListen, (sockaddr*) &addrClient, &len);
		if (socketMsg == INVALID_SOCKET)
		{
			cout<<"accept ����"<<endl;
			exit(-1);
		}
		return *this;
	}

	Server Server::Receive(void)
	{
		memset(tmp, 0, sizeof(tmp));
		fstream fp;

		fp.open(FILE_PATH, ios::trunc | ios::out | ios::binary);

		if (fp.fail())
		{
			cout<<"��ʼ���ļ�����"<<endl;
			exit(-1);
		}

		while (true) {
			iResult = recv(socketMsg, tmp, sizeof(tmp), 0);

			if (iResult == SOCKET_ERROR) {
				cout<<"���ܳ���"<<endl;
				closesocket(socketListen);
				closesocket(socketMsg);
				WSACleanup();
				fp.close();
				exit(-1);
			}

			if (iResult == 0) {
				cout<<"������ϣ�"<<endl;
				break;
			}

			//cout<<tmp<<" "<<iResult<<endl;
			fp.write(tmp, iResult);
		}
		fp.close();
	}
};

