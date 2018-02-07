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
list<Employee*> Link;        //创建一个用于存储Employee对象指针的list容器；  
  
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
    list<Employee*>::iterator l=Link.begin();  //创建容器Link1的迭代器 l;  
    while(l != Link.end())  
    {  
        sprintf(savestr,"insert into Employee (number,name,password,position,salary,logtime,flag,remark,leader) values(%d,'%s','%s','%s',%f,'%s',%d,'%s','%s')",  
            (*l)->number,(*l)->name.c_str(),(*l)->password.c_str(),(*l)->position.c_str(),  
            (*l)->salary,(*l)->logtime.c_str(),(*l)->flag,(*l)->mark.c_str(),(*l)->leader.c_str());  
        if(mysql_query(conn,savestr))    //发送SQL语句，成功返回0；  
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
    cout<<"\033[34;1m您的个人信息为：\033[0m"<<endl<<endl;  
      
    cout<<"----------------------------------------------------------------------------------------------"<<endl;  
    cout.width(10); cout<<"工号 |";  
    cout.width(19); cout<<"姓名 |";  
    cout.width(12); cout<<"职位 |";  
    cout.width(9);  cout<<"薪水 |";  
    cout.width(9);  cout<<"等级 |";  
    cout.width(19); cout<<"REMARK |";  
    cout.width(19); cout<<"上级 |";  
    cout.width(40); cout<<"上次登录时间";  
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
        cout<<"\n\033[34;1m请输入新密码：\033[0m";  
        system("stty -echo");  
        cin>>pwd;  
        system("stty echo");  
        cout<<"\n\033[34;1m请在输入一次：\033[0m";  
        system("stty -echo");  
        cin>>c_pwd;  
        system("stty echo");  
        if(pwd == c_pwd)  
        {  
            (*p)->set_passwd(pwd);  
            cout<<"\n\033[34;1m密码修改成功！\033[0m"<<endl;  
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
        cout<<"\033[34;1m创建数据库失败！\033[0m"<<endl;  
        exit(1);  
    }  
  
    char str[1024]="";  
    while(p!=Link.end())  
    {  
        (*p)->save_str(str);  
        if(mysql_query(conn,str))  
        {  
            cout<<"\033[34;1m添加数据失败！\033[0m"<<endl;  
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
    cout.width(10); cout<<"工号 |";  
    cout.width(19); cout<<"姓名 |";  
    cout.width(12); cout<<"职位 |";  
    cout.width(9);  cout<<"薪水 |";  
    cout.width(9);  cout<<"等级 |";  
    cout.width(19); cout<<"REMARK |";  
    cout.width(19); cout<<"上级 |";  
    cout.width(40); cout<<"上次登录时间 |";  
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
    string name;    cout<<"\033[34;1m请输入姓名：\033[0m";  cin>>name;  
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
            pos="销售职员";  
            ptr=new S_man(number,name,pwd,pos,d_salary,g_t,flag,mark,lead);  
            cout<<"请输入销售额：";  cin>>sale;  
            ptr->set_sales(sale);  
            ptr->set_salary();  
            m_fixed = (*p)->get_salary();  
            (*p)->set_sales(sale);  
            (*p)->set_fixed_salary(m_fixed);  
            (*p)->set_salary();  
            break;  
        case 4:  
            flag = 3;  
            pos="技术职员";  
            ptr=new T_man(number,name,pwd,pos,d_salary,g_t,flag,mark,lead);  
            cout<<"\033[34;1m请输入工作时间：\033[0m";    cin>>wt;  
            ptr->set_worktime(wt);  
            ptr->set_salary();  
            break;  
        default:  
            break;  
    }     
  
    Link.push_front(ptr);  
    save_all();  
    cout<<"\033[34;1m添加成功！\033[0m"<<endl;  
    cin.ignore(1000,'\n');  
    cin.get();  
}  
/////////////////////////////////////////////  
void update(list<Employee*>::iterator p)                  //view depart staff information  
{  
    int number;  
    string name = (*p)->get_name();  
    list<Employee*>::iterator q=Link.begin();  
    cout<<"\033[34;1m请输入工号：\033[0m";  
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
        cout<<"\033[34;1m没有该职员！\033[0m"<<endl;  
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
    cout<<"\033[34;1m修改成功！\033[0m"<<endl;  
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
            cout<<"\033[34;1m请输入销售额：\033[0m"; cin>>sales;  
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
            cout<<"\033[34;1m请输入修改后的薪水：\033[0m";  cin>>fixed;  
            (*p)->set_fixed_salary(fixed);  
            (*p)->set_salary();  
            break;  
        case 3:  
            cout<<"\033[34;1m请输入工作时间：\033[0m";    cin>>time;  
            (*p)->set_worktime(time);  
            (*p)->set_salary();  
            break;  
        case 4:  
            cout<<"\033[34;1m请输入修改后的薪水：\033[0m";  cin>>fixed;  
            (*p)->set_fixed_salary(fixed);  
            (*p)->set_salary();  
            break;  
        default:  
            break;  
    }  
    cout<<"\033[34;1m修改成功！\033[0m"<<endl;  
    cin.ignore(1000,'\n');  
    cin.get();  
    save_all();  
}  
//////////////删除/////////////////////////  
void del(list<Employee*>::iterator p)                         //delete an Employee  
{  
    list<Employee*>::iterator q=Link.begin();  
    int number;  
    cout<<"\033[34;1m请输入要删除的工号\033[0m";  
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
            cout<<"\033[34;1m删除成功！\033[0m"<<endl;  
            cin.ignore(1000,'\n');  
            cin.get();  
            break;  
        }  
        q++;  
    }  
  
    if(q == Link.end())  
    {  
        cout<<"\033[34;1m没有该员工！\033[0m"<<endl;  
        cin.ignore(1000,'\n');  
        cin.get();  
        return;  
    }  
    save_all();  
}  
////////////////添加经理////////////////////////////  
void add_manager(list<Employee*>::iterator p)                             //add manager  
{  
      
    Employee* ptr =NULL;  
    string name;    cout<<"\033[34;1m请输入姓名：\033[0m";  cin>>name;  
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
    cout<<"\033[34;1m请输入修改后的薪水：\033[0m";  cin>>fixed;  
      
    Link.sort(sort_num);//对容器内的对象按从小到大的顺序进行排序；  
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
        cout<<"\n\033[34;1m您想要增加那个信息：  1.销售经理   2.技术经理\033[0m\n";  
        int select;  
        cin>>select;  
        if(select == 1)  
        {  
            flag =2;  
            pos = "\033[34;1m销售经理\033[0m";  
            ptr=new S_manager(number,name,pwd,pos,fixed,g_t,flag,mark,lead);  
            ptr->set_fixed_salary(fixed);  
            ptr->set_sales(0);  
            ptr->set_salary();  
            break;  
        }  
        else if(select == 2)  
        {  
            flag = 4;  
            pos = "\033[34;1m技术经理\033[0m";  
            ptr=new T_manager(number,name,pwd,pos,fixed,g_t,flag,mark,lead);  
            break;  
        }  
    }  
    Link.push_front(ptr);  
    cout<<"\033[34;1m添加成功！\033[0m"<<endl;  
    cin.ignore(1000,'\n');  
    cin.get();  
    save_all();  
  
}  
///////////////显示所有的信息/////////////////////////  
void view_all(list<Employee*>::iterator p)                                //view all information  
{     
    while(1)  
    {  
        system("clear");  
        system("tput cup 15 38");   cout<<"\t\t\033[34;1m****************************************************"<<endl;  
        system("tput cup 16 38");   cout<<"\t\t*               显 示 模 式 ？                      *"<<endl;  
        system("tput cup 17 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 18 38");   cout<<"\t\t*               1.工号                             *"<<endl;  
        system("tput cup 19 38");   cout<<"\t\t*               2.姓名                             *"<<endl;  
        system("tput cup 20 38");   cout<<"\t\t*               3.部门                             *"<<endl;  
        system("tput cup 21 38");   cout<<"\t\t*               4.领导                             *"<<endl;  
        system("tput cup 22 38");   cout<<"\t\t*               5.所有                             *"<<endl;  
        system("tput cup 23 38");   cout<<"\t\t*               选 择 ：                           *"<<endl;  
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
////////////////经理界面////////////////////////////  
void manager_fun(list<Employee*>::iterator p)                   
{  
    while(1)  
    {  
  
        system("clear");  
        cout<<"\t\t\n\n\n";  
        system("tput cup 15 38");   cout<<"\t\t\033[34;1m****************************************************"<<endl;  
        system("tput cup 16 38");   cout<<"\t\t*             欢 迎 来 到 经 理 界 面               *"<<endl;  
        system("tput cup 17 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 18 38");   cout<<"\t\t*            请 选 择 ：                           *"<<endl;  
        system("tput cup 19 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 20 38");   cout<<"\t\t*            1.查看个人信息                         *"<<endl;  
        system("tput cup 21 38");   cout<<"\t\t*            2.查看部门员工信息                     *"<<endl;  
        system("tput cup 22 38");   cout<<"\t\t*            3.增加员工                            *"<<endl;  
        system("tput cup 23 38");   cout<<"\t\t*            4.修改员工信息                         *"<<endl;  
        system("tput cup 24 38");   cout<<"\t\t*            5.删除员工信息                         *"<<endl;  
        system("tput cup 25 38");   cout<<"\t\t*            6.修改密码                             *"<<endl;  
        system("tput cup 26 38");   cout<<"\t\t*            7.返回                                 *"<<endl;  
        system("tput cup 27 38");   cout<<"\t\t*            8.退出                                *"<<endl;  
        system("tput cup 28 38");   cout<<"\t\t*            选 择 ：                               *"<<endl;  
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
//////////////员工界面////////////////////////  
void man_fun(list<Employee*>::iterator p)                       
{  
    while(1)  
    {  
  
        system("clear");  
        cout<<"\t\t\n\n\n";  
        system("tput cup 15 38");   cout<<"\t\t\033[34;1m****************************************************"<<endl;  
        system("tput cup 16 38");   cout<<"\t\t*              欢 迎 来 到 员 工 界 面              *"<<endl;  
        system("tput cup 17 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 18 38");   cout<<"\t\t*            请 选 择 ：                           *"<<endl;  
        system("tput cup 19 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 20 38");   cout<<"\t\t*            1.查看个人信息                         *"<<endl;  
        system("tput cup 21 38");   cout<<"\t\t*            2.修改密码                             *"<<endl;  
        system("tput cup 22 38");   cout<<"\t\t*            3.返回                                *"<<endl;  
        system("tput cup 23 38");   cout<<"\t\t*            4.退出                                *"<<endl;  
        system("tput cup 24 38");   cout<<"\t\t*            选 择 ：                              *"<<endl;  
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
///////////////老板管理界面/////////////////////////////////  
void boss_fun(list<Employee*>::iterator p)      
{  
    while(1)  
    {  
        system("clear");  
        system("tput cup 15 38");   cout<<"\t\t\033[34;1m****************************************************"<<endl;  
        system("tput cup 16 38");   cout<<"\t\t*               请 选 择 您 要 操 作 的 选 项       *"<<endl;  
        system("tput cup 17 38");   cout<<"\t\t****************************************************"<<endl;  
        system("tput cup 18 38");   cout<<"\t\t*               1.增加经理                          *"<<endl;  
        system("tput cup 19 38");   cout<<"\t\t*               2.查看所有的员工信息                *"<<endl;  
        system("tput cup 20 38");   cout<<"\t\t*               3、删除一个员工                     *"<<endl;  
        system("tput cup 21 38");   cout<<"\t\t*               4、修改密码                         *"<<endl;  
        system("tput cup 22 38");   cout<<"\t\t*               5、返回:                            *"<<endl;  
        system("tput cup 23 38");   cout<<"\t\t*               6、退出                             *"<<endl;  
        system("tput cup 24 38");   cout<<"\t\t*               选 择 ：                            *"<<endl;  
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
            cout<<"\t\t\t\t\t\033[34;1m玩命加载中\033[0m\t\t"<<endl;  
            break;  
            case 1:  
            cout<<"\t\t\t\t\t\033[34;1m玩命加载中..........\033[0m\t\t"<<endl;  
            break;  
            case 2:  
            cout<<"\t\t\t\t\t\033[34;1m玩命加载中....................\033[0m\t\t"<<endl;  
            break;  
            case 3:  
            cout<<"\t\t\t\t\t\033[34;1m玩命加载中..............................\033[0m\t\t"<<endl;  
            break;  
        }  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        cout<<"\t\t\t\t\t\033[34;1m小提示：\033[0m"<<endl;  
        cout<<"\t\t\t\t\t\t\033[34;1m  您上次登录系统的时间为："<<endl;  
        //cout<<(*p)->get_logt()<<endl;  
        sleep(1);  
    }  
        putchar(10);  
        putchar(10);  
        putchar(10);  
        putchar(10);  
    //cout<<"加载成功！"<<endl;  
    cout<<"\t\t\t\t\t\t\033[34;1m启动成功！\033[0m"<<endl;  
    //cout<<"加载成功！"<<endl;  
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
        system("tput cup 16 38");   cout<<"\t\t*         欢 迎 使 用 公 司 管 理 系 统 v1.0        *"<<endl;  
        system("tput cup 17 38");   cout<<"\t\t*****************************************************"<<endl;  
        system("tput cup 18 38");   cout<<"\t\t*                   请 登 录 ：                     *"<<endl;  
        system("tput cup 19 38");   cout<<"\t\t*---------------------------------------------------*"<<endl;  
        system("tput cup 20 38");   cout<<"\t\t*            帐号：                                 *"<<endl;  
        system("tput cup 21 38");   cout<<"\t\t*            密码：                                 *"<<endl;  
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
///////////////登录账户///////////////////  
int login_account(int num,string pwd)  
{  
    list<Employee*>::iterator p=Link.begin();  
    cout<<"账号为："<<(*p)->get_num()<<endl;  
    cout<<"密码为："<<(*p)->get_pwd()<<endl;  
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
                cout<<"\033[34;1m您输入密码错误！请重新输入！\033[0m"<<endl;  
                cin.ignore(1000,'\n');  
                cin.get();  
                check++;  
                if(check>=3)  
                {  
                    cout<<"\033[34;1m错误次数太多！\033[0m"<<endl;  
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
        cout<<"\033[34;1m没有该帐号！\033[0m"<<endl;  
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
/////////////*链接数据库*/////////////////  
void connect_mysql()  
{  
    conn=mysql_init(NULL);  
    const char *server="localhost";  
    const char *user="root";  
    const char *paswd="512330";  
    const char *database="company";  
    if(!mysql_real_connect(conn,server,user,paswd,database,0,NULL,0))  
    {  
        cout<<"\033[34;1m加载数据库失败！\033[0m"<<endl;  
        exit(1);  
    }  
    mysql_set_character_set(conn,"utf8");  
}  
/////////////*加载数据库信息*/////////////  
void load()  
{  
    MYSQL_RES* res;  
    MYSQL_ROW row;  
    Employee* p=NULL;  
    int number;        //编号  
    string name;       //姓名  
    string pwd;   //密码  
    string position;    //职位  
    float salary;      //薪水  
    string logtime;    //登录时间  
    int flag;          //旗子  
    string mark;         
    string leader;     //直接领导  
    float sales;  
    float m_sales;  
    float fixed;  
    int worktime;  
    connect_mysql();  
    if(mysql_query(conn,"select*from Employee"))//打开"Employee"表;  
    {  
        cout<<mysql_error(conn)<<endl;  
        exit(1);  
    }  
    res=mysql_use_result(conn);  
    while((row=mysql_fetch_row(res))!=NULL)//将"Employee"表中的数据分别存入各个相应的变量中;  
    {  
        flag=atoi(row[7]);  
        //cout<<"\033[34;1m加载成功！\033[0m"<<endl;  
  
        switch(flag)//分别将已取出来的"Employee"表中的数据放入各个相应的类中;  
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
                cout<<"\033[34;1m加载成功！\033[0m"<<endl;  
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
                while((row=mysql_fetch_row(res))!=NULL)//将"Employee"表中的数据分别存入各个相应的变量中;  
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
                while((row=mysql_fetch_row(res))!=NULL)//将"Employee"表中的数据分别存入各个相应的变量中;  
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
                while((row=mysql_fetch_row(res))!=NULL)//将"Employee"表中的数据分别存入各个相应的变量中;  
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
