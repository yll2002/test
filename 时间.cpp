//����ȥ���԰�...�ȵ�20:35�ͻ�����������....��10��...��...
#include <iostream>
#include <windows.h>
using namespace std;
int main ()
{
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	while (true)
	{
		if (systime.wHour ==14 && systime.wMinute==58)
		{
			MessageBox(NULL,"Hello World","Hi",MB_OK);
			break;
		}
	}
	return 0;
}
