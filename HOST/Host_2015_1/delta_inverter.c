

#include <p30fxxxx.h>
#include 	"you_can_lib.h" 
#include 	"you_can2.h" 

           
#include  	"30f6010_io.h"            
#include  	"host_io.h"            
#include  	"iodef.h"
#include  	"door.h"
#include  	"com.h"
#include  	"counter.h"
#include	"Host_NewProtocol.h" 
#include	"you_can2.h" 


#define		CAN_BASE_TIME	20		

#define		HOST_SDO_0		0x60		
#define		HOST_SDO_1		0x61		
#define		HOST_SDO_2		0x62
		
#define		HOST_PDO		0x01		

#define		INVERTER_SDO	0x50		
#define		INVERTER_PDO	0x02		




#define		RD_SDO_INV_REG	0x03	
#define		RD_SDO_INV_ATB	0x60	
#define		RD_SDO_INV_DSR	0x61	

#define		WR_SDO_INV_REG	0x06



#define		IV_POWER_ON_CHK		0x01
#define		IV_FHM_SUCCESS		0x02
#define		IV_FHM_EXCUTE		0x04
#define		IV_PG_P_RECORD		0x08
#define		IV_PG_P_RESET		0x10


#define		FHM_CMD_EXCUT		(IV_FHM_EXCUTE 					| IV_POWER_ON_CHK)
#define		FHM_CMD_P_RESET_H	(IV_FHM_EXCUTE | IV_PG_P_RESET 	| IV_POWER_ON_CHK)
#define		FHM_CMD_P_RESET_L	(IV_FHM_EXCUTE  				| IV_POWER_ON_CHK)
#define		FHM_CMD_P_RECORD_H	(IV_FHM_EXCUTE | IV_PG_P_RECORD | IV_POWER_ON_CHK)
#define		FHM_CMD_P_RECORD_L	(IV_FHM_EXCUTE 					| IV_POWER_ON_CHK)
#define		FHM_CMD_SUCCESS		(IV_FHM_SUCCESS 				| IV_POWER_ON_CHK)




#define		ID_CODE			0
#define		RD_WR_CMD		1
#define		RD_WR_LENGTH	2
#define		BASE_ADDR_H		3
#define		BASE_ADDR_L		4
#define		DATA_0_H		5
#define		DATA_0_L		6
#define		DATA_1_H		7
#define		DATA_1_L		8
#define		DATA_2_H		9
#define		DATA_2_L		10
#define		DATA_3_H		11
#define		DATA_3_L		12
#define		DATA_4_H		13
#define		DATA_4_L		14
#define		DATA_5_H		15
#define		DATA_5_L		16
#define		DATA_6_H		17
#define		DATA_6_L		18
#define		DATA_7_H		19
#define		DATA_7_L		20
#define		DATA_8_H		21
#define		DATA_8_L		22
#define		DATA_9_H		23
#define		DATA_9_L		24
#define		REQ_TIMEOUT		25
#define		REQ_DATA_SEQ	26



unsigned int	DeltaNoAck=0;


#ifdef	DELTA_INVERTER	


unsigned int	InverterReady=0;
unsigned int	DeltaRdWrStatus=0;
unsigned int	DeltaRdWrStatusFhm=0;

unsigned char	EV_ReqRdWrTxBuf[27];
unsigned char	IV_AckRdWrTxBuf[27];
unsigned char	ElevStatus[8];
unsigned char	InvStatus[8];
unsigned char	ThisAttribute[8];




void     __attribute__((section(".usercode"))) C2RxSidEidDataLoad(void)
{
	unsigned long	tmp0,tmp1;

	C2ThisRxSid= ((C2RX0SID >> 2) & 0x007f);
	C2ThisRxDataCnt=(C2RX0DLC & 0x000f);

	tmp0=0;
	tmp1=0;
	tmp0=(unsigned long)(C2RX0DLC >> 10);
	tmp1=(unsigned long)(C2RX0EID);
	tmp1=(unsigned long)(tmp1 << 2);
	tmp1=(unsigned long)(tmp1 & 0xfffffffc);

	C2ThisRxEid=(tmp0 | tmp1);


	C2ThisRxBuf[0] =(UserDataType)(C2RX0B1 & 0x00ff);
	C2ThisRxBuf[1] =(UserDataType)((C2RX0B1 >> 8) & 0x00ff);     
	
	C2ThisRxBuf[2] =(UserDataType)(C2RX0B2 & 0x00ff);
	C2ThisRxBuf[3] =(UserDataType)((C2RX0B2 >> 8) & 0x00ff);     
	
	C2ThisRxBuf[4] =(UserDataType)(C2RX0B3 & 0x00ff);
	C2ThisRxBuf[5] =(UserDataType)((C2RX0B3 >> 8) & 0x00ff);     
	
	C2ThisRxBuf[6] =(UserDataType)(C2RX0B4 & 0x00ff);
	C2ThisRxBuf[7] =(UserDataType)((C2RX0B4 >> 8) & 0x00ff);     
}


