//初始化SOCKET
WSADATA wsaData;
int iRet = WSAStartup(MAKEWORD(2,1), &wsaData);
if ( iRet != 0 )
{
printf( "WSAStartup Error:%d\n", GetLastError() );
exit( 0 );
}
int nRemoteAddr = inet_addr( argv[1] );
remoteHostent= (struct hostent*)malloc( sizeof(struct hostent ));
struct in_addr sa;
for ( int i = 0; i < numberOfHost; i ++ )
{
//获取远程机器名
sa.s_addr = nRemoteAddr;
printf( "\nIpAddress : %s\n", inet_ntoa( sa ) );
remoteHostent = gethostbyaddr( (char*)&nRemoteAddr,4, AF_INET );
if ( remoteHostent )
printf( "HostName　: %s\n",remoteHostent->h_name );
else
printf( "gethostbyaddr Error:%d\n",GetLastError() );
//发送ARP查询包获得远程MAC地址
 
unsigned char macAddress[6];
ULONG macAddLen = 6;
iRet=SendARP(nRemoteAddr, (unsigned long)NULL,(PULONG)&macAddress, &macAddLen);
if ( iRet == NO_ERROR )
{
printf( "MacAddress: " );
for( int i =0; i<6; i++ )
{
printf( "%.2x", macAddress[i] );
if ( i<5 ) printf( "-" );
}
printf( "\n" );
}
else
printf( "SendARP Error:%d\n", GetLastError());
nRemoteAddr = htonl( ntohl( nRemoteAddr ) + 1 );
}
}
