#include<iostream>  
#include<windows.h>  
  
using namespace std;  
  
int b[11000],top=0;  
char a[10];  
bool f=true;   
  
int main(){  
    int n,num;  
    //初始化   
    a[0]='0';  
    a[1]='1';  
    a[2]='2';  
    a[3]='3';  
    a[4]='4';  
    a[5]='5';  
    a[6]='6';  
    a[7]='7';  
    a[8]='8';  
    a[9]='9';  
      
    while(1){  
        cout<<"请输入刷屏次数：";  
        cin>>n;  
        cout<<"请输入间隔时间(单位:毫秒  1000毫秒=1秒)：";  
        cin>>num;  
        if_return:  
        cout<<"是否需要前导回车？ 1.yes   2.no"<<endl;  
        int k;  
        cin>>k;  
        if(k==1){  
            f=true;  
        }  
        else if(k==2){  
            f=false;  
        }  
        else{  
            cout<<"输入错误！"<<endl;  
            goto if_return;//比较乱的但是很方便的循环   
        }  
        cout<<"请把光标移动到输入框"<<endl;  
        Sleep(2000);  
        mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);  
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//模拟单击鼠标左键   
        cout<<"请等待三秒。。。"<<endl;  
        Sleep(1000);  
        cout<<"3"<<endl;  
        Sleep(1000);  
        cout<<"2"<<endl;  
        Sleep(1000);  
        cout<<"1"<<endl;  
        for(int i=1; i<=n; i++){  
            if(f==true){  
                keybd_event(VK_RETURN,0,0,0);  
                keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);  
            }   
            int x=i;  
            while(x>0){  
                b[top++]=x%10;  
                x/=10;  
            }  
            top--;  
            for(int j=top; j>=0; j--){  
                keybd_event(a[b[j]],0,0,0);  
                keybd_event(a[b[j]],0,KEYEVENTF_KEYUP,0);//模拟按下某个数字键   
            }  
            top=0;  
            keybd_event(VK_RETURN,0,0,0);  
            keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);//模拟按下回车键   
            Sleep(num);  
        }  
        putchar(7);  
        system("cls");//清屏   
    }  
      
      
    return 0;  
}  