LocalType __attribute__((section(".usercode"))) Receive_All(void)
{
	unsigned int i;

	if(IV_AckRdWrTxBuf[1]==0x60){
		for(i=0;i<8;i++)	ThisAttribute[i]= IV_AckRdWrTxBuf[i+5];
	} 

	IV_AckRdWrTxBuf[REQ_DATA_SEQ]	=0;		// receive all good
}


LocalType __attribute__((section(".usercode"))) Ack_SDO(void)
{
	unsigned int i;
	
	switch(C2ThisRxSid){
		case	0x50:	
			IV_AckRdWrTxBuf[0]=C2ThisRxSid;
			for(i=0;i<8;i++)	IV_AckRdWrTxBuf[i+1] = C2ThisRxBuf[i];
			if(IV_AckRdWrTxBuf[2] <= 2){
				Receive_All();
			}
			break;			
		case	0x51:
			for(i=0;i<8;i++)	IV_AckRdWrTxBuf[i+9] = C2ThisRxBuf[i];
			if(IV_AckRdWrTxBuf[2] <= 6){
				Receive_All();
			}
			break;
		case	0x52:
			for(i=0;i<8;i++)	IV_AckRdWrTxBuf[i+17] = C2ThisRxBuf[i];
			if(IV_AckRdWrTxBuf[2] <= 10){
				Receive_All();
			}
			break;
	}
	
	return(0);
}



LocalType __attribute__((section(".usercode"))) C2InvAckDataSort(void)
{
	unsigned int ret;
	unsigned int i;

	ret=0xff;

	if( !((C2ThisRxSid == 0x02) || (C2ThisRxSid == 0x50)	|| (C2ThisRxSid == 0x51) || (C2ThisRxSid == 0x52)) ){
		return(ret);	
	}	 

	switch(C2ThisRxSid){
		case	0x02:
			for(i=0;i<8;i++)	InvStatus[i] = C2ThisRxBuf[i];
			EV_ReqRdWrTxBuf[REQ_TIMEOUT]	  = 0;
			ret=0; 	
			break;
		case	0x50:
			if( !((C2ThisRxBuf[0] == 0x03) || (C2ThisRxBuf[0] == 0x06)	|| (C2ThisRxBuf[0] == 0x60) || (C2ThisRxBuf[0] == 0x61) || (C2ThisRxBuf[0] == 0x62)) ){
				ret=1;
				return(ret);	
			}	 
			else if(C2ThisRxBuf[0] == WR_SDO_INV_REG){
				Receive_All();
				ret=0; 	
			}	 	
			else{
				Ack_SDO();			
			}	
			break;	
		case	0x51:
		case	0x52:
			Ack_SDO();
			break;
		default:
			ret=1; 	
			break;
	}

	return(ret);	
}




void _ISR_X _C2Interrupt(void)
{
    if(C2INTFbits.RX0IF){        
		C2RxSidEidDataLoad();
		C2InvAckDataSort();				

/*
		Delta_LoadThisTxCan2Buf(C2ThisRxSid,C2ThisTxDataCnt,&C2ThisRxBuf[0]);
		youCAN2TxSidSet(0,C2ThisTxSid);
		youCAN2TxEidSet(0,0,0);
		CAN2SendMessageyou(0,&C2ThisTxBuf[0], C2ThisTxDataCnt);        
*/

        C2INTFbits.RX0IF=0;
        C2RX0CONbits.RXFUL=0;
    }    
    else{
        C2CTRLbits.ABAT=1;      // aboart all pending transmit
        C2INTFbits.RX1IF=0;
        C2RX1CONbits.RXFUL=0;
        C2INTFbits.WAKIF=0;
        C2INTF=0;
        C2INTFbits.ERRIF=0;        
    }

    C2IF=0;
    C2INTFbits.RX0IF=0;
    C2RX0CONbits.RXFUL=0;
}



