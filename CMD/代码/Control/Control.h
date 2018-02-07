
#  ifndef  CONTROL_h
#  define  CONTROL_h


#  include <string>

using namespace std;

#  define    _void_                         0x000  
#  define    _pstr_                         0x001
#  define    _char_                         0x002
#  define    _int_                          0x003
#  define    _float_                        0x004
#  define    _double_                       0x005
#  define    _string_                       0x006


///////////////////////////////////////////////////////////////////////////////
#  define InputInfo                         0x010
#  define FucCallFail                       0x011
#  define FewParm                           0x012
#  define MuchParm                          0x013
#  define FucNotFind                        0x014
#  define FucHelp                           0x015
#  define FucNotDefine                      0x016
#  define DllNotFind                        0x017
#  define DLLLoadFail                       0x018
#  define FucInfoFail                       0x019
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
struct command_parm  //���ڴ��ת����Ĳ�����int char char* float double)
{
	char    parm[16][256];//֧��16�������Ĵ��� ע�⵽parm[0]Ϊ������
	int     parmstyle[16];
	int     factparmnum;//ʵ������Ĳ�������
    string  all_parm;
};

struct fuc_info
{
 int      fucnum;/*save the function number in the FunctionInfo.txt*/
 char     fucname[128];/*save function name*/
 char     dllname[128];//��������dll���ļ���
 int      dllnum;//��������dll�е�λ��
 int      parmtype;/*save the type of the parms*/
 int      parmnum;/*ideal parm number*/
};

struct temp_fuc_info
{
	char info[6][128];
};
struct realparm
{
char char_parm[16];
int int_parm[16];
float float_parm[16];
double double_parm[16];
char str_parm[16][64];
string string_parm[16];
};

struct workspace
{
	string s_work_space;
    string s_temp_work_space;
	string filename;
};

#  endif


