/*

---------- file information -----------------------------------------------
file name: 
define   : <ÎÄ¼şËµÃ÷>
version  : ¼ûÎÄ¼şÎ²¶Ë
---------------------------------------------------------------------------
*/
#ifndef  LB_IR_h
#define  LB_IR_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//È«¾Ö±äÁ¿ÉùÃ÷
#ifdef  KAKA_IR_GB
#define KAKA_IR_EXT
#else
#define  KAKA_IR_EXT extern
#endif

 typedef struct
{
	INT8U  NowVoltage;
	INT16U  Nowcount;
	INT8U  ReadIRBit;
	INT8U  ReadIRFlag;
	INT8U  ReadIRByte;
	INT8U  AABit;
	INT8U  ReadIR[4];
	INT8U  ReadASTAR[6][2]; //
	INT8U  ReadOpenList[8];  //æ‰§è¡Œå¼€å‘åˆ—è¡¨çš„å€¼ï¼Œ
	INT8U  ReadCloseList[8];  //å…³é—­åˆ—è¡¨å€¼ï¼Œä¸å†æ‰§è¡Œï¼Œè¾¹ç•Œ
	INT8U  ReadIRData[80];
	INT8U  Runcontrol;
	INT8U  Interrupt_IR2; //WT.EDIT 

} ReadIRByte ;

KAKA_IR_EXT	 xdata ReadIRByte Remote1_ReadIR;



KAKA_IR_EXT void Init_IR();
KAKA_IR_EXT void Iint_T5(void);

KAKA_IR_EXT void Remote1_Count(void);
KAKA_IR_EXT void Read_Remote1IR();

KAKA_IR_EXT INT8U CheckHandsetIR();
KAKA_IR_EXT  void Delay_ms(INT16U fui_i);

#endif