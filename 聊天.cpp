#pragma comment(lib,"ws2_32.lib")
using namespace std;
string strCurMsg="";
void recvProc(SOCKET sockConnect)
{
char msgRcv[100]={0};
while(true)
{
if(SOCKET_ERROR==recv(sockConnect,msgRcv,sizeof(msgRcv),0))
{
cout<<"\nHe is leaving";
return;
}
if(msgRcv[0]!='\0')
{
strCurMsg.erase(strCurMsg.end()-7,strCurMsg.end());
strCurMsg+="He said: ";
strCurMsg+=msgRcv;
strCurMsg+='\n';
strCurMsg+="input: ";
system("cls");
cout< 
}
}
}
int main(int argc, char* argv[])
{
WORD wVersionRequested;
WSADATA wsaData;
int err;
wVersionRequested = MAKEWORD( 1, 1 );
err = WSAStartup( wVersionRequested, &wsaData );
if ( err != 0 ) {
return 1;
}
if ( LOBYTE( wsaData.wVersion ) != 1||
HIBYTE( wsaData.wVersion ) != 1) {
WSACleanup( );
return 1;
}
SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
sockaddr_in addrSrv;
memset(&addrSrv,0,sizeof(addrSrv));
addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
addrSrv.sin_family=AF_INET;
addrSrv.sin_port=htons(5000);
if(bind(sockSrv,(sockaddr*)&addrSrv,sizeof(sockaddr))==SOCKET_ERROR)
{
cout<<"bind error"< 
}
if(listen(sockSrv,5)==SOCKET_ERROR)
{
cout<<"listen error"< 
}
SOCKADDR_IN addrClient;
int len=sizeof(sockaddr);
while(true)
{
cout<<"Waiting .....";
SOCKET sockConnect=accept(sockSrv,(sockaddr*)&addrClient,&len);
if(sockConnect==INVALID_SOCKET)
{
cout<<"invalid socket"< 
return 0;
}
else
{
cout<<"He is coming\n";
}
CreateThread(NULL,0,
(LPTHREAD_START_ROUTINE)recvProc,(void*)sockConnect,
0,NULL);
while(true)
{
char buf[100]={0};
strCurMsg+="input: ";
system("cls");
cout< 
cin.getline(buf,100);
strCurMsg.erase(strCurMsg.end()-7,strCurMsg.end());
strCurMsg+="You said:";
strCurMsg+=buf;
strCurMsg+='\n';
send(sockConnect,buf,sizeof(buf),0);
}
closesocket(sockConnect);
}
WSACleanup();
return 0;
}
// 2009-06-28
#pragma comment(lib,"ws2_32.lib")
using namespace std;
string strCurMsg="";
void recvProc(SOCKET sockConnect)
{
char msgRcv[100]={0};
while(true)
{
if(SOCKET_ERROR==recv(sockConnect,msgRcv,sizeof(msgRcv),0))
{
cout<<"\nHe is leaving";
return;
}
if(msgRcv[0]!='\0')
{
strCurMsg.erase(strCurMsg.end()-7,strCurMsg.end());
strCurMsg+="He said: ";
strCurMsg+=msgRcv;
strCurMsg+='\n';
strCurMsg+="input: ";
system("cls");
cout< 
}
}
}
int main(int argc, char* argv[])
{
WORD wVersionRequested;
WSADATA wsaData;
int err;
wVersionRequested = MAKEWORD( 1, 1 );
err = WSAStartup( wVersionRequested, &wsaData );
if ( err != 0 ) {
return 1;
}
if ( LOBYTE( wsaData.wVersion ) != 1||
HIBYTE( wsaData.wVersion ) != 1) {
WSACleanup( );
return 1;
}
SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
sockaddr_in addrSrv;
memset(&addrSrv,0,sizeof(addrSrv));
addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
addrSrv.sin_family=AF_INET;
addrSrv.sin_port=htons(5000);
if(bind(sockSrv,(sockaddr*)&addrSrv,sizeof(sockaddr))==SOCKET_ERROR)
{
cout<<"bind error"< 
}
if(listen(sockSrv,5)==SOCKET_ERROR)
{
cout<<"listen error"< 
}
SOCKADDR_IN addrClient;
int len=sizeof(sockaddr);
while(true)
{
cout<<"Waiting .....";
SOCKET sockConnect=accept(sockSrv,(sockaddr*)&addrClient,&len);
if(sockConnect==INVALID_SOCKET)
{
cout<<"invalid socket"< 
return 0;
}
else
{
cout<<"He is coming\n";
}
CreateThread(NULL,0,
(LPTHREAD_START_ROUTINE)recvProc,(void*)sockConnect,
0,NULL);
while(true)
{
char buf[100]={0};
strCurMsg+="input: ";
system("cls");
cout< 
cin.getline(buf,100);
strCurMsg.erase(strCurMsg.end()-7,strCurMsg.end());
strCurMsg+="You said:";
strCurMsg+=buf;
strCurMsg+='\n';
send(sockConnect,buf,sizeof(buf),0);
}
closesocket(sockConnect);
}
WSACleanup();
return 0;
}
view plaincopy to clipboardprint? 
// 2009-06-28
#pragma comment(lib,"ws2_32.lib")
using namespace std;
string strCurMsg="";
void recvProc(SOCKET sockClient)
{
char msgRcv[100]={0};
while(true)
{
if(SOCKET_ERROR==recv(sockClient,msgRcv,sizeof(msgRcv),0))
{
cout<<"\nHe is leaving";
return;
}
if(msgRcv[0]!='\0')
{
strCurMsg.erase(strCurMsg.end()-7,strCurMsg.end());
strCurMsg+="He said: ";
strCurMsg+=msgRcv;
strCurMsg+='\n';
strCurMsg+="input: ";
system("cls");
cout< 
}
}
}
int main(int argc, char* argv[])
{
WORD wVersionRequested;
WSADATA wsaData;
int err;
wVersionRequested = MAKEWORD( 1, 1 );
err = WSAStartup( wVersionRequested, &wsaData );
if ( err != 0 ) {
return 1;
}
if ( LOBYTE( wsaData.wVersion ) != 1||
HIBYTE( wsaData.wVersion ) != 1) {
WSACleanup( );
return 1;
}
SOCKET sockClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
SOCKADDR_IN addrSrv;
addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
addrSrv.sin_family=AF_INET;
addrSrv.sin_port=htons(5000);
if (connect(sockClient,(sockaddr*)&addrSrv,sizeof(sockaddr)) == SOCKET_ERROR)
{
cout<<"connected failed\n";
return 1;
}
else
{
cout<<"connect OK\n";
}
CreateThread(NULL,0,
(LPTHREAD_START_ROUTINE)recvProc,(void*)sockClient,
0,NULL);
while(true)
{
char buf[100]={0};
strCurMsg+="input: ";
system("cls");
cout< 
cin.getline(buf,100);
strCurMsg.erase(strCurMsg.end()-7,strCurMsg.end());
strCurMsg+="You said:";
strCurMsg+=buf;
strCurMsg+='\n';
send(sockClient,buf,sizeof(buf),0);
}
closesocket(sockClient);
WSACleanup();
return 0;
}
// 2009-06-28


