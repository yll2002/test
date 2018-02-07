#  include <iostream>
#  include <fstream>
#  include <string>
#  include <windows.h>
#  include "DataDefine.h"
#  include "ParmStack.h"

   using namespace std;

#  pragma comment(lib,"System.lib")

typedef void (_stdcall *lpFun) ();//定义函数指针

extern  __declspec(dllimport) command_parm *p_parm;
extern  __declspec(dllimport) fuc_info *p_fucinfo ;
extern  __declspec(dllimport) LinkStack<string> *parm_stack;
extern  __declspec(dllimport) realparm *parm;
extern  __declspec(dllimport) workspace *work_space;

extern "C" __declspec(dllimport) int __stdcall  FindFunction(char *command,fuc_info *p_fucinfo,command_parm *p_parm);
extern "C" __declspec(dllimport) int __stdcall  DivideCommand(char* cmdline,command_parm *p_parm);
extern "C" __declspec(dllimport) int __stdcall  ShowInfo(int infomode,char *info);
extern "C" __declspec(dllimport) int __stdcall  ParmChange();

void   cd();       //cd命令
void   cd2();      //cd..命令
void   copy();     //copy命令
void   paste();    //paste命令


void main()
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
            FOREGROUND_GREEN | FOREGROUND_BLUE);
	for( int firstvar=0;firstvar<80;firstvar++)
	{cout<<"*";}
	cout<<endl;
	Sleep(100);
	cout<<"\t\t\t\tCOMMAND SYSTEM"<<endl;
    cout<<endl;
	cout<<"\t\t\t     writen by  Cao Runze"<<endl;
	for( firstvar=0;firstvar<80;firstvar++)
	{cout<<"*";}
	cout<<endl;

    char szAppPath[512]; 
    GetCurrentDirectory(512,szAppPath);
    work_space->s_work_space = szAppPath;
	//cout<<work_space->s_work_space<<endl;

	while(1)
	{
     int  i=0,j=0,k=0,m=0,n=0;

     char cmdline[512];

	 string a,b;

     ShowInfo(InputInfo,NULL);

     cin.getline(cmdline,256);
	 //cout<<cmdline<<endl;
     //cout<<endl;
     p_parm->all_parm = cmdline;
     DivideCommand(cmdline,p_parm);//分解 输入的命令

	 /*for(i = 0; i <= p_parm->factparmnum ; i++)
	 {cout<<p_parm->parm[i]<<endl;}*/
	 //cout<<"p_parm->all_parm: "<<p_parm->all_parm<<endl;
     //cout<<"p_parm->factparmnum before push in stack is: "<<p_parm->factparmnum<<endl;
     parm_stack->Clear();//空栈

     string **ps_parm = new string*[p_parm->factparmnum];
	 //cout<<"p_parm->factparmnum pass in stack is: "<<p_parm->factparmnum<<endl;

     for( i = 0; i < p_parm->factparmnum; i++ )
        ps_parm[i] = new string;

	 for( i = p_parm->factparmnum-1; i >= 0; i--)//用上0下标 从右往左压栈
	 {
        (*(ps_parm[i])).assign(p_parm->parm[i+1]);//parm[0]为函数名
        parm_stack->Push(*(ps_parm[i]));//参数压栈
		//cout<<"参数压栈：*(ps_parm["<<i<<"]: "<<*(ps_parm[i])<<endl;
	 }

	 /*for(i=0;i<p_parm->factparmnum;i++)
	 {
       parm_stack->Pop(*(ps_parm[i]));//参数出栈
	   cout<<"参数出栈*(ps_parm[i]:"<<*(ps_parm[i])<<endl;
	 }*/


     //cout<<"p_parm->factparmnum before FindFunction is: "<<p_parm->factparmnum<<endl;
	 //cout<<"p_parm->parm[0]: "<<"*"<<p_parm->parm[0]<<"*"<<endl;
     int returnvalue = FindFunction(p_parm->parm[0],p_fucinfo,p_parm);
	 //cout<<"returnvalue: "<<returnvalue<<endl;
	 if(returnvalue != 0)
		 continue;
		
    /*cout<<"p_parm->factparmnum after FindFunction is: "<<p_parm->factparmnum<<endl;
               cout<<"p_fucinfo->fucnum "<<p_fucinfo->fucnum<<endl;  
			   cout<<"p_fucinfo->fucname "<<p_fucinfo->fucname<<endl; 
               cout<<"p_fucinfo->dllname "<<p_fucinfo->dllname<<endl; 
               cout<<"p_fucinfo->parmtype "<<p_fucinfo->parmtype<<endl; 
               cout<<"p_fucinfo->dllnum "<<p_fucinfo->dllnum<<endl;*/

    ParmChange();

    HINSTANCE hDll;
	lpFun Function;
	//cout<<"p_fucinfo->dllnum:"<<p_fucinfo->dllnum<<"*"<<endl;

	if(strcmp(p_fucinfo->dllname,"Command.exe")==0)
	{
               switch(p_fucinfo->dllnum)
			   {
                 case (1):
					 {
                         cd();
                         break;
					 }
                 case (2):
					 {
                         cd2();
	                     break;
					 }
				 case (3):
					 {
						 copy();
						 break;
					 }
				 case (4):
					 {
						 paste();
						 break;
					 }
   
			   }//end-switch

			   continue;
	}

	hDll = LoadLibrary(p_fucinfo->dllname);
	if(hDll != NULL)
	{
		//Function = (lpFun) GetProcAddress(hDll,p_fucinfo->fucname);//利用名称
        Function = (lpFun) GetProcAddress(hDll,MAKEINTRESOURCE(p_fucinfo->dllnum));//利用序号
		if(Function != NULL)
		{
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
            FOREGROUND_RED | FOREGROUND_BLUE);
            //cout<<"Function called success!"<<endl;
			//cout<<parm->double_parm[0]<<endl;
            //cout<<parm->double_parm[1]<<endl;
			Function();
		}
		else
		{
			cout<<"Function called fail!"<<endl;
		}//end-else
		
	   FreeLibrary(hDll);
	   //for( i = 0; i < p_parm->factparmnum; i++ )
         //delete ps_parm[i];

	}//end-if

	}//end-while
}
////////////////////////////////////////////////////////////////////////////////////
void cd()
{
   string temp = p_parm->parm[0];
   //cout<<temp<<endl;
   int len = temp.length();
   int pos = p_parm->all_parm.find(temp,0);
   pos=pos+len;
   int length = p_parm->all_parm.length();
   //cout<<"length is:"<<length<<endl;
   temp = p_parm->all_parm.substr(pos,length-pos);
   //cout<<temp<<endl;
   length = temp.length();
   //cout<<"temp length is:"<<length<<endl;
   pos = temp.find_first_not_of(" ",0);
   //cout<<"first not " " is:"<<pos<<endl;
   string temp2 = temp.substr(pos,length-pos);
   if(temp2 =="..")
   {
	   len = work_space->s_work_space.length();
	   pos = work_space->s_work_space.find_last_of("\\",len);
	   work_space->s_work_space=work_space->s_work_space.substr(0,pos);
   }
   else if(0<(temp2.find(":",0))&&(temp2.find(":",0))<temp2.length())
   {
       work_space->s_work_space.assign(temp2);
   }

   else
   {
       work_space->s_work_space+="\\";
       work_space->s_work_space+=temp2;
   }
   //cout<<work_space->s_work_space<<endl;
}
//////////////////////////////////////////////////////////////////////////////////
void cd2()
{
	int len = work_space->s_work_space.length();
	int pos = work_space->s_work_space.find_last_of("\\",len);
	work_space->s_work_space=work_space->s_work_space.substr(0,pos);
}
//////////////////////////////////////////////////////////////////////////////////
void   copy()
{   
   string temp = p_parm->parm[0];
   //cout<<temp<<endl;
   int len = temp.length();
   int pos = p_parm->all_parm.find(temp,0);
   pos=pos+len;
   int length = p_parm->all_parm.length();
   //cout<<"length is:"<<length<<endl;
   temp = p_parm->all_parm.substr(pos,length-pos);
   //cout<<temp<<endl;
   length = temp.length();
   //cout<<"temp length is:"<<length<<endl;
   pos = temp.find_first_not_of(" ",0);
   //cout<<"first not " " is:"<<pos<<endl;
   string temp2 = temp.substr(pos,length-pos);
   work_space->filename=temp2;
   work_space->s_temp_work_space =work_space->s_work_space;
   work_space->s_temp_work_space+="\\";
   work_space->s_temp_work_space+=temp2;
}
//////////////////////////////////////////////////////////////////////////////////
void paste()
{
	bool bFailIfExists = true;
	string newpath = work_space->s_work_space;
    newpath +="\\";
	newpath += work_space->filename;
	cout<<work_space->s_temp_work_space<<endl;
	cout<<newpath<<endl;
    CopyFile(work_space->s_temp_work_space.c_str(),newpath.c_str(),bFailIfExists);		     
    //BOOL bFailIfExists          // operation if file exists
}
//////////////////////////////////////////////////////////////////////////////////