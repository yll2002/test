#include "stdafx.h"
#include <string.h>
#include <WinSock.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
    //��ʼ��Windows Sockets ��̬��
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        cout<<"�Ҳ�����ʹ�õ�WinSock dll!"<<endl;
        return 1;
    }
    SOCKET sClient = NULL;
    SOCKADDR_IN addrServ;
    addrServ.sin_family=AF_INET;
    addrServ.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
    for (int _port = 0;_port<100;_port++){
        if (sClient == NULL)
        {
            //�����׽���
            sClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(sClient==INVALID_SOCKET)
            {
                cout<<"�����ͻ���socketʧ�ܣ�"<<endl;
                return 1;
            }
        }
    addrServ.sin_port=htons(_port);
    //���ӷ�����
    if(connect(sClient,(sockaddr *)&addrServ,sizeof(sockaddr))==SOCKET_ERROR)
    {
        cout<<"port "<<_port<<" is not open��"<<endl;
   //closesocket(sClient);
        //return 1;
    }
    else{
        cout<<"port "<<_port<<" open on host!!!!!!!!!!!!"<<endl;
        closesocket(sClient);
        sClient = NULL;
    }
}
    //�ر��׽��֣��ͷ���Դ
    getchar();
    WSACleanup();
    return 0;
