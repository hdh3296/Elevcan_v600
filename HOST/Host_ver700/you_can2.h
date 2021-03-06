
#include  "iomap.h"


extern  void  Can2Interrupt(void);
extern  void  Can2Init(void);

extern  LocalType 	__attribute__((section(".usercode")))   Can2Check(void);
extern	void  		__attribute__((section(".usercode")))	C2RxSidEidDataLoad(void);



extern	UserDataType   C2DataSeqStart;
extern  UserDataType   C2Time;
extern	UserDataType   C2DataSeq;

extern  unsigned int   C2ReceiveSlaveAdr;
extern  unsigned int   C2ReceiveAdrStatus;
extern  unsigned int   C2Loop;
extern	unsigned int   CAN2_RxBuf[13];
extern	unsigned int   CAN2_TxBuf[13];






extern	unsigned long	C2ThisRxEid;
extern	unsigned int	C2ThisRxSid;
extern	unsigned int	C2ThisRxDataCnt;
extern	unsigned int   	C2ThisRxBuf[8];

extern	unsigned long	C2ThisTxEid;
extern	unsigned int	C2ThisTxSid;
extern	unsigned int	C2ThisTxDataCnt;
extern	unsigned int   	C2ThisTxBuf[8];







