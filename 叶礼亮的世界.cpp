#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include <Windows.h>
using namespace std;
string name;
string what;
void beijing();
void set();
void before();
void beijing();
void start();
void todo(string);
void exit();
void changename();
int main()
{
	cout<<"��ʼ���У����Ժ�......"<<endl;
	system("Cls");
	before();
	start();
	cout<<name<<">";
	loop:cin>>what;
	todo(what);
	cout<<name<<">";
	goto loop;
}
void changename()
{
	cout<<"����һ���µ��˻����ƣ�";
	cin>>name; 
}
void exit()
{
	exit(0);
}
void beijing() 
{
	int a=0;
	cout<<"0 = ��ɫ       1 = ��ɫ "<<endl
	<<"2 = ��ɫ       3 = ����ɫ"<<endl
	<<"4 = ��ɫ       5 = ��ɫ "<<endl
	<<"6 = ��ɫ       7 = ��ɫ "<<endl
	<<"8 = ��ɫ       9 = ����ɫ"<<endl;
    cin>>a;
    switch (a)
    {
    case 0:
    	system("color 0f");
    	break;
    case 1:
    	system("color 1f");
    	break;
    case 2:
    	system("color 2f");
    	break;
    case 3:
    	system("color 3f");
    	break;
    case 4:
    	system("color 4f");
    	break;
    case 5:
    	system("color 5f");
    	break;
    case 6:
    	system("color 6f");
    	break;
    case 7:
    	system("color 70");
    	break;
    case 8:
    	system("color 81");
    	break;
    case 9:
    	system("color 9f");
    	break;
    default:
    	cout<<"�������"; 
    } 
}
void set()
{
	int temp=0;
	cout<<"set>"<<"����1�ı䴰�ڱ���"<<endl;
	cout<<"set>"<<"����2���Ĺ����˻�"<<endl; 
	cin>>temp;
	switch(temp) 
	{
	case 1:beijing();break;
	case 2:changename();break;
    }
} 
void before()
{
	SetWindowTextA( GetConsoleWindow(), "Kingdom of God" );
	system("color 3f");
}
void start()
{
	cout<<"Kingdom of God [�汾 1.0]" <<endl;
	cout<<"��Ȩ���� (c) 2017 Ҷ��������������Ȩ����"<<endl;
	cout<<"����һ������Ա�˻���"<<endl;
	cout<<"�˺ţ�";
	cin>> name;
	cout<<"ϵͳ>";
	cout<<name<<" join the system"<<endl; 
	cout<<"ϵͳ>"<<"����help�ɻ�ȡ����"<<endl; 
}


void todo(string a)
{
    if (a=="help")
    {
    	cout<<"����ָ�set" <<endl;
    	cout<<"�˳�ָ�exit"<<endl; 
    	cout<<"" ; 
	}
	if (a=="set")
	{
		set();
	}
	if (a=="exit")
	{
		int x;  
        x=MessageBox(GetForegroundWindow(),"ȷ��Ҫ�˳���","���˳���",1);  
        if(x==1) 
        exit();
	}
}
