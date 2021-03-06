
#include <p30fxxxx.h>

#include  "door.h"
#include  "iodef.h"
#include  "default_setup.h"


extern 	__attribute__((section(".usercode"))) UserDataType SubDoorFlrChk(void);



////////////////////////////////////////////
LocalType	__attribute__((section(".usercode"))) MainSubDoorFlrChk(LocalType flr)
{
    LocalType i,j,k;
  
	i=0x0;
    k=0x0;

	if(flr > 0){
	    i=flr/4;
	    k=flr%4;
		k=k*2;
	}

    j=0;

    switch(i){
        case    0:
            j=cF_SUBDOORFLR1;
            break;
        case    1:
            j=cF_SUBDOORFLR2;
            break;
        case    2:
            j=cF_SUBDOORFLR3;
            break;
        case    3:        
            j=cF_SUBDOORFLR4;
            break;
        case    4:
            j=cF_SUBDOORFLR5;
            break;
        case    5:
            j=cF_SUBDOORFLR6;
            break;
        case    6:
            j=cF_SUBDOORFLR7;
            break;
        case    7:        
            j=cF_SUBDOORFLR8;
            break;
        case    8:
            j=cF_SUBDOORFLR9;
            break;
        case    9:
            j=cF_SUBDOORFLR10;
            break;
        case    10:
            j=cF_SUBDOORFLR11;
            break;
        case    11:        
            j=cF_SUBDOORFLR12;
            break;
        case    12:
            j=cF_SUBDOORFLR13;
            break;
        case    13:
            j=cF_SUBDOORFLR14;
            break;
        case    14:
            j=cF_SUBDOORFLR15;
            break;
        case    15:        
            j=cF_SUBDOORFLR16;
            break;
    }

    j=(j >> k);
    j=(j & 0x03);

	return(j);
}	




