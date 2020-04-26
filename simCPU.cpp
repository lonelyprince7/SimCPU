#include  <iostream>
#include  <fstream>
#include  <string>
#include  "stdlib.h"
#include  <assert.h>
#define arraydata 100

using   namespace  std;
// string instruction_path="./prime_instruction.txt";
// string result_path="./prime_result.txt";
string instruction_path="./square_instruction.txt";
string result_path="./square_result.txt";
//地址
typedef struct ID 
{
	string array[arraydata];
	int index;
} id;


//寄存器01存乘积的高位和低位
typedef struct JCQ01
{
	char array[2][2];
}jcq01;


//数据存储
typedef struct CCQ
{
	int array[arraydata];
	char ccqarray[arraydata][2];
}ccq;


typedef struct StateR
{
	int array[6];
	
}stater;


//指令位置初始化 
void initID(id *instruction)
{
	instruction->index=0;
}


//换行格式对齐  
void  OutputEmptyLine()
{ 
	cout<< "\n\n" ;
}

int hex__ten(char c);
//读取文件 
int  ReadDataFromFileWBW(id *instruction)
{	
	string x=instruction_path;
	ifstream inf(x.c_str());
	if(!inf)
    {
    	 cout<<"文件不存在!请重新输入"<<endl;
    	 return 0;
    }
	cout<<"系统逐次读指令:"<<endl;
	/*ifstream fin( "data.txt" );*/
	string  s;
	while ( inf >> s ) {
		cout <<"从文档中指令如下: "<< s <<endl;
		instruction->array[instruction->index]=s;
		instruction->index++;;
	}
	return 1;
}


//判断寄存器号，如果为常数，直接返回常数
int Regnumber(string character)
{
	if(character=="R0"){return 0;}
	if(character=="R1"){return 1;}
	if(character=="R2"){return 2;}
	if(character=="R3"){return 3;}
	if(character=="R4"){return 4;}
	if(character=="R5"){return 5;}
	if(character=="R6"){return 6;}
	if(character=="R7"){return 7;}
	if(character=="R8"){return 8;}
	if(character=="R9"){return 9;}
	if(character=="R10"){return 10;}
	if(character=="R11"){return 11;}
	if(character=="R12"){return 12;}
	if(character=="R13"){return 13;}
	if(character=="R14"){return 14;}
	if(character=="R15"){return 15;}
} 


//十进制转二进制
int ten__two(int data) 
{
	if(data>=16) cout<<"危险!"<<endl;
	string x[16] = {"0000",
					 "0001", 
					 "0010", 
					 "0011",
				     "0100", 
					 "0101", 
					 "0110", 
					 "0111",
				     "1000", 
					 "1001", 
					 "1010", 
					 "1011",
				     "1100", 
					 "1101", 
					 "1110", 
					 "1111"};
 	cout<<x[data];
}

//十六进制转二进制
int hex__two2(char c) 
{
	 char x[17][5] = {
        "0000", "0001", "0010", "0011",
        "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011",
        "1100", "1101", "1110", "1111"
    };
    int n = 16;
    if (c >= 'a' && c <= 'f') n = c - 'a' + 10;
    if (c >= 'A' && c <= 'F') n = c - 'A' + 10;
    if (c >= '0' && c <= '9') n = c - '0';
    
	if(x[n][0]==x[n][1])
	return 0;
	else return 1;
	
}    

//十六进制转二进制
int hex__two(char c) 
{
	 char x[17][5] = {
        "0000", "0001", "0010", "0011",
        "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011",
        "1100", "1101", "1110", "1111"
    };
    int n = 16;
    if (c >= 'a' && c <= 'f') n = c - 'a' + 10;
    if (c >= 'A' && c <= 'F') n = c - 'A' + 10;
    if (c >= '0' && c <= '9') n = c - '0';
    printf("%s", x[n]);
}

//二进制转十六进制
int two_hex(string c) 
{
	if(c=="0000")	printf("0");
	if(c=="0001")	printf("1");
	if(c=="0010")	printf("2");
	if(c=="0011")	printf("3");
	if(c=="0100")	printf("4");
	if(c=="0101")	printf("5");
	if(c=="0110")	printf("6");
	if(c=="0111")	printf("7");
	if(c=="1000")	printf("8");
	if(c=="1001")	printf("9");
	if(c=="1010")	printf("A");
	if(c=="1011")	printf("B");
	if(c=="1100")	printf("C");
	if(c=="1101")	printf("D");
	if(c=="1110")	printf("E");
	if(c=="1111")	printf("F");
}


