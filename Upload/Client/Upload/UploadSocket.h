#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#pragma once
namespace client {
	class UploadSocket
	{
	private:
		WSADATA wsaData;
		WORD versionRequired;
		SOCKET clientSocket;
		SOCKADDR_IN clientSock_in;
		int err;
		int connect_err;
		void OpenMsg(int err);
	public:
		UploadSocket(void);
		~UploadSocket(void);
		UploadSocket Initialize(void);
		UploadSocket Connect(void);
		UploadSocket GetFile(void);
	};
}

