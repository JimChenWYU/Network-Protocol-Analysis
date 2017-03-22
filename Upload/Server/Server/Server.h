#include <iostream>
#include <fstream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Config.h"
#pragma comment(lib,"ws2_32.lib")
#pragma once
namespace server {
	class Server
	{
	private:
		WSADATA wsaData;
		WORD versionRequired;
		SOCKET socketListen, socketMsg;
		int err;
		int iResult;
		int len;
		char tmp[DEFAULT_BUFLEN];
		struct sockaddr_in addrServer, addrClient;

		void OpenMsg(int err);
	public:
		Server(void);
		~Server(void);
		Server GetAddrInfo(void);
		Server Socket(void);
		Server Bind(void);
		Server Listen(void);
		Server Accept(void);
		Server Receive(void);
	};
}


