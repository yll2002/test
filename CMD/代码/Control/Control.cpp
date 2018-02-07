#  include <iostream>
#  include <windows.h>
#  include "DataDefine.h"
#  include "ParmStack.h"
#  include <string>
#  include <fstream>
#  include <iomanip>
#  include <shellapi.h>
#  include <tlhelp32.h>
#  include "Psapi.h"   


   using namespace std;

#  pragma comment(lib,"System.lib")
#  pragma comment(lib,"Psapi.lib")

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);

extern  __declspec(dllimport) command_parm *p_parm;
extern  __declspec(dllimport) fuc_info *p_fucinfo ;
extern  __declspec(dllimport) LinkStack<string> *parm_stack;//��������ջ
extern  __declspec(dllimport) realparm *parm;
extern  __declspec(dllimport) workspace *work_space;

extern "C" _declspec(dllexport) void _stdcall help();
//extern "C" _declspec(dllexport) void _stdcall commandlist();
//extern "C" _declspec(dllexport) void _stdcall functionlist();
//extern "C" _declspec(dllexport) void _stdcall dllinfo();
extern "C" _declspec(dllexport) void _stdcall dos();
extern "C" _declspec(dllexport) void _stdcall exe();
extern "C" _declspec(dllexport) void _stdcall run();
//extern "C" _declspec(dllexport) void _stdcall fileinfo();
//extern "C" _declspec(dllexport) void _stdcall currentdir();
//extern "C" _declspec(dllexport) void _stdcall open();
//extern "C" _declspec(dllexport) void _stdcall copy();
//extern "C" _declspec(dllexport) void _stdcall paste();
extern "C" _declspec(dllexport) void _stdcall dir();
extern "C" _declspec(dllexport) void _stdcall del();
//extern "C" _declspec(dllexport) void _stdcall play();
//extern "C" _declspec(dllexport) void _stdcall exit1();
//extern "C" _declspec(dllexport) void _stdcall close();
extern "C" _declspec(dllexport) void _stdcall closewindow();
extern "C" _declspec(dllexport) void _stdcall closeprocess();
extern "C" _declspec(dllexport) void _stdcall listwindow();
extern "C" _declspec(dllexport) void _stdcall listprocess();

HWND m_hwndFind[256] = {0};
int  m_num = 0;
string s_input;


//////////////////////////////////////////////////////////////////////////////
//void _stdcall exit1()
//{
 //exit();
