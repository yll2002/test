#  include <iostream>
#  include <fstream>
#  include <windows.h>
#  include <string>
#  include "System.h"
#  include "ParmStack.h"

   using namespace std;

command_parm      command_parm_1;
fuc_info          fuc_info_1;
workspace         work_space_1;
LinkStack<string> stack;
realparm          hparm;

extern __declspec(dllexport)  command_parm *p_parm =  &command_parm_1 ;
extern __declspec(dllexport)  fuc_info *p_fucinfo =  &fuc_info_1;
extern __declspec(dllexport)  LinkStack<string>* parm_stack = &stack;
extern __declspec(dllexport)  realparm *parm = &hparm;
extern __declspec(dllexport)  workspace *work_space = &work_space_1;

extern "C" _declspec(dllexport) int  _stdcall DivideCommand(char* cmdline,command_parm *p_parm);
extern "C" _declspec(dllexport) int  _stdcall FindFunction(char *command,fuc_info *p_fucinfo,command_parm *p_parm);
extern "C" _declspec(dllexport) int  _stdcall ShowInfo(int infomode,char *info);
extern "C" _declspec(dllexport) int  _stdcall ParmChange();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  _stdcall  DivideCommand(char* cmdline,command_parm *p_parm)
{
     int i = 0,j = 0,k = 0;
     p_parm->factparmnum = 0;
 
	 for(i=0;i<16;i++)
	 {
        p_parm->parmstyle[i] = 0;
	 }
	 i = 0;

      

       for(i; ; i++)
	 { 
         if((cmdline[i] == ' ') && (cmdline[i+1] != ' ') && (cmdline[i+1] !='\0'))//first=' ',second!=' 'second!='\0'
		 {
             continue;
		 }

         else if((cmdline[i] != ' ') && (cmdline[i+1] == ' '))//first!=' ',second!=' '
		 {
			 p_parm->parm[j][k] = cmdline[i];
		     p_parm->parm[j][k+1] = '\0';
             k = 0;
			 j++;
			 continue;
		 }
         else if((cmdline[i] == ' ') && (cmdline[i+1] == ' '))//first==' 'second==' ' 
		 {
			 continue;
		 }

		 else if((cmdline[i] != ' ') && (cmdline[i+1] != ' ') && (cmdline[i+1] != '\0'))//first!=' ',second!=' 'second!='\0' 
		 {
            p_parm->parm[j][k] = cmdline[i];
            p_parm->parm[j][k+1] = '\0';
            k++;
			continue;
		 }
		 else if((cmdline[i] != ' ') && (cmdline[i+1] == '\0'))//first!=' 'second!='\0' 
		 {
            p_parm->parm[j][k] = cmdline[i];
            p_parm->parm[j][k+1] = '\0';
            p_parm->factparmnum = j;
			break;
		 }
		 else if((cmdline[i] == ' ') && (cmdline[i+1] == '\0'))//first==' 'second=='\0' 
		 {
             p_parm->factparmnum = j-1;
			 break;
		 }
		 

	 }//end-for
	   //cout<<"p_parm->parm[0] in divide is: "<<p_parm->parm[0]<<endl;
	   
	  // cout<<"p_parm->factparmnum after DivideCommand is: "<<p_parm->factparmnum<<endl;
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  _stdcall  FindFunction(char *command,fuc_info *p_fucinfo,command_parm *p_parm)
{
	
	
	 int linenum = 0;

     char     * FileName = "FunctionInfo.txt";
     
     char     subline[4];

      p_fucinfo->fucnum = 0;
      //strcpy(p_fucinfo->fucname,"\0");
      //strcpy(p_fucinfo->dllname,"\0");
      p_fucinfo->dllnum = 0;
      p_fucinfo->parmtype = 0;
      p_fucinfo->parmnum = 0;
	 

     string   s,temp;

     temp = command;
	 //cout<<"temp in FindFuc is: "<<temp<<endl;

     ifstream infile(FileName);//读文件

        if(infile.fail())//如果打开失败
        {
           //cout<<"读取FunctionInfo.txt文件失败!"<<endl;
           ShowInfo(FucInfoFail,NULL);
		   return -1;
        }

        while(!infile.eof())
        {
               char     line[256];/*save one line info*/
               char     tempfucinfo[6][128]; // 在FunctionInfo.txt中 每一行 有6个 标示
               int i = 0,j = 0,k = 0;

               infile.getline(line,256);/*read the file line by line*/
			   linenum++;//行数增加
               
               for(i=0; ; i++)//对该行进行处理
			   {
				   
                    if((line[i] == ' ') && (line[i+1] != ' ') && (line[i+1] !='\0'))//first=' ',second!=' 'second!='\0'
					{
                       continue;
					}

                    else if((line[i] != ' ') && (line[i+1] == ' '))//first!=' ',second!=' '
					{
			           tempfucinfo[j][k] = line[i];
		               tempfucinfo[j][k+1] = '\0';
                       k=0;
			           j++;
			           continue;
					}

                    else if((line[i] == ' ') && (line[i+1] == ' '))//first==' 'second==' ' 
					{
			           continue;
					}

                    else if((line[i] != ' ') && (line[i+1] != ' ') && (line[i+1] != '\0'))//first!=' ',second!=' 'second!='\0' 
					{
                       tempfucinfo[j][k] = line[i];
                       tempfucinfo[j][k+1] = '\0';
                       k++;
			           continue;
					}

                    else if((line[i] != ' ') && (line[i+1] == '\0'))//first!=' 'second!='\0' 
					{
                       tempfucinfo[j][k] = line[i];
                       tempfucinfo[j][k+1] = '\0';
			           break;
					}

                    else if((line[i] == ' ') && (line[i+1] == '\0'))//first==' 'second=='\0' 
					{ 
			           break;
					}

			   }//end-for完成对该行的处理
			   //cout<<"第"<<linenum<<"行 函数名: "<<tempfucinfo[1]<<endl;
		   
               if( !strcmp(tempfucinfo[1],command))//如果 输入的命令名 和 函数名一样
			   {
                   p_fucinfo->fucnum   = atoi(tempfucinfo[0]);
			       strcpy(p_fucinfo->fucname, tempfucinfo[1]);
                   strcpy(p_fucinfo->dllname, tempfucinfo[2]);
                   p_fucinfo->parmtype = atoi(tempfucinfo[3]);
                   p_fucinfo->dllnum   = atoi(tempfucinfo[4]);
				   

                   int temp = p_fucinfo->parmtype;
				   for(;;)
				   {
                       if(p_fucinfo->parmtype == 0)
					   {
                         p_fucinfo->parmnum=0;break; 
					   }
					   temp = temp/10;
                       p_fucinfo->parmnum++;
					   if (temp == 0)
						   break;
				   }

                   temp = p_fucinfo->parmtype;
			       for( i = p_fucinfo->parmnum-1 ; i >=0 ; i--)
				   {
                       //if(p_fucinfo->parmtype==0)
					   //{p_parm->parmstyle[0] = 0; break;}

				       if(temp==0)
					   {
					      break;
						  
					   }

                       p_parm->parmstyle[i] = temp%10;//使用0下标

				       temp = temp/10;

				   }
                   //cout<<"i :"<<i<<endl;
				   //cout<<"p_fucinfo->parmnum in Find Fuc (ideal parm num): "<<p_fucinfo->parmnum<<endl;

				   if(p_fucinfo->parmnum!=0)//判断functioninfo.txt中理想参数个数是否为0
				   {
				        if(p_fucinfo->parmnum > p_parm->factparmnum)
						{
                            ShowInfo(FewParm,NULL);
                            return -1;
						}

                        if(p_fucinfo->parmnum < p_parm->factparmnum)
						{
                            ShowInfo(MuchParm,NULL);
                            return -1;
						}
				   }

			     //for(i = 0; i <= p_parm->factparmnum ; i++)
				 //{
				  // cout<<"p_parm->parmstyle[i]: "<<p_parm->parmstyle[i]<<endl;
				 //}
                    return 0;
			   }//if( !strcmp(tempfucinfo[1],command))
              else
			  {
                
                  //for(int l=0;i<6;i++)
				  //{strcpy(tempfucinfo[i],"\0");}
				  continue;
			  }
			   //已查找到 并且处理了

        }//end-while while(!infile.eof())
		//到文件结束还没找到
		ShowInfo(FucNotFind,NULL);
        return -1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int _stdcall ShowInfo(int infomode,char *info)
{
	if(infomode==InputInfo)
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
            FOREGROUND_GREEN );
	else
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
            FOREGROUND_RED );

	switch(infomode)
	{
	case InputInfo:
		cout<<work_space->s_work_space<<" ->"; 
		break;
	case FucCallFail:
		cout<<"Call Function Failed!"<<endl;
        break;
	case FewParm:
		cout<<"The parm you input is few than ideal!"<<endl;
        break;
	case MuchParm:
		cout<<"The parm you input is much than ideal!"<<endl;
        break;
	case FucNotFind:
		cout<<"Function not find!"<<endl;
        break;
	case FucHelp:
		cout<<"Input \"help "<<info<<"\" to get more information"<<endl;
        break;
	case FucNotDefine:
		cout<<"Function \""<<info<<"\" not defined in FunctionInfo.txt!"<<endl;
        break;
	case DllNotFind:
		cout<<"The DLL \""<<info<<"\" not find!"<<endl;
        break;
	case DLLLoadFail:
		cout<<"The DLL \""<<info<<"\" load failed!"<<endl;
        break;
	case FucInfoFail:
        cout<<"读取FunctionInfo.txt文件失败!"<<endl;
		break;
	default:
		cout<<"Use ShowInfo() not in low!"<<endl;
		return -1;
	}
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
            FOREGROUND_RED | FOREGROUND_GREEN);
	return 0;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int _stdcall ParmChange()
{
	string **p_string = new string *[p_parm->factparmnum];
	for(int i = 0;i < p_parm->factparmnum; i++)
	{
		p_string[i] = new string;
		parm_stack->Pop(*(p_string[i]));
		//cout<<"弹出参数：*(p_string["<<i<<"]): "<<*(p_string[i])<<endl;
	}
	int int_num     = 0;
	int float_num   = 0;
	int double_num  = 0;
	int char_num    = 0;
	int string_num  = 0;

	for(i = 0;i < p_parm->factparmnum; i++)
	{
		switch(p_parm->parmstyle[i])
		{
		case 0: {return 0; break;}
		case 3:      {
			           parm->int_parm[int_num] = atoi((*(p_string[i])).c_str()); 
			           //cout<<"in ParmChange: parm->int_parm["<<int_num<<"]: "<<parm->int_parm[int_num]<<endl;
					   int_num++ ;
					   break;
					 }
		case 4:      {
			           parm->float_parm[float_num] = atof((*(p_string[i])).c_str());
					   //cout<<"in ParmChange: parm->float_parm["<<float_num<<"]: "<<parm->float_parm[float_num]<<endl;
					   float_num++;
					   break;
					 }
        case 5:      {
			           parm->double_parm[double_num] = atof((*(p_string[i])).c_str());
					   //cout<<"in ParmChange: parm->float_parm["<<float_num<<"]: "<<parm->float_parm[float_num]<<endl;
					   double_num++;
					   break;
					 }
		case 6:{parm->string_parm[string_num] = *(p_string[i]); string_num++; break;}
        default: cout<<"不可识别的参数类型！"<<endl; return -1;
		}
    //cout<<"in ParmChange: parm->int_parm["<<int_num<<"]: "<<parm->int_parm[int_num]<<endl;
    //cout<<"in ParmChange: parm->float_parm["<<float_num<<"]: "<<parm->float_parm[float_num]<<endl;

	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