void Delta_LoadThisTxCan2Buf(unsigned int Tsid,unsigned int Tdatacnt,unsigned int *Tdata)
{
	unsigned int i;

	C2ThisTxSid=Tsid;
	C2ThisTxDataCnt=Tdatacnt;

    for(i = 0;i < C2ThisTxDataCnt;i++)	          C2ThisTxBuf[i]= *(Tdata + i);


/*
  *((unsigned char *)&C2TX0B1+i)= data[i];

    {
        switch(MsgFlag)
        {
        case 0: 
            *((unsigned char *)&C2TX0B1+i)= data[i];
            break;
        case 1: *((unsigned char *)&C2TX1B1+i)= data[i];
            break;
        case 2: *((unsigned char *)&C2TX2B1+i)= data[i];
            break;
        default:*((unsigned char *)&C2TX0B1+i)= data[i];
            break;
        }
    }

	C2ThisTxBuf[0]=C2ThisRxBuf[0];
	C2ThisTxBuf[1]=C2ThisRxBuf[1];
	C2ThisTxBuf[2]=C2ThisRxBuf[2];
	C2ThisTxBuf[3]=C2ThisRxBuf[3];
	C2ThisTxBuf[4]=C2ThisRxBuf[4];
	C2ThisTxBuf[5]=C2ThisRxBuf[5];
	C2ThisTxBuf[6]=C2ThisRxBuf[6];
	C2ThisTxBuf[7]=C2ThisRxBuf[7];
*/

}





LocalType __attribute__((section(".usercode"))) C2TxAct(void)
{    	
	youCAN2TxSidSet(0,C2ThisTxSid);
	youCAN2TxEidSet(0,0,0);

    if(C2TX0CONbits.TXREQ)		return(1);    				// fault
	CAN2SendMessageyou(0,&C2ThisTxBuf[0], C2ThisTxDataCnt); // tx success       
	return(0);
}



LocalType __attribute__((section(".usercode"))) RdWrBufInit(void)
{    
	unsigned	int	i;
	for(i=0;i<8;i++)	C2ThisTxBuf[i]=0;
	return(0);
}




LocalType __attribute__((section(".usercode"))) Read_SDO(void)
{

	RdWrBufInit();

	C2ThisTxSid 	=EV_ReqRdWrTxBuf[ID_CODE];
	C2ThisTxBuf[0] 	=EV_ReqRdWrTxBuf[RD_WR_CMD];
	C2ThisTxBuf[1]	=EV_ReqRdWrTxBuf[RD_WR_LENGTH];
	C2ThisTxBuf[2]	=EV_ReqRdWrTxBuf[BASE_ADDR_H];
	C2ThisTxBuf[3]	=EV_ReqRdWrTxBuf[BASE_ADDR_L];

	C2ThisTxDataCnt	=0x04;
	
	if( !C2TxAct()){
		EV_ReqRdWrTxBuf[REQ_TIMEOUT]=0;
		EV_ReqRdWrTxBuf[REQ_DATA_SEQ]--;
		IV_AckRdWrTxBuf[REQ_DATA_SEQ]=1;
	}

/*
	EV_ReqRdWrTxBuf[REQ_TIMEOUT]++;
	if(EV_ReqRdWrTxBuf[REQ_TIMEOUT] > 200){
		EV_ReqRdWrTxBuf[ID_CODE]		=0;
		EV_ReqRdWrTxBuf[REQ_TIMEOUT]	=0;
	}
*/

	return(0);
}



