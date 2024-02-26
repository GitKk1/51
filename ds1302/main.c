#include<reg51.h>
#include"DS1302.H"
#include"LCD1602.H"
	
void main()
{
 
	LCD_Init();
	DS1302_Init();
	DS1302_SetTime();	
	LCD_ShowString(1,1,"  -  -");
	LCD_ShowString(2,1,"  :  :");
	while(1)
	{
		DS1302_ReadTime();
		LCD_ShowNum(1,1,Time[0],2);
		LCD_ShowNum(1,4,Time[1],2);
		LCD_ShowNum(1,7,Time[2],2);
		LCD_ShowNum(2,1,Time[3],2);
		LCD_ShowNum(2,4,Time[4],2);
		LCD_ShowNum(2,7,Time[5],2);
		LCD_ShowNum(1,14,Time[6],2);
		
	}


}