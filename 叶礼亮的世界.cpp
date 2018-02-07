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
	cout<<"初始化中，请稍后......"<<endl;
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
	cout<<"输入一个新的账户名称：";
	cin>>name; 
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
	<<"8 = 灰色       9 = 淡蓝色"<<endl;
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
    	cout<<"输入错误"; 
    } 
}
void set()
{
	int temp=0;
	cout<<"set>"<<"输入1改变窗口背景"<<endl;
	cout<<"set>"<<"输入2更改管理账户"<<endl; 
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
	cout<<"Kingdom of God [版本 1.0]" <<endl;
	cout<<"版权所有 (c) 2017 叶礼亮。保留所有权利。"<<endl;
	cout<<"创建一个管理员账户："<<endl;
	cout<<"账号：";
	cin>> name;
	cout<<"系统>";
	cout<<name<<" join the system"<<endl; 
	cout<<"系统>"<<"输入help可获取帮助"<<endl; 
}


void todo(string a)
{
    if (a=="help")
    {
    	cout<<"设置指令：set" <<endl;
    	cout<<"退出指令：exit"<<endl; 
    	cout<<"" ; 
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
}