¿Í»§¶Ë
#pragma comment(lib,"ws2_32.lib")
#include
#include
#include
using namespace std;
string strCurMsg="";
void recvProc(SOCKET sockClient)
{
char msgRcv[100]={0};
while(true)
{
if(SOCKET_ERROR==recv(sockClient,msgRcv,sizeof(msgRcv),0))
{
cout<<"\nHe is leaving";
return;
}
if(msgRcv[0]!='\0')
{
strCurMsg.erase(strCurMsg.end()-7,strCurMsg.end());
strCurMsg+="He said: ";
strCurMsg+=msgRcv;
strCurMsg+='\n';
strCurMsg+="input: ";
system("cls");
cout< 
}
}
}
int main(int argc, char* argv[])
{
WORD wVersionRequested;
WSADATA wsaData;
int err;
wVersionRequested = MAKEWORD( 1, 1 );
err = WSAStartup( wVersionRequested, &wsaData );
if ( err != 0 ) {
return 1;
}
if ( LOBYTE( wsaData.wVersion ) != 1||
HIBYTE( wsaData.wVersion ) != 1) {
WSACleanup( );
return 1;
}
SOCKET sockClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
SOCKADDR_IN addrSrv;
addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
addrSrv.sin_family=AF_INET;
addrSrv.sin_port=htons(5000);
if (connect(sockClient,(sockaddr*)&addrSrv,sizeof(sockaddr)) == SOCKET_ERROR)
{
cout<<"connected failed\n";
return 1;
}
else
{
cout<<"connect OK\n";
}
CreateThread(NULL,0,
(LPTHREAD_START_ROUTINE)recvProc,(void*)sockClient,
0,NULL);
while(true)
{
char buf[100]={0};
strCurMsg+="input: ";
system("cls");
cout< 
cin.getline(buf,100);
strCurMsg.erase(strCurMsg.end()-7,strCurMsg.end());
strCurMsg+="You said:";
strCurMsg+=buf;
strCurMsg+='\n';
send(sockClient,buf,sizeof(buf),0);
}
closesocket(sockClient);
WSACleanup();
return 0;
}