LocalType __attribute__((section(".usercode"))) Write_SDO(void)
{

	RdWrBufInit();

	switch(EV_ReqRdWrTxBuf[ID_CODE]){
		case	HOST_SDO_0:
			C2ThisTxSid 	=EV_ReqRdWrTxBuf[ID_CODE];
			C2ThisTxBuf[0] 	=EV_ReqRdWrTxBuf[RD_WR_CMD];
			C2ThisTxBuf[1]	=EV_ReqRdWrTxBuf[RD_WR_LENGTH];
			C2ThisTxBuf[2]	=EV_ReqRdWrTxBuf[BASE_ADDR_H];
			C2ThisTxBuf[3]	=EV_ReqRdWrTxBuf[BASE_ADDR_L];				

			C2ThisTxBuf[4] 	=EV_ReqRdWrTxBuf[DATA_0_H];
			C2ThisTxBuf[5]	=EV_ReqRdWrTxBuf[DATA_0_L];
			C2ThisTxBuf[6]	=EV_ReqRdWrTxBuf[DATA_1_H];
			C2ThisTxBuf[7]	=EV_ReqRdWrTxBuf[DATA_1_L];				

			if(EV_ReqRdWrTxBuf[RD_WR_LENGTH] > 2){
				C2ThisTxDataCnt	=8;
				EV_ReqRdWrTxBuf[ID_CODE]++;
				C2Time=CAN_BASE_TIME;
			}
			else{
				C2ThisTxDataCnt	=(EV_ReqRdWrTxBuf[RD_WR_LENGTH] * 2) + 4;
				EV_ReqRdWrTxBuf[ID_CODE]=0;
			}
			break;
		case	HOST_SDO_1:
			C2ThisTxSid 	=EV_ReqRdWrTxBuf[ID_CODE];
			C2ThisTxBuf[0] 	=EV_ReqRdWrTxBuf[DATA_2_H];
			C2ThisTxBuf[1]	=EV_ReqRdWrTxBuf[DATA_2_L];
			C2ThisTxBuf[2]	=EV_ReqRdWrTxBuf[DATA_3_H];
			C2ThisTxBuf[3]	=EV_ReqRdWrTxBuf[DATA_3_L];				
			C2ThisTxBuf[4] 	=EV_ReqRdWrTxBuf[DATA_4_H];
			C2ThisTxBuf[5]	=EV_ReqRdWrTxBuf[DATA_4_L];
			C2ThisTxBuf[6]	=EV_ReqRdWrTxBuf[DATA_5_H];
			C2ThisTxBuf[7]	=EV_ReqRdWrTxBuf[DATA_5_L];				

			if(EV_ReqRdWrTxBuf[RD_WR_LENGTH] > 6){
				C2ThisTxDataCnt	=8;
				EV_ReqRdWrTxBuf[ID_CODE]++;
				C2Time=CAN_BASE_TIME;
			}
			else{
				EV_ReqRdWrTxBuf[ID_CODE]=0;

				if(EV_ReqRdWrTxBuf[RD_WR_LENGTH]==3){
					C2ThisTxDataCnt	=2;
				}
				else if(EV_ReqRdWrTxBuf[RD_WR_LENGTH]==4){
					C2ThisTxDataCnt	=4;
				}
				else if(EV_ReqRdWrTxBuf[RD_WR_LENGTH]==5){
					C2ThisTxDataCnt	=6;
				}
				else{
					C2ThisTxDataCnt	=8;
				}
			}
			break;
		case	HOST_SDO_2:
			C2ThisTxSid 	=EV_ReqRdWrTxBuf[ID_CODE];
			C2ThisTxBuf[0] 	=EV_ReqRdWrTxBuf[DATA_6_H];
			C2ThisTxBuf[1]	=EV_ReqRdWrTxBuf[DATA_6_L];
			C2ThisTxBuf[2]	=EV_ReqRdWrTxBuf[DATA_7_H];
			C2ThisTxBuf[3]	=EV_ReqRdWrTxBuf[DATA_7_L];				
			C2ThisTxBuf[4] 	=EV_ReqRdWrTxBuf[DATA_8_H];
			C2ThisTxBuf[5]	=EV_ReqRdWrTxBuf[DATA_8_L];
			C2ThisTxBuf[6]	=EV_ReqRdWrTxBuf[DATA_9_H];
			C2ThisTxBuf[7]	=EV_ReqRdWrTxBuf[DATA_9_L];				

			EV_ReqRdWrTxBuf[ID_CODE]=0;

			if(EV_ReqRdWrTxBuf[RD_WR_LENGTH]==7){
				C2ThisTxDataCnt	=2;
			}
			else if(EV_ReqRdWrTxBuf[RD_WR_LENGTH]==8){
				C2ThisTxDataCnt	=4;
			}
			else if(EV_ReqRdWrTxBuf[RD_WR_LENGTH]==9){
				C2ThisTxDataCnt	=6;
			}
			else{
				C2ThisTxDataCnt	=8;
			}
			break;

	}


	C2TxAct();

	EV_ReqRdWrTxBuf[REQ_TIMEOUT]++;
	if(EV_ReqRdWrTxBuf[REQ_TIMEOUT] > 200){
		EV_ReqRdWrTxBuf[ID_CODE]		=0;
		EV_ReqRdWrTxBuf[REQ_TIMEOUT]	=0;
	}

	return(0);
}


