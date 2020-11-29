/*

---------- file information -----------------------------------------------
file name: 
define   : <文件说明>
version  : 见文件尾端
---------------------------------------------------------------------------
*/

//全局变量声明
#define  KAKA_Run_GB

#ifdef   CodeC_Includes
#include "PJ_Includes.h"
#else
//#include "LB_hc89f003_IO.h"
#include "..\include\PJ_TypeRedefine.h"
#include "LB_Motor.h"
#include "LB_Run.h"
#include "LB_AD.h"
#include "LB_Led.h"
#include "LB_IR.h"
#endif

/***************************************************************************
	*
	*Function Name:void AutoCharge(void)
	*Function :robot auto look for route be charged batter
	*
	*
***************************************************************************/
void AutoCharge(void)
{
      
	  static INT8U left_ccw,right_cw,line ,costValue,cw_3,ccw_5,compareValue_1;
	  static INT8U compareValue_2,conline=0;
	
	   switch(Step){
		case 0:
                 LedRedON();// 
				 RunMs=0;
				 KeyclearTime=0;
				 Step =1;
	    break;

		case 1:  // Line 
		
			  LedGreenON();
		
			if(ReadPowerDCIn()){ //Be charged detect GPIO
		              
			             AllStop();
						 Step =20 ;
						 LedGreenON();
			 }
			#if 1
			else if(Remote1_ReadIR.ReadCloseList[2]==1){
						
						 RunMs=0;
						 Step=2;			  

			}
			#endif 
            else if(RunMs < 50 && conline ==1)
		    {	
				    SetXMotor(1,10,15,1,1,10,15,1);//SetXMotor(2,10,15,2,2,10,15,2);
			        SetMotorcm(1,50);
					conline=0;
					
			}
			else if(RunMs < 10 && conline ==2 ){
					SetXMotor(1,5,5,1,1,5,5,1);//SetXMotor(2,5,5,2,2,5,5,2);
			        SetMotorcm(1,50);
					conline =0;
					
            }
			else if(RunMs < 5 ){
					SetXMotor(1,1,1,1,1,1,1,1);//SetXMotor(2,1,1,2,2,1,1,2);
			        SetMotorcm(1,50);
					conline =0;
					
            }
			else Step=2;
			
			
	    break;

        case 2: //Adjust line run condition
           
				 AllStop();
				 Delay_ms(10);
				right_cw =0;
				left_ccw = 0;
				ccw_5=0;
				cw_3=0;	
				 Remote1_ReadIR.ReadCloseList[1]=0;
				 Remote1_ReadIR.ReadCloseList[0]=0;
		       
			    costValue++;
				line++ ;
			
				Remote1_ReadIR.ReadASTAR[0][1]=Remote1_ReadIR.Interrupt_IR2;//
				Remote1_ReadIR.ReadASTAR[1][1]=Remote1_ReadIR.ReadIR[0];
				if(costValue ==1)compareValue_1 = Remote1_ReadIR.ReadASTAR[0][1];
				else {
					compareValue_2 = Remote1_ReadIR.ReadASTAR[0][1];
					costValue =0 ;
				}

			   if(line > 9){
				   	RunMs =0;
					Step =10;
					line=0;

			   }
			   {
			  if(Remote1_ReadIR.ReadASTAR[0][1] >= 0x0A){

					      conline =1;
						  RunMs =0 ;
						  Step =0;
                         
				}
			   else if(Remote1_ReadIR.ReadASTAR[0][1] > 0x8){
                        conline =2;
						RunMs =0 ;
						Step =0;
			   }
			    else if(Remote1_ReadIR.ReadASTAR[0][1] > 0){

					   conline =0;
						RunMs =0 ;
						Step =0;

				}
			   else {
                         

				          //直线行走，偏离了目标
						// if(Remote1_ReadIR.ReadASTAR[0][1]< compareValue_2  ){
						{
							#if 0
						 	 if(runcw==0){
	                              RunMs=0;
								  Step=10;
							  }
							  if(runcw==1){
                                 runcw =2;
                                 RunMs=0;
                                 Step =10;
							  } 
                             else
							 #endif 
							 {
								// left IR > right IR
								if(Remote1_ReadIR.ReadASTAR[4][1] >Remote1_ReadIR.ReadASTAR[2][1] ){

									RunMs=0; 
									Step=5;  //CCW run 
								}	
								else if(Remote1_ReadIR.ReadASTAR[4][1] < Remote1_ReadIR.ReadASTAR[2][1]){

										RunMs=0; 
										Step=3;  //CCW run 
											
								}
								
								else if(Remote1_ReadIR.ReadASTAR[0][1] < Remote1_ReadIR.ReadASTAR[2][1]  ){ // CW  IR 
										RunMs=0; 
										Step=3;  //CCW run 
									}
								else if(Remote1_ReadIR.ReadASTAR[0][1] > Remote1_ReadIR.ReadASTAR[2][1] &&  Remote1_ReadIR.ReadASTAR[2][1] !=0) {
											RunMs=0; 
											Step=0;  //CCW run 

									}

									else if(Remote1_ReadIR.ReadASTAR[0][1] < Remote1_ReadIR.ReadASTAR[4][1] ){ //right IR
										
											RunMs=0; 
											Step=5;  //CCW run 
											
									}
									else if(Remote1_ReadIR.ReadASTAR[0][1] > Remote1_ReadIR.ReadASTAR[4][1] &&  Remote1_ReadIR.ReadASTAR[4][1] !=0) {
											RunMs=0; 
											Step=0;  //CCW run 

									}
									else {

										RunMs=0;
										Step=3;

									}
								}
						  }
			            }
			    }	
				
			break;

		case 3: //CW slow Run  //CW motor 90 degree ---??????? 90 ??
		          LedRedON();// 
		         if(ReadPowerDCIn()){ //???????
		              
			               AllStop();
						   Step =20 ;
						   LedGreenON();
				} 	
               else{
					  if(RunMs<5)//To motor move to right dir 
					  {	
							 LedRedON();
							
							 SetXMotor(1,1,1,2,2,1,1,2);//SetXMotor(2,1,1,1,1,1,1,1);
							 SetMotorcm(3,45);
							 
					   }
					   else 
		   	             Step=4;
				  }
				
		break;

	   case 4:  //CW run adjust Ref
                 AllStop();
				 Delay_ms(1);
	             Remote1_ReadIR.ReadCloseList[2]=0;
		  
				
					Remote1_ReadIR.ReadASTAR[2][1]=Remote1_ReadIR.Interrupt_IR2;
					Remote1_ReadIR.ReadASTAR[3][1]=Remote1_ReadIR.ReadIR[0];
			
		           if(Remote1_ReadIR.ReadASTAR[2][1]==0){//close list value 
				 	         
					   Remote1_ReadIR.ReadCloseList[0]=1;
					   
                                right_cw++;
							   if(left_ccw==2){
							   if(right_cw<5){
										RunMs=0; 
										Step=3;  //CCW run 执行4次
									}
							   }
							   else if(right_cw==1){
                                    RunMs =0;
									Step =3;  //执行第二次

							   }
							   else if(right_cw==2){

                                    RunMs=0;
									Step=5;
							   }
							   else {
								   	line = 0;
									RunMs=0; 
									Step=0;  //试探走一步
							   }
							   
					   		
					  Remote1_ReadIR.ReadCloseList[1]=0;
						
				}

                else if(Remote1_ReadIR.ReadASTAR[2][1] >= 0x0A){

						    RunMs=0;
							Step=0;
				           Remote1_ReadIR.ReadCloseList[0]=0; 
						   right_cw =0;
						   left_ccw = 0;
						   conline =1;
							
				 }
				 
				 else if(Remote1_ReadIR.ReadASTAR[2][1] >= Remote1_ReadIR.ReadASTAR[0][1]){
				 	        RunMs=0;
							Step=0;
				            Remote1_ReadIR.ReadCloseList[0]=0; 
							line =0;
							right_cw =0;
						    left_ccw = 0;
							conline=0;
				 }
				 else if(Remote1_ReadIR.ReadASTAR[2][1] < Remote1_ReadIR.ReadASTAR[0][1]){

				        cw_3++;
						if(ccw_5 ==1)
						{
                           if(cw_3 < 4){ //WT.EDIT 
								RunMs =0;
								Step=3;  //再运行 4次 
						   }
						   else if(cw_3==4){
							    RunMs=0;
								Step=0;
								conline=0;
								
						   }
						}
						else if(cw_3==1){
                           RunMs=0; 
					       Step=5;  //CCW run
						}

					   
                 }

			break;

            case 5:
				 //CCW 90 RUN,CCW dir run 
			    if(ReadPowerDCIn()){ //???????
		              
			               AllStop();
						   Step =20 ;
						   LedGreenON();
				} 	
				else{
				 if(ReadPowerDCIn()){ //CCW 90 
		             AllStop();
				 }
				 else if(RunMs <5)//To motor CCW   90 degree
				  {	
					 SetXMotor(2,1,1,2,1,1,1,2); //SetXMotor(1,1,1,1,2,1,1,1);
					  SetMotorcm(4,45);//SetMotorcm(4,45);
					  
				  }
				 else 
				   Step=6;
				}
	    break; 

		case 6:
			     AllStop();

				 Delay_ms(10);
		         Remote1_ReadIR.ReadCloseList[2]=0;
		
		      
					Remote1_ReadIR.ReadASTAR[4][1]=Remote1_ReadIR.Interrupt_IR2;
				    Remote1_ReadIR.ReadASTAR[5][1]=Remote1_ReadIR.ReadIR[0];
				

				if(Remote1_ReadIR.ReadASTAR[4][1]==0){ //CloseList =1


						   left_ccw++;
						   if(right_cw==2){
							   if(left_ccw<5){
										RunMs=0; 
										Step=5;  //CCW run 执行4次
									}
							   }
							   else if(left_ccw==1){
                                    RunMs =0;
									Step =5;  //执行第二次

							   }
							   else if(left_ccw==2){

                                    RunMs=0;
									Step=3;   //to Step3
							   }
							   else {
								
									RunMs=0; 
									Step=0;  //试探走一步
							   }
				}

				else  if(Remote1_ReadIR.ReadASTAR[4][1]   >= 0x0A ){

						    RunMs=0;
							Step=0;
						    conline=1;
				            Remote1_ReadIR.ReadCloseList[1]=0;
							right_cw=0;
							left_ccw=0;
							ccw_5=0;
							cw_3=0;	
							
				}
				else if(Remote1_ReadIR.ReadASTAR[4][1]   > Remote1_ReadIR.ReadASTAR[0][1] ){

							RunMs=0;
							Step=0;
				            Remote1_ReadIR.ReadCloseList[1]=0;
				            line=0;
							right_cw=0;
							left_ccw=0;
							ccw_5=0;
							cw_3=0;	
							conline=0;

				 }
				 else {
						ccw_5++ ;	
					    if(cw_3 ==1)
						{
                           if(ccw_5==1){
								RunMs =0;
								Step=5;  //再运行一次
						   }
						   else if(ccw_5==2){
							    RunMs=0;
								Step=0;
								
						   }
						}
						else if(ccw_5==1){
                           RunMs=0; 
					       Step=3;  //CCW run
						}
					}
	        break;

        case 10://Back run

             if(ReadPowerDCIn()){ //???????
		              
			               AllStop();
						   Step =20 ;
						   LedGreenON();
			} 	
            else{
            	
	             if(RunMs < 10)
			    {	
					   SetXMotor(2,5,5,2,2,5,5,2); // SetXMotor(1,5,5,1,1,5,5,1); 
				        SetMotorcm(1,50);
						
				 }
				 else Step =0;
		}  

        break; 

		case 20:

		 if(Batter_Charging()==1){
		 	Step =20 ;
			            
		 }
		 else  Step =0;

	   break;
		
	}
}

