



#include <p30fxxxx.h>
#include  "30f6010_io.h"            
#include  "host_io.h"            
#include  "iodef.h"
#include  "com.h"
#include  "iomap.h"
#include  "default_setup.h" 



	
//#ifndef	AUTO_LANDING_485	



void  Comport1Tx_interrupt(void);
void  Comport1Rx_interrupt(void);


#define     ASCTOHEX(x) ((x <= '9') ? (x - '0') : (x - '7')) 
#define     L_SHIFT(x)  (x << 4)



UserDataType    RxBuffer[MAX_RTX_BUF]={0,0};
UserDataType    RcvBuf[MAX_SAVE_BUF]={0};
UserDataType    RxStatus=0;
UserDataType    RxCurCnt=0;
UserDataType    SerialTime=0x0;
UserDataType    Chksum=0;

unsigned char   Com1RxBuffer[MAX_RTX_BUF]={0,0};
unsigned char   Com1TxBuffer[MAX_RTX_BUF]={0,0};
unsigned char   Com1RxStatus=0;
unsigned char   Com1TxOn=0;
unsigned char   Com1SerialTime=0x0;
unsigned char   Com1AckTime=0;
unsigned char   Com1Chksum=0;

unsigned char   Com1RxCnt=0;
unsigned char   Com1RxThisPt=0;
unsigned char   Com1TxCnt=0;
unsigned char   Com1TxThisPt=0;

UserDataType	Com1Crc=0;	



/*
unsigned char  __attribute__((section(".usercode")))  ASCIItoHex(unsigned char f,unsigned char s)
{
	if(f > 0x39)	f= f - '7';
	else			f= f - '0';
	f=(f << 4);	

	if(s > 0x39)	s= s - '7';
	else			s= s - '0';
	f=(f | s);
	return(f);
}
*/


void  __attribute__((section(".usercode"))) Com1RxREGClear(void)
{
	unsigned	char	buf1;
   	if(_U1RXDA)    buf1=U1RXREG;
   	if(_U1RXDA)    buf1=U1RXREG;
   	if(_U1RXDA)    buf1=U1RXREG;
   	if(_U1RXDA)    buf1=U1RXREG;
   	if(_U1RXDA)    buf1=U1RXREG;
}



void    Crc_Calulate_Cmm1(unsigned int crcdata)
{
	register unsigned int    i;

   Com1Crc=Com1Crc ^ (crcdata & 0x00ff);
   for(i=0;i<=7;i++){
      if( (Com1Crc & 0x0001) == 0x0001)    Com1Crc=(Com1Crc >> 1) ^ 0xA001;
      else Com1Crc=Com1Crc >> 1;
   }
}


void     __attribute__((section(".usercode")))  Chksum_Sum(void)
{
        LocalType    i;
        LocalType    temp;

        Chksum=0;
        for(i=0;RxBuffer[i];i++){
                Chksum=Chksum+RxBuffer[i];
        }
        temp=(Chksum & 0xf0) >> 4;
        if(temp < 0x0a) temp=temp+'0';
        else            temp=temp+'7';
        RxBuffer[i]=temp;

        temp=(Chksum & 0x0f);
        if(temp<0x0a)   temp=temp+'0';        
        else            temp=temp+'7';
        RxBuffer[i+1]=temp;
        RxBuffer[i+2]=0;
}



void	__attribute__((section(".usercode"))) Serial(void)
{

	Com1RxREGClear();

   	Chksum_Sum();   	
   	RxCurCnt=0;
   	RxStatus=TX_SET;
    U1TXREG=RxBuffer[RxCurCnt];
   	RxCurCnt=1;   
}







void  __attribute__((section(".usercode"))) SerialCheck(void)
{
   	LocalType   buf1=0;

	if(bInvCommActive485){
		Com1Autolanding();
	}
	else{	

	#ifndef		RS485_FOR_CRT	
	    HibHpiReqCheck();
	#else
		CrtReqCheck();
	#endif
		
		if((RxStatus==TX_SET) && (SerialTime > 2)){
			TXEN=1;  		
			RxCurCnt=0;
	      	RxStatus = STX_CHK;
		}
	
		if(RxStatus != TX_SET){
			TXEN=1;  		
		}
	}


	if(_U1OERR){
		Com1RxREGClear();
		_U1OERR=0;
	}

}




void _ISR_X _U1TXInterrupt(void)
{
    unsigned int  i;

    _U1TXIF=0;

	if(bInvCommActive485){
		Com1AutolandingTxInt();
	}
	else{
	#ifndef		RS485_FOR_CRT	    
	    if(RxBuffer[RxCurCnt] == 0){
	      SerialTime=0;
	    }
	#else
		if(RxStatus != TX_SET){
	      	RxStatus = STX_CHK;
		}
	    else if(RxCurCnt >= (RxBuffer[3]+6)){
	      SerialTime=0;
	    }
	#endif
	
	    else{
	      U1TXREG=RxBuffer[RxCurCnt];
	      RxCurCnt++;
	      SerialTime=0;
	      RxStatus = TX_SET;
	
	      if(RxCurCnt >= MAX_RTX_BUF){
	        RxCurCnt=0;
	        RxBuffer[RxCurCnt]=0;
	      	RxStatus = STX_CHK;
	      }
	    }
	}
}