LocalType __attribute__((section(".usercode"))) Read_PDO(void)
{
	unsigned int i;

	RdWrBufInit();

	C2ThisTxSid 	=HOST_PDO;
//	C2ThisTxBuf[0] 	=0;
	C2ThisTxBuf[1]	=0;
//	C2ThisTxBuf[2]	=0;
	C2ThisTxBuf[3]	=0;				
	C2ThisTxBuf[4] 	=0;
//	C2ThisTxBuf[5]	=0;
	C2ThisTxBuf[6]	=0;
	C2ThisTxBuf[7]	=0;				

	if(bAuto && !bManualStop && bManualAuto){
		C2ThisTxBuf[0]	= 0x04;
		C2ThisTxBuf[5]	=((sRamDArry[mAckStopFloor] & ONLY_FLR) + 1);
	}							
	else{
		C2ThisTxBuf[0]	=0x10;							
		C2ThisTxBuf[5]	=0;
	}
	if(CurSelOutPortChk(cF_UP))			C2ThisTxBuf[2]	=0x02;	
	else if(CurSelOutPortChk(cF_DN))	C2ThisTxBuf[2]	=0x04;	
	else								C2ThisTxBuf[2]	=0x0;
	C2ThisTxDataCnt	=0x08;

	C2TxAct();
	return(0);
}





LocalType __attribute__((section(".usercode"))) InverterReadyCheck(void)
{    

	InverterReady=(InverterReady | 0x01);

//	Read_SDO();

	return(0);
}


LocalType __attribute__((section(".usercode"))) SDOReqMode(void)
{
	unsigned int	ret;

	ret=1;

	if(EV_ReqRdWrTxBuf[REQ_DATA_SEQ] > 0){
		switch(EV_ReqRdWrTxBuf[RD_WR_CMD]){
			case	RD_SDO_INV_REG:
			case	RD_SDO_INV_ATB:
			case	RD_SDO_INV_DSR:
				Read_SDO();
				ret=0;
				break;
			case	WR_SDO_INV_REG:
				Write_SDO();
				ret=0;
				break;
			default:
				break;
		}
	}

	return(ret);
}


LocalType __attribute__((section(".usercode"))) PDOReqMode(void)
{
//	ThisReqSdoPdo=HOST_PDO;
	Read_PDO();    
	return(0);
}





LocalType __attribute__((section(".usercode"))) Can2Check(void)
{    
	unsigned int i;

	i=1;

	if(C2Time < CAN_BASE_TIME)	return(0);
    if(C2TX0CONbits.TXREQ)		return(0);


	C2Time=0;

	if(InverterReady == 0x01){
		if(SDOReqMode()){
			PDOReqMode();
		}
	}
	else{
		InverterReadyCheck();
	}

    return(0);
}




LocalType __attribute__((section(".usercode"))) ReadAttribute(unsigned char addressH,unsigned char addressL)
{    
	EV_ReqRdWrTxBuf[ID_CODE]		=HOST_SDO_0;
	EV_ReqRdWrTxBuf[RD_WR_CMD]		=RD_SDO_INV_ATB;
	EV_ReqRdWrTxBuf[RD_WR_LENGTH]	=0x04;
	EV_ReqRdWrTxBuf[BASE_ADDR_H]	=addressH;
	EV_ReqRdWrTxBuf[BASE_ADDR_L]	=addressL;
	EV_ReqRdWrTxBuf[REQ_DATA_SEQ]	=1;
	IV_AckRdWrTxBuf[REQ_DATA_SEQ]	=1;

	C2Time = CAN_BASE_TIME;
	DeltaNoAck=0;

}

