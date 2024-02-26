#include <REGX51.H>
#include "DELAY.H"
#include "TIMER0.H"

sbit RCLK=P3^5;
sbit SRCLK=P3^6;
sbit SER=P3^4;

unsigned char a;
unsigned char b;
unsigned int c=10;
	
unsigned char code Animation[]=
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x7f,0x08,0x08,0x08,0x7f,0x00,0x0e,0x15,
	0x15,0x15,0x08,0x00,0x7e,0x01,0x02,0x00,
	0x7e,0x01,0x02,0x00,0x0e,0x11,0x11,0x0e,
	0x00,0x7d,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,
};        //每一帧动画

void HC595_WriteByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=Byte&(0x80>>i);
		SRCLK=1;
		SRCLK=0;
	}
	RCLK=1;
	RCLK=0;
}

void MatrixLED_ShowColumn(unsigned char Column,Data)   
{
	HC595_WriteByte(Data);   //74hc595接出高电平，拓展程序，第几行亮
	P1=~(0x80>>Column);    //P1口出低电平，第几列亮
	Delay(2);
	P1=0xff;	
}

void main()
{
	SRCLK=0;
	RCLK=0;    //初始化	

	while(1)
	{
		for(a=0;a<8;a++)
		{
			MatrixLED_ShowColumn(a,Animation[a+b]);    //数码管动态动画显示子程序
		}
		Timer_Init();   //定时器初始化		
		if(b>33)
		{
			b=0;
		}		
	}
}


void Timer0_Rountine() interrupt 1  //延时一秒程序示例
{
	static unsigned int T0count;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256; //1ms
	T0count++;
	if(T0count>=10)
	{
		T0count=0;
		b++;
	}
}