void _ISR_X _U1RXInterrupt(void)
{
   	LocalType   buf1=0;
   	LocalType   temp=0;
   	unsigned char   My485Address=0;

    _U1RXIF=0;

	if(_U1RXDA)    buf1=U1RXREG;
	
    if(_U1FERR){
        _U1FERR=0;
    }

    if(_U1PERR){
        _U1PERR=0;
    }
    
///////////////////

	if(bInvCommActive485){
		Com1AutolandingRxInt(buf1);
	}
	else{	
		
	    if(RxStatus != TX_SET){   
			if(SerialTime > 3){
				RxCurCnt=0;
			}		
	
	        if(RxCurCnt >= (MAX_RTX_BUF-2)){
	            RxCurCnt=0;
	        }
	
	#ifndef	RS485_FOR_CRT
	        else	        RxCurCnt++;
	
	        RxBuffer[RxCurCnt]=buf1;
	
	
	        switch(RxStatus){
	            case    STX_CHK:
	                if((buf1==ACK) || (buf1==ENQ)){
	                    RxStatus=ETX_CHK;
	                    RxBuffer[0]=buf1;
	                    RxCurCnt=0;
	                    Chksum=buf1;
	                }
	                break;
	            case    ETX_CHK:
	                Chksum=Chksum+buf1;
	                if((buf1==ETX) || (buf1 == EOT)){
	                    RxBuffer[RxCurCnt]=0x0;
	                    RxStatus=BCC1_CHK;                  
	                }
	                else if(buf1 < '0')   RxStatus=STX_CHK;
	                break;
	            case    BCC1_CHK:               
	                buf1=ASCTOHEX(buf1);
	                RxBuffer[RxCurCnt]=0x0;
	                temp=(Chksum & 0xf0) >> 4; 
	           
	                if(temp==buf1){                 
	                    RxStatus=BCC2_CHK;                                                                    
	                }
	                else    RxStatus=STX_CHK;                  
	                break;
	            case    BCC2_CHK :
	                buf1=ASCTOHEX(buf1);
	                temp=(Chksum & 0x0f);
	                RxBuffer[RxCurCnt]=0x0;
	                RxBuffer[MAX_RTX_BUF-1]=0x0;
	               
	                if((temp==buf1) && (RxCurCnt <= (MAX_RTX_BUF-1))){
	                    buf1=0;                                                                             
	                    for(temp=1;(RxBuffer[temp] >= '0');temp++){                   
	                        RxBuffer[temp]=ASCTOHEX(RxBuffer[temp]);
	                        RxBuffer[temp]=L_SHIFT(RxBuffer[temp]);
	                        temp++;
	                        RxBuffer[temp]=ASCTOHEX(RxBuffer[temp]);
	                        RcvBuf[buf1]=(RxBuffer[temp-1] | RxBuffer[temp]);
	                        buf1++;
	                        if(buf1 > MAX_SAVE_BUF){
	                            RxStatus=STX_CHK;
	                            RxCurCnt=0;
	                            break;
	                        }                     
	                    }
	                    RxStatus=RX_GOOD;
	                }
	                else    RxStatus=STX_CHK;                  
	                break;              
	            case    RX_ERROR:
	                RxStatus=STX_CHK;
	                RxCurCnt=0;
	                break;
	            default:
	                RxStatus=STX_CHK;
	                RxCurCnt=0;
	                break;
	        }
	#else
			My485Address=cF_GroupNm;
			My485Address=(My485Address << 3);
			My485Address=(My485Address | cF_LocalNm);
	
	
	
	
	        RxBuffer[RxCurCnt]=buf1;
	
	        switch(RxCurCnt){
	            case    0:
					if(RxBuffer[0]== My485Address){
						RxCurCnt++;
					}
					else{
						RxCurCnt=0;
					}
					break;
	            case    1:
					if(RxBuffer[1]== 0xfe){
						RxCurCnt++;
					}
					else	RxCurCnt=0;
					break;
	            case    2:
					RxCurCnt++;
	
	/*
					if((RxBuffer[2]== 0x23) || (RxBuffer[2]== 0x24)){ 
						RxCurCnt++;
					}
					else	RxCurCnt=0;
	*/
	
					break;
	            case    3:
					RxCurCnt++;
					break;
				default:
					temp=RxBuffer[3];
					temp=(unsigned char)(temp + 5);
					if(RxCurCnt == temp){
	                    RxStatus=RX_GOOD;	
					}
					else if(RxCurCnt > temp){
						RxCurCnt=0;
					}
					else	RxCurCnt++;
					break;						
			}
		
	#endif
	    }
	    SerialTime=0;
	}
}


//#endif
