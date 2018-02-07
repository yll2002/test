#include "stdafx.h"
#include <string.h>
#include <WinSock.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
    //初始化Windows Sockets 动态库
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        cout<<"找不到可使用的WinSock dll!"<<endl;
        return 1;
    }
    SOCKET sClient = NULL;
    SOCKADDR_IN addrServ;
    addrServ.sin_family=AF_INET;
    addrServ.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
    for (int _port = 0;_port<100;_port++){
        if (sClient == NULL)
        {
            //创建套接字
            sClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(sClient==INVALID_SOCKET)
            {
                cout<<"创建客户端socket失败！"<<endl;
                return 1;
            }
        }
    addrServ.sin_port=htons(_port);
    //连接服务器
    if(connect(sClient,(sockaddr *)&addrServ,sizeof(sockaddr))==SOCKET_ERROR)
    {
        cout<<"port "<<_port<<" is not open！"<<endl;
   //closesocket(sClient);
        //return 1;
    }
    else{
        cout<<"port "<<_port<<" open on host!!!!!!!!!!!!"<<endl;
        closesocket(sClient);
        sClient = NULL;
    }
}
    //关闭套接字，释放资源
    getchar();
    WSACleanup();
    return 0;