//}
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	 char windtext[64];
     if(::GetWindowLong(hWnd,GWL_STYLE) & WS_VISIBLE)
     {
         m_num++;
         //��ȡ���ڱ���
         GetWindowText( hWnd, windtext, 64 );
         
		 if(lParam==1)
		 {
             string s_windtext = windtext;
			 if(0<=s_windtext.find(s_input,0) && s_windtext.find(s_input,0)<s_windtext.length())
			 {
                 SendMessage(hWnd, WM_CLOSE, 0, 0);
				 cout<<"�رմ���:"<<s_windtext<< "�ɹ�!"<<endl;
			 }

		 }
		 else
		 {
             cout<<"����:"<<setw(3)<<m_num<<"   "<<windtext<<endl;
		 }
         m_hwndFind[m_num] = hWnd;     
     }
     return true;
}
//////////////////////////////////////////////////////////////////////////////
void _stdcall closewindow()
{
   string temp = p_parm->parm[0];
   string filepath;
   //cout<<temp<<endl;
 
       int len = temp.length();
       int pos = p_parm->all_parm.find(temp,0);
           pos = pos+len;
       int length = p_parm->all_parm.length();
       //cout<<"length is:"<<length<<endl;
       temp = p_parm->all_parm.substr(pos,length-pos);
       //cout<<temp<<endl;
       length = temp.length();
       //cout<<"temp length is:"<<length<<endl;
       pos = temp.find_first_not_of(" ",0);
       //cout<<"first not " " is:"<<pos<<endl;
       string temp2 = temp.substr(pos,length-pos);
	   filepath = temp2;

       s_input = filepath;
	   //cout<<"s_input:"<<s_input<<endl;

      EnumWindows( EnumWindowsProc,1);
}
//////////////////////////////////////////////////////////////////////////////
void _stdcall listwindow()
{
  EnumWindows( EnumWindowsProc,0);
  cout<<"\t\t�ܹ�:"<<m_num<<"������"<<endl;
  return;
}
//////////////////////////////////////////////////////////////////////////////
void _stdcall closeprocess()
{
  
   string temp = p_parm->parm[0];
   string filepath;
   //cout<<temp<<endl;
 
       int len = temp.length();
       int pos = p_parm->all_parm.find(temp,0);
           pos = pos+len;
       int length = p_parm->all_parm.length();
       //cout<<"length is:"<<length<<endl;
       temp = p_parm->all_parm.substr(pos,length-pos);
       //cout<<temp<<endl;
       length = temp.length();
       //cout<<"temp length is:"<<length<<endl;
       pos = temp.find_first_not_of(" ",0);
       //cout<<"first not " " is:"<<pos<<endl;
       string temp2 = temp.substr(pos,length-pos);
	   filepath = temp2;

      cout<<"filepath:"<<filepath<<endl;
     HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
     if(hProcessSnap==INVALID_HANDLE_VALUE)
	 {
            cout<<"�������̿���ʧ��!"<<endl;
           return ;
	 }
	 cout<<"�������̿��ճɹ�!"<<endl;
     PROCESSENTRY32 processEntry={0};
     processEntry.dwSize=sizeof(PROCESSENTRY32);//��ʼ�������̿���

     bool bRet=(bool)Process32First(hProcessSnap,&processEntry);

     while(bRet) //������ز�Ϊ�վͼ���ִ��ѭ��
	 { //ExtraceFileName����ȡ�����ļ�����ȥ��·��
         if(strcmp(processEntry.szExeFile,filepath.c_str())==0)//"taskmgr.exe"
		 {
            cout<<"���ֽ���"<<endl;
            //���ݽ���PID����ȫȨ�޴򿪴˽��̣�Ȼ��ǿ����ֹ
         cout<<"���ҵ�"<<filepath<<"!"<<endl;
         HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS,false,processEntry.th32ProcessID);
         if(TerminateProcess(handle,0)==0)
		 {cout<<"��������ʧ�ܣ�"<<endl;}
		 else
		 {cout<<"�������̳ɹ�!"<<endl;}
         CloseHandle(handle);
         //�����Ѿ�������!;
		 }
         bRet = (bool)Process32Next(hProcessSnap,&processEntry);
	 }
     CloseHandle(hProcessSnap);

}