UserDataType __attribute__((section(".usercode"))) NoUseNoOpen(void)
{
    LocalType i,j,k;
          
	if(OnlyOneCallOnOffChk)	return(1);		// modify            

    i=sRamDArry[mcurfloor]/8;
    j=sRamDArry[mcurfloor]%8;
    k=0x01;
    k = (k << j);

	#ifdef	FLOOR_64
	switch(i){
		case	0:
		    if(sRamDArry[FLR_ON_OFF0] & k)  return(1);
		    else                            return(0);
			break;   											
		case	1:
		    if(sRamDArry[FLR_ON_OFF1] & k)  return(1);
		    else                            return(0);
			break;   
		case	2:
		    if(sRamDArry[FLR_ON_OFF2] & k)  return(1);
		    else                            return(0);
			break;   
		case	3:
		    if(sRamDArry[FLR_ON_OFF3] & k)  return(1);
		    else                            return(0);
			break;   
		case	4:
		    if(sRamDArry[FLR_ON_OFF4] & k)  return(1);
		    else                            return(0);
			break;   
		case	5:
		    if(sRamDArry[FLR_ON_OFF5] & k)  return(1);
		    else                            return(0);
			break;   
		case	6:
		    if(sRamDArry[FLR_ON_OFF6] & k)  return(1);
		    else                            return(0);
			break;   
		case	7:
		    if(sRamDArry[FLR_ON_OFF7] & k)  return(1);
		    else                            return(0);
			break;
		default:
			return(0);   

	}
	#else
    if(sRamDArry[FLR_ON_OFF0+i] & k)  return(1);
    else                              return(0);   
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////



/*
////////////////////////////////////////////////////////////
void	__attribute__((section(".usercode"))) CurDoorSelChk(void)
{

//    if((CurDoorSelect == NO_DOOR) && !bDoorCloseOk)
    
}
*/
////////////////////////////////////////////////////////////





void	__attribute__((section(".usercode"))) ValidDoorSel(void)
{
	LocalType i;

	i=MainSubDoorFlrChk(sRamDArry[mcurfloor]);

    switch(i)
    {
        case    NO_DOOR:
            NewDoorSelect=NO_DOOR;
            break;
        case    MAIN_DOOR:
            NewDoorSelect=MAIN_DOOR;
            break;
        case    SUB_DOOR:
            NewDoorSelect=SUB_DOOR;
            break;
        case    MAIN_SUB_DOOR:
            NewDoorSelect=MAIN_SUB_DOOR;
            break;
    }

	if(!NoUseNoOpen())      NewDoorSelect=NO_DOOR;

    if(NewDoorSelect==NO_DOOR){
        NewDoorSelect = NO_DOOR;
        CurDoorSelect = NewDoorSelect;

		sRamDArry[mDoor]    = (sRamDArry[mDoor] & CLEAR_ALL_DOOR_KEY);   
    }  
}




UserDataType	__attribute__((section(".usercode"))) OpenKeyCheck(void)
{
	LocalType ret;

    ret=1;

	if(bDoorSlowExe){
		sRamDArry[mDoor]    = (sRamDArry[mDoor] & MAIN_SUB_OPEN_KEY_CLEAR);   
	}


    ValidDoorSel();

    switch(NewDoorSelect)
    {
        case    MAIN_DOOR:
            if((sRamDArry[mDoor] & MAIN_OPEN_KEY) || (sRamDArry[mDoor] & SUB_OPEN_KEY)){ 
                NewDoorSelect = MAIN_DOOR;
                CurDoorSelect = NewDoorSelect;            
                LoopTime=0;
                ret=0;
            }
            break;
        case    SUB_DOOR:
            if((sRamDArry[mDoor] & MAIN_OPEN_KEY) || (sRamDArry[mDoor] & SUB_OPEN_KEY)){ 
                NewDoorSelect = SUB_DOOR;
                CurDoorSelect = NewDoorSelect;            
                LoopTime=0;
                ret=0;
            }
            break;
        case    MAIN_SUB_DOOR:
            if(sRamDArry[mDoor] & MAIN_OPEN_KEY){
                if( (CurDoorSelect !=  SUB_DOOR) || (bDoorCloseOk)){		//ver6.AH->ver6.AI  
                    NewDoorSelect = MAIN_DOOR;
                    CurDoorSelect = NewDoorSelect;
                    LoopTime=0;
                    ret=0;
                }
            } 
            else if(sRamDArry[mDoor] & SUB_OPEN_KEY){
                if( (CurDoorSelect !=  MAIN_DOOR)  || (bDoorCloseOk)){  	//ver6.AH->ver6.AI 
                    NewDoorSelect = SUB_DOOR;
                    CurDoorSelect = NewDoorSelect;
                    LoopTime=0;
                    ret=0;
                }
            } 
            break;
    }

    return(ret);
}



UserDataType	__attribute__((section(".usercode"))) CloseKeyCheck(void)
{
	LocalType ret;

    ret=1;

    if((sRamDArry[mDoor] & MAIN_OPEN_KEY) || (sRamDArry[mDoor] & SUB_OPEN_KEY)){
		sRamDArry[mDoor]= (sRamDArry[mDoor] & MAIN_SUB_CLOSE_KEY_CLEAR);        
    }
    else{
        ValidDoorSel();
    
        switch(NewDoorSelect)
        {
            case    MAIN_DOOR:
                if((sRamDArry[mDoor] & MAIN_CLOSE_KEY) || (sRamDArry[mDoor] & SUB_CLOSE_KEY)){ 
                    NewDoorSelect = MAIN_DOOR;
                    CurDoorSelect = NewDoorSelect;            
                    ret=0;
                }
                break;
            case    SUB_DOOR:
                if((sRamDArry[mDoor] & MAIN_CLOSE_KEY) || (sRamDArry[mDoor] & SUB_CLOSE_KEY)){ 
                    NewDoorSelect = SUB_DOOR;
                    CurDoorSelect = NewDoorSelect;            
                    ret=0;
                }
                break;
            case    MAIN_SUB_DOOR:
                if((sRamDArry[mDoor] & MAIN_CLOSE_KEY) || (sRamDArry[mDoor] & SUB_CLOSE_KEY)){ 
                	ret=0;
				}

/*
                if(sRamDArry[mDoor] & MAIN_CLOSE_KEY){
                    if(CurDoorSelect !=  SUB_DOOR){  
                        NewDoorSelect = MAIN_DOOR;
                        CurDoorSelect = NewDoorSelect;
                        ret=0;
                    }
                } 
                else if(sRamDArry[mDoor] & SUB_CLOSE_KEY){
                    if(CurDoorSelect !=  MAIN_DOOR){  
                        NewDoorSelect = SUB_DOOR;
                        CurDoorSelect = NewDoorSelect;
                        ret=0;
                    }
                } 
*/
                break;
        }
    }

    return(ret);
}




UserDataType	__attribute__((section(".usercode"))) OpenKeyClear(void)
{

    ValidDoorSel();

    switch(NewDoorSelect)
    {
        case    MAIN_DOOR:
			sRamDArry[mDoor]    = (sRamDArry[mDoor] & MAIN_SUB_OPEN_KEY_CLEAR);   
            break;
        case    SUB_DOOR:
			sRamDArry[mDoor]    = (sRamDArry[mDoor] & MAIN_SUB_OPEN_KEY_CLEAR);   
            break;
        case    MAIN_SUB_DOOR:
            if(CurDoorSelect == MAIN_DOOR){
				sRamDArry[mDoor]    = (sRamDArry[mDoor] & MAIN_OPEN_KEY_CLEAR);   
            } 
            else if(CurDoorSelect ==  SUB_DOOR){  
				sRamDArry[mDoor]    = (sRamDArry[mDoor] & SUB_OPEN_KEY_CLEAR);   
            } 
            break;
    }

    return(0);
}




UserDataType	__attribute__((section(".usercode"))) OneDoorSelOpenKeyCheck(void)
{
	LocalType ret;

    ret=1;

    ValidDoorSel();

    switch(NewDoorSelect)
    {
        case    MAIN_DOOR:
//            if( !(sRamDArry[mDoor] & MAIN_OPEN_KEY) && !(sRamDArry[mDoor] & SUB_OPEN_KEY)){ 
                NewDoorSelect = MAIN_DOOR;
                CurDoorSelect = NewDoorSelect;            
                ret=0;
//            }
            break;
        case    SUB_DOOR:
//            if( !(sRamDArry[mDoor] & MAIN_OPEN_KEY) || !(sRamDArry[mDoor] & SUB_OPEN_KEY)){ 
                NewDoorSelect = SUB_DOOR;
                CurDoorSelect = NewDoorSelect;            
                ret=0;
//            }
            break;
        case    MAIN_SUB_DOOR:
            if( !(sRamDArry[mDoor] & MAIN_OPEN_KEY) && !(sRamDArry[mDoor] & SUB_OPEN_KEY)){ 
                if(CurDoorSelect == SUB_DOOR){                            
                    NewDoorSelect = SUB_DOOR;
                    CurDoorSelect = NewDoorSelect;            
                    ret=0;
                }
                else{                            
                    NewDoorSelect = MAIN_DOOR;
                    CurDoorSelect = NewDoorSelect;            
                    ret=0;
                }                
            }
			else{
                if(CurDoorSelect == MAIN_DOOR){
	                if(sRamDArry[mDoor] & MAIN_OPEN_KEY){                            
	                    NewDoorSelect = MAIN_DOOR;
	                    CurDoorSelect = NewDoorSelect;            
	                    ret=0;
	                }
				}
                else if(CurDoorSelect == SUB_DOOR){                            
	                if(sRamDArry[mDoor] & SUB_OPEN_KEY){                            
	                    NewDoorSelect = SUB_DOOR;
	                    CurDoorSelect = NewDoorSelect;            
	                    ret=0;
	                }
				}
				else{
	                if(sRamDArry[mDoor] & MAIN_OPEN_KEY){                            
	                    NewDoorSelect = MAIN_DOOR;
	                    CurDoorSelect = NewDoorSelect;            
	                    ret=0;
	                }
	                else if(sRamDArry[mDoor] & SUB_OPEN_KEY){                            
	                    NewDoorSelect = SUB_DOOR;
	                    CurDoorSelect = NewDoorSelect;            
	                    ret=0;
	                }          
				}
			}
            break;

    }

    return(ret);
}


	                   
///////////////////////////////////////////////////////////////



void	__attribute__((section(".usercode"))) DoorPortInit_abc(void)
{
    OUT_CL_S(0);   
    OUT_OP_S(0);   	
   	OUT_CL(0);
    OUT_OP(0);

    if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){
        OUT_HOP(0);   //main hole door  open    
        OUT_HCL(0);   //main hole door  close    
    }        


}



