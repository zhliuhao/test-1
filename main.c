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

sbit j=P3^3;//�̵����˿�
sbit led1=P0^0;  //����һ��LED ΪP1.0 IO��
sbit led11=P0^1; 

 uint num;
 uint aa=0;
 uint bb=0; //ȷ�ϼ�
 uint flag=0;

void Timer0Init()
{
	TMOD|=0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������
	TH0=0XFC;	//����ʱ������ֵ����ʱ1ms
	TL0=0X18;	
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=0;//�򿪶�ʱ��			
}



void keypros()
{
	if(k4==0)		  //��ⰴ��K1�Ƿ���
	{	
		delay_ms(100);
		if(k4==0)	  //�ٴ��жϰ����Ƿ���
		{
			aa=1;     //ģʽѡ�� 
			
		}
		while(!k4);	  //��ⰴ���Ƿ��ɿ�
	}	
	
  if  (aa==1||aa==2)         // ֻ������ˮ������ɲ������� ***����ˮֱ�Ӽ���
{	
	if(k3==0)		  //��ⰴ��K3�Ƿ���
	{	
		delay_ms(100);
		if(k3==0)	  //�ٴ��жϰ����Ƿ���
		{
		    num=num+10; 
			if (num==100)
			num=10;
		}
		while(!k3);	  //��ⰴ���Ƿ��ɿ�
	}	
	
	
	
			if(k2==0)	  //��ⰴ��K1�Ƿ���
	{	
		delay_ms(100);
		if(k2==0)	  //�ٴ��жϰ����Ƿ���
		{
			   bb=1;  //*********ȷ�ϼ�
		}
		while(!k1);	  //��ⰴ���Ƿ��ɿ�
	}	

}     

	
		if(k1==0)	  //��ⰴ��K1�Ƿ���
	{	
		delay_ms(100);
		if(k1==0)	  //�ٴ��жϰ����Ƿ���
		{
			aa=2;     //�л���ģʽ��
		}
		while(!k1);	  //��ⰴ���Ƿ��ɿ�
	}	
	
}
//���ȵ�100�Ȳ���������3����
void mode1()
{
      OLED_ShowCHinese(16,0,0);  //��
	  OLED_ShowCHinese(36,0,1);  //��
	  OLED_ShowCHinese(56,0,2);  //ˮ
	  OLED_ShowCHinese(76,0,3);  //��
	  OLED_ShowCHinese(96,0,4);  //��
	
	  OLED_ShowCHinese(4,6,11);//ʵ
	  OLED_ShowCHinese(22,6,16);//ʱ
	  OLED_ShowCHinese(40,6,12);//��
	  OLED_ShowCHinese(58,6,13);//��
	  
	  OLED_ShowCHinese(4,4,14);//��
	  OLED_ShowCHinese(22,4,15);//��
	  OLED_ShowCHinese(40,4,12);//��
	  OLED_ShowCHinese(58,4,13);//��
	
	  OLED_ShowNum(94,4,num,3,16);   //��ʾ�¶� 
	
      OLED_ShowCHinese(112,6,5);//��
	  OLED_ShowNum(86,6,temp/1000,1,16);   //��ʾ�¶Ȱٷ�λ
	  OLED_ShowNum(94,6,temp/100,1,16);   //��ʾ�¶�   
      OLED_ShowNum(102,6,temp%100/10,1,16);//��ʾ�¶�
	  
	  
        if ((temp/1000>=1)&&(temp%100/10>=0))//�趨�¶�ֵ��ʹ�����
		{
	 	TR0=1;           //�򿪶�ʱ���ж�
		beep=0;           //��������
		}

		if (flag==0)    //�Զ�����
		{
			led1=1;     //�����
			led11=0;
			j=1;        // �̵�����������
		}
		}
		


void mode2()
{
      OLED_ShowCHinese(16,0,6);  //����ˮ
	  OLED_ShowCHinese(36,0,7);  //
	  OLED_ShowCHinese(56,0,8);  //
	  OLED_ShowCHinese(76,0,9);  //����
	  OLED_ShowCHinese(96,0,10); //
	
	  OLED_ShowCHinese(4,6,11); //ʵ
	  OLED_ShowCHinese(22,6,16);//ʱ
	  OLED_ShowCHinese(40,6,12);//��
	  OLED_ShowCHinese(58,6,13);//��
	
	  OLED_ShowCHinese(4,4,14); //��
	  OLED_ShowCHinese(22,4,15);//��
	  OLED_ShowCHinese(40,4,12);//��
	  OLED_ShowCHinese(58,4,13);//��
	 
	  OLED_ShowNum(94,4,num,3,16);   //��ʾ�¶� 
      OLED_ShowCHinese(112,6,5);           //��
	  OLED_ShowNum(86,6,temp/1000,1,16);   //��ʾ�¶Ȱٷ�λ
	  OLED_ShowNum(94,6,temp/100,1,16);    //��ʾ�¶�   
      OLED_ShowNum(102,6,temp%100/10,1,16);//��ʾ�¶�	
}

 int main(void)
 {	
	  j=0;                    //��ʼ״̬�̵��� 
	  OLED_Init();			//��ʼ��OLED  
      OLED_Clear(0); 
      init_18b20();           //��ʼ��ds18b20
	  Timer0Init(); 
	  beep=1;
	  OLED_ShowCHinese(16,0,17);  //��
	  OLED_ShowCHinese(36,0,18);  //��
	 
  while(1) 
	{		
        keypros();              //����ɨ��
		get_temp();             //��ȡ�¶�ֵ
		
		switch (aa)             //ģʽ�л�
	{

		case  1:  mode1();break;//ģʽ1 ��ʼ���ȵ�100���϶�
		case  2:  mode2();break;//ģʽ1 ��ʼ���ȵ�100����
	}
	
		 if (flag==1||aa==2)  //�������
		{
		 led1=0; //�ƹ�
	     led11=0;
		 beep=1;//���� �������ر�
		 j=0;	 //���ȹر�
			
	     if ((temp/100<num/10)&&bb==1) //�趨�¶�&&(temp%100/10)
		 {
			led1=1;     //�����
			led11=0;
			j=1;        // �̵�����������			
         }	
	    }	  
    }
 }
 
 
void Timer() interrupt 1 //��������3����
{
	static uint i;
	TH0=0XFC;	         //����ʱ������ֵ����ʱ1ms
	TL0=0X18;
	i++;
	
	if(i==6000)          // 6��
	{
		i=0;			
		TR0=0;	
		flag=1;
	}	
	
}
		
