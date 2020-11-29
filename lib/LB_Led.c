/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_Led_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Led.h"

#endif

void InitT1(void)
{
	TCON1 = 0x00;						//T1定时器时钟为Fosc
	TMOD = 0x00;						//16位重装载定时器/计数器

	//Tim1计算时间 	= (65536 - 0xFACB) * (1 / (Fosc /Timer分频系数))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//定时0.1ms
	//反推初值 	= 65536 - ((1/10000) / (1/(Fosc / Timer分频系数)))
	//		   	= 65536 - ((1/10000) / (1/(16000000 / 12)))
	//			= 65536 - 133
	//			= 0xFf78
	TH1 = 0xFf;
	TL1 = 0x78;
	IE |= 0x08;							//打开T1中断
	TCON |= 0x40;						//使能T1
    
	EA = 1;	

}

void InitLed(void)
{
  P2M3=0X84;
  P3M3=0X84;
  P3_3=1;
  P2_3=1;
}



void LedGreenON()
{
  P3_3=0;
  P2_3=1;
}


void LedGreenOff()
{
  P3_3=1;
}

void LedRedON()
{
  P3_3=1;
  P2_3=0;
}


void LedRedOff()
{
  P2_3=1;
}
void AllLedOff()
{
  P3_3=1;
  P2_3=1;
}

void InitKey(void)
{
  P0M0 = 0x60;                        //P00设置为施密特数字带上拉输入
  P3M2 = 0x60;                        //P32设置为施密特数字带上拉输入
  P0_0=1;
  P3_2=1;

}

void InitIMP(void)
{
  P2M1 = 0x60;                        //P01设置为施密特数字带上拉输入
  P2M0 = 0xC2;                        //P21
  P2_0=0;
  //P2_1=0;

}
void SetIMPOutOn()
{
  P2_0=1;
}

 void SetIMPOutOff()
{
  P2_0=0;
}

void ReadIMP(void)
{
  if(P2_1)
  ImpStatus=1;
  else
  ImpStatus=0;
}

INT8U ReadKey(void)
{

  static INT8U  K1temp,K2temp,K12temp;
  INT8U t_Key;
  t_Key=0;
  if(P3_2==0 && P0_0==0){  //WT.EDIT --right key
		if(K12temp<200)
	   	 K12temp++;
		 BuzzerON();
 }
 else if(K12temp==190) //WT.EDIT 
 {
	    K12temp=201;
		t_Key|=4;
		BuzzerOff();
  }
  else{
	  if(P3_2==0)
	  {
	    if(K1temp<200)
	   	 K1temp++;
		 BuzzerON();
	  }
	  else	
	  {	  

	   	K1temp=0;
		BuzzerOff();
	  }

	  if(P0_0==0)
	  {
	    if(K2temp<200)
	   	 K2temp++;
		 BuzzerON();
	  }
	  else	
	  {	  

	   	K2temp=0;
		BuzzerOff();
	  }


	  if(K1temp==190)
	  {
	    K1temp=201;
	   //return(1);
		t_Key|=1;
	  }
	  if(K2temp==190)
	  {
	    K2temp=201;
	   //return(1);
		t_Key|=2;
	  }
  }
  return(t_Key);  
}
void InitPowerIn(void)
{
  P1M7 = 0x60; 
  P1M0 = 0x50;                        //P10设置为施密特数字带上拉输入
  P1_0=1;

}

/**************************************************************
  *
  *Function Name:INT8U ReadPowerDCIn(void) 
  *Function :Batter to charged 
  *
  *
  *
**************************************************************/
 INT8U ReadPowerDCIn(void)
{
  return(P1_0);
}


void InitBuzzer(void)
{

    P2M2 = 0xC2;                        //P35设置为推挽输出
	PWM3_MAP = 0x22;					//PWM3映射P35口
	//周期计算 	= 0xFF / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0xFF /(16000000 / 4)			
	// 			= 255 /4000000
	//			= 63.75us		即15.69KHZ		

	PWM3P = 0xc4;						//PWM周期为0xFF
	//有效电平时间计算（即占空比） 	
	//			= 0x55 / (Fosc / PWM分频系数)		（Fosc见系统时钟配置的部分）
	//			= 0x55 /(16000000 / 4)			
	// 			= 85 /4000000
	//			= 21.25us		占空比为 21.25 / 63.75 = 34%

	PWM3D = 0x30;						//PWM占空比设置
	PWM3C = 0x06; 						//使能PWM3，关闭中断，允许输出，时钟32分频	


//  P2M2 = 0x84;                        //P01设置为施密特数字带上拉输入
//  P2_2=0;

}
void BuzzerON()
{
  BuzzerFlag=1;
  SetBuzzerTime(4);
//  PWM3C = 0x96; 						//使能PWM3，关闭中断，允许输出，时钟32分频
//  P2_2=0;
}


void BuzzerOff()
{
  BuzzerFlag=0;
//  PWM3C = 0x06; 						//使能PWM3，关闭中断，允许输出，时钟32分频
//  P2_2=1;
}

void SetBuzzerTime(INT8U time)
{
	BuzzerTime=time;
	
	PWM3C = 0x96; 						//使能PWM3，关闭中断，允许输出，时钟32分频	
}

void CheckBuzzer()
{
   if(BuzzerTime<200)
   {
     
     BuzzerTime--;

	 if(BuzzerTime<1)
	 {
	   PWM3C = 0x06; 						//使能PWM3，关闭中断，允许输出，时钟32分频	
	 }
   }
}
