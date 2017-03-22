#include <iostream>
#include "UploadSocket.h"

using namespace std;
using namespace client;

void main(void)
{
	UploadSocket up;
	up.Initialize().Connect().GetFile();
	system("pause");
}