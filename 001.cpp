#include<bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define rep(i, a, b)              for(int i(a); i <= (b); ++i)
#define dec(i, a, b)              for(int i(a); i >= (b); --i)
#define MP                        make_pair

const int INF   =    0x3f3f3f;
const int N     =    100000      +       10;
const int M     =    10000       +       10;
const int Q     =    1500        +       10;
const int A     =    100         +       10;

int mod=40;  
set<int> S;         

int main(){
    srand(time(0));  //��֤������

    S.clear();
    int cnt = 0;     //�Ѿ���ȡ������
    while(cnt < 1){
        int number = rand() % mod + 1;   //��֤����� 1~mod�ķ�Χ

        if(S.find(number) == S.end()){    //�����ظ�ѡ��ͬһ����
            S.insert(number);
            cnt++;
        }
    }

    set<int>::iterator it = S.begin();
    cnt = 0;
    while(it != S.end()){                 //�����ǩ���
        printf("��%d����ѡ�еĺ��ӵĺ�����\t %d\n",++cnt,*it);
        it++;
    }

    return 0;
}