LocalType __attribute__((section(".usercode"))) ReadParameter(unsigned char addressH,unsigned char addressL,unsigned char ReadWordNm)
{    
	EV_ReqRdWrTxBuf[ID_CODE]		=HOST_SDO_0;
	EV_ReqRdWrTxBuf[RD_WR_CMD]		=RD_SDO_INV_REG;
	EV_ReqRdWrTxBuf[RD_WR_LENGTH]	=ReadWordNm;
	EV_ReqRdWrTxBuf[BASE_ADDR_H]	=addressH;
	EV_ReqRdWrTxBuf[BASE_ADDR_L]	=addressL;
	EV_ReqRdWrTxBuf[REQ_DATA_SEQ]	=1;
	IV_AckRdWrTxBuf[REQ_DATA_SEQ]	=1;

	C2Time = CAN_BASE_TIME;
	DeltaNoAck=0;

}


/*
LocalType __attribute__((section(".usercode"))) WriteParameter(unsigned char addressH,unsigned char addressL,unsigned char ReadWordNm,unsigned char valH,unsigned char valL)
{    
	EV_ReqRdWrTxBuf[ID_CODE]		=HOST_SDO_0;
	EV_ReqRdWrTxBuf[RD_WR_CMD]		=WR_SDO_INV_REG;
	EV_ReqRdWrTxBuf[RD_WR_LENGTH]	=WriteWordNm;
	EV_ReqRdWrTxBuf[BASE_ADDR_H]	=addressH;
	EV_ReqRdWrTxBuf[BASE_ADDR_L]	=addressL;

	EV_ReqRdWrTxBuf[DATA_0_H]		=valH;
	EV_ReqRdWrTxBuf[DATA_0_L]		=valL;

	EV_ReqRdWrTxBuf[REQ_DATA_SEQ]	=1;
	IV_AckRdWrTxBuf[REQ_DATA_SEQ]	=1;

	C2Time = CAN_BASE_TIME;
}
*/


LocalType __attribute__((section(".usercode"))) EqualAddrWriteParameter(unsigned char WriteWordNm,unsigned char valH,unsigned char valL)
{    
	EV_ReqRdWrTxBuf[ID_CODE]		=HOST_SDO_0;
	EV_ReqRdWrTxBuf[RD_WR_CMD]		=WR_SDO_INV_REG;
	EV_ReqRdWrTxBuf[RD_WR_LENGTH]	=WriteWordNm;
//	EV_ReqRdWrTxBuf[BASE_ADDR_H]	=addressH;
//	EV_ReqRdWrTxBuf[BASE_ADDR_L]	=addressL;

	EV_ReqRdWrTxBuf[DATA_0_H]		=valH;
	EV_ReqRdWrTxBuf[DATA_0_L]		=valL;

	EV_ReqRdWrTxBuf[REQ_DATA_SEQ]	=1;
	IV_AckRdWrTxBuf[REQ_DATA_SEQ]	=1;

	C2Time = CAN_BASE_TIME;
	DeltaNoAck=0;
}





LocalType __attribute__((section(".usercode"))) DeltaInverterRdWr(unsigned char addressH,unsigned char addressL)
{    
	unsigned int val,dp;
	unsigned int ret;

	ret=0;

	if(DeltaRdWrStatus>0){
		switch(DeltaRdWrStatus){
			case	1:
				ReadAttribute(addressH,addressL);
				DeltaRdWrStatus=2;
				break;
			case	2:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					DeltaRdWrStatus=3;
				}		
				break;
			case	3:
				ReadParameter(addressH,addressL,1);
				DeltaRdWrStatus=4;
				break;
			case	4:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					Delta_inverter_Par_DataSort( &ThisAttribute[0], &IV_AckRdWrTxBuf[0]);					
					DeltaRdWrStatus=5;
				}		
				break;
			case	5:
				break;
			case	6:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					DeltaRdWrStatus=0;
					ret=1;
				}		
				break;
			default:
				break;
		}
	}	

	return(ret);
}	




