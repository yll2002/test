
//ǿ���˳�QQ�ĳ������

#include <iostream>

#include <stdio.h>

#include <string>

#include <windows.h>

#include <tlhelp32.h>

using namespace std;

 

 

string str_exp="explorer.exe";

string str_qq="QQ.exe";

bool TerminateProcessFromId(long Id)

{

    bool bRet = false ;

    //��Ŀ����̣�ȡ�ý��̾��

    HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS,false,Id);

    if(hProcess != NULL)

    {

        //��ֹ���̣�

        bRet = ::TerminateProcess(hProcess,0);

    }

    CloseHandle(hProcess);

    return bRet;

}

void Find_Exit(long Id)

{

    bool i=TerminateProcessFromId(Id); //������Ҫ�رյĽ���Id

    if(i)

        cout<<"��������Щ����������QQ"<<endl;

    else

        cout<<"ʧ�ܣ���"<<endl;

}

void ProcessControl()

{

    PROCESSENTRY32 pe32;

    //ʹ������ṹǰ���������Ĵ�С

    pe32.dwSize=sizeof(pe32);

    //��ϵͳ�����еĳ���һ������

    HANDLE hProccessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    if(hProccessSnap == INVALID_HANDLE_VALUE)

    {

       // printf("CreateToolhelp32Snapshot ����ʧ�ܣ���\n");

        return ;

    }

    //�������̿��գ�������ʾÿ�����̵���Ϣ

    BOOL bMore = ::Process32First(hProccessSnap,&pe32);

    while(bMore)

    {

        //printf("�������ƣ� %s\n",pe32.szExeFile);

        //printf("����ID�ţ� %u\n\n",pe32.th32ProcessID);

        while(str_qq == pe32.szExeFile)

        {

            Find_Exit(pe32.th32ProcessID);

        }

        bMore = ::Process32Next(hProccessSnap,&pe32);

    }

    //��� snapshot ����

    ::CloseHandle(hProccessSnap);

    return ;

}

 

int main()

{

    ProcessControl();

    return 0;

}
