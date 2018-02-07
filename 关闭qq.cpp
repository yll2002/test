
//强制退出QQ的程序软件

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

    //打开目标进程，取得进程句柄

    HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS,false,Id);

    if(hProcess != NULL)

    {

        //终止进程！

        bRet = ::TerminateProcess(hProcess,0);

    }

    CloseHandle(hProcess);

    return bRet;

}

void Find_Exit(long Id)

{

    bool i=TerminateProcessFromId(Id); //传递所要关闭的进程Id

    if(i)

        cout<<"让你们这些蠢货天天上QQ"<<endl;

    else

        cout<<"失败！！"<<endl;

}

void ProcessControl()

{

    PROCESSENTRY32 pe32;

    //使用这个结构前，设置他的大小

    pe32.dwSize=sizeof(pe32);

    //给系统内所有的程序一个快照

    HANDLE hProccessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    if(hProccessSnap == INVALID_HANDLE_VALUE)

    {

       // printf("CreateToolhelp32Snapshot 调用失败！！\n");

        return ;

    }

    //遍历进程快照，轮流显示每个进程的信息

    BOOL bMore = ::Process32First(hProccessSnap,&pe32);

    while(bMore)

    {

        //printf("进程名称： %s\n",pe32.szExeFile);

        //printf("进程ID号： %u\n\n",pe32.th32ProcessID);

        while(str_qq == pe32.szExeFile)

        {

            Find_Exit(pe32.th32ProcessID);

        }

        bMore = ::Process32Next(hProccessSnap,&pe32);

    }

    //清除 snapshot 对像！

    ::CloseHandle(hProccessSnap);

    return ;

}

 

int main()

{

    ProcessControl();

    return 0;

}
