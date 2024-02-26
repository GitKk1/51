#include<reg51.h>
#include"DELAY.H"
#include"DS1302.H"
#include"LCD1602.H"

//寄存器写入地址/指令定义
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_WEEK			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E



sbit En=P1^6;
sbit select=P2^4;
sbit add=P2^0;
sbit subtracat=P2^1;

unsigned char Key(void)
{	
	unsigned char key=0;
	
	if(En==0){Delay(20);while(En==0)Delay(20);key=1;}
	if(select==0){Delay(20);while(select==0)Delay(20);key=2;}
	
	return key;
}

unsigned char Key2(void)
{	
	unsigned char key2=0;
	
	if(add==0){Delay(20);while(add==0)Delay(20);key2=1;}
	if(subtracat==0){Delay(20);while(subtracat==0)Delay(20);key2=2;}
	
	return key2;
}



				 

	