//十六进制转十进制 
int hex__ten(char c)  
{  
    if(c >= '0' && c <= '9')  
        return c - '0';  
    else if(c >= 'a' && c <= 'f')  
        return (c - 'a' + 10);  
    else if(c >= 'A' && c <= 'F')  
        return (c - 'A' + 10);  
    assert(0);  
    return 0;  
}


//十进制转十六进制
void ten_hex(int n,char *buf)
{
	sprintf(buf, "%X", n);
}

//加载常数指令 
int LDI(int Rnumbed,int data,char fird,char secd,stater *s,int datarray[16][1],char charray[16][2])
{	
	char a[32];
	string op="1000";
	
	datarray[Rnumbed][0]=data;
	charray[Rnumbed][0]=fird;
	charray[Rnumbed][1]=secd;
	//要输出机器码需要16进制转2进制 
	
	ten_hex(Rnumbed,a);//把寄存器号转为16进制 
	cout<<"1110 ";//操作码 
	
	hex__two(fird);// 
	cout<<" ";
	ten__two(Rnumbed);
	cout<<" ";
	hex__two(secd);
	cout<<" ";
	//E 5 A 5 后面的16进制编码 
	two_hex(op);
	cout<<fird;//十进制转16进制 10->A 
	cout<<a;
	cout<<secd<<"      ";
	
	for(int m=0;m<6;m++)
	{
		
		cout<<s->array[m]<<" ";
		
	}
	
	cout<<endl<<endl;	
}


//数据传送指令 
int MOV(int Rnumberd,int Rnumberr,int datarray[16][1],char charray[16][2],stater *s)
{
	char a[32];char b[32];
	string op1="0010";
	string op2="1100";
	//目的寄存器号 Rnumberd
	//源寄存器号 Rnumberr
	
	datarray[Rnumberd][0]=datarray[Rnumberr][0];
	charray[Rnumberd][0]=charray[Rnumberr][0];
	charray[Rnumberd][1]=charray[Rnumberr][1];

	ten_hex(Rnumberd,a);
	ten_hex(Rnumberr,b);
	
	cout<<"0010 1100 " ;
	ten__two(Rnumberd);
	cout<<" ";
	ten__two(Rnumberr);
	cout<<" ";
	two_hex(op1);
	two_hex(op2);
	cout<<a<<b<<"      ";
	for(int m=0;m<6;m++)
	{
		
		cout<<s->array[m]<<" ";
		
	} 
	cout<<endl<<endl;
}


//加法指令 
int ADD(int Rnumberd,int Rnumberr,int datarray[16][1],char charray[16][2],stater *s)
{
	int nums[10]={0,1,2,3,4,5,6,7,8,9}; //常数备选
	int data1,data2;
	char a[32];char b[32];
	char c[32];char z1,z2;
	string op1="0000";
	string op2="1100";
	//目的寄存器号 Rnumberd
	//源寄存器号 Rnumberr
	if(charray[Rnumberd][0]+charray[Rnumberr][0]>'F')
	{
		s->array[0]=1;//H
	}
	// if('0'<Rnumberr)
	datarray[Rnumberd][0]=datarray[Rnumberd][0]+datarray[Rnumberr][0];
	//判断状态寄存器
 	//判断有符号位溢出，根据最高位进位状态⊕次高位进位状态=1，则溢出	
    ten_hex(datarray[Rnumberd][0],c);
	//比较最高位和次高位，如果两个不同，溢出 S置为1 
	if(hex__two2(c[0]))
	{
		s->array[2]=1;//V
		s->array[1]=0;//S
	} 

 	if(datarray[Rnumberd][0]>255)
	{
		//无符号数判断及自己理解的异或值 
		s->array[5]=1;//C
		s->array[1]=0;//S
	}
 	if(datarray[Rnumberd][0]==0)
	{
		s->array[4]=1;//Z
	}
	if(datarray[Rnumberd][0]<0)
	{
		s->array[3]=1;//N
	}  
	
	
	ten_hex(Rnumberd,a);
	ten_hex(Rnumberr,b);
	
	cout<<"0000 1100 ";
	ten__two(Rnumberd);
	cout<<" ";
	ten__two(Rnumberr);

	cout<<" ";
	// 后面的16进制编码
	two_hex(op1);
	two_hex(op2);
	cout<<a<<b;
	cout<<"      ";
	//状态寄存器
	for(int m=0;m<6;m++)
	{
		cout<<s->array[m]<<" ";
	} 
	
	cout<<endl<<endl;
}