LocalType __attribute__((section(".usercode"))) DeltaInverterRdWrFhm(unsigned char addressH,unsigned char addressL)
{    
	unsigned int val,dp;
	unsigned int ret;

	ret=0;


	if(DeltaRdWrStatusFhm>0){
		switch(DeltaRdWrStatusFhm){
			case	1:
				ReadParameter(addressH,addressL,1);
				DeltaRdWrStatusFhm=2;
IV_AckRdWrTxBuf[REQ_DATA_SEQ]=0xff;
				break;
			case	2:
//				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ] != 0xff){
					EqualAddrWriteParameter(1,0,FHM_CMD_EXCUT);
					DeltaRdWrStatusFhm=3;
				}
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=1;	
				}		
				break;
			case	3:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					ReadParameter(addressH,addressL,1);
					DeltaRdWrStatusFhm=4;
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=1;	
				}		
				break;
			case	4:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					if(IV_AckRdWrTxBuf[6] == FHM_CMD_EXCUT){
						EqualAddrWriteParameter(1,0,FHM_CMD_P_RESET_H);
						DeltaRdWrStatusFhm=5;
					}
					else{
						DeltaRdWrStatusFhm=1;
					}					
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=1;	
				}		
				break;
			case	5:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					ReadParameter(addressH,addressL,1);
					DeltaRdWrStatusFhm=6;
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=1;	
				}		
				break;
			case	6:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					if(IV_AckRdWrTxBuf[6] == FHM_CMD_P_RESET_H){
						EqualAddrWriteParameter(1,0,FHM_CMD_P_RESET_L);
						DeltaRdWrStatusFhm=7;
					}
					else{
						DeltaRdWrStatusFhm=1;
					}					
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=1;	
				}		
				break;
			case	7:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					ReadParameter(addressH,addressL,1);
					DeltaRdWrStatusFhm=8;
				}
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=1;	
				}		
				break;
			case	8:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					if(IV_AckRdWrTxBuf[6] == FHM_CMD_P_RESET_L){
						ret=1;
						DeltaRdWrStatusFhm=9;
					}
					else{
						DeltaRdWrStatusFhm=1;
					}
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=1;	
				}		
				break;
			case	9:
				break;

			case	10:
				ReadParameter(addressH,addressL,1);
				DeltaRdWrStatusFhm=11;
				break;
			case	11:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					EqualAddrWriteParameter(1,0,FHM_CMD_P_RECORD_H);
					DeltaRdWrStatusFhm=12;
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;
			case	12:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					ReadParameter(addressH,addressL,1);
					DeltaRdWrStatusFhm=13;
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;
			case	13:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					if(IV_AckRdWrTxBuf[6] == FHM_CMD_P_RECORD_H){
						if(DeltaNoAck > 10){
						EqualAddrWriteParameter(1,0,FHM_CMD_P_RECORD_L);
						DeltaRdWrStatusFhm=14;
						}
					}
					else{
						DeltaRdWrStatusFhm=10;
					}					
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;
			case	14:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					ReadParameter(addressH,addressL,1);
					DeltaRdWrStatusFhm=15;
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;

			case	15:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					if(IV_AckRdWrTxBuf[6] == FHM_CMD_P_RECORD_L){
						EqualAddrWriteParameter(1,0, (IV_AckRdWrTxBuf[6] & (~IV_FHM_EXCUTE)));   // dsb excute
						DeltaRdWrStatusFhm=16;
					}
					else{
						DeltaRdWrStatusFhm=10;
					}					
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;
			case	16:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					ReadParameter(addressH,addressL,1);
					DeltaRdWrStatusFhm=17;
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;
/*
			case	17:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					if(IV_AckRdWrTxBuf[6] == 0x00){
						EqualAddrWriteParameter(1,0,0x0);
						DeltaRdWrStatusFhm=16;
					}
					else{
						DeltaRdWrStatusFhm=10;
					}					
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;
			case	18:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					ReadParameter(addressH,addressL,1);
					DeltaRdWrStatusFhm=17;
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;

*/

			case	17:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					if( !(IV_AckRdWrTxBuf[6] & IV_FHM_EXCUTE)){
						EqualAddrWriteParameter(1,0,FHM_CMD_SUCCESS);
						DeltaRdWrStatusFhm=18;
					}
					else{
						DeltaRdWrStatusFhm=10;
					}					
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;
			case	18:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					ReadParameter(addressH,addressL,1);
					DeltaRdWrStatusFhm=19;
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;
			case	19:
				if(IV_AckRdWrTxBuf[REQ_DATA_SEQ]==0){
					if(IV_AckRdWrTxBuf[6] == FHM_CMD_SUCCESS){
						ret=1;
						DeltaRdWrStatusFhm=20;
					}
					else{
						DeltaRdWrStatusFhm=10;
					}					
				}		
				else{
					if(DeltaNoAck > 20)	DeltaRdWrStatusFhm=10;	
				}		
				break;
			case	20:
				break;
			default:
				break;
		}
	}	

	return(ret);
}	


#endif



