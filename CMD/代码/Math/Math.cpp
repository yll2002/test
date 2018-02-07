
#  include <iostream>
#  include <windows.h>
#  include "DataDefine.h"
#  include "ParmStack.h"
#  include <string>
#  include <math.h>


   using namespace std;

#  pragma comment(lib,"System.lib")

extern  __declspec(dllimport) command_parm *p_parm;
extern  __declspec(dllimport) fuc_info *p_fucinfo ;
extern  __declspec(dllimport) LinkStack<string> *parm_stack;//创建参数栈
extern  __declspec(dllimport) realparm *parm;
//======================================================================
extern "C" _declspec(dllexport) void _stdcall add();
extern "C" _declspec(dllexport) void _stdcall minus();
extern "C" _declspec(dllexport) void _stdcall multiply();
extern "C" _declspec(dllexport) void _stdcall divide();
extern "C" _declspec(dllexport) void _stdcall sqrt1();
extern "C" _declspec(dllexport) void _stdcall cos1();
extern "C" _declspec(dllexport) void _stdcall sin1();
extern "C" _declspec(dllexport) void _stdcall tan1();
extern "C" _declspec(dllexport) void _stdcall ln();
extern "C" _declspec(dllexport) void _stdcall lg();
extern "C" _declspec(dllexport) void _stdcall acos1();
extern "C" _declspec(dllexport) void _stdcall asin1();
extern "C" _declspec(dllexport) void _stdcall atan1();
extern "C" _declspec(dllexport) void _stdcall atan22();
extern "C" _declspec(dllexport) void _stdcall pow1();
extern "C" _declspec(dllexport) void _stdcall exp1();
extern "C" _declspec(dllexport) void _stdcall cosh1();
extern "C" _declspec(dllexport) void _stdcall sinh1();
extern "C" _declspec(dllexport) void _stdcall tanh1();
//extern "C" _declspec(dllexport) ;

//======================================================================
/////////////////////////////////////////////////////////////////////////////
void _stdcall add()
{		 	
	cout<<parm->double_parm[0]+parm->double_parm[1]<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall minus()
{	
	cout<<parm->double_parm[0]-parm->double_parm[1]<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall multiply()
{
	cout<<parm->double_parm[0]*parm->double_parm[1]<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall divide()
{
	if(abs(parm->double_parm[1])<0.0000001)
	{cout<<"除数为0！"<<endl; return;}
	cout<<parm->double_parm[0]/parm->double_parm[1]<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall sqrt1()
{   
	if(parm->double_parm[0] < 0)
		cout<<"参数小于0，不可开方！"<<endl;
	cout<<sqrt(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall cos1()
{
	cout<<cos(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall sin1()
{
	cout<<sin(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall tan1()
{
	cout<<sin(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall ln()
{
	cout<<log(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall lg()
{
	cout<<log10(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall acos1()
{
    if(parm->double_parm[0]<-1)
	{
		cout<<"参数必须大于 -1！"<<endl;
		return;
	}
    if(parm->double_parm[0]>1)
	{
		cout<<"参数必须小于 1！"<<endl;
		return;
	}
	cout<<acos(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall asin1()
{
	if(parm->double_parm[0]<-1)
	{
		cout<<"参数必须大于 -1！"<<endl;
		return;
	}
    if(parm->double_parm[0]>1)
	{
		cout<<"参数必须小于 1！"<<endl;
		return;
	}
	cout<<asin(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall atan1()
{
	cout<<atan(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall atan22()
{ 
	if(abs(parm->double_parm[1])<0.0001)
      parm->double_parm[1]=0.0001;
	cout<<atan2(parm->double_parm[0],parm->double_parm[1])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall pow1()
{
    cout<<pow(parm->double_parm[0],parm->double_parm[1])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
/*void _stdcall pow10()
{
	cout<<pow10(parm->int_parm[0])<<endl;
}*/
/////////////////////////////////////////////////////////////////////////////
void _stdcall exp1()
{
	cout<<exp(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall cosh1()
{
	cout<<cosh(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall sinh1()
{
	cout<<sinh(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////
void _stdcall tanh1()
{
	cout<<tanh(parm->double_parm[0])<<endl;
}
/////////////////////////////////////////////////////////////////////////////