//减法指令 
int SUB(int Rnumberd,int Rnumberr,int datarray[16][1],char charray[16][2],stater *s)
{
	int data1,data2;
	char a[32];char b[32];char c[32];
	string op1="0000";
	string op2="1000";
	//目的寄存器号 Rnumberd;
	//源寄存器号 Rnumberr
	
	if(charray[Rnumberd][0]<charray[Rnumberd][0])
	{
		s->array[0]=1;//H
	}
	datarray[Rnumberd][0]=datarray[Rnumberd][0]-datarray[Rnumberr][0];
	//判断有符号位溢出，根据最高位进位状态⊕次高位进位状态=1，则溢出		
    ten_hex(datarray[Rnumberd][0],c);
	//比较最高位和次高位，如果两个不同，溢出 S置为1 
	if(hex__two2(c[0]))
	{
		s->array[2]=1;//V
		s->array[1]=0;//S
	} 

	if(datarray[Rnumberd][0]>255)//减法这里没考虑溢出 
	{
		//无符号数判断及自己理解的异或值 
		s->array[5]=1;//C
		s->array[1]=0;//S
	}
	if(datarray[Rnumberd][0]==0)
	{
		s->array[4]=1;//Z
	} 
	if(datarray[Rnumberd][0]<0)
	{
		s->array[3]=1;//N
	}  
	
	ten_hex(Rnumberd,a);
	ten_hex(Rnumberr,b);
	
	cout<<"0000 1000 ";
	ten__two(Rnumberd);
	cout<<" ";
	ten__two(Rnumberr);
	cout<<" ";
	// 后面的16进制编码
	two_hex(op1);
	two_hex(op2);
	cout<<a<<b;
	cout<<"      ";
	for(int m=0;m<6;m++)
	{
		
		cout<<s->array[m]<<" ";
		
	} 
	cout<<endl<<endl;
}


//乘法指令 
int MUL(int Rnumberd,int Rnumberr,jcq01 *zf,int datarray[16][1],stater *s)
{
	int product;//乘积 
	char a[32];char b[32];char c[32];//保存十六进制
	string op1="1001";
	string op2="1100";  


	product=datarray[Rnumberd][0]*datarray[Rnumberr][0];
	datarray[Rnumberd][0]=product;
	//这里影响到乘机高位和乘积低位，乘积高位存在r1里 乘积低位存在r0里 
	ten_hex(Rnumberd,a);
	ten_hex(Rnumberr,b);
	ten_hex(product,c);

	//将所得结果存入寄存器
	zf->array[1][0]=c[0];
	zf->array[1][1]=c[1];
	//乘积低位
	zf->array[0][0]=c[2];
	zf->array[0][1]=c[3];


	//打印指令的二进制形式
	cout<<"1001 1100 ";
	ten__two(Rnumberd);
	cout<<" ";
	ten__two(Rnumberr);
	cout<<" ";

	//打印指令的十六机制形式
	two_hex(op1);
	two_hex(op2);
	cout<<a<<b<<"      ";

	//打印标志位
	for(int m=0;m<6;m++)
	{
		
		cout<<s->array[m]<<" ";
		
	} 
	cout<<endl<<endl;
	
}

int ST(int Rnumberr,ccq *c,int datarray[16][1],char charray[16][2],stater *s)
{
	string op1="1001";
	string op2="0010";
	string op3="1100";
	char a[32];
	//将源寄存器中的内容 付给 以r14中的内容为地址 的数据存储器  
	int data = datarray[Rnumberr][0];
	int locate = datarray[14][0];
	c->array[locate]=data;
	c->ccqarray[locate][0]=charray[Rnumberr][0];
	c->ccqarray[locate][1]=charray[Rnumberr][1];
	
	ten_hex(Rnumberr,a);
	cout<<"1001 0010 ";
	ten__two(Rnumberr);
	cout<<" 1100 ";
	two_hex(op1);
	two_hex(op2);
	cout<<a;
	two_hex(op3);
	cout<<"      ";
	for(int m=0;m<6;m++)
	{
		cout<<s->array[m]<<" ";	
	} 
	cout<<endl<<endl;
	
} 