/***************************************************************************
	*
	*Function Name:void  CheckRun()
	*Function :Motor run status 
	*

	*
	*
***************************************************************************/
INT8U Batter_Charging(void)
{

  if(ReadPowerDCIn()){ //???????
		              
           AllStop();
		   Step =20 ;
		   LedGreenON();
           Delay_ms(500);
		   LedGreenOff();
			Delay_ms(500);
		   LedGreenON();
           Delay_ms(500);
		   Step =20;
		
			if(Voltage>820)
			{
                 Mode=0;
		         Step=0;
				LedGreenON();
				Step=20;
	        }
	    return 1 ;  //charge batter
  	  }
      else return 0 ; // don't charging batter
 }

/***************************************************************************
	*
	*Function Name:void  CheckRun()
	*Function :Motor run status 
	*

	*
	*
***************************************************************************/
void  CheckRun()
{

		switch(RunStep)
		{
		case 0:
		{

		}
		break;

        case 0x0D: //To check wheel and barrier wheel of current value
		{

			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))
			{
				ImpSecond=0;
				RunStep=0x0;  //Nothing
				AllStop();
			}
			else 

			if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1); // 倒退顺时针运行,to back cw run
				SetMotorcm(2,10);
				RunMs=0;  //
				RunStep=0;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				SetXMotor(2,10,20,1,2,10,20,1); // 倒退顺时针运行,to back cw run
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=0;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1); // 倒退顺时针运行,to back cw run
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=0;
			}
		}
		break;
		case 0x0c: //检测 motor run status 
		{
			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))
			{
				ImpSecond=0;
				RunStep=0x1;   //GO straight
				AllStop();
			}
			else if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1); //Back to run and CW
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=3;
				Enter3=8;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				SetXMotor(2,10,20,1,2,10,20,1); //be back CCW
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=3;
				Enter3=9;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);//be back CCW
				SetMotorcm(2,10);
				RunMs=0;
				RunStep=3;
				Enter3=10;
			}
		}
		break;

		case 1: //go straight
		{
			ImpSecond=0;
			SetXMotor(1,10,15,1,1,10,15,1);
			SetMotorcm(1,1000);
			RunStep=2;
			RunMs=0;
		}
		break;
		case 2: // CCW 90
		///*
		     if(ImpSecond>5)
			 Imp2Time=0;

			if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x3;
				SetXMotor(2,10,25,1,2,10,25,1); //倒退 CW
				SetMotorcm(2,5);
				RunMs=20;
				Imp2Time++;
				Enter3=1;
			}
			else if(GroundDp[0]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x3;
				SetXMotor(2,10,20,1,1,10,20,1); //CCW 90 ,left don't run and right run
				SetMotorcm(3,45);
				RunMs=0;
				Imp2Time++;
				Enter3=2;
			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x3;
				SetXMotor(1,10,20,1,2,10,20,1); //CW,right run and left wheel don't run.
				SetMotorcm(4,45);
				RunMs=0;
				Imp2Time++;
				Enter3=3;
			}
			else   
			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))//motor run
			{
				NoImpSecond=0;
				RunStep=0x3;
				AllStop();
				RunMs=0;
				Enter3=4;		
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;

				NoImpSecond=0;

				RunStep=0x3;
				AllStop();
				RunMs=0;
				Enter3=5;

			}
            else if(ImpStatus==1)
			{
				Imp2Time++;

				NoImpSecond=0;

				RunStep=0x3;
				AllStop();
				RunMs=0;
				Enter3=6;

			}
			//*/
			break;
		case 3: //到退，CCW
