#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include <Windows.h>
#include <fstream>
#include <mmsystem.h>
#include<conio.h>
#include <time.h>
#define FILENAME "user.yll"
using namespace std;
string name;
string what=" ";
string user;
string pwd;
string pwd2;
string str; 
void beijing();
void set();
void before();
void beijing();
void start();
void todo(string);
void exit();
void changename();
void first();
void sign();
void getin();
void time();
int main()
{
	cout<<"��ʼ���У����Ժ�......"<<endl;
	system("Cls");
	before();
	start();
	cout<<endl;
	cout<<name<<">";
	loop: 
    getline(cin, str);
    todo(str);
	cout<<name<<">";  
	goto loop;
}
void time()
{
	SYSTEMTIME st = {0};
    GetLocalTime(&st);
    printf("%d-%02d-%02d %02d:%02d:%02d", 
    st.wYear,
    st.wMonth,
    st.wDay,
    st.wHour,
    st.wMinute,
    st.wSecond);
}
void before()
{
	HWND hwnd=GetForegroundWindow();
    int x=GetSystemMetrics(SM_CXSCREEN)+300;
    int y=GetSystemMetrics(SM_CYSCREEN)+300;
    char setting[30];
    sprintf(setting,"mode con:cols=%d lines=%d",x,y);
    system(setting); 
   SetWindowPos(hwnd,HWND_TOPMOST,0,0,x+300,y+300,NULL);
    MoveWindow(hwnd,-10,-40,x+300,y+300,1);
    printf("\n\n");
	SetWindowTextA( GetConsoleWindow(), "Kingdom of God" );
	system("color 3f");
    fstream _file; 
	_file.open(FILENAME,ios::in);
	if(!_file)
	{ 
	first();
	}
	else
	{
	getin();
	}
}
void first()
{
	temp:
	cout<<endl;
	cout<<"ϵͳ>��һ�ο��������봴��һ���˻�."<<endl;
	cout<<"ϵͳ>����1����,����2��¼��"<<endl; 
	sign();
}
void sign()
{
	a:cout<<"����һ������Ա�û�����";
	cin>>user;
	cout<<"�������룺";
	cin>>pwd; 
	cout<<"�ٴ��������룺";
	cin>>pwd2;
	if(pwd!=pwd2)
	{
		cout<<"�������벻һ�£������ԡ�"<<endl; 
		goto a;
	}
	else
	{
		ofstream fout("user.yll");
        fout<<user;
        fout<<" ";
        fout<<pwd;
        fout.close();
        system("Cls");
        getin();
	}
}
void getin()
{
	string a,b;
	cout<<endl;
	cout<<"��¼"<<endl;
    cout<<"���������Ա�˻���";
	cin>>a;
	cout<<"���������룺";
	cin>>b;
	ifstream icin;
    icin.open("user.yll");
    icin>>user;
    icin>>pwd;
	if((a==user)&&(b==pwd))
	{
	   cout<<"��¼�ɹ���"<<endl; 
	   name=user;
	   getchar();
	   system("Cls");
	} 
	else
	{
		cout<<"�Ƿ��û�!����ϵ�����ߡ�"<<endl;
		exit();
		
	}
}
void changename()
{
	string w;
	cout<<"������ԭ����:";
	cin>>w;
	if(w==pwd)
	{
	cout<<"����һ���µ��˻����ƣ�";
	cin>>user; 
	cout<<"�����������룺";
	cin>>pwd; 
	ofstream fout("user.yll");
    fout<<user;
    fout<<" ";
    fout<<pwd;
    fout.close();
	name=user;
	system("Cls");
	getin();
    }
    else
    {
    	cout<<"ԭ�������";
	}
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
	    <<"8 = ��ɫ       9 = ����ɫ"<<endl
	    <<"����10�˳���" <<endl;
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
    case 10:break;
    default:
    	cout<<"�������"; 
    } 
}
void set()
{
	int temp=0;
	cout<<"set>"<<"����0������һ��"<<endl;
	cout<<"set>"<<"����1�ı䴰�ڱ���"<<endl;
	cout<<"set>"<<"����2���Ĺ����˻�"<<endl; 
	cout<<name<<">";
	cin>>temp;
	switch(temp) 
	{
	case 0:break;
	case 1:beijing();break;
	case 2:changename();break;
    }
} 
void start()
{
	cout<<endl;
	cout<<"Kingdom of God [�汾 1.0]" <<endl;
	cout<<"��Ȩ���� (c) 2017 Ҷ��������������Ȩ����"<<endl;
	cout<<"��ǰʱ�䣺"<<endl;
	time();
	cout<<endl;
	cout<<"ϵͳ>";
	cout<<name<<" ����ϵͳ"<<endl; 
	cout<<"ϵͳ>"<<"����help�ɻ�ȡ����"<<endl; 
}


void todo(string a)
{
    if (a=="help")
    {
    	cout<<"����ָ�set" <<endl;
    	cout<<"�˳�ָ�exit"<<endl; 
    	cout<<"ϵͳʱ�䣺time"<<endl; 
    	cout<<"��ϵ�����ߣ�more" <<endl; 
    	cout<<"֧��cmd��䣬��ֱ����������,����cmdֱ�ӽ���cmd���棬������exit���ر�����"<<endl;
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
	if (a=="more")
	{
		cout<<"������QQ��2764863869��"<<endl;
		cout<<"�����ߣ�Ҷ������"<<endl;
	}
	if (a=="time")
	{
		time();
		cout<<endl;
	}
	if ((a!="help")&&(a!="set")&&(a!="exit")&&(a!="more")&&(a!="time"))
	{
		char b[100]={};
		for(int i=0;i<a.length();i++) //���Ԫ�ظ�ֵ
        b[i]=a[i];
		system(b);
	} 
}