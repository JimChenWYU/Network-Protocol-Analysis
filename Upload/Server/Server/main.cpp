#include "Server.h"

using namespace std;

void main(void)
{
	server::Server s;
	s.Socket().GetAddrInfo().Bind().Listen().Accept().Receive();
	system("pause");
}