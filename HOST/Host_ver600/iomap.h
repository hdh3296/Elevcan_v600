
#define     LocalType       unsigned int
#define     UserDataType    unsigned int


#define  RW_EEP_AREA          1
#define  RW_SRAM0_AREA        2
#define  RW_EEP_RAM_AREA      3

#define  USER_LAMP_SORT       9
#define  BYTE_OFFSET          4


#define  ERR_SAVE_CNT       40
#define  ERR_SAVE_WIDE      6
#define  ERR_SAVE_SIZE      (ERR_SAVE_CNT+1) * (ERR_SAVE_WIDE)

#define  ABS_ADDRESS        76


#define  AUTOTUN_SEQ_0     0
#define  AUTOTUN_SEQ_1     1
#define  AUTOTUN_SEQ_2     2
#define  AUTOTUN_SEQ_3     3
#define  AUTOTUN_SEQ_4     4
#define  AUTOTUN_SEQ_5     5
#define  AUTOTUN_SEQ_6     6
#define  AUTOTUN_SEQ_7     7
#define  AUTOTUN_SEQ_8     8
#define  AUTOTUN_SEQ_9     9
#define  AUTOTUN_SEQ_10    10
#define  AUTOTUN_SEQ_11    11
#define  AUTOTUN_SEQ_12    12
#define  AUTOTUN_SEQ_13    13
#define  AUTOTUN_SEQ_14    14
#define  AUTOTUN_SEQ_15    15

#define  AUTOTUN_END		AUTOTUN_SEQ_15    



#define  FHM_SEQ_0            0x0
#define  FHM_SEQ_1            0x1
#define  FHM_SEQ_2            0x2
#define  FHM_SEQ_3            0x3
#define  FHM_SEQ_4            0x4
#define  FHM_SEQ_5            0x5
#define  FHM_SEQ_6            0x6
#define  FHM_SEQ_7            0x7
#define  FHM_SEQ_8            0x8


#define  BASE_ADDR            0                         
#define  eSysErCnt            BASE_ADDR                 				// 78   84 
#define  eErrCntPt            eSysErCnt+ERR_SAVE_SIZE + ERR_SAVE_WIDE  	// 175  1
#define  E_END                256                   	// 



#define  ADR_NO_SET         'N'   
#define  ADR_SET_SEND       'S'   
#define  ADR_SET_REC        's'   
#define  ADR_SET_ACK        'A'   
#define  NORMAL             '0'   
#define  WRITE_DATA         'W'   
#define  READ_DATA          'R'   
#define  BIT_WRITE_DATA     'w'   
#define  BIT_READ_DATA      'r'   
#define  LOGADR_CLR         'C'   
#define  NO_DATA            'Z'   
#define  RET_GOOD           'G'   
#define  RET_NOGOOD         'X'   
#define  LONG_READ_DATA     'L'
#define  FLASH_RD_WR        'F'
#define  NEW_FLASH_RD_WR    'f'

#define  LONG_WR_DATA       'M'


#define  RCV_GROUP      0                       
#define  RCV_LOGADR     1                        
#define  RCV_ABSADR     2                        
#define  RCV_CMD        3                       
#define  RCV_CMDTYPE    4                       
#define  RCV_BASE_ADR   5                        
#define  RCV_OFFS_ADR   6 
#define  RCV_DATA_CNT   7                        
#define  RCV_DATA       8                        






#define  NcNoOpLmS       0x01
#define  NcNoParking     0x02
#define  NcNoSafety      0x04
#define  NcNoOverload    0x08


#define  NcNoGr          0x01
#define  NcNoBat         0x02
#define  NcNoPass        0x04
#define  NcNoFire        0x08
#define  NcNoWater       0x10
#define  NcNoEx0         0x20
#define  NcNoEx1         0x40
#define  NcNoEx2         0x80


#define  NcNoFr1         0x01
#define  NcNoFr2         0x02
#define  NcNoFr3         0x04
#define  NcNoFr4         0x08
#define  NcNoSu2         0x10
#define  NcNoSd2         0x20
#define  NcNoSu3         0x40
#define  NcNoSd3         0x80


#define  NcNoX0          0x01
#define  NcNoX1          0x02
#define  NcNoX2          0x04
#define  NcNoX3          0x08
#define  NcNoX4          0x10
#define  NcNoX5          0x20
#define  NcNoX6          0x40
#define  NcNoX7          0x80