UserDataType	__attribute__((section(".usercode"))) DoorOpenSetCheck(void)
{
	UserDataType ret;

	ret=0;

	if(AutoRunReady()){
		if(OpenOutSet){
	    	if(sRamDArry[mDoorSeq] <= DOOR_OPEN_WAIT){		    		      
				ret=1;  
			}
		}
	}
	return(ret);
}


void  __attribute__((section(".usercode"))) MainDoorOpenCmd_abc(void)
{
    DoorPortInit_abc();


    if(!bOpenEnd || DoorOpenSetCheck() )	     OUT_OP(1);      


    if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){
        if(!bHoleDoorOpenEnd && (!IN_LU || !IN_LD) )  OUT_HOP(1);   //main sub hole door  open    1
    }
}



void  __attribute__((section(".usercode"))) SubDoorOpenCmd_abc(void)
{
    DoorPortInit_abc();

    if(!bOpenEnd || DoorOpenSetCheck() )       OUT_OP_S(1);      


    if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){
        if(!bOpenEnd)                                       OUT_OP(1);      
        if(!bHoleDoorOpenEnd && (!IN_LU || !IN_LD) )        OUT_HOP(1);      //main sub hole door open 2
    }   

}



void  __attribute__((section(".usercode"))) MainDoorCloseCmd_abc(void)
{

    DoorPortInit_abc();

    if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){
        if(!bCarDoorCloseEnd){
            OUT_CL(1);
            OUT_CL_S(1);
        }
        if(!bHoleDoorCloseEnd && (!IN_LU || !IN_LD)){
            OUT_HCL(1);                                 //hole door close
        }
    }
    else{      
       OUT_CL(1);      
       OUT_CL_S(1);	              
    }

}





