#include<cstdio>
#include<iostream>
#include <ctime> 
#include<cstdlib>
#include <cstring> 
using namespace std;
int main()
{
	string subject="";
	int howmany=0;
	int need;
	cout<<"2017��40���˶����ǩϵͳ by Ҷ����"<<endl;
	cout<<"���� ��Ŀ ���� ѡȡ��Χ����������Ҫ����"<<endl;
	cin>> subject>>howmany>>need;
	int temp[need+1]={};
	string name[howmany+1]={};
	for(int i=1;i<=howmany;i++)
	{
		cin>>name[i];
	}
	for(int j=1;j<=howmany;j++)
	{
		temp[j]=(rand()%(howmany-1+1))+1;
		for(int i=1;i<=j;i++)
		{
			if((temp[i]==1)||(temp[j]=temp[i]))
			{
				j--;
			}
		}
	}
	cout<<subject<<endl;
	for(int i=1;i<=need;i++)
	{
		cout<<name[temp[i]]<<endl;
	}
	cout<<"���";
	system("pause"); 
}
