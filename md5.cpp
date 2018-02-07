#include "memory.h"
#include "stdio.h"
enum {encrypt,decrypt};//ENCRYPT:���ܣ�DECRYPT������
void des_run(char out[8],char in[8],bool type=encrypt);
//������Կ
void des_setkey(const char key[8]);
static void f_func(bool in[32],const bool ki[48]);//f����
static void s_func(bool out[32],const bool in[48]);//s�д���
//�任
static void transform(bool *out, bool *in, const char *table, int len);
static void xor(bool *ina, const bool *inb, int len);//���
static void rotatel(bool *in, int len, int loop);//ѭ������
 //�ֽ���ת����λ��
static void bytetobit(bool *out,const char *in, int bits);
//λ��ת�����ֽ���
static void bittobyte(char *out, const bool *in, int bits);
//�û�IP��
const static char ip_table[64]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
//���û�IP-1��
const static char ipr_table[64]={40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11, 51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
//E λѡ���
static const char e_table[48]={32,1, 2, 3, 4, 5,4, 5, 6, 7, 8, 9,8, 9, 10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
//P��λ��
const static char p_table[32]={16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
//pc1ѡλ��
const static char pc1_table[56]={
   57,49,41,33,25,17,9,1,
   58,50,42,34,26,18,10,2,
   59,51,43,35,27,19,11,3,
   60,52,44,36,63,55,47,39,
   31,23,15,7,62,54,46,38,
   30,22,14,6,61,53,45,37,
   29,21,13,5,28,20,12,4
};
//pc2ѡλ��
const static char pc2_table[48]={
   14,17,11,24,1,5,3,28,
   15,6,21,10,23,19,12,4,
   26,8,16,7,27,20,13,2,
   41,52,31,37,47,55,30,40,
   51,45,33,48,44,49,39,56,
   34,53,46,42,50,36,29,32
};
//����λ����
const static char loop_table[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
//S��
const static char s_box[8][4][16]={
    //s1
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
    //s2
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
    //s3
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
    //s4
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
    //s5
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
    //s6
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
    //s7
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
    //s8
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
};
static bool subkey[16][48];//16Ȧ����Կ
void des_run(char out[8],char in[8], bool type)
{
    static bool m[64],tmp[32],*li=&m[0], *ri=&m[32];
    bytetobit(m,in,64);
    transform(m,m,ip_table,64);
    if(type==encrypt){
       for(int i=0;i<16;i++){
           memcpy(tmp,ri,32);
           f_func(ri,subkey[i]);
           xor(ri,li,32);
           memcpy(li,tmp,32);
       }
    }else{
       for(int i=15;i>=0;i--){
           memcpy(tmp,li,32);
           f_func(li,subkey[i]);
           xor(li,ri,32);
           memcpy(ri,tmp,32);
       }
    }
    transform(m,m,ipr_table,64);
    bittobyte(out,m,64);
}
void des_setkey(const char key[8])
{
    static bool k[64], *kl=&k[0], *kr=&k[28];
    bytetobit(k,key,64);
    transform(k,k,pc1_table,56);
    for(int i=0;i<16;i++)
    {
       rotatel(kl,28,loop_table[i]);
       rotatel(kr,28,loop_table[i]);
       transform(subkey[i],k,pc2_table,48);
    }
}
void f_func(bool in[32],const bool ki[48])
{
    static bool mr[48];
    transform(mr,in,e_table,48);
    xor(mr,ki,48);
    s_func(in,mr);
    transform(in,in,p_table,32);
}
void s_func(bool out[32],const bool in[48])
{
    for(char i=0,j,k;i<8;i++,in+=6,out+=4)
    {
       j=(in[0]<<1)+in[5];
       k=(in[1]<<3)+(in[2]<<2)+(in[3]<<1)+in[4];
       bytetobit(out,&s_box[i][j][k],4);
    }
}
void transform(bool *out,bool *in,const char *table,int len)
{
    static bool tmp[256];
    for(int i=0;i<len;i++)
       tmp[i]=in[table[i]-1];
    memcpy(out,tmp,len);
}
void xor(bool *ina,const bool *inb,int len)
{
    for(int i=0;i<len;i++)
       ina[i]^=inb[i];
}
void rotatel(bool *in,int len,int loop)
{
    static bool tmp[256];
    memcpy(tmp,in,loop);
    memcpy(in,in+loop,len-loop);
    memcpy(in+len-loop,tmp,loop);
}
void bytetobit(bool *out,const char *in,int bits)
{
    for(int i=0;i<bits;i++)
       out[i]=(in[i/8]>>(i%8)) &1;
}
void bittobyte(char *out,const bool *in,int bits)
{
    memset(out,0,(bits+7)/8);
    for(int i=0;i<bits;i++)
       out[i/8]|=in[i]<<(i%8);
}
void main()
{
    char key[8]={'p','r','o','g','r','a','m'},str[8];
    puts("*****************DES***********************");
    printf("\n");
    printf("\n");
    puts("please input your words");
    gets(str);
    printf("\n");
    puts("****************************************");
    des_setkey(key);
    des_run(str,str,encrypt);
    puts("after encrypting:");
    puts(str);
    printf("\n");
    puts("****************************************");
    puts("after decrypting:");
    des_run(str,str,decrypt);
    puts(str);
    printf("\n");
    puts("****************************************");
    printf("\n");
}
