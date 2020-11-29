/*

---------- file information -----------------------------------------------
file name: 
define   : <ÎÄ¼þËµÃ÷>
version  : ¼ûÎÄ¼þÎ²¶Ë
---------------------------------------------------------------------------
*/

//È«¾Ö±äÁ¿ÉùÃ÷
#define  KAKA_IR_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\HC89F0541.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_IR.h"
#include "..\lib\LB_Usart.h"
#include "LB_Motor.h"
#include "LB_Run.h"

#endif

void Iint_T5(void)
{
 /**********************************TIM5????3?ï¿½ï¿½??ï¿½ï¿½**************************************/
    P1M6 = 0x68;//P3M3 = 0x62;                        //P33ï¿½ï¿½ï¿½ï¿½???aï¿½ï¿½?ï¿½ï¿½-ï¿½ï¿½?ï¿½ï¿½?    
	T5_MAP = 0x16;						//T52????ï¿½ï¿½ï¿½ï¿½3ï¿½ï¿½?P33???ï¿½ï¿½
	T5CON = 0x3F;						//256ï¿½ï¿½Æµï¿½ï¿½16Î»ï¿½Â½ï¿½ï¿½Ø²ï¿½ï¿½ï¿½
	T5CON1 = 0x00;						//T5ï¿½ï¿½ï¿½ï¿½Ñ¡ï¿½ï¿½ T5ï¿½ÅµÄ±ä»¯
	TH5 = 0x00;
	TL5 = 0x00;
	IE1 |= 0x10;						//ï¿½ä¨°?aT5?D??
	EA = 1;



}

void Init_IR()
{

	P1M6 = 0x68;			        	//P16ÉèÖÃÎª´øSMTÉÏÀ­ÊäÈë

 	PITS3 |= 00;//0x30;						//14 
    PINTE1 |= 0x40;						//Ê¹ÄÜINT14

	IE2 |= 0x01;						//´ò¿ªINT8-17ÖÐ¶Ï
	EA=1;
	Remote1_ReadIR.ReadIRFlag=0;


}
void Remote1_Count(void)
{
  if(Remote1_ReadIR.ReadIRFlag==1)
	{
		Remote1_ReadIR.Nowcount++;
		if(Remote1_ReadIR.Nowcount>200)
		{
			Remote1_ReadIR.ReadIRFlag=2;
		}
	}
	
}



 
void Read_Remote1IR(void)
{
	Remote1_ReadIR.NowVoltage=P1_6;

	if(
	    (Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==0)
	)
	{
		Remote1_ReadIR.ReadIRFlag=1;
		Remote1_ReadIR.Nowcount=0;
		Remote1_ReadIR.ReadIRBit=0;
	}
//	else if(
//	    (Remote1_ReadIR.NowVoltage==1)&&(Remote1_ReadIR.ReadIRFlag==1)
//	)
//	{
//		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
//		Remote1_ReadIR.Nowcount=0;
//
//	  Usart1Send[0]=1;
//	  Usart1Send[1]=Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit];
//	  SendCount=1;
//	  SBUF=Usart1Send[SendCount];
//
//		Remote1_ReadIR.ReadIRBit++;
//		if(Remote1_ReadIR.ReadIRBit>80)
//			Remote1_ReadIR.ReadIRFlag=2;
//	}
	else if(
	    (Remote1_ReadIR.NowVoltage==0)&&(Remote1_ReadIR.ReadIRFlag==1)
	)
	{
		Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit]=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Runcontrol=Remote1_ReadIR.Nowcount;
		Remote1_ReadIR.Nowcount=0;

//	  Usart1Send[0]=1;
//	  Usart1Send[1]=Remote1_ReadIR.ReadIRData[Remote1_ReadIR.ReadIRBit];
//	  SendCount=1;
//	  SBUF=Usart1Send[SendCount];

		Remote1_ReadIR.ReadIRBit++;
		if(Remote1_ReadIR.ReadIRBit>32)//if(Remote1_ReadIR.ReadIRBit>80)
			Remote1_ReadIR.ReadIRFlag=2;
	}
}


void CheckXReadIR(ReadIRByte *P)
{
	INT8U k,ReadIR_cnt,FristCodeflag;
	FristCodeflag=0;
	ReadIR_cnt=0;
	P->AABit=0;

	if(P->ReadIRFlag==2)
	{		
		P->ReadIRByte=0;
		k=0;
		if(P->ReadIRData[P->AABit]>1)//if(P->ReadIRData[P->AABit]>120)
		{
			for(P->AABit=1; P->AABit<P->ReadIRBit;P->AABit++)
			{				     
					 if((P->ReadIRData[P->AABit]>0)&&(P->ReadIRData[P->AABit]<=7))
					 {
					 	P->ReadIRByte<<=1;
					    k++;
						if(k>7)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
						    k=0;
						    P->ReadIRByte=0;
//							P->ReadIRFlag=3;

					    }
					 }
					 if((P->ReadIRData[P->AABit]>7)&&(P->ReadIRData[P->AABit]<28))
					 {
					 	P->ReadIRByte<<=1;
						P->ReadIRByte|=1;
					    k++;
						if(k>7)
					    {
						    P->ReadIR[ReadIR_cnt++]=P->ReadIRByte;
						    k=0;
						    P->ReadIRByte=0;
//							P->ReadIRFlag=3;
					    }
					 }
					 if(ReadIR_cnt==4)
					 {
//			    	    Usart1Send[0]=4;
//	                    Usart1Send[1]=P->ReadIR[0];
//						Usart1Send[2]=P->ReadIR[1];
//						Usart1Send[3]=P->ReadIR[2];
//						Usart1Send[4]=P->ReadIR[3];
//	                    SendCount=1;
//	                    SBUF=Usart1Send[SendCount];
						ReadIR_cnt=0;
						FristCodeflag=0;
						P->ReadIRFlag=3;


					 }
			}
			for(P->AABit=0; P->AABit<80; P->AABit++)
			{
			    P->ReadIRData[P->AABit]=0;
			}
		}
	
	}

}
/****************************************************************
***
*Function Name:INT8U CheckHandsetIR()
*Function:
*
*
*****************************************************************/
INT8U CheckHandsetIR()
{
   INT8U KK=0,i =0;
	INT8U N=0;
	INT8U M=0;
	
	CheckXReadIR(&Remote1_ReadIR);
	  #if 1
		Usart1Send[0]=5;
		Usart1Send[1]=Remote1_ReadIR.ReadIR[0];
		Usart1Send[2]=Remote1_ReadIR.ReadIR[1];
		Usart1Send[3]=Remote1_ReadIR.ReadIR[2];
		Usart1Send[4]=Remote1_ReadIR.ReadIR[3];
		Usart1Send[5]=0x88;
		SendCount=1;
		SBUF=Usart1Send[SendCount];
	#endif 

  if(Remote1_ReadIR.ReadIRFlag==3)
   {
   
	//  KeyclearTime=0;
     Remote1_ReadIR.ReadIRFlag=0;
	
	 
	
	 Remote1_ReadIR.ReadIRBit=0; 
	
	
    }
   return(0XFF);
}
/*******************************************************
  * 
  * Function Name:void Delay_ms(INT16U fui_i)
  * Function :
  *           Fcpu = 16MHz delay 1ms
  * 
**************************************************************/
void Delay_ms(INT16U fui_i)
{
	INT16U fui_j;
	for(;fui_i > 0;fui_i --)
	for(fui_j = 1596;fui_j > 0;fui_j --)
	{
		;
	}
}


