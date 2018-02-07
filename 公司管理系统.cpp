//#include"my_main.h"  
#include"my_company.h"  
#include<stdio.h>  
#include<time.h>  
#include<iomanip>  
#include<iostream>  
#include<string.h>  
#include<mysql/mysql.h>  
#include<stdlib.h>  
#include <list>  
#include <climits>  
#include<unistd.h>  
using namespace std;  
  
MYSQL* conn;  
list<Employee*> Link;        //����һ�����ڴ洢Employee����ָ���list������  
  
void Load_Menu();  
void Main_Menu();  
int login_account(int num,string pwd);  
void conn_mysql();  
void load();  
  
void boss_fun(list<Employee*>::iterator p);  
void man_fun(list<Employee*>::iterator p);  
void manager_fun(list<Employee*>::iterator p);      
  
  
void view_all(list<Employee*>::iterator p);  
void view_all(list<Employee*>::iterator p);  
void add_manager(list<Employee*>::iterator p);  
void del(list<Employee*>::iterator p);  
void modify_salary(list<Employee*>::iterator p,list<Employee*>::iterator q);  
void modify_mark(list<Employee*>::iterator p);  
void update(list<Employee*>::iterator p);  
void add_man(list<Employee*>::iterator p);  
void show_depart(list<Employee*>::iterator p);      
void save_all();  
void change_pwd(list<Employee*>::iterator p);  
void show_personal(list<Employee*>::iterator p);  
bool sort_any (const Employee *first,const Employee * second);    
bool sort_lead (const Employee *first,const Employee * second);  
bool sort_depart (const Employee *first,const Employee * second);  
bool sort_num (const Employee *first, const Employee * second);   
bool sort_name (const Employee *first,const Employee * second);       
  