//			if(RunMs>10)
//			{
//			    if(Gong_Step==1)
//			    {
//				  SetXMotor(2,10,20,1,2,10,20,1);
//				  SetMotorcm(2,5);
//				}
//				
//				RunMs=0;
//				RunStep=4;
//			}
//			break;
            if(RunMs>10)
			{
				SetXMotor(2,10,20,1,2,10,20,1);//倒退 CW
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=4;
			}
			break;

		case 4://检测马达运行状态，继续运行
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
			    if((ImpStatus==1))
				{
				AllStop();
				RunMs=0;
				RunStep=3;
				IMPTime++;
				Enter3=11;
				}
				else 
				{
				AllStop();
				RunMs=0;
				RunStep=5;
				IMPTime=0;
				IMPTime=0;
				}
			}
//			else if(Gong_Step==0)
//			{				
//				AllStop();
//				RunMs=0;
//				RunStep=5;
//				IMPTime=0;
//				IMPTime=0;
//				Gong_Step=1;
//			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				NoImpSecond=0;
				RunStep=0x3;
				AllStop();
				RunMs=0;
				Enter3=7;
			}
			break;
		case 5: // CCW  ---left motor don't run and right motor run
			if(RunMs>10)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,90);
				RunMs=0;
				RunStep=6;
			}
			break;

		case 6: //

			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))//motor run ""
			{
				AllStop();
				//InitMotorForward();
				RunMs=0;
				RunStep=7;
				LCurrent=0;
				RCurrent=0;
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				NoImpSecond=0;
				RunStep=3;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				Enter3=12;

			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=20;
				Enter3=13;
			}
			else if(GroundDp[0]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				Enter3=14;
			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Enter3=15;
			}


			break;
		case 7: //go straight
		{
			if(RunMs>10)
			{
				SetXMotor(1,10,20,1,1,10,20,1);
				SetMotorcm(1,20);
				RunMs=0;
				RunStep=8;
				LCurrent=0;
				RCurrent=0;
			}
		}
		break;
		case 8://
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				RunMs=0;
				RunStep=9;

			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=9;
				SetXMotor(2,10,20,1,2,10,20,1); //back run CCW
				SetMotorcm(2,5);
				RunMs=0;
			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				CurrentMax++;
			}
			else if(GroundDp[0]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				Imp2Time++;
			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Imp2Time++;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=9;
			}
			else if((ImpStatus==1))
			{

				Imp2Time++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=9;
			}
			break;
		case 9:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				if(ImpStatus==1)
			   {
			   	  IMPTime++;
				SetXMotor(2,10,20,1,2,10,20,1); //back run CCW
				SetMotorcm(2,5);				  
			   }
			   else
			   {
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,90);
				RunMs=0;
				RunStep=10;
				IMPTime=0;
			   }
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				NoImpSecond=0;
				RunStep=10;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			break;
			break;

		case 10:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{

				{
					//InitMotorForward();
					AllStop();
					RunMs=0;
					RunStep=11;
					LCurrent=0;
					RCurrent=0;
				}
			}
			else if((ImpStatus==1))
			{

				Imp2Time++;
				SetXMotor(2,10,20,1,2,10,20,1); //back run CCW
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=11;
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=11;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				CurrentMax++;
			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=20;
				Enter3=16;
			}
			else if(GroundDp[0]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				Enter3=17;
			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=3;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;
				Enter3=18;
			}

			break;
		case 11: //go straight
			if(RunMs>10)
			{
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,1000);
				RunMs=0;
				RunStep=0x12;
				ImpSecond=0;
				LCurrent=0;
				RCurrent=0;
			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=9;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			break;
		case 0x12:
		{
		   	if(ImpSecond>5)
			 Imp2Time=0;
			 if(RunMs>200)
			   CurrentMax=0;
			if(GroundDp[2]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x13;
				SetXMotor(2,10,20,1,2,10,20,1); //Back run CCW
				SetMotorcm(2,5);
				RunMs=20;

			}
			else if(GroundDp[0]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x13;
				SetXMotor(2,10,20,1,1,10,20,1); //CCW ,left don't move right wheel run
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x13;
				SetXMotor(1,10,20,1,2,10,20,1);//CW ,right run and left don't run
				SetMotorcm(4,45);
				RunMs=0;

			}
 			else   
			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))
			{
				NoImpSecond=0;

				RunStep=0x13;
				AllStop();
				RunMs=0;		
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				CurrentMax++;
				EdgeTime=0;
				NoImpSecond=0;
				RunStep=0x13;
				AllStop();
				RunMs=0;
			}
			else if(ImpStatus==1)
			{

				Imp2Time++;
				EdgeTime=0;
				NoImpSecond=0;
				RunStep=0x13;
				AllStop();
				RunMs=0;
			}
			else  if(RunMs>500)
			{
				CurrentMax=0;
			}
		}
		break;
		case 0x13:
			if(RunMs>10)
			{
				SetXMotor(2,10,20,1,2,10,20,1); //back run CCW
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x14;
			}
			break;

		case 0x14:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
			   if(ImpStatus==1)
			   {
			   	  IMPTime++;
				SetXMotor(2,10,20,1,2,10,20,1); //back run CCW
				SetMotorcm(2,5);				  
			   }
			   else
			   {
				AllStop();
				RunMs=0;
				RunStep=0x15;
				IMPTime=0;
				}
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{

				NoImpSecond=0;
				RunStep=0x15;
				SetXMotor(2,10,20,1,2,10,20,1); //back run CCW
				SetMotorcm(2,5);
				RunMs=0;

			}
			break;
		case 0x15:
			if(RunMs>10)
			{
				SetXMotor(1,10,20,1,2,10,20,1); //CW 
				SetMotorcm(4,90);
				RunMs=0;
				RunStep=0x16;
			}
			break;

		case 0x16:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				//InitMotorForward();
				RunMs=0;
				RunStep=0x17;
				LCurrent=0;
				RCurrent=0;
			}
 			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x14;
				SetXMotor(2,10,20,1,2,10,20,1); //back run 
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x14;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x14;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x14;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}

			break;
		case 0x17: //go straight
		{
			if(RunMs>10)
			{
				SetXMotor(1,10,20,1,1,10,20,1);
				SetMotorcm(1,20);
				RunMs=0;
				RunStep=0x18;
				LCurrent=0;
				RCurrent=0;
			}
		}
		break;
		case 0x18:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				RunMs=0;
				RunStep=0x19;

			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,2,10,20,1); //back CCW
				SetMotorcm(2,5);
				RunMs=0;

			}
			else 	  if(GroundDp[2]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x19;
			}
			else if(ImpStatus==1)
			{
				Imp2Time++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x19;
			}
			break;
		case 0x19:
			if(RunMs>20)
			{
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,90);
				RunMs=0;
				RunStep=0x1a;
			}
			break;

		case 0x1a:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				//InitMotorForward();

				AllStop();
				RunMs=0;
				RunStep=0x1b;
				LCurrent=0;
				RCurrent=0;

			}
						else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else 	  if(GroundDp[2]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}

			break;
		case 0x1b:
			if(RunMs>20)
			{
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,1000);
				RunMs=0;
				RunStep=0x2;
				ImpSecond=0;
				LCurrent=0;
				RCurrent=0;
			}
			else 	  if(GroundDp[2]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{
				Imp2Time++;
				NoImpSecond=0;
				RunStep=0x19;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}

			break;
			//沿墙----WALL 
		case 0x20:
		{
			if(RunMs>20)
			{
				SetXMotor(2,10,20,1,2,10,20,1); //go back CCW
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x21;
			}
		}
		break;
		case 0x21:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				RunMs=0;
				RunStep=0x22;
			}

		}
		break;
		case 0x22:
		{
			if(RunMs>5)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,60);
				RunMs=0;
				RunStep=0x23;
			}
		}
		break;
		case 0x23:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
			   if(ImpStatus==1)
			   {
			   	  IMPTime++;
				SetXMotor(2,10,20,1,2,10,20,1); //be back run CCW
				SetMotorcm(2,5);				  
			   }
			   else
			   {
				AllStop();
				RunMs=0;
				RunStep=0x24;
				IMPTime=0;
				}
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x21;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else 	  if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x21;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
		}
		break;
		case 0x24:
		{
			if(RunMs>10)
			{
				SetXMotor(1,20,20,1,1,10,10,1);
				SetMotorcm(5,100);
				RunMs=0;
				RunStep=0x25;
			}

		}
		break;

		case 0x25:
		{
			if(RunMs>250)
			{
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,1000);
				RunMs=0;
				RunStep=0x26;
			}
			else 	  if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x21;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x22;
				//InitMotorLeftMax();
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x22;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				AllStop();
				NoImpSecond=0;
				RunMs=0;
				RunStep=0x20;
			}
			else if(ImpStatus==1)
			{
				//CurrentMax++;
				AllStop();
				NoImpSecond=0;
				RunMs=0;
				RunStep=0x20;
			}
		}
		break;

		case 0x26:
		{
			if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[0]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x20;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				AllStop();
				NoImpSecond=0;
				RunMs=0;
				RunStep=0x20;
			}
			else if(ImpStatus==1)
			{
				//CurrentMax++;
				AllStop();
				NoImpSecond=0;
				RunMs=0;
				RunStep=0x20;
			}


		}
		break;
		/****************************************************************/
        /****************************************************************/
		/*********************直线行走*****************************/
		case 0x2c: //
		{
			if(RunMs>70)
			{
				ImpSecond=0;
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,1000);
				RunMs=0;
				RunStep=0x21;
			}
			else if((GroundDp[0] >GroundMin)||(GroundDp[2] >GroundMin))//else if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1); //back up run CCW
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x22;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);//back up run CCW
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x22;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);//back up run CCW
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x22;
			}
		}
		break;
		//定点
		case 0x30:
		{
			SetXMotor(2,10,10,1,1,10,10,1);
			SetMotorcm(3,360);
			RunMs=0;
			RunStep=0x31;
			RunSecond=0;
			LCurrent=0;
			RCurrent=0;
		}
		break;
		case 0x31:
		{
			if((LeftMoveMotorData.Flag==1)||(RightMoveMotorData.Flag==1))
			{
				RunSecond=0;
				RunStep=0x32;
				SetXMotor(1,4,4,1,1,15,15,1);
				SetMotorcm(5,1000);
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x38;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin))//||(GroundDp[2]>GroundMin))
			//{//else if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}

			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x32:
		{
			if(RunSecond>5)
			{
				RunSecond=0;
				RunStep=0x33;
				SetXMotor(1,6,6,1,1,20,20,1);
				SetMotorcm(5,1000);
			}
  			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x38;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin))//||(GroundDp[2]>GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}

			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x33:
		{
			if(RunSecond>10)
			{
				RunSecond=0;
				RunStep=0x34;
				SetXMotor(1,8,8,1,1,20,20,1);
				SetMotorcm(5,1000);
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x38;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin))//||(GroundDp[2]>GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}

			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x34:
		{
			if(RunSecond>15)
			{
				RunSecond=0;
				RunStep=0x35;
				SetXMotor(1,10,10,1,1,20,20,1);
				SetMotorcm(5,1000);
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x38;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin)){//||(GroundDp[2]>GroundMin))
			
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x35:
		{
			if(RunSecond>30)
			{
				RunSecond=0;
				RunStep=0x31;
				SetXMotor(2,10,10,1,1,10,10,1);
				SetMotorcm(3,360);
			}
 			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x38;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin)){//||(GroundDp[2]>GroundMin))
			
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		case 0x38:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
			   if(ImpStatus==1)
			   {
			   	  IMPTime++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);				  
			   }
			   else
			   {
				AllStop();
				RunMs=0;
				RunStep=0x39;
				IMPTime=0;
			  }
			}
		}
		break;
		case 0x39:
		{
			if(RunMs>5)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,90);
				RunMs=0;
				RunStep=0x3a;
			}
		}
		break;
		case 0x3a:
		{
			if(RunMs>90)
			{
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,100);
				RunMs=0;
				ImpSecond=0;
				RunStep=0x3b;
				LCurrent=0;
				RCurrent=0;
			}
		}
		break;
		case 0x3b:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				ImpSecond=0;
				RunStep=0x31;
				SetXMotor(2,10,10,1,1,10,10,1);
				SetMotorcm(3,360);
			}
			else if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin))//||(GroundDp[2]>GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		/******************************************************/
		case 0x3c: //CCW 
		{
			if(RunMs>70)
			{
				ImpSecond=0;
				RunStep=0x31;
				SetXMotor(2,10,10,1,1,10,10,1);
				SetMotorcm(3,360);
			}
			else if((GroundDp[0]>GroundMin)||(GroundDp[2]>GroundMin))//||(GroundDp[2]>GroundMin))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				CurrentMax++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
			else if(ImpStatus==1)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x38;
			}
		}
		break;
		//打滑
		case 0x40:
		{
			AllStop();
			RunMs=0;
			RunStep=0x41;
		}
		break;
		case 0x41:
		{
			if(RunMs>5)
			{
				SetXMotor(2,15,15,1,2,15,15,1);
				SetMotorcm(2,20);
				RunMs=0;
				RunStep=0x42;
			}
		}
		break;
		case 0x42:
		{
			if(RunMs>40)
			{
				AllStop();
				RunMs=0;
				RunStep=0x43;
			}
		}
		break;
		case 0x43:
		{
			if(RunMs>40)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				RunStep=0x44;
			}
		}
		break;
		case 0x44:
		{
			if(RunMs>80)
			{
				SetXMotor(1,10,15,1,1,10,15,1);
				SetMotorcm(1,1000);
				RunMs=0;
				RunStep=0x2;
			}
		}
		break;
		//	自由走
		case 0x50:
		{

			SetXMotor(1,10,15,1,1,10,15,1);
			SetMotorcm(1,1000);
			RunStep=0x51;
			LCurrent=0;
			RCurrent=0;
		}
		break;
		case 0x51:
			if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				Imp2Time++;
				if(Imp2Time>4)
				{
					if(Imp2Second<300)
					{
						RunStep=0x20;
						SetXMotor(2,10,20,1,2,10,20,1);
						SetMotorcm(2,5);
					}
					else
					{
						Imp2Second=0;
						Imp2Time=0;
						RunStep=0x52;
						SetXMotor(2,10,20,1,2,10,20,1);
						SetMotorcm(2,5);
					}

				}
				else
				{
					RunStep=0x52;
					SetXMotor(2,10,20,1,2,10,20,1);
					SetMotorcm(2,5);
				}
				RunMs=20;
			}
			else if(GroundDp[0]>GroundMin)
			{

				NoImpSecond=0;
				Imp2Time++;
				if(Imp2Time>4)
				{
					if(Imp2Second<300)
					{
						RunStep=0x20;
						SetXMotor(2,10,20,1,2,10,20,1);
						SetMotorcm(2,5);
					}
					else
					{
						Imp2Second=0;
						Imp2Time=0;
						RunStep=0x52;
						SetXMotor(2,10,20,1,2,10,20,1);
						SetMotorcm(2,5);
					}
				}
				else
				{
					RunStep=0x52;
					SetXMotor(2,10,20,1,1,10,20,1);
					SetMotorcm(3,45);
				}
			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				Imp2Time++;
				if(Imp2Time>4)
				{
					if(Imp2Second<300)
					{
						RunStep=0x20;
						SetXMotor(1,10,20,1,2,10,20,1);
						SetMotorcm(4,45);
					}
					else
					{
						Imp2Second=0;
						Imp2Time=0;
						RunStep=0x52;
						SetXMotor(1,10,20,1,2,10,20,1);
						SetMotorcm(4,45);
					}

				}
				else
				{
					RunStep=0x52;
					SetXMotor(1,10,20,1,2,10,20,1);
					SetMotorcm(4,45);
				}
			}
			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
				NoImpSecond=0;
				Imp2Time++;
				CurrentMax++;
				if(Imp2Time>4)
				{
					if(Imp2Second<300)
					{
						RunStep=0x20;
					}
					else
					{
						Imp2Second=0;
						Imp2Time=0;
						RunStep=0x52;
						AllStop();
					}
				}
				else
				{
					RunStep=0x52;
					AllStop();
				}
				RunMs=0;
			}
			else if(ImpStatus==1)
			{
				NoImpSecond=0;
				Imp2Time++;
				if(Imp2Time>4)
				{
					if(Imp2Second<300)
					{
						RunStep=0x20;
					}
					else
					{
						Imp2Second=0;
						Imp2Time=0;
						RunStep=0x52;
						AllStop();
					}
				}
				else
				{
					RunStep=0x52;
					AllStop();
				}
				RunMs=0;			
			}
			break;
		case 0x52:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x53;
			}
			else if(RunMs>20)
			{
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;
				RunStep=0x53;
			}
			break;

		case 0x53:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
			   if(ImpStatus==1)
			   {
			   	  IMPTime++;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);				  
			   }
			   else
			   {
			   IMPTime=0;
				AllStop();
				RunMs=0;
				RunStep=0x54;
			   }
			}
			break;
		case 0x54:
			if(RunMs>5)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;
				RunStep=0x55;
			}
			break;

		case 0x55:
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				AllStop();
				RunMs=0;
				RunStep=0x56;
			}
 			else
			if((LCurrent>LCurrentMax)||(RCurrent>RCurrentMax))
			{
			    CurrentMax++;
				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(2,10,20,1,2,10,20,1);
				SetMotorcm(2,5);
				RunMs=20;

			}
			else if(GroundDp[0]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,45);
				RunMs=0;

			}
			else if(GroundDp[2]>GroundMin)
			{

				NoImpSecond=0;
				RunStep=0x52;
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,45);
				RunMs=0;

			}
			break;
		case 0x56:
			if(RunMs>50)
			{
				RunMs=0;
				RunStep=0x50;
			}
			break;

			//边扫脱困
		case 0x70:
		{
			SetXMotor(2,10,20,1,2,10,20,1);
			SetMotorcm(2,5);
			RunMs=0;
			RunStep=0x71;
		}
		break;
		case 0x71:
		{
			if(RunMs>40)
			{
				AllStop();
				RunMs=0;
				RunStep=0x72;
			}
		}
		break;
		case 0x72:
		{
			if(RunMs>20)
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,90);
				RunMs=0;
				RunStep=0x73;
			}
		}
		break;

		case 0x73:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,90);
				RunMs=0;
				RunStep=0x74;
			}
		}
		break;
		case 0x74:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				SetXMotor(2,10,20,1,1,10,20,1);
				SetMotorcm(3,90);
				RunMs=0;
				RunStep=0x75;
			}
		}
		break;

		case 0x75:
		{
			if((LeftMoveMotorData.Flag==1)&&(RightMoveMotorData.Flag==1))
			{
				SetXMotor(1,10,20,1,2,10,20,1);
				SetMotorcm(4,90);
				RunMs=0;
				RunStep=0x76;
			}
		}
		break;
		case 0x76:
		{
			if(RunMs>80)
			{
				//InitMotorForward();
				RunMs=0;
				RunStep=0x77;
				//SetEdge(11);
			}

		}
		break;
		case 0x77:
			break;

		}
}
		
