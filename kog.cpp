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
	cout<<"初始化中，请稍后......"<<endl;
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
	cout<<"系统>第一次开启程序，请创建一个账户."<<endl;
	cout<<"系统>输入1创建,输入2登录。"<<endl; 
	sign();
}
void sign()
{
	a:cout<<"输入一个管理员用户名：";
	cin>>user;
	cout<<"输入密码：";
	cin>>pwd; 
	cout<<"再次输入密码：";
	cin>>pwd2;
	if(pwd!=pwd2)
	{
		cout<<"两次输入不一致，请重试。"<<endl; 
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
	cout<<"登录"<<endl;
    cout<<"请输入管理员账户：";
	cin>>a;
	cout<<"请输入密码：";
	cin>>b;
	ifstream icin;
    icin.open("user.yll");
    icin>>user;
    icin>>pwd;
	if((a==user)&&(b==pwd))
	{
	   cout<<"登录成功！"<<endl; 
	   name=user;
	   getchar();
	   system("Cls");
	} 
	else
	{
		cout<<"非法用户!请联系开发者。"<<endl;
		exit();
		
	}
}
void changename()
{
	string w;
	cout<<"请输入原密码:";
	cin>>w;
	if(w==pwd)
	{
	cout<<"输入一个新的账户名称：";
	cin>>user; 
	cout<<"请输入新密码：";
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
    	cout<<"原密码错误！";
	}
}
void exit()
{
	exit(0);
}
void beijing() 
{
	int a=0;
	cout<<"0 = 黑色       1 = 蓝色 "<<endl
	    <<"2 = 绿色       3 = 湖蓝色"<<endl
	    <<"4 = 红色       5 = 紫色 "<<endl
	    <<"6 = 黄色       7 = 白色 "<<endl
	    <<"8 = 灰色       9 = 淡蓝色"<<endl
	    <<"输入10退出。" <<endl;
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
    	cout<<"输入错误"; 
    } 
}
void set()
{
	int temp=0;
	cout<<"set>"<<"输入0返回上一级"<<endl;
	cout<<"set>"<<"输入1改变窗口背景"<<endl;
	cout<<"set>"<<"输入2更改管理账户"<<endl; 
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
	cout<<"Kingdom of God [版本 1.0]" <<endl;
	cout<<"版权所有 (c) 2017 叶礼亮。保留所有权利。"<<endl;
	cout<<"当前时间："<<endl;
	time();
	cout<<endl;
	cout<<"系统>";
	cout<<name<<" 登入系统"<<endl; 
	cout<<"系统>"<<"输入help可获取帮助"<<endl; 
}


void todo(string a)
{
    if (a=="help")
    {
    	cout<<"设置指令：set" <<endl;
    	cout<<"退出指令：exit"<<endl; 
    	cout<<"系统时间：time"<<endl; 
    	cout<<"联系开发者：more" <<endl; 
    	cout<<"支持cmd语句，请直接输入命令,输入cmd直接进入cmd界面，再输入exit返回本程序。"<<endl;
	}
	if (a=="set")
	{
		set();
	}
	if (a=="exit")
	{
		int x;  
        x=MessageBox(GetForegroundWindow(),"确定要退出吗？","【退出】",1);  
        if(x==1) 
        exit();
	}
	if (a=="more")
	{
		cout<<"开发者QQ：2764863869。"<<endl;
		cout<<"开发者：叶礼亮。"<<endl;
	}
	if (a=="time")
	{
		time();
		cout<<endl;
	}
	if ((a!="help")&&(a!="set")&&(a!="exit")&&(a!="more")&&(a!="time"))
	{
		char b[100]={};
		for(int i=0;i<a.length();i++) //逐个元素赋值
        b[i]=a[i];
		system(b);
	} 
}
