#include<reg51.h>

sbit DS1302_SCLK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

unsigned char SECOND,MINUTE,HOUR,DATE,MONTH,WEEK,YEAR;

//寄存器写入地址/指令定义
#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_WEEK			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E
//                  0年1月2日3时4分5秒6周
unsigned char Time[]={23,1,8,13,32,0,7};

void DS1302_Init(void)
{
	DS1302_CE=0;
	DS1302_SCLK=0;
}

void DS1302_WriteByte(unsigned char Command,unsigned char Date)
{
	unsigned char i=0;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=1;	
		DS1302_SCLK=0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO=Date&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}	
	DS1302_CE=0;
}

void DS1302_SetTime(void)
{	
	DS1302_WriteByte(DS1302_WP,0/10*16+0%10);
	DS1302_WriteByte(DS1302_YEAR,Time[0]/10*16+Time[0]%10);//十进制转BCD码后写入
	DS1302_WriteByte(DS1302_MONTH,Time[1]/10*16+Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,Time[2]/10*16+Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,Time[3]/10*16+Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,Time[4]/10*16+Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,Time[5]/10*16+Time[5]%10);
	DS1302_WriteByte(DS1302_WEEK,Time[6]/10*16+Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80/10*16+0X80%10);
}

unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i,Byte=0x00;
	DS1302_CE=1;
	Command|=0x01;
	for(i=0;i<8;i++)
	{	
			
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;	
		DS1302_SCLK=1;
	}
	for(i=0;i<8;i++)
	{	
		DS1302_SCLK=1;
		DS1302_SCLK=0;		
		if(DS1302_IO){Byte|=(0x01<<i);}		
	}
	DS1302_CE=0; 
	return Byte;
}

void DS1302_ReadTime(void)
{
	SECOND=DS1302_ReadByte(DS1302_SECOND);
	Time[5]=SECOND/16*10+SECOND%16;
	MINUTE=DS1302_ReadByte(DS1302_MINUTE);
	Time[4]=MINUTE/16*10+MINUTE%16;
	HOUR=DS1302_ReadByte(DS1302_HOUR);
	Time[3]=HOUR/16*10+HOUR%16;
	DATE=DS1302_ReadByte(DS1302_DATE);
	Time[2]=DATE/16*10+DATE%16;
	MONTH=DS1302_ReadByte(DS1302_MONTH);
	Time[1]=MONTH/16*10+MONTH%16;
	YEAR=DS1302_ReadByte(DS1302_YEAR);
	Time[0]=YEAR/16*10+YEAR%16;
	WEEK=DS1302_ReadByte(DS1302_WEEK);
	Time[6]=WEEK/16*10+WEEK%16;
}