void	__attribute__((section(".usercode"))) AllDoorOpenClrCmd_abcdefg(void)
{
    OUT_OP(0);   
    OUT_OP_S(0);   

    if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){
        OUT_HOP(0);  //main hole door   open
    }

}

      
void	__attribute__((section(".usercode"))) AllDoorCloseClrCmd_abcdefg(void)
{
    OUT_CL_S(0);   
    OUT_CL(0);
   
    if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){
        OUT_HCL(0);  //main hole door   close
    }

}      





void	__attribute__((section(".usercode"))) SelectDoorOpen_abc(void)
{


    if(CurDoorSelect == MAIN_DOOR){
        OUT_D_S(0);                     //sel door          
		MainDoorOpenCmd_abc();
    }
    else if(CurDoorSelect == SUB_DOOR){
        OUT_D_S(1);                     //sel door          
		SubDoorOpenCmd_abc();	
    }		
}



void	__attribute__((section(".usercode"))) SelectDoorClose_abc(void)
{

    if(CurDoorSelect == MAIN_DOOR){
        OUT_D_S(0);                     //sel door          
    }
    else if(CurDoorSelect == SUB_DOOR){
        OUT_D_S(1);                     //sel door          
    }
    MainDoorCloseCmd_abc();
}






////////////////////////////////////////////////////////////////////////

////////////////////////////
void	__attribute__((section(".usercode"))) SelectDoorOpen_you(void)
{
    bDoorOpenCmd=1;
}