/***********************************************************
	*
	*Function Name:void CheckMode(INT8U Key)
	*Function :To check input key of decodes 
	*
	*
	*
************************************************************/
void CheckMode(INT8U Key)
{

	 if(KeydelayTime>3)
     {
	   	   	   //定点
	   if(Key>0)
	   {
		 KeydelayTime=0;
//	     SBUF=Key;
	   }
   switch(Key)
   {
     

	   case 1:
                Mode = 8 ;
			   RunMs = 0x64;
	   
	   case 4:
	   {
	    if(Mode!=2)
		{
	   	  Mode=2;
	   	  Step=0;
		  ModeBackup=0;
		}
	   }
	   break;
	   //启动/暂停
	   case 2:
				
	   //KeyRunTime=0;
	           Mode=3;
	           
			   if(Mode<4)
			   {
			   SetXMotor(1,10,10,1,1,10,10,1);
			   SetMotorcm(1,10);
			   }
			   if(Mode==0)
			   {
				   RunStep=0x0D; //
				  
			   }
			   if(Mode==1)
			   {
				 RunStep=0x0C;//
			   }
			   if(Mode==2)
			   {
				 RunStep=0x3c;//
			   }
			   if(Mode==3)
			   {
				 RunStep=0x2c;//直线
			   }
	      

	   break ;
	   case 7:  //key 
	   {
	     if(ModeBackup!=0)
		 {
		   Mode= ModeBackup;
		   Step=0;	
		   ModeBackup=0;
		 }
	   	  else if((Mode>0)&&(Mode<4))
		  {
	   	    Mode=0;
	   	    Step=0;		  
		  }
		  else if(Mode==0)
		  {
	   	    Mode=1;
	   	    Step=0;			  
		  }
	   }
	   break;
	   //弓形
	   case 3:
	   {
	   	  if(Mode!=1)
		  {
	   	    Mode=1;
	   	    Step=0;	
			ModeBackup=0;		  
		  }
	   }
	   break;
	   //模式切换
	   case 10:
	   {
	   
	   	  Mode++;
		  Step=0;
		  if(Mode>3)
		   Mode=1; //模式 =1 回退功能
		  ModeBackup=0;
	   }
	   break;
	   //前--go straight
	   case 5:
	   {
		 //KeyRunTime=0;
	     if(Mode<4)
		 {
		 SetXMotor(1,10,10,1,1,10,10,1);
		 SetMotorcm(1,10);
		 }
	   	 if(Mode==0)
		 {
		   RunStep=0x0D; //
		 }
	   	 if(Mode==1)
		 {
		   RunStep=0x0C;//
		 }
	   	 if(Mode==2)
		 {
		   RunStep=0x3c;//
		 }
	   	 if(Mode==3)
		 {
		   RunStep=0x2c;//
		 }

	  
	   }
	   break;
	   //左 
	   case 6:
	   {
	      RunMs=0;
	     if(Mode<4)
		 {
		 SetXMotor(2,10,10,1,1,10,10,1);
		 SetMotorcm(3,45);
		 }
	   	 if(Mode==0)
		 {
		   RunStep=0x0D;
		 }
	   	 if(Mode==1)
		 {
		   RunStep=0x0C;
		 }
	   	 if(Mode==2)
		 {
		   RunStep=0x3c;
		 }
	   	 if(Mode==3)
		 {
		   RunStep=0x2c;
		 }
	   }
	   break;
	   //右-to right run 
	   case 8: //key =8 
	   {
		 RunMs=0;
	     if(Mode<4)
		 {
		 SetXMotor(1,10,10,1,2,10,10,1);
		 SetMotorcm(4,45);
		 }
	   	 if(Mode==0)  //
		 {
		   RunStep=0x0D;
		 }
	   	 if(Mode==1)
		 {
		   RunStep=0x0C;
		 }
	   	 if(Mode==2)
		 {
		   RunStep=0x3c;
		 }
	   	 if(Mode==3)
		 {
		   RunStep=0x2c;
		 }
	   }
	   break;
	   //后
	   case 9:
	   {
	     RunMs=0;
	     if(Mode<4)
		 {
		 SetXMotor(2,10,10,1,2,10,10,1);
		 SetMotorcm(2,10);
		 }
	   	 if(Mode==0)
		 {
		   RunStep=0x0D;
		 }
	   	 if(Mode==1)
		 {
		   RunStep=0x0C;
		 }
	   	 if(Mode==2)
		 {
		   RunStep=0x3c;
		 }
	   	 if(Mode==3)
		 {
		   RunStep=0x2c;
		 }
	   }
	   break;
     }	   
   
   }
    switch(Mode)
	{
	  //暂停
	  case 0:
	  {
	   switch(Step)
	   {
	   	 case 0:
				SetFan(0);
				SetEdge(0);
				RunStep=0;
				Step=1;
				RunSecond=0;
				ADCtl=1;
				MotorSpeedIRON();
				AllStop();
		 break;
		 case 1:
		 if(RunSecond>30)
		 {
		   LedGreenOff();
		   Step=2;
		 }
		 break;
		 //电池充电
		 case 2: 
		 if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}
		 break;
	   }
	  }
	  break;
	  //弓形---模式
	  case 1:
	  {
	   switch(Step)
	   {
	   	 case 0:
		 {
		 	RunSecond=0;
			Step=1;
			ADCtl=1;
			LedGreenON();
			AllStop();
			SetIMPOutOn();
			MotorSpeedIRON();
			IMPTime=0;
		 }
		 break;
		 //边缘校正 
		 case 1:
		 {
		 	if(RunSecond>1)
			{
			  Step=2;
				SetFan(255);
				SetEdge(200);
			  RunStep=1;
			}
		 }
		 break;
		 //障碍物
		 case 2:
		 {
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				GroundSecond=0;
			}
			if((RunSecond%30)==0)
			{
				CurrentMax=0;
				RunSecond++;
			}
			//驱动轮
			if(CurrentMax>4)
			{
				Mode=5;
				Step=5;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);			
			}
			//边扫电流
			else if(EdgeCurrentCount>3)
			{
			    EdgeCurrentCount2++;
				if(EdgeCurrentCount2<3)
				{
				   INT8U j=0;
				   LedGreenOff();
				   SetEdge(0);
				   for(EdgeErrordelayTime=0;EdgeErrordelayTime<7;)
                   {
	                   if(EdgeErrordelayTime==0 && j==0)
					   {
					   	 SetXMotor(2,10,10,1,2,10,10,1);
				         SetMotorcm(2,10);
						 LedRedON();
						 j++;
					   }
					   if(EdgeErrordelayTime==2 && j==1)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==3 && j==2)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==4 && j==3)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==5 && j==4)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==6 && j==5)
					   {
					   	 Mode=1;
	   	                 Step=0;
						 LedRedOff();
						 j++;
					   }
	               }
				   EdgeErrordelayTime=0;
				   EdgeCurrentCount=0;
				   j=0;	
				}
				else
				{
				   Mode=5;
				   Step=2;			
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);
				}							
			}
			//风机电流
			else if(FanCurrent>1700)
			{
				Mode=5;
				Step=9;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			//卡壳
			else if(IMPTime>5)
			{
				Mode=5;
				Step=0;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			else if((RunSecond==300)||(Imp2Time>5))
			{
				AllStop();
				RunSecond=301;
				RunStep=0x50;
				CurrentMax=0;
				Imp2Time=0;
				Imp2Second=0;
			}

			else if(RunSecond>360)

			{
			    Imp2Time=0;
				AllStop();
				RunSecond=0;
				RunStep=1;
				RunMs=0;
			}


			else if(Voltage<620)
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
			}

			else if(GroundSecond>1)
			{
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=3;
				ModeBackup=Mode;
				LedRedON();
				RunSecond=0;
			}		 
		 if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}		 
		 }
		 break;
		   case 3:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=4;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }
			if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}
		   }
		   break;
		   case 4:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
				Step=3;
				RunSecond=0;
			 }

		   }
		   break;
	   }	  
	  }
	  break;
	  //定点----清扫
	  case 2:
	  {	 
	    switch(Step)
	     {
	   	 case 0:
		 {
		 	RunSecond=0;
			Step=1;
			LedGreenON();
			AllStop();
			ADCtl=1;
			SetIMPOutOn();
			IMPTime=0;
		 }
		 break;
		 case 1:
		 {
		 	if(RunSecond>1)
			{
			  Step=2;
			  RunStep=0x30;
				SetFan(255);
				SetEdge(200);
			}
		 }
		 break;	
		 case 2:
		 {
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				GroundSecond=0;
			}
			if((RunSecond%30)==0)
			{
				CurrentMax=0;
				RunSecond++;
			}
			//驱动轮
			if(CurrentMax>4)
			{
				Mode=5;
				Step=5;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);			
			}
			//边扫电流
			else if(EdgeCurrentCount>3)
			{
			    EdgeCurrentCount2++;
				if(EdgeCurrentCount2<3)
				{
				   INT8U j=0;
				   LedGreenOff();
				   SetEdge(0);
				   for(EdgeErrordelayTime=0;EdgeErrordelayTime<7;)
                   {
	                   if(EdgeErrordelayTime==0 && j==0)
					   {
					   	 SetXMotor(2,10,10,1,2,10,10,1);
				         SetMotorcm(2,10);
						 LedRedON();
						 j++;
					   }
					   if(EdgeErrordelayTime==2 && j==1)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==3 && j==2)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==4 && j==3)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==5 && j==4)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==6 && j==5)
					   {
					   	 Mode=1;
	   	                 Step=0;
						 LedRedOff();
						 j++;
					   }
	               }
				   EdgeErrordelayTime=0;
				   EdgeCurrentCount=0;
				   j=0;	
				}
				else
				{
				   Mode=5;
				   Step=2;			
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);
				}
