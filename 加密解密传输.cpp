#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
string st;
int flag;
char q='#';
void jiami()
{
	cout<<"һ���������һ���Ҳ������пո������@#������"<<endl; 
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
	loop:cout<<"����(1)or����(2)"<<endl;
	cin>>temp;
	switch(temp)
	{
		case 1:
		jiami();
		break;
		case 2:
		break;
		default:
			cout<<"�������"<<endl;
			goto loop;
	}
	return 0;
}
