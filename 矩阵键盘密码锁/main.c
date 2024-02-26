#include <regx51.h>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum,count;
unsigned int num;

void main()
{
	LCD_Init();	
	while(1)
	{
		LCD_ShowString(1,1,"PASSWORD");
		KeyNum=MatrixKey();
		if(KeyNum) //判断是否有按键按下
		{
			if(KeyNum<=10)//判断是哪个按键按下
			{
				if(count<4)
				{
					num*=10; 
					num+=KeyNum%10; 
					count++;
				}	
			}
		}
		LCD_ShowNum(2,1,num,4);
		if(count==4)
		{
			if(num==6666)
			{
				LCD_ShowString(2,8,"FBIopen");
				count=0;
				Delay(2000);
				LCD_Init();
				num=0;
			}
			else
				
			{
				LCD_ShowString(2,8,"ERROR");
				count=0;
				Delay(2000);
				LCD_Init();
				num=0;
			}
		}		
		
	}
}