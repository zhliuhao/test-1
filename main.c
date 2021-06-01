#include "REG51.h"
#include "oled.h"
#include "ds18b20.h"

#define uchar unsigned char
#define uint unsigned int

sbit k4=P3^4;
sbit k3=P3^5;
sbit k2=P3^6;
sbit k1=P3^7;
sbit beep=P1^7;

sbit j=P3^3;//继电器端口
sbit led1=P0^0;  //定义一个LED 为P1.0 IO口
sbit led11=P0^1; 

 uint num;
 uint aa=0;
 uint bb=0; //确认键
 uint flag=0;

void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=0;//打开定时器			
}



void keypros()
{
	if(k4==0)		  //检测按键K1是否按下
	{	
		delay_ms(100);
		if(k4==0)	  //再次判断按键是否按下
		{
			aa=1;     //模式选择 
			
		}
		while(!k4);	  //检测按键是否松开
	}	
	
  if  (aa==1||aa==2)         // 只有自来水加热完成才能设置 ***纯净水直接加热
{	
	if(k3==0)		  //检测按键K3是否按下
	{	
		delay_ms(100);
		if(k3==0)	  //再次判断按键是否按下
		{
		    num=num+10; 
			if (num==100)
			num=10;
		}
		while(!k3);	  //检测按键是否松开
	}	
	
	
	
			if(k2==0)	  //检测按键K1是否按下
	{	
		delay_ms(100);
		if(k2==0)	  //再次判断按键是否按下
		{
			   bb=1;  //*********确认键
		}
		while(!k1);	  //检测按键是否松开
	}	

}     

	
		if(k1==0)	  //检测按键K1是否按下
	{	
		delay_ms(100);
		if(k1==0)	  //再次判断按键是否按下
		{
			aa=2;     //切换到模式二
		}
		while(!k1);	  //检测按键是否松开
	}	
	
}
//加热到100度并持续加热3分钟
void mode1()
{
      OLED_ShowCHinese(16,0,0);  //自
	  OLED_ShowCHinese(36,0,1);  //来
	  OLED_ShowCHinese(56,0,2);  //水
	  OLED_ShowCHinese(76,0,3);  //除
	  OLED_ShowCHinese(96,0,4);  //氯
	
	  OLED_ShowCHinese(4,6,11);//实
	  OLED_ShowCHinese(22,6,16);//时
	  OLED_ShowCHinese(40,6,12);//温
	  OLED_ShowCHinese(58,6,13);//度
	  
	  OLED_ShowCHinese(4,4,14);//设
	  OLED_ShowCHinese(22,4,15);//置
	  OLED_ShowCHinese(40,4,12);//温
	  OLED_ShowCHinese(58,4,13);//度
	
	  OLED_ShowNum(94,4,num,3,16);   //显示温度 
	
      OLED_ShowCHinese(112,6,5);//℃
	  OLED_ShowNum(86,6,temp/1000,1,16);   //显示温度百分位
	  OLED_ShowNum(94,6,temp/100,1,16);   //显示温度   
      OLED_ShowNum(102,6,temp%100/10,1,16);//显示温度
	  
	  
        if ((temp/1000>=1)&&(temp%100/10>=0))//设定温度值，使其加热
		{
	 	TR0=1;           //打开定时器中断
		beep=0;           //蜂鸣器响
		}

		if (flag==0)    //自动加热
		{
			led1=1;     //红灯亮
			led11=0;
			j=1;        // 继电器跳，加热
		}
		}
		


void mode2()
{
      OLED_ShowCHinese(16,0,6);  //纯净水
	  OLED_ShowCHinese(36,0,7);  //
	  OLED_ShowCHinese(56,0,8);  //
	  OLED_ShowCHinese(76,0,9);  //加热
	  OLED_ShowCHinese(96,0,10); //
	
	  OLED_ShowCHinese(4,6,11); //实
	  OLED_ShowCHinese(22,6,16);//时
	  OLED_ShowCHinese(40,6,12);//温
	  OLED_ShowCHinese(58,6,13);//度
	
	  OLED_ShowCHinese(4,4,14); //设
	  OLED_ShowCHinese(22,4,15);//置
	  OLED_ShowCHinese(40,4,12);//温
	  OLED_ShowCHinese(58,4,13);//度
	 
	  OLED_ShowNum(94,4,num,3,16);   //显示温度 
      OLED_ShowCHinese(112,6,5);           //℃
	  OLED_ShowNum(86,6,temp/1000,1,16);   //显示温度百分位
	  OLED_ShowNum(94,6,temp/100,1,16);    //显示温度   
      OLED_ShowNum(102,6,temp%100/10,1,16);//显示温度	
}

 int main(void)
 {	
	  j=0;                    //初始状态继电器 
	  OLED_Init();			//初始化OLED  
      OLED_Clear(0); 
      init_18b20();           //初始化ds18b20
	  Timer0Init(); 
	  beep=1;
	  OLED_ShowCHinese(16,0,17);  //自
	  OLED_ShowCHinese(36,0,18);  //来
	 
  while(1) 
	{		
        keypros();              //按键扫描
		get_temp();             //获取温度值
		
		switch (aa)             //模式切换
	{

		case  1:  mode1();break;//模式1 开始加热到100摄氏度
		case  2:  mode2();break;//模式1 开始加热到100摄氏
	}
	
		 if (flag==1||aa==2)  //加热完成
		{
		 led1=0; //灯关
	     led11=0;
		 beep=1;//蜂鸣 器报警关闭
		 j=0;	 //加热关闭
			
	     if ((temp/100<num/10)&&bb==1) //设定温度&&(temp%100/10)
		 {
			led1=1;     //红灯亮
			led11=0;
			j=1;        // 继电器跳，加热			
         }	
	    }	  
    }
 }
 
 
void Timer() interrupt 1 //沸腾再煮3分钟
{
	static uint i;
	TH0=0XFC;	         //给定时器赋初值，定时1ms
	TL0=0X18;
	i++;
	
	if(i==6000)          // 6秒
	{
		i=0;			
		TR0=0;	
		flag=1;
	}	
	
}
		
