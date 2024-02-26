#include<reg51.h>
#include"DS1302.H"
#include"LCD1602.H"
#include"DELAY.H"
#include"KEY.H"

sbit led_c=P2^3;

extern Keynum,MODE,Keynum2;

unsigned char TimeSetSelect;

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
	Keynum2=Key2();
	Keynum=Key();
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
	if(Keynum2==1) Time[TimeSetSelect-1]++;		//1:set year	2:set month 3:set date 	
	if(Keynum2==2) Time[TimeSetSelect-1]--;  	//4:set hour  5:set minute
		
	Time[5]=0;
	DS1302_SetTime();

	
}