//空指令
void NOP(stater *s) 
{
	string op1="0000";
	string op2="0000";
	string op3="0000";
	string op4="0000";
	
	cout<<op1<<" "<<op2<<" "<<op3<<" "<<op4<<" "<<"0000";
	cout<<"      ";
	for(int m=0;m<6;m++)
	{
		cout<<s->array[m]<<" ";
	}
	cout<<endl<<endl;	
}


//无条件跳转指令
int RJMP(int Rdata1,int Rdata2,stater *s) 
{
	string op1="1100";
	char a[32];
	char b[32];
	ten_hex(Rdata1,a);
	ten_hex(Rdata2,b);
	
	cout<<op1<<" ";
	ten__two(Rdata1);
	cout<<" ";
	ten__two(Rdata1);
	cout<<" ";
	ten__two(Rdata2);
	cout<<" ";
	
	two_hex(op1);
	cout<<a<<a<<b;
	cout<<"      ";
	for(int m=0;m<6;m++)
	{
		cout<<s->array[m]<<" ";	
	}
	cout<<endl<<endl;
}


//有条件跳转指令
int BRMI(int Rdata1,int Rdata2,stater *s) 
{
	string op1="1111";
	string op2="0001";
	char a[32];
	char b[32];
	ten_hex(Rdata1,a);
	ten_hex(Rdata2,b);
	
	cout<<op1<<" "<<op2;
	cout<<" ";
	ten__two(Rdata1);
	cout<<" ";
	ten__two(Rdata2);
	cout<<" ";
	
	two_hex(op1);
	two_hex(op2);
	cout<<a<<b;
	cout<<"      ";
	for(int m=0;m<6;m++)
	{	
		cout<<s->array[m]<<" ";	
	}
	cout<<endl<<endl;
}

//装载指令 
int LD(int Rnumberd,ccq *c,int datarray[16][1],char charray[16][2],stater *s)
{
	string op1="1001";
	string op2="0000";
	string op3="1100";
	char a[4];
//将r14中的内容做为地址去数据寄存器中寻找，把相应寄存器的内容付给目的寄存器	
	int locate = datarray[14][0];
	datarray[Rnumberd][0]=c->array[locate];
	charray[Rnumberd][0]=c->ccqarray[locate][0];
	charray[Rnumberd][1]=c->ccqarray[locate][1];
	
	ten_hex(Rnumberd,a);
	
	cout<<"1001 0000 ";
	ten__two(Rnumberd);
	cout<<" 1100 ";
	
	two_hex(op1);
	two_hex(op2);
	cout<<a;
	two_hex(op3);
	cout<<"      ";
	for(int m=0;m<6;m++)
	{
		cout<<s->array[m]<<" ";
	}
	cout<<endl<<endl;	
}

//分支判断指令
int BLE(int& loopi,int& i,int& cnt,int upper,stater *s,int& flag1,int& flag2)
{
	cout<<"1100 0001 0100 1111 ";
	two_hex("1001");
	two_hex("0001");
	two_hex("0000");
	two_hex("0000");
	cout<<"      ";
	for(int m=0;m<6;m++)
	{
		cout<<s->array[m]<<" ";
	}
	cout<<endl<<endl;	
	if(cnt>upper){
		loopi=-1;
	}
	else{
		i=loopi-1; //因为跳出函数后还要+1,这里-1以抵消，意为跳转到循环入口
	}
	if(flag1==1&&flag2==1) flag2=0;
	else if(flag1==1&&flag2==0) flag1=0;
	return 0;
}
int	Print(int Rnumberr,int c,int datarray[16][1],stater *s,ofstream& of){
	cout<<"1111 1110 1000 ";
	ten__two(Rnumberr);
	cout<<" ";
	two_hex("1001");
	two_hex("0000");
	two_hex("1000");
	char b[32];
	if(c==-1) ten_hex(Rnumberr,b);
	else ten_hex(c,b);
	cout<<b;
	cout<<"      ";
	for(int m=0;m<6;m++)
	{
		cout<<s->array[m]<<" ";
	}
	cout<<endl<<endl;	
	int a;
	if(c==-1 )a=datarray[Rnumberr][0];
	else a=c;
	cout<<"**************************按照要求打印的数为:"<<a<<"**************************"<<endl;
	
	of<<a<<endl;
}
//循环指令
int Loop(int& loopi,int i,stater *s)
{
	cout<<"1110 0000 1100 0000 ";
	two_hex("1001");
	two_hex("0000");
	two_hex("1100");
	two_hex("0000");
	cout<<"      ";
	for(int m=0;m<6;m++)
	{
		cout<<s->array[m]<<" ";
	}
	cout<<endl<<endl;	
	loopi=i;
}
//条件指令
int Compa(int Rnumberr,int Rnumberd,int& i,int datarray[16][1],stater* s){
	cout<<"1111 1000 ";
	char a[32];char b[32];
	ten__two(Rnumberr);
	cout<<" ";
	ten__two(Rnumberd);
	cout<<" ";
	two_hex("1111");
	two_hex("1000");
	ten_hex(Rnumberr,a);
	ten_hex(Rnumberd,b);
	cout<<a<<b<<"      ";
	for(int m=0;m<6;m++)
	{
		cout<<s->array[m]<<" ";
	}
	cout<<endl;
	int mod=datarray[Rnumberr][0]%datarray[Rnumberd][0];
	if(mod!=0){
		i+=5;
	}
}
int Compb(int Rnumberr,int& i,int datarray[16][1],stater* s){
	cout<<"1111 1000 0100";
	char a[32];
	ten__two(Rnumberr);
	two_hex("1111");
	two_hex("1000");
	two_hex("0100");
	ten_hex(Rnumberr,a);
	cout<<a<<"      ";
	for(int m=0;m<6;m++)
	{
		cout<<s->array[m]<<" ";
	}
	cout<<endl;
	if(datarray[Rnumberr][0]==0){
		i+=3;
	}
}

