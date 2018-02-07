//你拿去测试吧...等到20:35就会跳出个东东....才10分...汗...
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