//////////////////////////////////////////////////////////////////////////////
void _stdcall listprocess()
{
     int labelone=0;
     HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
     if(hProcessSnap==INVALID_HANDLE_VALUE)
     {
       cout<<"�������̿���ʧ��!"<<endl;
       return ;
	 }

     HMODULE hMods;
     HANDLE  hProcess;
     char    szModName[MAX_PATH];
	 DWORD   needed;

     PROCESSENTRY32 processEntry={0};
     processEntry.dwSize=sizeof(PROCESSENTRY32);//��ʼ�������̿���

     bool bRet=Process32First(hProcessSnap,&processEntry);
	 cout<<"\tĿǰ�������еĽ�������:"<<endl;
     int processnum=0;
     while(bRet) //������ز�Ϊ�վͼ���ִ��ѭ��
	 {  //ExtraceFileName����ȡ�����ļ�����ȥ��·��
        //if(ExtractFileName(processEntry.szExeFile)=="360tray.exe")//"taskmgr.exe"
		    processnum++;
			cout<<setw(3)<<processnum;
			
			cout<<"  "<<"ID:"<<setw(5)<<processEntry.th32ProcessID;
			cout<<"  "<<processEntry.szExeFile<<endl;
            hProcess = OpenProcess( PROCESS_ALL_ACCESS,false, processEntry.th32ProcessID );
            EnumProcessModules(hProcess, &hMods, sizeof(hMods), &needed);
            GetModuleFileNameEx( hProcess, hMods, szModName,MAX_PATH);
			if(strlen(szModName)<=2)
			{
				cout<<"\t\t    ϵͳ����!"<<endl;
			}
			else if(strstr(szModName,"��"))
			{
			    cout<<"\t\t    ϵͳ����!"<<endl;
			}
			else
			{
                cout<<"\t\t·��->  "<<szModName<<endl;
			}
            bRet=Process32Next(hProcessSnap,&processEntry);
	 }
     
     CloseHandle(hProcessSnap);
cout<<"\t\t"<<setw(4)<<processnum<<" ������"<<endl;
     return ;
}
//////////////////////////////////////////////////////////////////////////////
void _stdcall del()
{
   string temp = p_parm->parm[0];
   string filepath;
   //cout<<temp<<endl;
 
       int len = temp.length();
       int pos = p_parm->all_parm.find(temp,0);
           pos = pos+len;
       int length = p_parm->all_parm.length();
       //cout<<"length is:"<<length<<endl;
       temp = p_parm->all_parm.substr(pos,length-pos);
       //cout<<temp<<endl;
       length = temp.length();
       //cout<<"temp length is:"<<length<<endl;
       pos = temp.find_first_not_of(" ",0);
       //cout<<"first not " " is:"<<pos<<endl;
       string temp2 = temp.substr(pos,length-pos);
	   if(0<temp2.find(":\\",0) && temp2.find(":\\",0)<temp2.length())
	   {
		   filepath = temp2;
	   }
	   else
	   {
       filepath = work_space->s_work_space;
       filepath += "\\";
       filepath += temp2;
	   }


   bool returnvalue = DeleteFile(filepath.c_str());
   if(returnvalue)
   {
	   cout<<"Delete File :"<<filepath<<" Succeed!"<<endl;
   }
   else
   {
	   cout<<"Delete File :"<<filepath<<" Failed!"<<endl;
	   cout<<"���ļ����ܲ����ڣ������������У������ļ�·���Ƿ���ȷ������ļ��Ƿ���������"<<endl;
   }
}
//////////////////////////////////////////////////////////////////////////////
void _stdcall help()
{
    char FileName[128];
    char line[256];

    strcpy(FileName,"help//");
    strcat(FileName,parm->string_parm[0].c_str());
    strcat(FileName,".txt");

    ifstream infile(FileName);

      if(infile.fail())//if open file failed
        {
          cout<<"The help file: "
			  <<FileName<<" not find!"<<endl;
        }
      else
        {
          while(!infile.eof())
          {
               infile.getline(line,256);
               cout<<line<<endl;
          }
        }
}
//////////////////////////////////////////////////////////////////////////////
void _stdcall run()
{
   string temp = p_parm->parm[0];
   string filepath;
   //cout<<temp<<endl;
 
       int len = temp.length();
       int pos = p_parm->all_parm.find(temp,0);
           pos = pos+len;
       int length = p_parm->all_parm.length();
       //cout<<"length is:"<<length<<endl;
       temp = p_parm->all_parm.substr(pos,length-pos);
       //cout<<temp<<endl;
       length = temp.length();
       //cout<<"temp length is:"<<length<<endl;
       pos = temp.find_first_not_of(" ",0);
       //cout<<"first not " " is:"<<pos<<endl;
       string temp2 = temp.substr(pos,length-pos);

	   if(0<temp2.find(":\\",0) && temp2.find(":\\",0)<temp2.length())
	   {
		   filepath = temp2;
	   }
	   else
	   {
       filepath = work_space->s_work_space;
       filepath += "\\";
       filepath += temp2;
	   }
   ShellExecute(NULL,"open",filepath.c_str(),NULL,NULL,SW_SHOWNORMAL);
   cout<<endl;
}
//////////////////////////////////////////////////////////////////////////////
void _stdcall currentdir()
{
  char szAppPath[256]; 
  GetModuleFileName(NULL, szAppPath, 256);
  cout<<szAppPath<<endl;
}
//////////////////////////////////////////////////////////////////////////////
void _stdcall exe()
{
    string temp = p_parm->parm[0];
   string filepath;
   //cout<<temp<<endl;
 
       int len = temp.length();
       int pos = p_parm->all_parm.find(temp,0);
           pos = pos+len;
       int length = p_parm->all_parm.length();
       //cout<<"length is:"<<length<<endl;
       temp = p_parm->all_parm.substr(pos,length-pos);
       //cout<<temp<<endl;
       length = temp.length();
       //cout<<"temp length is:"<<length<<endl;
       pos = temp.find_first_not_of(" ",0);
       //cout<<"first not " " is:"<<pos<<endl;
       string temp2 = temp.substr(pos,length-pos);

	   if(0<temp2.find(":\\",0) && temp2.find(":\\",0)<temp2.length())
	   {
		   filepath = temp2;
	   }
	   else
	   {
       filepath = work_space->s_work_space;
       filepath += "\\";
       filepath += temp2;
	   }
   WinExec(filepath.c_str(),SW_SHOW);
   cout<<endl;
}
//////////////////////////////////////////////////////////////////////////////
void _stdcall dos()
{
	while(1)
	{
		cout<<"    Input DOS Command ->";
		string dos_command;
		cin>>dos_command;
		if(dos_command.compare("enddos")==0)
			return;
		if(dos_command.compare("exitdos")==0)
			return;
		system(dos_command.c_str());
		cout<<endl;
	}
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
void _stdcall dir()
{
    char szFind[1024];
	int filenum = 0;
	int dirnum = 0;
    WIN32_FIND_DATA FindFileData;
   
    strcpy(szFind,(work_space->s_work_space).c_str());

    strcat(szFind,"\\*.*");

    HANDLE hFind = FindFirstFile(szFind,&FindFileData);

    cout<<" "<<work_space->s_work_space<<" ��Ŀ¼"<<endl;

    while(FindNextFile(hFind,&FindFileData))
	{
/*#define FILE_ATTRIBUTE_READONLY             0x00000001  
#define FILE_ATTRIBUTE_HIDDEN               0x00000002  
#define FILE_ATTRIBUTE_SYSTEM               0x00000004  
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010  
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020  
#define FILE_ATTRIBUTE_ENCRYPTED            0x00000040  
#define FILE_ATTRIBUTE_NORMAL               0x00000080  
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100  
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200  
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400  
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800  
#define FILE_ATTRIBUTE_OFFLINE              0x00001000  
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000 */
SYSTEMTIME SYS_TIME;
FileTimeToSystemTime(&(FindFileData.ftLastWriteTime),&SYS_TIME);

         switch(FindFileData.dwFileAttributes)//�������Ŀ¼
		 {
		 case (0x00000010):{
			                 dirnum++;

			                 cout<<SYS_TIME.wYear;
							 cout<<"-";

                             if(SYS_TIME.wMonth<10)
							 {cout<<0<<SYS_TIME.wMonth;}
							 else
							 {cout<<SYS_TIME.wMonth;}
							 cout<<"-";

							 if(SYS_TIME.wDay<10)
							 {cout<<0<<SYS_TIME.wDay;}
							 else
							 {cout<<SYS_TIME.wDay;}
							 cout<<"  ";

							 if(SYS_TIME.wHour<10)
							 {cout<<0<<SYS_TIME.wHour;}
							 else
							 {cout<<SYS_TIME.wHour;}
							 cout<<":";

                             if(SYS_TIME.wMinute<10)
							 {cout<<0<<SYS_TIME.wMinute;}
							 else
							 {cout<<SYS_TIME.wMinute;}

							 cout<<"  ";
			                 cout<<"<DIR>  ";
							 //cout<<"<"<<setw(-4)<<(filenum+dirnum)<<">  ";
							 cout<<FindFileData.cFileName<<endl;

						 	 break;
						   }
		 case (0x00000011):{
                             dirnum++;

			                 cout<<SYS_TIME.wYear;
							 cout<<"-";

                             if(SYS_TIME.wMonth<10)
							 {cout<<0<<SYS_TIME.wMonth;}
							 else
							 {cout<<SYS_TIME.wMonth;}
							 cout<<"-";

							 if(SYS_TIME.wDay<10)
							 {cout<<0<<SYS_TIME.wDay;}
							 else
							 {cout<<SYS_TIME.wDay;}
							 cout<<"  ";

							 if(SYS_TIME.wHour<10)
							 {cout<<0<<SYS_TIME.wHour;}
							 else
							 {cout<<SYS_TIME.wHour;}
							 cout<<":";

                             if(SYS_TIME.wMinute<10)
							 {cout<<0<<SYS_TIME.wMinute;}
							 else
							 {cout<<SYS_TIME.wMinute;}

							 cout<<"  ";
			                 cout<<"<DIR>  ";
							 //cout<<"<"<<setw(-4)<<(filenum+dirnum)<<">  ";
							 cout<<FindFileData.cFileName<<endl;

							 break;
						   }
		 case (0x00000012):{
                             dirnum++;

			                 cout<<SYS_TIME.wYear;
							 cout<<"-";

                             if(SYS_TIME.wMonth<10)
							 {cout<<0<<SYS_TIME.wMonth;}
							 else
							 {cout<<SYS_TIME.wMonth;}
							 cout<<"-";

							 if(SYS_TIME.wDay<10)
							 {cout<<0<<SYS_TIME.wDay;}
							 else
							 {cout<<SYS_TIME.wDay;}
							 cout<<"  ";

							 if(SYS_TIME.wHour<10)
							 {cout<<0<<SYS_TIME.wHour;}
							 else
							 {cout<<SYS_TIME.wHour;}
							 cout<<":";

                             if(SYS_TIME.wMinute<10)
							 {cout<<0<<SYS_TIME.wMinute;}
							 else
							 {cout<<SYS_TIME.wMinute;}

							 cout<<"  ";
			                 cout<<"<DIR>  ";
							 //cout<<"<"<<setw(-4)<<(filenum+dirnum)<<">  ";
							 cout<<FindFileData.cFileName<<endl;

							  break;
						   }
         case (0x00000014):{
			                 dirnum++;

			                 cout<<SYS_TIME.wYear;
							 cout<<"-";

                             if(SYS_TIME.wMonth<10)
							 {cout<<0<<SYS_TIME.wMonth;}
							 else
							 {cout<<SYS_TIME.wMonth;}
							 cout<<"-";

							 if(SYS_TIME.wDay<10)
							 {cout<<0<<SYS_TIME.wDay;}
							 else
							 {cout<<SYS_TIME.wDay;}
							 cout<<"  ";

							 if(SYS_TIME.wHour<10)
							 {cout<<0<<SYS_TIME.wHour;}
							 else
							 {cout<<SYS_TIME.wHour;}
							 cout<<":";

                             if(SYS_TIME.wMinute<10)
							 {cout<<0<<SYS_TIME.wMinute;}
							 else
							 {cout<<SYS_TIME.wMinute;}

							 cout<<"  ";
			                 cout<<"<DIR>  ";
							 //cout<<"<"<<setw(-4)<<(filenum+dirnum)<<">  ";
							 cout<<FindFileData.cFileName<<endl;

							  break;
						   }
         case (0x00000013):{
			                 dirnum++;

			                 cout<<SYS_TIME.wYear;
							 cout<<"-";

                             if(SYS_TIME.wMonth<10)
							 {cout<<0<<SYS_TIME.wMonth;}
							 else
							 {cout<<SYS_TIME.wMonth;}
							 cout<<"-";

							 if(SYS_TIME.wDay<10)
							 {cout<<0<<SYS_TIME.wDay;}
							 else
							 {cout<<SYS_TIME.wDay;}
							 cout<<"  ";

							 if(SYS_TIME.wHour<10)
							 {cout<<0<<SYS_TIME.wHour;}
							 else
							 {cout<<SYS_TIME.wHour;}
							 cout<<":";

                             if(SYS_TIME.wMinute<10)
							 {cout<<0<<SYS_TIME.wMinute;}
							 else
							 {cout<<SYS_TIME.wMinute;}

							 cout<<"  ";
			                 cout<<"<DIR>  ";
							 //cout<<"<"<<setw(-4)<<(filenum+dirnum)<<">  ";
							 cout<<FindFileData.cFileName<<endl;

							  break;
						   }
         case (0x00000015):{break;}
         case (0x00000016):{break;}
		 case (0x00000017):{break;}

		 default:{
                             filenum++;
			                 cout<<SYS_TIME.wYear;
							 cout<<"-";

                             if(SYS_TIME.wMonth<10)
							 {cout<<0<<SYS_TIME.wMonth;}
							 else
							 {cout<<SYS_TIME.wMonth;}
							 cout<<"-";

							 if(SYS_TIME.wDay<10)
							 {cout<<0<<SYS_TIME.wDay;}
							 else
							 {cout<<SYS_TIME.wDay;}
							 cout<<"  ";

							 if(SYS_TIME.wHour<10)
							 {cout<<0<<SYS_TIME.wHour;}
							 else
							 {cout<<SYS_TIME.wHour;}
							 cout<<":";

                             if(SYS_TIME.wMinute<10)
							 {cout<<0<<SYS_TIME.wMinute;}
							 else
							 {cout<<SYS_TIME.wMinute;}

							 cout<<"    ";
			                 cout<<"     ";
                             //cout<<"<"<<setw(-4)<<(filenum+dirnum)<<">  ";
							 cout<<FindFileData.cFileName<<endl;
							  break;
				 }
		 }

	}//end-while

 FindClose(hFind);
 cout<<"\t\t"<<setw(5)<<filenum<<" ���ļ�"<<endl;
 cout<<"\t\t"<<setw(5)<<dirnum-1<<" ��Ŀ¼"<<endl;
 return;
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////