//				Mode=5;
//				Step=2;			
//				RunStep=0;
//				RunSecond=0;
//				SetFan(0);
//				SetEdge(0);				
			
			}
			//风机电流
			else if(FanCurrent>1700)
			{
				Mode=5;
				Step=9;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			//卡壳
			else if(IMPTime>5)
			{
				Mode=5;
				Step=0;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			else if(Voltage<620)
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				AllStop();
				SetFan(0);
				SetEdge(0);


			}

			else if(GroundSecond>1)
			{
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=3;
				ModeBackup=Mode;
			}		 
		    if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}		 
		 }
		 break;
		   case 3:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=4;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }
			if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}
		   }
		   break;
		   case 4:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
				Step=3;
				RunSecond=0;
			 }

		   }
		   break;
		 }		   
	  }
	  break;
	  //沿边
	  case 3:
	  {
	    switch(Step)
	     {
	   	 case 0:
		 {
		 	RunSecond=0;
			Step=1;
			LedGreenON();
			AllStop();
			ADCtl=1;
			SetIMPOutOn();
			IMPTime=0;
		 }
		 break;
		 case 1:
		 {
		 	if(RunSecond>1)
			{
			  Step=2;
			  RunStep=0x20;
				SetFan(255);
				SetEdge(200);
			}
		 }
		 break;	
		 case 2:
		 {
			if((GroundDp[0]>GroundMin)||(GroundDp[1]>GroundMin)||(GroundDp[2]>GroundMin))
			{
				GroundSecond=0;
			}
			if((RunSecond%30)==0)
			{
				CurrentMax=0;
				RunSecond++;
			}
			//驱动轮
			if(CurrentMax>4)
			{
				Mode=5;
				Step=5;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);			
			}
			//边扫电流
			else if(EdgeCurrentCount>3)
			{
			    EdgeCurrentCount2++;
				if(EdgeCurrentCount2<3)
				{
				   INT8U j=0;
				   LedGreenOff();
				   SetEdge(0);
				   for(EdgeErrordelayTime=0;EdgeErrordelayTime<7;)
                   {
	                   if(EdgeErrordelayTime==0 && j==0)
					   {
					   	 SetXMotor(2,10,10,1,2,10,10,1);
				         SetMotorcm(2,10);
						 LedRedON();
						 j++;
					   }
					   if(EdgeErrordelayTime==2 && j==1)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==3 && j==2)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==4 && j==3)
					   {
					   	 SetXMotor(1,10,20,1,2,10,20,1);
				         SetMotorcm(4,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==5 && j==4)
					   {
					   	 SetXMotor(2,10,20,1,1,10,20,1);
				         SetMotorcm(3,45);
						 j++;
					   }
					   if(EdgeErrordelayTime==6 && j==5)
					   {
					   	 Mode=1;
	   	                 Step=0;
						 LedRedOff();
						 j++;
					   }
	               }
				   EdgeErrordelayTime=0;
				   EdgeCurrentCount=0;
				   j=0;	
				}
				else
				{
				   Mode=5;
				   Step=2;			
				   RunStep=0;
				   RunSecond=0;
				   SetFan(0);
				   SetEdge(0);
				}
//				Mode=5;
//				Step=2;			
//				RunStep=0;
//				RunSecond=0;
//				SetFan(0);
//				SetEdge(0);				
			}
			//风机电流
			else if(FanCurrent>1700)
			{
				Mode=5;
				Step=9;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			//卡壳
			else if(IMPTime>5)
			{
				Mode=5;
				Step=0;			
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);				
			
			}
			else if(Voltage<620)
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				AllStop();
				SetFan(0);
				SetEdge(0);

			}

			else if(GroundSecond>1)
			{
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=3;
				ModeBackup=Mode;
			}		 
		   if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}		 
		 }
		 break;	
		   case 3:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=4;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }
			if(ReadPowerDCIn())
			{
				Mode=4;
				Step=0;
				RunStep=0;
				RunSecond=0;
				SetFan(0);
				SetEdge(0);
				ADCtl=0;
				AllLedOff();
				AllStop();
			}
		   }
		   break;
		   case 4:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
				Step=3;
				RunSecond=0;
			 }

		   }
		   break;


		 }	   
	  }
	  break;
	  //充电
	  case 4:
	  {
	    switch(Step)
	     {
	   	 case 0:
		 {
			if(ReadPowerDCIn())
			{
			  Step=2;
			}
			if(RunSecond>1)
			{
			   RunSecond=0;
			   Step=1;
			   LedRedON();
			   ADCtl=0;
			   SetBuzzerTime(10);
			}
		 }
		 break;
		 case 1:
		 {
			if(ReadPowerDCIn())
			{
			  Step=2;
			}
			if(RunSecond>1)
			{
			   RunSecond=0;
			   Step=0;
			   LedRedOff();
			}
		 }
		 break;	
		 case 2:
		 {
			if(RunSecond>1)
			{
			   RunSecond=0;
			   Step=3;
			   LedRedON();
			}
		 
		 }
		 break;
		 case 3:
		 {
			if(RunSecond>1) //
			{
			   RunSecond=0;
			   Step=2;
			   LedRedOff();
			}
			if(Voltage>820)
			{
			   Step=4;
			   LedGreenON();
			}					 
		 }
		 break;
		 case 4:
		 {
		 	if(ReadPowerDCIn()==0)
			{
			   Mode=0;
			   Step=0;
			}
		 }
		 break;
		 }	  
	  }
	  break;
	  //故障
	  case 5:
	  {
	    switch(Step)
		{
		   //机器卡住,红灯亮，每隔5秒响一声哔声；
		   case 0:
		   {
		   	  LedRedON();
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=1;
				RunSecond=0;
		   }
		   break;
		   case 1:
		   {
		   	  if(RunSecond>4)
			  {
			  	 RunSecond=0;
				 SetBuzzerTime(5);
			  }
		   }
		   break;
		   //边扫马达堵转  红灯亮，每隔5秒响三声哔声；

		   case 2:
		   {
		   	  LedRedON();
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=3;
				RunSecond=0;
		   }
		   break;
		   case 3:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=4;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }

		   }
		   break;
		   case 4:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
			 }
		   	 if(Run100MSecond==7)
			 {
			    Run100MSecond=0;
				RunSecond=0;
				Step=3;
			 	SetBuzzerTime(5);
			 }
		   }
		   break;
		   //后轮马达堵转 红灯亮，每隔5秒响两声哔声，1秒后响一声哔声；
		   case 5:
		   {
		   	  LedRedON();
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=6;
				RunSecond=0;
		   }
		   break;
		   case 6:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=7;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }

		   }
		   break;
		   case 7:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
			 }
		   	 if(Run100MSecond==7)
			 {
				RunSecond=0;
				Step=8;
			 	SetBuzzerTime(5);
			 }
		   }
		   break;
		   case 8:
		   {
		   	  if(RunSecond>1)
			  {
				 Step=6;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
				 RunSecond=0;
			  }		   
		   
		   }
		   break;
		   //风扇堵转或者电流大	红灯亮，每隔5秒响三声哔声，1秒后响两声哔声；
		   case 9:
		   {
		   	  LedRedON();
				ADCtl=0;
				RunStep=0;
				AllStop();
				SetFan(0);
				SetEdge(0);
				Step=10;
				RunSecond=0;
		   }
		   break;
		   case 10:
		   {
		   	  if(RunSecond>4)
			  {
			  	 //RunSecond=6;
				 Step=11;
				 SetBuzzerTime(5);
				 Run100MSecond=0;
			  }

		   }
		   break;
		   case 11:
		   {
		   	 if(Run100MSecond==3)
			 {
			    Run100MSecond=4;
			 	SetBuzzerTime(5);
			 }
		   	 if(Run100MSecond==7)
			 {
			    Run100MSecond=2;
				RunSecond=0;
				Step=12;
			 	SetBuzzerTime(5);
			 }
		   }
		   break;
		   case 12:
		   {
		   	  if(RunSecond>1)
			  {
				 Step=13;
				 SetBuzzerTime(3);
				 Run100MSecond=0;
				 RunSecond=0;
			  }		   
		   
		   }
		   break;
 		   case 13:
		   {

		   	 if(Run100MSecond==3)
			 {
				RunSecond=0;
				Step=9;
			 	SetBuzzerTime(5);
			 }
		   }
		   break;
		}
	  }
	  break;
	}
}