int check=0;  
  
  
void Employee::save_str(char *savestr)                                      //save information to mysql  
{  
    list<Employee*>::iterator l=Link.begin();  //��������Link1�ĵ����� l;  
    while(l != Link.end())  
    {  
        sprintf(savestr,"insert into Employee (number,name,password,position,salary,logtime,flag,remark,leader) values(%d,'%s','%s','%s',%f,'%s',%d,'%s','%s')",  
            (*l)->number,(*l)->name.c_str(),(*l)->password.c_str(),(*l)->position.c_str(),  
            (*l)->salary,(*l)->logtime.c_str(),(*l)->flag,(*l)->mark.c_str(),(*l)->leader.c_str());  
        if(mysql_query(conn,savestr))    //����SQL��䣬�ɹ�����0��  
        {  
            fprintf(stderr,"%s\n",mysql_error(conn));  
            exit(1);  
        }  
        l++;  
    }  
}  
////////////////////////////////////////////////////  
bool sort_lead (const Employee *first,const Employee * second)          //sort from little to greater by lead  
{  
    return (first->leader) < (second->leader)?true:false;  
}  
////////////////////////  
bool sort_depart (const Employee *first,const Employee * second)                //sort from little to greater by depart  
{  
    return (first->flag) <(second->flag)?true:false;  
}  
////////////////////////////  
bool sort_num (const Employee *first, const Employee * second)          //sort from little to greater by number  
{  
    return (first->number) < (second->number)?true:false;  
}  
//////////////////////////  
bool sort_name (const Employee *first,const Employee * second)          //sort from little to greater by name  
{  
    return (first->name) < (second->name)?true:false;  
}  
////////////////////////////////////////////////////////  
bool sort_any (const Employee *first,const Employee * second)           //sort from little to greater by depart  
{  
    bool res;  
    if((first->flag) < (second->flag))  
    {  
        if((first->leader) < (second->leader))  
        {  
            if((first->number) < (second->number))  
            {  
                res = true;  
            }  
            else  
            {  
                res = false;  
            }  
        }  
    }   
    else  
    {  
        res = false;  
    }  
    return res = true?true:false;  
}  
///////////////////////////////////////////////  
void show_personal(list<Employee*>::iterator p)                       //show saleman's  information   
{  
    system("clear");  
    cout<<"\033[34;1m���ĸ�����ϢΪ��\033[0m"<<endl<<endl;  
      
    cout<<"----------------------------------------------------------------------------------------------"<<endl;  
    cout.width(10); cout<<"���� |";  
    cout.width(19); cout<<"���� |";  
    cout.width(12); cout<<"ְλ |";  
    cout.width(9);  cout<<"нˮ |";  
    cout.width(9);  cout<<"�ȼ� |";  
    cout.width(19); cout<<"REMARK |";  
    cout.width(19); cout<<"�ϼ� |";  
    cout.width(40); cout<<"�ϴε�¼ʱ��";  
    cout<<endl;  
    cout<<"----------------------------------------------------------------------------------------------"<<endl;  
    (*p)->print();  
    cin.ignore(1000,'\n');  
    cin.get();  
      
}  
/////////////////////////////////////////////  
void change_pwd(list<Employee*>::iterator p)                  //change salesman's password   
{  
    string pwd;  
    string c_pwd;  
    while(1)  
    {  
        cout<<"\n\033[34;1m�����������룺\033[0m";  
        system("stty -echo");  
        cin>>pwd;  
        system("stty echo");  
        cout<<"\n\033[34;1m��������һ�Σ�\033[0m";  
        system("stty -echo");  
        cin>>c_pwd;  
        system("stty echo");  
        if(pwd == c_pwd)  
        {  
            (*p)->set_passwd(pwd);  
            cout<<"\n\033[34;1m�����޸ĳɹ���\033[0m"<<endl;  
            cout<<"Input any key";  
            cin.ignore(1000,'\n');  
            cin.get();  
            break;  
        }         
    }  
    save_all();  
}  
//////////////////////////////////////////////  
void save_all()                                                 //save all data to mysql  
{  
    list<Employee*>::iterator p=Link.begin();  
    if(mysql_query(conn,"drop table Employee"))  
    {  
        cout<<"mysql error"<<endl;  
        exit(1);  
    }  
    if(mysql_query(conn,"create table Employee(no int auto_increment not null primary key,number int not null,name varchar(20) not null,password varchar(20) not null default '1234',position varchar(20) not null,salary float not null,logtime timestamp default current_timestamp,flag tinyint not null,remark varchar(128),leader varchar(20))default charset=utf8"))  
    {  
        cout<<"\033[34;1m�������ݿ�ʧ�ܣ�\033[0m"<<endl;  
        exit(1);  
    }  
  
    char str[1024]="";  
    while(p!=Link.end())  
    {  
        (*p)->save_str(str);  
        if(mysql_query(conn,str))  
        {  
            cout<<"\033[34;1m�������ʧ�ܣ�\033[0m"<<endl;  
            exit(1);  
        }  
        p++;  
    }  
}  
/////////////////////////////////////////////  
void show_depart(list<Employee*>::iterator p)                 //view depart staff information  
{  
    string name;  
    name = (*p)->get_name();  
    p=Link.begin();  
    system("clear");  
    cout<<"---------------------------------------------------------------------------------------------------------"<<endl;  
    cout.width(10); cout<<"���� |";  
    cout.width(19); cout<<"���� |";  
    cout.width(12); cout<<"ְλ |";  
    cout.width(9);  cout<<"нˮ |";  
    cout.width(9);  cout<<"�ȼ� |";  
    cout.width(19); cout<<"REMARK |";  
    cout.width(19); cout<<"�ϼ� |";  
    cout.width(40); cout<<"�ϴε�¼ʱ�� |";  
    cout<<endl;  
    cout<<"---------------------------------------------------------------------------------------------------------"<<endl;  
    while(p!=Link.end())  
    {  
        if( (((*p)->get_lead()) == name)  )  
        {  
            (*p)->print();  
        }  
        p++;  
    }  
    cin.ignore(1000,'\n');  
    cin.get();  
}  
//////////////////////////////////////////  
void add_man(list<Employee*>::iterator p)                     //add sales man  
{  
      
    Employee* ptr =NULL;  
    string name;    cout<<"\033[34;1m������������\033[0m";  cin>>name;  
    string pwd = "www";                       
    string pos;  
    float d_salary =3000;  
    int flag;  
    string mark;    cout<<"Input remark:";        cin>>mark;  
    string lead =   (*p)->get_name();  
    time_t t;   t=time(NULL);  
    string g_t;  
    char tt[1024]="";  
    struct tm *tmper;  
    tmper = localtime(&t);  
    sprintf(tt,"%d-%d-%d %d:%d:%d",tmper->tm_year+1900,tmper->tm_mon+1,tmper->tm_mday,tmper->tm_hour,tmper->tm_min,tmper->tm_sec);  
    g_t = tt;  
    int wt;  
    float sale;  
    float m_fixed;  
  
    Link.sort(sort_num);  
    list<Employee*>::iterator q =Link.begin();  
  
    q=Link.begin();  
    int number = ((*q)->get_num());    
    while(q!=Link.end())  
    {  
        if( number < ((*q)->get_num()) )  
        {  
            break;  
        }  
        q++;  
        number++;  
    }  
  
    switch((*p)->get_flag())  
    {  
        case 2:  
            flag = 1;  
            pos="����ְԱ";  
            ptr=new S_man(number,name,pwd,pos,d_salary,g_t,flag,mark,lead);  
            cout<<"���������۶";  cin>>sale;  
            ptr->set_sales(sale);  
            ptr->set_salary();  
            m_fixed = (*p)->get_salary();  
            (*p)->set_sales(sale);  
            (*p)->set_fixed_salary(m_fixed);  
            (*p)->set_salary();  
            break;  
        case 4:  
            flag = 3;  
            pos="����ְԱ";  
            ptr=new T_man(number,name,pwd,pos,d_salary,g_t,flag,mark,lead);  
            cout<<"\033[34;1m�����빤��ʱ�䣺\033[0m";    cin>>wt;  
            ptr->set_worktime(wt);  
            ptr->set_salary();  
            break;  
        default:  
            break;  
    }     
  
    Link.push_front(ptr);  
    save_all();  
    cout<<"\033[34;1m��ӳɹ���\033[0m"<<endl;  
    cin.ignore(1000,'\n');  
    cin.get();  
}  
/////////////////////////////////////////////  
void update(list<Employee*>::iterator p)                  //view depart staff information  
{  
    int number;  
    string name = (*p)->get_name();  
    list<Employee*>::iterator q=Link.begin();  
    cout<<"\033[34;1m�����빤�ţ�\033[0m";  
    cin>>number;  
    while(q!=Link.end())  
    {  
        if( number == (*q)->get_num() && name == (*q)->get_lead() )  
        {  
            break;  
        }  
        q++;  
    }  
    if(q==Link.end())  
    {  
        cout<<"\033[34;1mû�и�ְԱ��\033[0m"<<endl;  
        cin.ignore(1000,'\n');  
        cin.get();  
        return;  
    }  
    system("clear");  
    system("tput cup 15 38");   cout<<"\t\t****************************************************"<<endl;  
    system("tput cup 16 38");   cout<<"\t\t*      CHOOSE THE ITEM YOU WANT TO MODIFY          *"<<endl;  
    system("tput cup 17 38");   cout<<"\t\t*--------------------------------------------------*"<<endl;  
    system("tput cup 18 38");   cout<<"\t\t*               1.MODIFY SALARY                    *"<<endl;  
    system("tput cup 19 38");   cout<<"\t\t*               2.MODIFY REMARK                    *"<<endl;  
    system("tput cup 21 38");   cout<<"\t\t*               3.RETURN                           *"<<endl;  
    system("tput cup 20 38");   cout<<"\t\t*               SELECT:                            *"<<endl;  
    system("tput cup 21 38");   cout<<"\t\t****************************************************"<<endl;  
    int select;  
    cin.clear();  
    cin.sync();  
    system("tput cup 20 75");   cin>>select;  
    switch(select)  
    {  
        case 1:  
            modify_salary(q,p);  
            break;  
        case 2:  
            modify_mark(q);  
            break;  
        case 3:  
            return;  
        default:  
            break;  
    }  
}  
////////////////////////////////////////////  
void modify_mark(list<Employee*>::iterator p)             //modify remark  
{  
    string mark;  
    cout<<"Input remark:";  
    cin>>mark;  
    (*p)->set_mark(mark);  
    cout<<"\033[34;1m�޸ĳɹ���\033[0m"<<endl;  
    cin.ignore(1000,'\n');  
    cin.get();  
    save_all();  
}  
//////////////////////////////////////////////////////////////  
void modify_salary(list<Employee*>::iterator p,list<Employee*>::iterator q)                     //modify salary   
{  
    int time;  
    float sales;  
    float fixed;  
    float m_fixed;  
    float s_fixed;  
    switch((*p)->get_flag())  
    {  
        case 1:  
            cout<<"\033[34;1m���������۶\033[0m"; cin>>sales;  
            s_fixed = (*p)->get_salary();  
            (*p)->set_sales(sales);  
            (*p)->set_salary();  
            m_fixed = (*q)->get_salary();  
            m_fixed = m_fixed - s_fixed/5;  
            (*q)->set_fixed_salary(m_fixed);  
            (*q)->set_sales(sales);  
            (*q)->set_salary();  
            break;  
        case 2:  
            cout<<"\033[34;1m�������޸ĺ��нˮ��\033[0m";  cin>>fixed;  
            (*p)->set_fixed_salary(fixed);  
            (*p)->set_salary();  
            break;  
        case 3:  
            cout<<"\033[34;1m�����빤��ʱ�䣺\033[0m";    cin>>time;  
            (*p)->set_worktime(time);  
            (*p)->set_salary();  
            break;  
        case 4:  
            cout<<"\033[34;1m�������޸ĺ��нˮ��\033[0m";  cin>>fixed;  
            (*p)->set_fixed_salary(fixed);  
            (*p)->set_salary();  
            break;  
        default:  
            break;  
    }  
    cout<<"\033[34;1m�޸ĳɹ���\033[0m"<<endl;  
    cin.ignore(1000,'\n');  
    cin.get();  
    save_all();  
}  
//////////////ɾ��/////////////////////////  
void del(list<Employee*>::iterator p)                         //delete an Employee  
{  
    list<Employee*>::iterator q=Link.begin();  
    int number;  
    cout<<"\033[34;1m������Ҫɾ���Ĺ���\033[0m";  
    cin>>number;  
    float m_fixed;  
    while(q!=Link.end())  
    {  
        if((number == (*q)->get_num()) && ((*p)->get_name() == (*q)->get_lead()) )  
        {  
            m_fixed = (*p)->get_salary();  
            m_fixed = m_fixed - (*q)->get_salary()/5;  
            (*p)->set_sales(0);  
            (*p)->set_fixed_salary(m_fixed);  
            (*p)->set_salary();        
            Link.erase(q);  
            cout<<"\033[34;1mɾ���ɹ���\033[0m"<<endl;  
            cin.ignore(1000,'\n');  
            cin.get();  
            break;  
        }  
        q++;  
    }  
  
    if(q == Link.end())  
    {  
        cout<<"\033[34;1mû�и�Ա����\033[0m"<<endl;  
        cin.ignore(1000,'\n');  
        cin.get();  
        return;  
    }  
    save_all();  
}  
////////////////��Ӿ���////////////////////////////  
void add_manager(list<Employee*>::iterator p)                             //add manager  
{  
      
    Employee* ptr =NULL;  
    string name;    cout<<"\033[34;1m������������\033[0m";  cin>>name;  
    string pwd = "123";                       
    string pos;  
    int flag;  
  
    string mark;    cout<<"Input remark:";        cin>>mark;  
    time_t t;   t=time(NULL);  
    string g_t;  
    char tt[1024]="";  
    struct tm *tmper;  
    tmper = localtime(&t);  
    sprintf(tt,"%d-%d-%d %d:%d:%d",tmper->tm_year+1900,tmper->tm_mon+1,tmper->tm_mday,tmper->tm_hour,tmper->tm_min,tmper->tm_sec);  
    g_t = tt;  
  
    string lead = (*p)->get_name();  
    float fixed;  
    cout<<"\033[34;1m�������޸ĺ��нˮ��\033[0m";  cin>>fixed;  
      
    Link.sort(sort_num);//�������ڵĶ��󰴴�С�����˳���������  
    list<Employee*>::iterator q =Link.begin();  
  
    q=Link.begin();  
    int number = ((*q)->get_num());    
    while(q!=Link.end())  
    {  
        if( number < ((*q)->get_num()) )  
        {  
            break;  
        }  
        q++;  
        number++;  
    }  
    while(1)  
    {  
        cout<<"\n\033[34;1m����Ҫ�����Ǹ���Ϣ��  1.���۾���   2.��������\033[0m\n";  
        int select;  
        cin>>select;  
        if(select == 1)  
        {  
            flag =2;  
            pos = "\033[34;1m���۾���\033[0m";  
            ptr=new S_manager(number,name,pwd,pos,fixed,g_t,flag,mark,lead);  
            ptr->set_fixed_salary(fixed);  
            ptr->set_sales(0);  
            ptr->set_salary();  
            break;  
        }  
        else if(select == 2)  
        {  
            flag = 4;  
            pos = "\033[34;1m��������\033[0m";  
            ptr=new T_manager(number,name,pwd,pos,fixed,g_t,flag,mark,lead);  
            break;  
        }  
    }  
    Link.push_front(ptr);  
    cout<<"\033[34;1m��ӳɹ���\033[0m"<<endl;  
    cin.ignore(1000,'\n');  
    cin.get();  
    save_all();  
  
}  
///////////////��ʾ���е���Ϣ/////////////////////////  
void view_all(list<Employee*>::iterator p)                                //view all information  
{     
    while(1)  
    {  
        system("clear");  
        system("tput cup 15 38");   cout<<"\t\t\033[34;1m****************************************************"<<endl;  
        system("tput cup 16 38");   cout<<"\t\t*               �� ʾ ģ ʽ ��                      *"<<endl;  
        system("tput cup 17 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 18 38");   cout<<"\t\t*               1.����                             *"<<endl;  
        system("tput cup 19 38");   cout<<"\t\t*               2.����                             *"<<endl;  
        system("tput cup 20 38");   cout<<"\t\t*               3.����                             *"<<endl;  
        system("tput cup 21 38");   cout<<"\t\t*               4.�쵼                             *"<<endl;  
        system("tput cup 22 38");   cout<<"\t\t*               5.����                             *"<<endl;  
        system("tput cup 23 38");   cout<<"\t\t*               ѡ �� ��                           *"<<endl;  
        system("tput cup 24 38");   cout<<"\t\t****************************************************\033[0m"<<endl;  
        system("tput cup 23 73");string select;  
        cin>>select;  
        if(select == "1")  
        {  
            Link.sort(sort_num);  
            break;  
        }  
        else if(select == "2")  
        {  
            Link.sort(sort_name);  
            break;  
        }  
        else if(select == "3")  
        {  
            Link.sort(sort_depart);  
            break;  
        }  
        else if(select == "4")  
        {  
            Link.sort(sort_lead);  
            break;  
        }  
        else if(select == "5")  
        {  
            Link.sort(sort_any);  
            break;  
        }  
    }  
    system("clear");  
    p=Link.begin();  
}  
////////////////�������////////////////////////////  
void manager_fun(list<Employee*>::iterator p)                   
{  
    while(1)  
    {  
  
        system("clear");  
        cout<<"\t\t\n\n\n";  
        system("tput cup 15 38");   cout<<"\t\t\033[34;1m****************************************************"<<endl;  
        system("tput cup 16 38");   cout<<"\t\t*             �� ӭ �� �� �� �� �� ��               *"<<endl;  
        system("tput cup 17 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 18 38");   cout<<"\t\t*            �� ѡ �� ��                           *"<<endl;  
        system("tput cup 19 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 20 38");   cout<<"\t\t*            1.�鿴������Ϣ                         *"<<endl;  
        system("tput cup 21 38");   cout<<"\t\t*            2.�鿴����Ա����Ϣ                     *"<<endl;  
        system("tput cup 22 38");   cout<<"\t\t*            3.����Ա��                            *"<<endl;  
        system("tput cup 23 38");   cout<<"\t\t*            4.�޸�Ա����Ϣ                         *"<<endl;  
        system("tput cup 24 38");   cout<<"\t\t*            5.ɾ��Ա����Ϣ                         *"<<endl;  
        system("tput cup 25 38");   cout<<"\t\t*            6.�޸�����                             *"<<endl;  
        system("tput cup 26 38");   cout<<"\t\t*            7.����                                 *"<<endl;  
        system("tput cup 27 38");   cout<<"\t\t*            8.�˳�                                *"<<endl;  
        system("tput cup 28 38");   cout<<"\t\t*            ѡ �� ��                               *"<<endl;  
        system("tput cup 29 38");   cout<<"\t\t****************************************************\033[0m"<<endl;  
        int select;  
        cin.clear();  
        cin.sync();  
        system("tput cup 28 69");   cin>>select;  
        switch(select)  
        {  
            case 1:  
                show_personal(p);           //show information of sale manager  
                break;  
            case 2:  
                show_depart(p);             //show depart information  
                break;  
            case 3:  
                add_man(p);  
                break;  
            case 4:  
                update(p);  
                break;  
            case 5:  
                del(p);  
                break;  
            case 6:  
                change_pwd(p);//change sales manager's password  
                return;  
                break;  
            case 7:  
                return;  
            case 8:                 //save all data  
                system("clear");  
                exit(0);  
            default:  
                break;  
        }  
    }  
}  
//////////////Ա������////////////////////////  
void man_fun(list<Employee*>::iterator p)                       
{  
    while(1)  
    {  
  
        system("clear");  
        cout<<"\t\t\n\n\n";  
        system("tput cup 15 38");   cout<<"\t\t\033[34;1m****************************************************"<<endl;  
        system("tput cup 16 38");   cout<<"\t\t*              �� ӭ �� �� Ա �� �� ��              *"<<endl;  
        system("tput cup 17 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 18 38");   cout<<"\t\t*            �� ѡ �� ��                           *"<<endl;  
        system("tput cup 19 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 20 38");   cout<<"\t\t*            1.�鿴������Ϣ                         *"<<endl;  
        system("tput cup 21 38");   cout<<"\t\t*            2.�޸�����                             *"<<endl;  
        system("tput cup 22 38");   cout<<"\t\t*            3.����                                *"<<endl;  
        system("tput cup 23 38");   cout<<"\t\t*            4.�˳�                                *"<<endl;  
        system("tput cup 24 38");   cout<<"\t\t*            ѡ �� ��                              *"<<endl;  
        system("tput cup 25 38");   cout<<"\t\t****************************************************\033[0m"<<endl;  
        int select;  
        cin.clear();  
        cin.sync();  
        system("tput cup 24 69");   cin>>select;  
        switch(select)  
        {  
            case 1:  
                show_personal(p);                       //see information  
                break;  
            case 2:  
                change_pwd(p);                  //change password  
                break;  
            case 3:  
                return;                         //return to login  
                break;  
            case 4:                             //exit program                        
                system("clear");  
                exit(1);  
                break;  
            default:  
                break;  
        }  
    }  
}  
///////////////�ϰ�������/////////////////////////////////  
void boss_fun(list<Employee*>::iterator p)      
{  
    while(1)  
    {  
        system("clear");  
        system("tput cup 15 38");   cout<<"\t\t\033[34;1m****************************************************"<<endl;  
        system("tput cup 16 38");   cout<<"\t\t*               �� ѡ �� �� Ҫ �� �� �� ѡ ��       *"<<endl;  
        system("tput cup 17 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 18 38");   cout<<"\t\t*               1.���Ӿ���                          *"<<endl;  
        system("tput cup 19 38");   cout<<"\t\t*               2.�鿴���е�Ա����Ϣ                *"<<endl;  
        system("tput cup 20 38");   cout<<"\t\t*               3��ɾ��һ��Ա��                     *"<<endl;  
        system("tput cup 21 38");   cout<<"\t\t*               4���޸�����                         *"<<endl;  
        system("tput cup 22 38");   cout<<"\t\t*               5������:                            *"<<endl;  
        system("tput cup 23 38");   cout<<"\t\t*               6���˳�                             *"<<endl;  
        system("tput cup 24 38");   cout<<"\t\t*               ѡ �� ��                            *"<<endl;  
        system("tput cup 25 38");   cout<<"\t\t****************************************************\033[0m"<<endl;  
        int select;  
        cin.clear();  
        cin.sync();  
        system("tput cup 24 75");   cin>>select;  
        switch(select)  
        {  
            case 1:  
                add_manager(p);  
                break;  
            case 2:  
                view_all(p);  
                break;  
            case 3:  
                del(p);  
                break;  
            case 4:  
                change_pwd(p);  
                break;  
            case 5:  
                return;  
                break;  
            case 6:  
                system("clear");  
                exit(0);  
                break;  
            default:  
                break;  
        }  
    }  
}  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
void Load_Menu()  
{  
    list<Employee*>::iterator p=Link.begin();  
    load();  
    for(int i=0;i<4;i++)  
    {  
        system("clear");  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        switch(i)  
        {  
            case 0:  
            cout<<"\t\t\t\t\t\033[34;1m����������\033[0m\t\t"<<endl;  
            break;  
            case 1:  
            cout<<"\t\t\t\t\t\033[34;1m����������..........\033[0m\t\t"<<endl;  
            break;  
            case 2:  
            cout<<"\t\t\t\t\t\033[34;1m����������....................\033[0m\t\t"<<endl;  
            break;  
            case 3:  
            cout<<"\t\t\t\t\t\033[34;1m����������..............................\033[0m\t\t"<<endl;  
            break;  
        }  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        cout<<"\t\t\t\t\t\033[34;1mС��ʾ��\033[0m"<<endl;  
        cout<<"\t\t\t\t\t\t\033[34;1m  ���ϴε�¼ϵͳ��ʱ��Ϊ��"<<endl;  
        //cout<<(*p)->get_logt()<<endl;  
        sleep(1);  
    }  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
    //cout<<"���سɹ���"<<endl;  
    cout<<"\t\t\t\t\t\t\033[34;1m�����ɹ���\033[0m"<<endl;  
    //cout<<"���سɹ���"<<endl;  
    for(int i=0;i<2;i++){sleep(1);}  
    system("clear");  
}  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
void Main_Menu()  
{  
    while(1)  
    {     
        Load_Menu();  
        system("clear");  
        system("tput cup 15 38");   cout<<"\t\t\033[34;1m*****************************************************"<<endl;  
        system("tput cup 16 38");   cout<<"\t\t*         �� ӭ ʹ �� �� ˾ �� �� ϵ ͳ v1.0        *"<<endl;  
        system("tput cup 17 38");   cout<<"\t\t*****************************************************"<<endl;  
        system("tput cup 18 38");   cout<<"\t\t*                   �� �� ¼ ��                     *"<<endl;  
        system("tput cup 19 38");   cout<<"\t\t*---------------------------------------------------*"<<endl;  
        system("tput cup 20 38");   cout<<"\t\t*            �ʺţ�                                 *"<<endl;  
        system("tput cup 21 38");   cout<<"\t\t*            ���룺                                 *"<<endl;  
        system("tput cup 22 38");   cout<<"\t\t*****************************************************\033[0m"<<endl;  
    int l_num;  
    string l_pwd;  
    cin.clear();  
    cin.sync();  
    system("tput cup 20 67");     
    cin>>l_num;  
    cin.clear();  
    cin.sync();  
    system("stty -echo");  
    system("tput cup 21 67");     
    cin>>l_pwd;  
    system("stty echo");  
    login_account(l_num,l_pwd);  
    }  
}  
///////////////��¼�˻�///////////////////  
int login_account(int num,string pwd)  
{  
    list<Employee*>::iterator p=Link.begin();  
    cout<<"�˺�Ϊ��"<<(*p)->get_num()<<endl;  
    cout<<"����Ϊ��"<<(*p)->get_pwd()<<endl;  
    while(p!=Link.end())  
    {  
        if(((*p)->get_num())==num)  
        {  
            if(((*p)->get_pwd())==pwd)  
            {  
                check=0;  
                break;  
            }  
            else{  
                cout<<"\033[34;1m����������������������룡\033[0m"<<endl;  
                cin.ignore(1000,'\n');  
                cin.get();  
                check++;  
                if(check>=3)  
                {  
                    cout<<"\033[34;1m�������̫�࣡\033[0m"<<endl;  
                    cin.get();  
                    exit(0);  
                }  
                return 0;  
            }     
        }  
        p++;  
    }  
    if(p==Link.end())  
    {  
        cout<<"\033[34;1mû�и��ʺţ�\033[0m"<<endl;  
        cin.ignore(1000,'\n');  
        cin.get();  
        return 0;  
    }  
    switch((*p)->get_flag())  
    {  
        case 0:  
            boss_fun(p);  
            break;  
        case 1:  
            man_fun(p);  
            break;  
        case 2:  
            manager_fun(p);  
            break;  
        case 3:  
            man_fun(p);  
            break;  
        case 4:  
            manager_fun(p);  
            break;  
        default:  
            break;  
    }  
    return 0;  
}  
/////////////////////////////////  
/////////////*�������ݿ�*/////////////////  
void connect_mysql()  
{  
    conn=mysql_init(NULL);  
    const char *server="localhost";  
    const char *user="root";  
    const char *paswd="512330";  
    const char *database="company";  
    if(!mysql_real_connect(conn,server,user,paswd,database,0,NULL,0))  
    {  
        cout<<"\033[34;1m�������ݿ�ʧ�ܣ�\033[0m"<<endl;  
        exit(1);  
    }  
    mysql_set_character_set(conn,"utf8");  
}  
/////////////*�������ݿ���Ϣ*/////////////  
void load()  
{  
    MYSQL_RES* res;  
    MYSQL_ROW row;  
    Employee* p=NULL;  
    int number;        //���  
    string name;       //����  
    string pwd;   //����  
    string position;    //ְλ  
    float salary;      //нˮ  
    string logtime;    //��¼ʱ��  
    int flag;          //����  
    string mark;         
    string leader;     //ֱ���쵼  
    float sales;  
    float m_sales;  
    float fixed;  
    int worktime;  
    connect_mysql();  
    if(mysql_query(conn,"select*from Employee"))//��"Employee"��;  
    {  
        cout<<mysql_error(conn)<<endl;  
        exit(1);  
    }  
    res=mysql_use_result(conn);  
    while((row=mysql_fetch_row(res))!=NULL)//��"Employee"���е����ݷֱ���������Ӧ�ı�����;  
    {  
        flag=atoi(row[7]);  
        //cout<<"\033[34;1m���سɹ���\033[0m"<<endl;  
  
        switch(flag)//�ֱ���ȡ������"Employee"���е����ݷ��������Ӧ������;  
        {  
            case 0:  
                number=atoi(row[1]);  
                name=row[2];  
                pwd=row[3];  
                position=row[4];  
                salary=atof(row[5]);  
                logtime=row[6];  
                flag=atoi(row[7]);  
                mark=row[8];  
                leader=row[9];  
                p=new Boss(number,name,pwd,position,salary,logtime,flag,mark,leader);  
                Link.push_front(p);  
                delete p;  
                p=NULL;  
                cout<<"\033[34;1m���سɹ���\033[0m"<<endl;  
                break;  
            case 1:  
                number=atoi(row[1]);  
                name=row[2];  
                pwd=row[3];  
                position=row[4];  
                salary=atof(row[5]);  
                logtime=row[6];  
                flag=atoi(row[7]);  
                mark=row[8];  
                leader=row[9];  
                p=new S_man(number,name,pwd,position,salary,logtime,flag,mark,leader);  
                Link.push_front(p);  
                delete p;  
                p=NULL;  
                break;  
            case 2:  
                while((row=mysql_fetch_row(res))!=NULL)//��"Employee"���е����ݷֱ���������Ӧ�ı�����;  
                {  
                    number=atoi(row[1]);  
                    name=row[2];  
                    pwd=row[3];  
                    position=row[4];  
                    salary=atof(row[5]);  
                    logtime=row[6];  
                    flag=atoi(row[7]);  
                    mark=row[8];  
                    leader=row[9];  
                }  
                p=new S_manager(number,name,pwd,position,salary,logtime,flag,mark,leader);  
                Link.push_front(p);  
                delete p;  
                p=NULL;  
                break;  
            case 3:  
                while((row=mysql_fetch_row(res))!=NULL)//��"Employee"���е����ݷֱ���������Ӧ�ı�����;  
                {  
                    number=atoi(row[1]);  
                    name=row[2];  
                    pwd=row[3];  
                    position=row[4];  
                    salary=atof(row[5]);  
                    logtime=row[6];  
                    flag=atoi(row[7]);  
                    mark=row[8];  
                    leader=row[9];  
                }  
                p=new T_man(number,name,pwd,position,salary,logtime,flag,mark,leader);  
                Link.push_front(p);  
                delete p;  
                p=NULL;  
                break;  
            case 4:  
                while((row=mysql_fetch_row(res))!=NULL)//��"Employee"���е����ݷֱ���������Ӧ�ı�����;  
                {  
                    number=atoi(row[1]);  
                    name=row[2];  
                    pwd=row[3];  
                    position=row[4];  
                    salary=atof(row[5]);  
                    logtime=row[6];  
                    flag=atoi(row[7]);  
                    mark=row[8];  
                    leader=row[9];  
                }  
                p=new T_manager(number,name,pwd,position,salary,logtime,flag,mark,leader);  
                Link.push_front(p);  
                delete p;  
                p=NULL;  
                break;  
            default:  
                break;  
        }  
    }  
}  
int main()  
{  
    Main_Menu();      
    return 0;  
}  
