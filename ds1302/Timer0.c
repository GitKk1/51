#include <REGX51.H>


void Timer_Init()  //定时器初始化
{
	TMOD=0x01;  //定时器0,模式1
	TF0=0;  //定时器一处标志位，初始化清0防止错误
	TR0=1;  //启动定时器；
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	ET0=1;
	EA=1;
	
}


/*
void Timer0_Rountine() interrupt 1  //延时一秒程序示例
{
	static unsigned int T0count;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	T0count++;
	if(T0count>=1000)
	{
		T0count=0;
	}
}
*/