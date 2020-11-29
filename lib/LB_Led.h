/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/
#ifndef  LB_Led_h
#define  LB_Led_h



#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else

#include "..\include\PJ_TypeRedefine.h"


#endif


//全局变量声明
#ifdef  KAKA_Led_GB
#define KAKA_Led_EXT
#else
#define  KAKA_Led_EXT extern
#endif

KAKA_Led_EXT  INT8U  ImpStatus;
KAKA_Led_EXT  INT8U  BuzzerFlag;
KAKA_Led_EXT  INT8U  BuzzerTime;

KAKA_Led_EXT  void InitLed(void);
KAKA_Led_EXT  void LedGreenON() ;
KAKA_Led_EXT  void LedGreenOff();
KAKA_Led_EXT  void LedRedON();
KAKA_Led_EXT  void LedRedOff();
KAKA_Led_EXT  void AllLedOff();


KAKA_Led_EXT void InitT1(void);
KAKA_Led_EXT void InitKey(void);
KAKA_Led_EXT INT8U ReadKey(void);
KAKA_Led_EXT void InitPowerIn(void);
KAKA_Led_EXT INT8U ReadPowerDCIn(void);

KAKA_Led_EXT void InitIMP(void);
KAKA_Led_EXT void SetIMPOutOn();
KAKA_Led_EXT void SetIMPOutOff() ;
KAKA_Led_EXT void ReadIMP(void);
KAKA_Led_EXT void InitBuzzer(void);
KAKA_Led_EXT void BuzzerON();
KAKA_Led_EXT void BuzzerOff();
KAKA_Led_EXT void SetBuzzerTime(INT8U time);
KAKA_Led_EXT void CheckBuzzer();


#endif