#include<iostream>
#include<cstdio>
#include<cstring>
#include<conio.h>
using namespace std;
int a[100];
int main()
{
	memset(a, '0', sizeof(a));
	for(int i=1;i<=100;i++)
	{
	cin>>a[i];
	if(a[i]=10) break;
	}
	for(int i=1;i<=100;i++)
	cout<<a[i]<<" ";
	return 0;
}