int  main() 
{
	ofstream of(result_path);
	id instruction;//所有的指令 寄存器 立即数 
	stater s;//状态寄存器 
	ccq c;   //数据存储器 
	jcq01 zf;//存乘积高位和低位 

	int datarray[16][1]={0};//这个数组用来存数据十进制 试试 
	char charray[16][2]={0};//这个数组存放数据的十六进制 
	cout<<"=============================================="<<endl;
	cout<<"||||||||||||欢迎进入CPU模拟程序|||||||||||||||"<<endl;
	cout<<"=============================================="<<endl;
	 
	
	initID(&instruction);

	for(int m=0;m<=6;m++)
	{
		s.array[m]=0;
	}

	int Right = ReadDataFromFileWBW(&instruction);  //逐词读入字符串
	while(!Right)
	{
		ReadDataFromFileWBW(&instruction);
	}
	
	OutputEmptyLine();  //输出空行
	int pctemp[4]={0};
	int loopi1=-1; //标记第一重循环入口所在的指令下标
	int loopi2=-1; //标记第二重循环入口所在的指令下标
	int flag1=0;
	int flag2=0;//标记是否进入两个循环中的一个
	for(int i=0; instruction.array[i]!="#"; i++)
	{
		if (instruction.array[i]=="Add") {

			printf("进行的是加法指令！              标 志 位\n");
			int Rnumberd=Regnumber(instruction.array[i+1]);
			int Rnumberr=Regnumber(instruction.array[i+2]);	

			ADD(Rnumberd,Rnumberr,datarray,charray,&s);
		}
		if (instruction.array[i]=="Sub") {
                    
			printf("进行的是减法指令！              标 志 位\n"); 
			int Rnumberd=Regnumber(instruction.array[i+1]);
			int Rnumberr=Regnumber(instruction.array[i+2]);

			SUB(Rnumberd,Rnumberr,datarray,charray,&s);
		}
		if (instruction.array[i]=="Mul") {
                    
			printf("进行的是无符号乘法指令！        标 志 位\n");
			int Rnumberd=Regnumber(instruction.array[i+1]);
			int Rnumberr=Regnumber(instruction.array[i+2]);
			
			MUL(Rnumberd,Rnumberr,&zf,datarray,&s);
		
		}
		if(instruction.array[i]=="RJMP") {
			        
			printf("进行的是无条件相对跳转指令！    标 志 位\n"); 
			string temp = instruction.array[i+1];
			const char *ten = temp.data();//字符串转换为字符数组
			int Rdata1=hex__ten(ten[0]);
			int Rdata2=hex__ten(ten[1]);
			
			RJMP(Rdata1,Rdata2,&s);				
			if(instruction.array[i+2]=="Nop")
			i=i+3;
			else
			i=i+4;
		}
		if(instruction.array[i]=="BRMI") {
			printf("进行的是有条件相对跳转指令！标 志 位\n");
			//Address(pctemp);
			string temp = instruction.array[i+1];
			const char *ten = temp.data();//字符串转换为字符数组
			int Rdata1=hex__ten(ten[0]);
			int Rdata2=hex__ten(ten[1]);

			BRMI(Rdata1,Rdata2,&s);
			if(s.array[3]==1)
			{
				if(instruction.array[i+2]=="Nop")
				i=i+3;
				else
				i=i+4;
			}
		}
		if(instruction.array[i]=="Mov") {
		        	
			printf("进行的是数据传送指令！          标 志 位\n");
			int Rnumberd=Regnumber(instruction.array[i+1]);
			int Rnumberr=Regnumber(instruction.array[i+2]);
			
			MOV(Rnumberd,Rnumberr,datarray,charray,&s);
		}
		if(instruction.array[i]=="Ldi") {
			
			printf("进行的是载入立即数指令！        标 志 位\n");		
			string temp = instruction.array[i+2];
			const char *twoc = temp.data();//字符串转换为字符数组
			//Rnumber是数字我们想要的数字 当前指令的下一位是寄存器号 再下一位是数据但是16进制 
			int Rnumbed=Regnumber(instruction.array[i+1]);//printf("%d",Rnumber); 
			int Rdata1=hex__ten(twoc[0]);//rdata1是第一个16进制数转化的10进制 
			int Rdata2=hex__ten(twoc[1]);//rdata2是第二个16进制数转化的10进制		
			int sum; //十进制数字，是立即数的十进制 
			sum=16*Rdata1+Rdata2;                 // 这是立即数的十六进制拆成两位 ↓
			LDI(Rnumbed,sum,twoc[0],twoc[1],&s,datarray,charray);
			//（ 寄存器号，立即数十进制数，A,A ,状态寄存器,存放十进制的寄存器，存放十六进制字符的寄存器） 
		}
		if(instruction.array[i]=="Ld") {	        
			printf("进行的是装载指令！              标 志 位\n");
			int Rnumberd=Regnumber(instruction.array[i+1]);
			LD(Rnumberd,&c,datarray,charray,&s);
			
		}
		if(instruction.array[i]=="St") {		
			printf("进行的是存储指令！              标 志 位\n");
			int Rnumberr=Regnumber(instruction.array[i+2]);		
			ST(Rnumberr,&c,datarray,charray,&s);
		}
		if(instruction.array[i]=="Nop") {
			        
			printf("进行的是空操作指令！            标 志 位\n");
			char pcchar3[1];
			char pcchar2[1];
			NOP(&s);
		}
		if(instruction.array[i]=="Loop:"){
			printf("进行的是循环指令!               标 志 位\n");
			if(flag1==0&&flag2==0){
				Loop(loopi1,i,&s);
				flag1=1;
			}
			else if(flag1==1&&flag2==0){
				Loop(loopi2,i,&s);
				flag2=1;
			}
		}
		if(instruction.array[i]=="Ble"){
			printf("进行的是分支判断指令!           标 志 位\n");
			int index=datarray[Regnumber(instruction.array[i+1])][0]; //获取循环变量
			string upper=instruction.array[i+2]; //循环次数
			int upperi;
			if(upper[0]=='R'){
				upperi=datarray[Regnumber(upper)][0];
			}
			else upperi=stoi(upper);
			if((flag1==1)&&(flag2==0)) BLE(loopi1,i,index,upperi,&s,flag1,flag2);
			else if((flag1==1)&&(flag2==1)) BLE(loopi2,i,index,upperi,&s,flag1,flag2);
		}

		if(instruction.array[i]=="Print"){
			printf("进行的是打印指令!               标 志 位\n");
			if((instruction.array[i+1])[0]=='R'){
				int Rnumberr=Regnumber(instruction.array[i+1]);
				Print(Rnumberr,-1,datarray,&s,of);
			}
			else{
				int c=stoi(instruction.array[i+1]);
				Print(0,c,datarray,&s,of);
			}
		}
		if(instruction.array[i]=="Cmpa"){
			printf("进行的是条件判断指令!           标 志 位\n");
			int Rnumberr=Regnumber(instruction.array[i+1]);
			int Rnumberd=Regnumber(instruction.array[i+2]);
			Compa(Rnumberr,Rnumberd,i,datarray,&s);
		}
		if(instruction.array[i]=="Cmpb"){
			printf("进行的是条件判断指令!           标 志 位\n");
			int Rnumberr=Regnumber(instruction.array[i+1]);
			Compb(Rnumberr,i,datarray,&s);
		}
	}
	cout<<endl;
	return 0 ;
}
