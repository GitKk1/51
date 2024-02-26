#include<reg51.h>
#include"DS1302.H"
#include"LCD1602.H"
#include"DELAY.H"
#include"KEY.H"
#include"TIMER0.H"

sbit led_c=P2^3;
sbit add=P2^0;
sbit subtracat=P2^1;
sbit select=P2^4;

unsigned char Keynum,MODE,Keynum2,TimeSetSelect,Flash;

void Timeshow(void)
{
	LCD_ShowString(1,12,"MODE");
	LCD_ShowString(2,12,"SELE");
	LCD_ShowNum(1,16,MODE,1);
	LCD_ShowNum(2,16,TimeSetSelect,1);
	led_c=1;
	
	DS1302_ReadTime();
	LCD_ShowNum(1,1,Time[0],2);
	LCD_ShowNum(1,4,Time[1],2);
	LCD_ShowNum(1,7,Time[2],2);
	LCD_ShowNum(2,1,Time[3],2);
	LCD_ShowNum(2,4,Time[4],2);
	LCD_ShowNum(2,7,Time[5],2);
}
	
void Timeset(void)
{
	LCD_ShowString(1,12,"MODE");
	LCD_ShowString(2,12,"SELE");
	LCD_ShowNum(1,16,MODE,1);
	LCD_ShowNum(2,16,TimeSetSelect,1);
	led_c=0;
	
	if(Keynum==2)
	{
		TimeSetSelect++;					//切换调整位置	
		TimeSetSelect%=6;
	}
	 
	if(Keynum2==1)
	{
	Time[TimeSetSelect-1]++;
	if(Time[1]>12) {Time[1]=1;}	
	
	if(Time[1]==4||Time[1]==6||Time[1]==9||Time[1]==11) {if(Time[2]>30){Time[2]=1;}}
	else if(Time[1]==2)
	{	
		if(Time[0]%4==0)
		{
			if(Time[2]>29)
			{
				Time[2]=1;	
			}
		}	
		else if(Time[0]%4!=0)
		{
			if(Time[2]>28)
			{Time[2]=1;}
		}

		}		
	else if(Time[1]==1||Time[1]==3||Time[1]==5||Time[1]==7||Time[1]==8||
			Time[1]==10||Time[1]==12) {if(Time[2]>31){Time[2]=1;}}
	if(Time[3]>23) {Time[3]=0;}
	if(Time[4]>60) {Time[4]=0;}		
	}
	
	if(Keynum2==2)	
	{
		Time[TimeSetSelect-1]--; 
		if(Time[1]<1) {Time[1]=12;}	
		
		if(Time[1]==4||Time[1]==6||Time[1]==9||Time[1]==11) {if(Time[2]<1){Time[2]=30;}}
		else if(Time[1]==2)
		{	
			if(Time[0]%4==0)
			{
				if(Time[2]<1)
				{
					Time[2]=29;	
				}
			}	
			else if(Time[0]%4!=0)
			{
				if(Time[2]<1)
				{Time[2]=28;}
			}
		}		
		else if(Time[1]==1||Time[1]==3||Time[1]==5||Time[1]==7||Time[1]==8||
				Time[1]==10||Time[1]==12) {if(Time[2]<1){Time[2]=31;}}	
		if(Time[3]<1) {Time[3]=23;}
		if(Time[4]<1) {Time[4]=59;}			
	}
	

	
	LCD_ShowNum(2,7,Time[5],2);
	
	if(TimeSetSelect==1&&Flash==1) {LCD_ShowString(1,1,"  ");}
	else{LCD_ShowNum(1,1,Time[0],2);}
	if(TimeSetSelect==2&&Flash==1) {LCD_ShowString(1,4,"  ");}
	else{LCD_ShowNum(1,4,Time[1],2);}
	if(TimeSetSelect==3&&Flash==1) {LCD_ShowString(1,7,"  ");}
	else{LCD_ShowNum(1,7,Time[2],2);}
	if(TimeSetSelect==4&&Flash==1) {LCD_ShowString(2,1,"  ");}	
	else{LCD_ShowNum(2,1,Time[3],2);}
	if(TimeSetSelect==5&&Flash==1) {LCD_ShowString(2,4,"  ");}
	else{LCD_ShowNum(2,4,Time[4],2);}
	Time[5]=0;
	DS1302_SetTime();	
}

void main()
{
	Timer_Init();
	LCD_Init();
	DS1302_Init();
	DS1302_SetTime();	
	LCD_ShowString(1,1,"  -  -");
	LCD_ShowString(2,1,"  :  :");
	
	while(1)
	{
		Keynum=Key();
		Keynum2=Key2();
		if(Keynum==1)
		{			
			if(MODE==0){MODE=1;}
			else if(MODE==1){MODE=0;TimeSetSelect=0;}
		}
		
		switch(MODE)
		{
			case 0:Timeshow();break;
			case 1:Timeset();break;
		}				
	}
}


void Timer0_Rountine() interrupt 1  //延时一秒程序示例
{
	static unsigned int T0count;
	TL0 = 0x18;		//设置定时初值   24   0001 1000    176=(65535-50000)%256
	TH0 = 0xFC;		//设置定时初值   252  1111 1100    60=(65536-50000)/256 
	T0count++;
	if(T0count>=500)
	{	
		Flash=!Flash;	
		T0count=0;
	}
}