void	__attribute__((section(".usercode"))) SelectDoorClose_you(void)
{
    bDoorCloseCmd=1;
}



void	__attribute__((section(".usercode"))) DoorOpenClose_you(void)
{
/*
    if(SafetyChk()){
        bDoorOpenCmd=1;
        bDoorCloseCmd=0;
    } 
*/



    if(bLevelFind){
        bDoorOpenCmd=1;
        bDoorCloseCmd=0;
    }

/* solmodify
    if(bDoorOpenCmd){
*/
    if(bDoorOpenCmd && bDoorOpenValid){
        SelectDoorOpen_abc();
    }
    else if(bDoorCloseCmd){
        SelectDoorClose_abc();
	}	
    else{
        AllDoorOpenClrCmd_abcdefg();
        AllDoorCloseClrCmd_abcdefg();
    }	
}
     


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void    __attribute__((section(".usercode"))) HoleDoorCloseEndCheck(UserDataType movecar)
{

	LocalType i;

    i=0;

    if(HoleDoor1UseChk){
        if(!IN_HL_D)                i=1;        //close            
        else                        i=0;        //open
	}
    else							i=1;




    if( bFR2Start1){  
        i=1;
        bOpenDoorOk=0;
    }




	if(i==0){
      	if(movecar){
			if( !bRunningOpenOn){
				bsHdsRunOff=1;
			}
        }
   		bHoleDoorCloseEnd=0;
   	}
   	else{
   		bHoleDoorCloseEnd=1;
   		bsHdsRunOff=0;
   	}	     
}



void    __attribute__((section(".usercode"))) CarDoorCloseEndCheck(UserDataType movecar)
{

	LocalType i;

    i=0;

    if(CarDoor1UseChk){
         if(!IN_CL_E)		i=1;        //close            
         else				i=0;        //open
    }
    else					i=1;        



    if(bFR2Start1){
        i=1;
        bOpenDoorOk=0;
    }


	if(i==0){
      	if(movecar){
			if( !bRunningOpenOn){
				bsCleRunOff=1;
			}	
        }
   		bCarDoorCloseEnd=0;
   	}
   	else{
   		bCarDoorCloseEnd=1;
   		bsCleRunOff=0;
   	}	     
}




