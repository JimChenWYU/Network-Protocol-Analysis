#include "UploadSocket.h"
#include <iostream>
#include <fstream>
#include "Config.h"

using namespace std;

namespace client {

	UploadSocket::UploadSocket(void)
	{
		versionRequired = MAKEWORD(1, 1);
		err = WSAStartup(versionRequired, &wsaData);
		OpenMsg(err);
	}


	UploadSocket::~UploadSocket(void)
	{
		closesocket(clientSocket);
		WSACleanup();
	}

	void UploadSocket::OpenMsg(int err)
	{
		if(!err) {
			cout<<"客户端打开成功！"<<endl;
		} else {
			cout<<"客户端打开失败！"<<endl;
			exit(-1);
		}
	}

	UploadSocket UploadSocket::Initialize(void)
	{
		char ip[15];
		int port;

		if (! DEBUG) {
			cout<<"请输入服务端ip：";
			cin>>ip;
			cout<<"请输入服务端端口：";
			cin>>port;
			cout<<endl;
		}
		

		clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		clientSock_in.sin_addr.S_un.S_addr = inet_addr(DEBUG ? SERVER_IP : ip);
		clientSock_in.sin_family = AF_INET;
		clientSock_in.sin_port = htons(DEBUG ? SERVER_PORT : port);
		return *this;
	}

	UploadSocket UploadSocket::Connect(void)
	{
		if (clientSocket != INVALID_SOCKET) {
			connect_err = connect(clientSocket, (SOCKADDR*) &clientSock_in, sizeof(SOCKADDR));
		} else {
			cout<<"无法建立连接！"<<endl;
			exit(-1);
		}
		return *this;
	}

	UploadSocket UploadSocket::GetFile(void)
	{
		if (!connect_err){
			fstream file;

			char buffer[BUFFSIZE];

			memset(buffer, 0, sizeof(buffer));

			file.open(FILE_PATH, ios::binary |ios::in);

			if (file.fail()) {
				cout<<"打开文件失败！"<<endl;
				exit(-1);
			}

			// cout<<FILE_PATH<<" len: "<<sizeof(FILE_PATH)<<endl;

			send(clientSocket, FILE_PATH, sizeof(FILE_PATH), 0);

			int size = 0, len = 0;

			while (! file.eof()) {
				file.read(buffer, BUFFSIZE);
				len = file.gcount();
				size += len;
				// cout<<buffer<<endl;
				cout<<"已经传输："<<size<<" 字节."<<endl;
				send(clientSocket, buffer, len, 0);
			}

			cout<<"传输完毕！！！！"<<endl;
			file.close();
		} else {
			cout<<"连接失败！"<<endl;
			exit(-1);
		}
		return *this;
	}
}

