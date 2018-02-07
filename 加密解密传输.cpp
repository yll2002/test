#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
string st;
int flag;
char q='#';
void jiami()
{
	cout<<"一次请仅输入一行且不可以有空格。最后以@#结束。"<<endl; 
    cin>>st;
    flag=st.length();
    int as[flag+1]={};
	for(int i=1;i<=flag+1;i++)
	{
		if(st[i]==q) break;
		as[i]=st[i];
		cout<<as[i]<<" ";
	}
}
int main()
{
	int temp;
	loop:cout<<"加密(1)or解密(2)"<<endl;
	cin>>temp;
	switch(temp)
	{
		case 1:
		jiami();
		break;
		case 2:
		break;
		default:
			cout<<"输入错误"<<endl;
			goto loop;
	}
	return 0;
}