UserDataType	__attribute__((section(".usercode"))) OpenCloseSet(void)
{

#ifdef	TEST_SIMULATION
    if(bDoorCloseOk && (sRamDArry[mDoorSeq] >= DOOR_CLOSE_END)){
#else
	LocalType TmpDoorOpenOn=0;
/*
    if(bDoorCloseOk && !bMoveCar && (!DoorJumperChkOnOffChk) && (PerfectAuto())){
    	if(bDoorCloseOk && (sRamDArry[mDoorSeq] >= DOOR_OPEN_WAIT)){
			TmpDoorOpenOn=1;
		}
	}
*/


    if( !PerfectAuto())	bDoorErr=0;

    if(bDoorErr && !bMoveCar){
    	if(sRamDArry[mDoorSeq] == DOOR_OPEN_WAIT){
			TmpDoorOpenOn=1;
		}
	}


    if(bDoorCloseOk && (TmpDoorOpenOn==0)){
#endif
        S1_OPEN1=0; 
        S3_OPEN_SUB1=0;
        S1_CLOSE1=1;
    }
    else{
        ValidDoorSel();
    
        switch(NewDoorSelect)
        {
            case    MAIN_DOOR:
            case    SUB_DOOR:
                S1_OPEN1=1; 
        	   	S3_OPEN_SUB1=1;
          	   	S1_CLOSE1=0;
                break;
            case    MAIN_SUB_DOOR:
                if(CurDoorSelect == MAIN_DOOR){
                    S1_OPEN1=1; 
            	   	S3_OPEN_SUB1=0;
              	   	S1_CLOSE1=0;
                }             
                else if(CurDoorSelect == SUB_DOOR){
                    S1_OPEN1=0; 
            	   	S3_OPEN_SUB1=1;
              	   	S1_CLOSE1=0;
                }       
                break;  
        }
    }

    return(0);
}



UserDataType	__attribute__((section(".usercode"))) OtherDoorKeyClear(void)
{

    ValidDoorSel();

    if(NewDoorSelect == MAIN_SUB_DOOR)
    {
        if(CurDoorSelect == MAIN_DOOR){
            if(!bDoorCloseOk){        
				sRamDArry[mDoor]    = (sRamDArry[mDoor] & SUB_KEY_CLEAR);
            }                
        } 
        else if(CurDoorSelect ==  SUB_DOOR){  
            if(!bDoorCloseOk){        
				sRamDArry[mDoor]    = (sRamDArry[mDoor] & MAIN_KEY_CLEAR);   
            }                
        } 
    }

    return(0);
}


void	__attribute__((section(".usercode"))) DoorCloseEndCheck(UserDataType movecar)
{	
                    
    HoleDoorCloseEndCheck(movecar);
    CarDoorCloseEndCheck(movecar);

    if(bHoleDoorCloseEnd && bCarDoorCloseEnd)   bDoorCloseOkSensor=1;   	
    else{
        bDoorCloseOkSensor=0;   	
    	bDoorCloseOk=0;
        DoorCloseOnTime=0;
    }

    
    if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){
        if(bDoorCloseOkSensor){
            bDoorCloseOk=1;    
            AllDoorCloseClrCmd_abcdefg();   			
    	}		
    }
    else{
        if(bDoorCloseOkSensor){
       		if(DoorCloseOnTime>2){
            	bDoorCloseOk=1;    
            }    
       		if(DoorCloseOnTime>30){
    			AllDoorCloseClrCmd_abcdefg();   			
       		}											
    	}		
    			

    	if(movecar){
			if( !bRunningOpenOn){
	            bDoorCloseCmd=1;
	    		DoorCloseOnTime=0;
			}
    	}

    }

    if(WarmingUpTime>100){
        OtherDoorKeyClear();
        OpenCloseSet();
    }
}



void	__attribute__((section(".usercode"))) DoorOpenEndCheck(void)
{

    if((USE_CHECK == BAGGAGE_USE) || (USE_CHECK == CARLIFT_USE)){
    	if(CarDoor1UseChk){
	        if(IN_OP_E) bOpenEnd=0;
	        else        bOpenEnd=1;
		}
		else			bOpenEnd=1;
	
    	if(HoleDoor1UseChk){
	        if(IN_X7)   bHoleDoorOpenEnd=0;
	        else        bHoleDoorOpenEnd=1;
		}
		else			bHoleDoorOpenEnd=1;

				
        if(bHoleDoorOpenEnd && bOpenEnd)    bOpenDoorOk =1;
        else                                bOpenDoorOk =0;

        if(bFR2Start1){
            bOpenDoorOk=0;
            bHoleDoorOpenEnd=0;
            bOpenEnd=0;
        }
    }
    else{
        bHoleDoorOpenEnd=1;

        if(IN_OP_E){
            bOpenEnd=0;
            bOpenDoorOk=0;
            DoorOpenOnTime=0;
        }
        else{
            bOpenEnd=1;
            bOpenDoorOk=1;
            if(DoorOpenOnTime>200){
                AllDoorOpenClrCmd_abcdefg();
            }      		
        }

        if(bFR2Start1){
            bOpenDoorOk=0;
            bOpenEnd=0;
        }
    }
}





UserDataType	__attribute__((section(".usercode"))) CarDoorCloseEndCheckForDoorjmp(void)
{

	LocalType i;

    i=0;

    if(CarDoor1UseChk){
        if(!IN_CL_E)                i=1;        //close            
        else                        i=0;        //open
	}

    return(i);
}



UserDataType	__attribute__((section(".usercode"))) HoleDoorCloseEndCheckForDoorjmp(void)
{

	LocalType i;

    i=0;

    if(HoleDoor1UseChk){
        if(!IN_HL_D)                i=1;        //close            
        else                        i=0;        //open
	}

    return(i);
}





