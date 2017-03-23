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
			cout<<"服务端打开成功！"<<endl;
		} else{
			cout<<"服务端打开失败！"<<endl;
			exit(-1);
		}
	}

	Server Server::Socket(void)
	{
		socketListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (socketListen == INVALID_SOCKET)
		{
			cout<<"socket 错误！";
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
			cout<<"bind 出错！"<<endl;
			exit(-1);
		}

	}

	Server Server::Listen(void)
	{
		iResult = listen(socketListen, 1);
		if (iResult == SOCKET_ERROR)
		{
			cout<<"listen 出错！"<<endl;
			exit(-1);
		}

		cout<<"服务端ip："<<SERVER_IP<<"  "<<"服务端端口："<<SERVER_PORT<<endl;
		cout<<"服务器启动成功，正在监听..."<<endl;
		return *this;
	}

	Server Server::Accept(void)
	{
		len = sizeof(sockaddr);
		socketMsg = accept(socketListen, (sockaddr*) &addrClient, &len);
		if (socketMsg == INVALID_SOCKET)
		{
			cout<<"accept 出错！"<<endl;
			exit(-1);
		}
		return *this;
	}

	Server Server::Receive(void)
	{
		char recvName[512];
		fstream fp;

		memset(tmp, 0, sizeof(tmp));
		memset(recvName, 0, sizeof(recvName));

		iResult = recv(socketMsg, recvName, sizeof(recvName), 0);

		if (iResult == SOCKET_ERROR) {
			cout<<"接受出错！"<<endl;
			closesocket(socketListen);
			closesocket(socketMsg);
			WSACleanup();
			exit(-1);
		}

		// cout<<recvName<<endl;

		fp.open(recvName, ios::trunc | ios::out | ios::binary);

		if (fp.fail())
		{
			cout<<"初始化文件出错！"<<endl;
			exit(-1);
		}

		cout<<"正在上传中..."<<endl;

		while (true) {
			iResult = recv(socketMsg, tmp, sizeof(tmp), 0);

			if (iResult == SOCKET_ERROR) {
				cout<<"接受出错！"<<endl;
				closesocket(socketListen);
				closesocket(socketMsg);
				WSACleanup();
				fp.close();
				exit(-1);
			}

			if (iResult == 0) {
				cout<<"上传完毕！"<<endl;
				break;
			}

			//cout<<tmp<<" "<<iResult<<endl;
			fp.write(tmp, iResult);
		}
		fp.close();
	}
};

