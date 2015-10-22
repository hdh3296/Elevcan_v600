/*****************************************
project :       elev    voice
name    :       you sang yong
date    :       1999,9,21
******************************************/

#include    <pic18.h>

#include        "..\..\system_com\memory_map.h"
#include        "..\comm_4480\iodef.h"
#include        "..\comm_4480\comdata.h"
#include        "..\comm_4480\setup.h"
#include        "..\comm_4480\spi.h"


#define START_FL	FLOOR_B7
#define END_FL		FLOOR_NO
#define VOICE_ADR  A_VOI;
#define VOICE_ON               0
#define VOICE_OFF              1

//층 정보 정의
#define         DINGDONG_MENT          0
#define         UP_MENT                1
#define         DOWN_MENT              2
#define         HWAJAE_MENT            3
#define         OVERLOAD_MENT          4
#define         EMERGENCY_MENT         5
#define         CLOSE_MENT             6
#define         POWER_DOWN_MENT        7
#define         FLOOR_B7               8
#define         FLOOR_B6                FLOOR_B7+1  //9
#define         FLOOR_B5                FLOOR_B7+2	//10
#define         FLOOR_B4                FLOOR_B7+3	//11
#define         FLOOR_B3                FLOOR_B7+4	//12
#define         FLOOR_B2                FLOOR_B7+5	//13
#define         FLOOR_B1                FLOOR_B7+6	//14
#define         FLOOR_F1                 FLOOR_B7+7	//15
#define         FLOOR_F2                 FLOOR_B7+8	//16
#define         FLOOR_F3                 FLOOR_B7+9	//17
#define         FLOOR_F4                 FLOOR_B7+10	//18
#define         FLOOR_F5                 FLOOR_B7+11	//19
#define         FLOOR_F6                 FLOOR_B7+12	//20
#define         FLOOR_F7                 FLOOR_B7+13	//21
#define         FLOOR_F8                 FLOOR_B7+14	//22
#define         FLOOR_F9                 FLOOR_B7+15	//23
#define         FLOOR_F10                FLOOR_B7+16	//24
#define         FLOOR_F11                FLOOR_B7+17	//25
#define         FLOOR_F12                FLOOR_B7+18	//26
#define         FLOOR_F13                FLOOR_B7+19	//27
#define         FLOOR_F14                FLOOR_B7+20	//28
#define         FLOOR_F15                FLOOR_B7+21	//29
#define         FLOOR_F16                FLOOR_B7+22	//30
#define         FLOOR_F17                FLOOR_B7+23	//31
#define         FLOOR_F18                FLOOR_B7+24	//32
#define         FLOOR_F19                FLOOR_B7+25	//33
#define         FLOOR_F20                FLOOR_B7+26	//34
#define         FLOOR_F21                FLOOR_B7+27	//35
#define         FLOOR_F22                FLOOR_B7+28	//36
#define         FLOOR_F23                FLOOR_B7+29	//37
#define         FLOOR_F24                FLOOR_B7+30	//38
#define         FLOOR_F25                FLOOR_B7+31	//39
#define         FLOOR_F26                FLOOR_B7+32	//40
#define         FLOOR_F27                FLOOR_B7+33	//41
#define         FLOOR_F28                FLOOR_B7+34	//42
#define         FLOOR_F29                FLOOR_B7+35	//43
#define         FLOOR_F30                FLOOR_B7+36	//44
#define         FLOOR_F31                FLOOR_B7+37	//45
#define         FLOOR_F32                FLOOR_B7+38	//46
#define         FLOOR_G                 FLOOR_B7+39 //47
#define         FLOOR_M                 FLOOR_B7+40	//48
#define         FLOOR_L                 FLOOR_B7+41	//49
#define         FLOOR_PH                FLOOR_B7+42	//50
#define         FLOOR_NO                FLOOR_B7+43	//51
#define         CARBTN_B7          		FLOOR_B7+44	//52
#define         CARBTN_B6          		FLOOR_B7+45	//53
#define         CARBTN_B5          		FLOOR_B7+46	//54
#define         CARBTN_B4          		FLOOR_B7+47	//55
#define         CARBTN_B3          		FLOOR_B7+48	//56
#define         CARBTN_B2          		FLOOR_B7+49 //57
#define         CARBTN_B1          		FLOOR_B7+50	//58
#define         CARBTN_F1          		FLOOR_B7+51	//59
#define         CARBTN_F2          		FLOOR_B7+52	//60
#define         CARBTN_F3          		FLOOR_B7+53	//61
#define         CARBTN_F4          		FLOOR_B7+54	//62
#define         CARBTN_F5          		FLOOR_B7+55	//63
#define         CARBTN_F6          		FLOOR_B7+56	//64
#define         CARBTN_F7          		FLOOR_B7+57	//65
#define         CARBTN_F8          		FLOOR_B7+58	//66
#define         CARBTN_F9          		FLOOR_B7+59	//67
#define         CARBTN_F10         		FLOOR_B7+60	//68
#define         CARBTN_F11          	FLOOR_B7+61	//69
#define         CARBTN_F12          	FLOOR_B7+62	//70
#define         CARBTN_F13          	FLOOR_B7+63	//71
#define         CARBTN_F14          	FLOOR_B7+64	//72
#define         CARBTN_F15          	FLOOR_B7+65	//73
#define         CARBTN_F16          	FLOOR_B7+66	//74
#define         CARBTN_F17          	FLOOR_B7+67	//75
#define         CARBTN_F18          	FLOOR_B7+68	//76
#define         CARBTN_F19          	FLOOR_B7+69	//77
#define         CARBTN_F20         		FLOOR_B7+70	//78
#define         CARBTN_F21          	FLOOR_B7+71	//79
#define         CARBTN_F22          	FLOOR_B7+72	//80
#define         CARBTN_F23          	FLOOR_B7+73	//81
#define         CARBTN_F24          	FLOOR_B7+74	//82
#define         CARBTN_F25          	FLOOR_B7+75	//83
#define         CARBTN_F26          	FLOOR_B7+76	//84
#define         CARBTN_F27          	FLOOR_B7+77 //85
#define         CARBTN_F28          	FLOOR_B7+78 //86
#define         CARBTN_F29          	FLOOR_B7+79 //87
#define         CARBTN_F30          	FLOOR_B7+80 //88
#define         CARBTN_F31          	FLOOR_B7+81 //89
#define         CARBTN_F32          	FLOOR_B7+82 //90
#define         PARKING_MENT      		FLOOR_B7+83 //91
#define         OPEN_MENT      		    FLOOR_B7+84	//92
#define         CANCLE_MENT      		FLOOR_B7+85	//93
#define         PUSH_MENT      		    FLOOR_B7+86	//94
#define         SILENCE_MENT            FLOOR_B7+87 //95
#define         SONG_MENT               FLOOR_B7+88 //96
#define         BEEP_MENT               FLOOR_B7+89 //97 삐 소리

#define NO_MENT 0xff // 멘트 없음




//IO 정의
#define   		_DIPSW1        RD4     //in , 테스트 모드 설정
#define   		_DIPSW2        RD5     //in , 카버튼 음성 설정
#define   		_DIPSW3        RD6     //in , Local 설정
#define   		_DIPSW4        RD7     //in ,    "

#ifdef	CPU45K80
#define   		_VOICE_ACT      LATE0   //out
#else
#define   		_VOICE_ACT      LATA4   //out
#endif

#define   		_BATTERY       LATC0   //out
#define   		_POWER_DOWN    RC2     //in
#define   		_VOICE_DOWNLOAD_PIN  RC1     //in


#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef OFF
#define OFF                    0
#endif

#ifndef ON
#define ON                     1
#endif

//
#define ELE_nCURFLOOR          RcvBuf[IdPt + S0_FLOOR] // 층수를 10진수로 표현

#define ELE_bOPEN           (RcvBuf[IdPt + S1_STATE] & S1_OPEN)
#define ELE_bCLOSE          (RcvBuf[IdPt + S1_STATE] & S1_CLOSE)
#define ELE_bOVERLOAD       (RcvBuf[IdPt + S1_STATE] & S1_OVERLOAD)
#define ELE_bEMG            (RcvBuf[IdPt + S1_STATE] & S1_EMG)
#define ELE_bBAT            (RcvBuf[IdPt + S1_STATE] & S1_BAT)
#define ELE_bAUTO           (RcvBuf[IdPt + S1_STATE] & S1_AUTO)
#define ELE_bMANUAL         (RcvBuf[IdPt + S1_STATE] & S1_MANUAL)
#define ELE_bUP             (RcvBuf[IdPt + S1_STATE] & S1_UP)

#define ELE_bDOWN           (RcvBuf[IdPt + S2_STATE] & S2_DN)
#define ELE_bCAR_MOVE       (RcvBuf[IdPt + S2_STATE] & S2_CAR_MOVE)
#define ELE_bEXT_BUT_CLR    (RcvBuf[IdPt + S2_STATE] & S2_EXT_BUT_CLR)
#define ELE_bFLOW           (RcvBuf[IdPt + S2_STATE] & S2_FLOW) // 음성시작
#define ELE_bFIRE           (RcvBuf[IdPt + S2_STATE] & S2_FIRE)
#define ELE_bCAR_BUT_CLR    (RcvBuf[IdPt + S2_STATE] & S2_CAR_BUT_CLR)
#define ELE_bOPEN_LAMP_ON   (RcvBuf[IdPt + S2_STATE] & S2_OPEN_LAMP_ON)
#define ELE_bLAMP_USER      (RcvBuf[IdPt + S2_STATE] & S2_LAMP_USER)

#define ELE_bVIP            (RcvBuf[IdPt + S3_STATE] & S3_VIP)
#define ELE_bPARKING        (RcvBuf[IdPt + S3_STATE] & S3_PARKING)
#define ELE_bSHIFT          (RcvBuf[IdPt + S3_STATE] & S3_SHIFT)
#define ELE_bUPDN_VO        (RcvBuf[IdPt + S3_STATE] & S3_UPDN_VO)
#define ELE_bOPEN_SUB       (RcvBuf[IdPt + S3_STATE] & S3_OPEN_SUB)
#define ELE_bFULL           (RcvBuf[IdPt + S3_STATE] & S3_FULL)
#define ELE_bCURKEY         (RcvBuf[IdPt + S3_STATE] & S3_CURKEY)
#define ELE_bSTOP           (RcvBuf[IdPt + S3_STATE] & S3_STOP)

#define ELE_bCAR_MOST_SERVICE   (RcvBuf[IdPt + S4_STATE] & S4_CAR_MOST_SERVICE)
#define ELE_bFAMILY_SERVICE     (RcvBuf[IdPt + S4_STATE] & S4_FAMILY_SERVICE)
//#define ELE_bARRIVE             (RcvBuf[IdPt + S4_STATE] & S4_ARRIVE)
#define ELE_bWAIT_FLR_SERVICE   (RcvBuf[IdPt + S4_STATE] & S4_WAIT_FLR_SERVICE)
#define ELE_bPARKING_READY      (RcvBuf[IdPt + S4_STATE] & S4_PARKING_READY)
#define ELE_bHALLLANTERN_UP     (RcvBuf[IdPt + S4_STATE] & S4_HALLLANTERN_UP)
#define ELE_bHALLLANTERN_DN     (RcvBuf[IdPt + S4_STATE] & S4_HALLLANTERN_DN)

#define ELE_DSP1         RcvBuf[IdPt + DSP1]
#define ELE_DSP2         RcvBuf[IdPt + DSP2]

#define ELE_mSYSSTATUS  RcvBuf[IdPt + SL_mSysStatus]

#define ELE_IN_EMG  	(RcvBuf[IdPt + SL_IN_EMG] & 0x01)
#define ELE_IN_AT  	(RcvBuf[IdPt + SL_IN_EMG] & (0x01 << 2)) // 입력 접점에 신호 ON = 0 
#define ELE_IN_UB  	(RcvBuf[IdPt + SL_IN_EMG] & (0x01 << 3))
#define ELE_IN_DB  	(RcvBuf[IdPt + SL_IN_EMG] & (0x01 << 4))



//mSysStatus
#define msysDOOROPEN    57
#define msysDOORCLOSE   58

#define BEEP_DELAY	4000 // 단위 msec


volatile const unsigned char FloorChar[] = {"B5B4B3B2B10102030405060708091011121314151617181920212223242526272829303132"};

unsigned char new_buf[64];	                                	    /*unlike the old_text this is not a CONST -> stored in data RAM */
far unsigned char * source_ptr_1 = (far unsigned char *)new_buf;    /*pointers to data*/
far unsigned char * dest_ptr_1 = (far unsigned char *)FloorChar;
unsigned char sizex = 64;


unsigned    char    TestMentDelayTimer;
unsigned    char    TmpCurVoice; //
unsigned    char    CurVoice; //
unsigned	char	CurFloorVoice;
unsigned    char    RunPgm;
unsigned    char    HwajaeVoiceCnt;
unsigned    char    OverLoadVoiceCnt;
unsigned    char    MyAddress;
unsigned    char    MyLogAdr;
unsigned    char    src;
unsigned    char    firstdata;
unsigned    char    seconddata;
unsigned    char    TimeOutBd = 0;
unsigned    char    CallMeAdr = 0;
unsigned    char    FloorXCnt;

/*
Error[000]   : _SetupDisplay (C:\micom\project\elevcan\dot_lamp\setup.obj)
Error[000]   : _DspModel (C:\micom\project\elevcan\dot_lamp\setup.obj)
*/

unsigned    char  shiftTime;
unsigned    char  MainTimer = 0;
unsigned    char  UpButtonTime = 0;
unsigned    char  DnButtonTime = 0;
unsigned    char  DspModel = 0;

unsigned    char     UpDnVoiceTimer = 0;
unsigned    char     abctimer = 0;

unsigned    char     nBefFlr = 0;
unsigned    char     nBefFlrTime = 0;

unsigned    char  YourDoor;
unsigned    char  YourDoor0;
unsigned    char  YourDoor1;
unsigned    char  YourDoor2;
unsigned    char  YourDoor3;

unsigned    char  CurCarKey[4] = {0, 0, 0, 0}; // 현재 등록된 카키 콜 상태 저장
unsigned    char  BefCarKey[4] = {0, 0, 0, 0};


bit FDsp;
bit UpKeyBit;
bit DnKeyBit;
bit BatteryRun;
bit Flow_Active;
bit valid_key;
bit active_key;
bit bVoicePlaying; // 현재 음성 방송 중인지 아닌지
bit bCloseVoice;
bit bSetCarBtnVoice;

typedef struct
{
    unsigned char CarKey[4];
} tag_Elevator;
tag_Elevator	Elevator0, Elevator1, Elevator2, Elevator3;

typedef unsigned char UCHAR;

unsigned int    IdPt;
bit bAfterCancel;
bit bSetAfterCancel;
bit bSetSong;
bit bBeepEnab;

// Voice Play Seqence
typedef enum
{
    DINGDONG_READY_SEQ,
    CURVOICE_READY_SEQ,
    DINGDONG_PLAY_SEQ,
    ALARM_PLAYING_SEQ,
    CURFLOORVOICE_PLAY_SEQ,
    CURVOICE_PLAY_SEQ,
    CURVOICE_PLAYING_SEQ,
    END_CHK_SEQ,
    END_SEQ,
    CALCEL_READY_SEQ,
    CALCEL_PLAY_SEQ,
    Default_SEQ
} tag_Sequence;
tag_Sequence	PlaySeq;

bit bDingdong;

unsigned int BeefDelayTimer = 0;



// 함수의 원형
extern void	WaitDownLoader(void);
extern void    SetupDisplayES15(unsigned char mdata, unsigned char mode);
extern void  SetupDisplay(unsigned char ft, unsigned char sd);
extern unsigned char SyncButtonCheck(unsigned char src);
extern void    SetCarKeyCancel();
extern unsigned char DspCharRdWr();
extern void    HextoASCIIByte();
extern void    TestVoicePlay();
extern unsigned char    GetCarCallMent(unsigned char);
extern unsigned char	GetVoice_CarCall(unsigned char, unsigned char*, unsigned char*);
extern  unsigned char    GetVoice_Floor(unsigned char, unsigned char);
extern unsigned char	GetVoice_OpenCloseUpDn(unsigned char);
extern unsigned char    GetVoice_State(unsigned char, unsigned char);
extern void    PortInit();
extern void InitVoice();
void SetVoice(void);
extern void SetDipSW();
extern unsigned char VoiceBusy();
extern unsigned char GetFloorMent();
extern unsigned char   GetVoice_Song(unsigned char);
extern unsigned char   GetVoice_Beep(unsigned char);




//##################################//
// 메인 함수				    	//
//##################################//

void main(void)
{
    di();
    Initial();
    PortInit();
    Timer0Init();
    InitSPI();
    Tx1ConfirmCnt = 0;
    Tx0ConfirmCnt = 0;
    ei();

    LoadSetupValue();  //120927 :SetupCheck() ?? ??
    CmpSetBit = 0;          //new
    MaskSetBit = 0;         //new

    di();
    CAN_Init();
    ei();

    InitVoice();
    SetDipSW();
    SetVoice();
    if (bSetSong) bSetCarBtnVoice = FALSE;

    while (1)
    {
        CLRWDT();

        // Voice Downlod 중...
        if (_VOICE_DOWNLOAD_PIN)
        {
            WaitDownLoader();
        }

        DspCharRdWr(); // CAR CALL 음성을 위한 엘리베이터 각층 디스플레이 값 저장
        SetCarKeyCancel(); // CAR CALL 취소 값 셋팅

        TmpCurVoice = NO_MENT;
        TmpCurVoice = GetVoice_State(TmpCurVoice, CurVoice);
        if (bDingdong == FALSE) TmpCurVoice = GetVoice_OpenCloseUpDn(TmpCurVoice);
        TmpCurVoice = GetVoice_Floor(TmpCurVoice, GetFloorMent());
        if (bSetCarBtnVoice) TmpCurVoice = GetVoice_CarCall(TmpCurVoice, CurCarKey, BefCarKey);
        if (bSetSong) TmpCurVoice = GetVoice_Song(TmpCurVoice);
        // Beef 멘트 관련
        if (TmpCurVoice != NO_MENT)	BeefDelayTimer = BEEP_DELAY;
		if(bBeepEnab)
		{
	        if (BeefDelayTimer > BEEP_DELAY)
	        {
	            TmpCurVoice = GetVoice_Beep(TmpCurVoice);
	            if (TmpCurVoice == BEEP_MENT)	BeefDelayTimer = 0;
	        }
		}

        if (TmpCurVoice != NO_MENT)
        {
            CurVoice = TmpCurVoice;
            _VOICE_ACT = VOICE_ON;
            if (bVoicePlaying)
            {
                SPI_Stop_Play(); // 일단, 기존 방송 중이던 음성 중지 !
                if ((CurVoice >= START_FL) && (CurVoice <= END_FL))
                {
                    PlaySeq = DINGDONG_READY_SEQ;
                    CurFloorVoice = CurVoice;
                }
                else
                {
                    PlaySeq = CURVOICE_READY_SEQ;
                }
            }
            else
            {
                if ((CurVoice >= START_FL) && (CurVoice <= END_FL))   // 층 도착 !
                {
                    PlaySeq = DINGDONG_PLAY_SEQ;
                    CurFloorVoice = CurVoice;
                }
                else
                {
                    PlaySeq = CURVOICE_PLAY_SEQ;
                }
            }
        }


        switch (PlaySeq)
        {
        case DINGDONG_READY_SEQ:
            if (bVoicePlaying == FALSE)
            {
                PlaySeq = DINGDONG_PLAY_SEQ;
            }
            break;
        case DINGDONG_PLAY_SEQ:
            SPI_Play(DINGDONG_MENT); // 도착 알림 딩동 !
            bDingdong = TRUE;
            PlaySeq = ALARM_PLAYING_SEQ;
            break;
        case ALARM_PLAYING_SEQ:
            if (bVoicePlaying)
            {
                PlaySeq = CURVOICE_READY_SEQ;
            }
            break;
        case CURVOICE_READY_SEQ:
            if (bVoicePlaying == FALSE)
            {
                if (CurVoice & 0x80)
                    PlaySeq = END_CHK_SEQ;
                else
                    PlaySeq = CURVOICE_PLAY_SEQ;

                if (bDingdong)
                    PlaySeq = CURFLOORVOICE_PLAY_SEQ;
            }
            break;
        case CURFLOORVOICE_PLAY_SEQ:
            SPI_Play(CurFloorVoice);
            bDingdong = FALSE;
            PlaySeq = CURVOICE_PLAYING_SEQ;
            break;
        case CURVOICE_PLAY_SEQ:
            SPI_Play(CurVoice); // 도착 '몇 층입다','문이열립이다','닫힙니다' 등 안내방송 출력
            PlaySeq = CURVOICE_PLAYING_SEQ;
            break;
        case CURVOICE_PLAYING_SEQ:
            if (bVoicePlaying)
            {
                PlaySeq = END_CHK_SEQ;
                if (bAfterCancel)
                {
                    bAfterCancel = FALSE;
                    PlaySeq = CALCEL_READY_SEQ;
                }
            }
            break;
        case END_CHK_SEQ:
            if (bVoicePlaying == FALSE)
            {
                PlaySeq = END_SEQ;
                _VOICE_ACT = VOICE_OFF;
            }
            break;
        case CALCEL_READY_SEQ:
            if (bVoicePlaying == FALSE)
            {
                PlaySeq = CALCEL_PLAY_SEQ;
            }
            break;
        case CALCEL_PLAY_SEQ:
            SPI_Play(CANCLE_MENT); // 도착 알림 딩동 !
            PlaySeq = CURVOICE_PLAYING_SEQ;
            break;
        }


        if (VoiceBusy())
        {
            bVoicePlaying = TRUE;
        }
        else
        {
            if (PlaySeq == END_SEQ)
            {
                CurVoice = NO_MENT;
                bBeepEnab = TRUE;
                bDingdong = FALSE;
            }
            bVoicePlaying = FALSE;
        }
    }
}


//##################################//
// 인터럽트 함수			    	//
//##################################//

void interrupt isr(void)
{
//    unsigned char i;


    if (TMR0IF)
    {

        TMR0IF = 0 ;
        TMR0L = MSEC_L;
        TMR0H = MSEC_H;

        TestMentDelayTimer++;
        shiftTime++;

        if (BeefDelayTimer < 0xffff) BeefDelayTimer++;

        abctimer++;
        if (abctimer > 100)
        {
            abctimer = 0;
            if (UpDnVoiceTimer < 200)	UpDnVoiceTimer++;
            if (nBefFlrTime < 200)	nBefFlrTime++;

            if (FloorXCnt < 200)	FloorXCnt++;


        }
    }


#ifdef	CPU45K80
    if (PIR5 > 0)
    {
        CanInterrupt();
    }
#else
    if (PIR3 > 0)
    {
        CanInterrupt();
    }
#endif

}


//##################################//
// 일반 함수들                      //
//##################################//


unsigned char GetFloorMent(void)
{
    unsigned char tmMent;
    unsigned char cDotDsp, bValid;

    bValid = TRUE;
    // Dot1 체크 (10의 자리)
    cDotDsp = ELE_DSP1;
    if (cDotDsp == 'B')
    {
        tmMent = FLOOR_F1;
    }
    else if (cDotDsp == 'P')
    {
        tmMent = FLOOR_F1;
    }
    else if (cDotDsp == 'G')
    {
        tmMent = FLOOR_F1;
    }
    else if (cDotDsp == '0')
    {
        tmMent = FLOOR_B1;
    }
    else if (cDotDsp == '1')
    {
        tmMent = 10 + FLOOR_B1;
    }
    else if (cDotDsp == '2')
    {
        tmMent = 20 + FLOOR_B1;
    }
    else if (cDotDsp == '3')
    {
        tmMent = 30 + FLOOR_B1;
    }
    else
    {
        //tmMent = (RcvBuf[IdPt] | 0x80);
        bValid = FALSE;
        tmMent = 0xff;
    }

    // Dot2 체크(1의 자리)
    if (bValid)
    {
        cDotDsp = ELE_DSP2;
        if (cDotDsp == '0')
        {
            if (tmMent < (10 + FLOOR_B1))
            {
                tmMent = 0xff;
            }
        }
        else if (cDotDsp == 'F')
        {
            if (ELE_DSP1 == 'G')
            {
                tmMent = FLOOR_G;
            }
            else
            {
                tmMent = (tmMent + 4);
            }
        }
        else if (cDotDsp == 'G')
        {
            tmMent = FLOOR_G;
        }
        else if (cDotDsp == 'M')
        {
            tmMent = FLOOR_M;
        }
        else if (cDotDsp == 'H')
        {
            tmMent = FLOOR_PH;
        }
        else if ((cDotDsp >= '1') && (cDotDsp <= '9'))
        {
            if (tmMent == FLOOR_F1)
                tmMent = tmMent - (cDotDsp - '0');
            else
                tmMent = tmMent + (cDotDsp - '0');
        }
        else
        {
            tmMent = 0xff;
        }
    }
    return tmMent;
}


unsigned char    GetVoice_Floor(unsigned char tmpCurVoice, unsigned char curFloorMent)
{
    static unsigned char befFloorMent = 0;
    static bit bmentSaveEnab;

    if (tmpCurVoice != 0xff)
        return tmpCurVoice;

    if (curFloorMent != 0xfe)
    {
        if (ELE_bAUTO)   // 자동 !
        {
            if (ELE_bFLOW)
            {
                if (bmentSaveEnab && (curFloorMent != befFloorMent))
                {
                    tmpCurVoice = befFloorMent = curFloorMent;
                    bmentSaveEnab = FALSE;
                }
            }
            else
            {
                bmentSaveEnab = TRUE;
            }
        }
        else   // 자동이 아닌 경우 !
        {
            if (curFloorMent != befFloorMent)
            {
                tmpCurVoice = befFloorMent = curFloorMent;
                bBeepEnab = FALSE;
            }
        }
    }
    return tmpCurVoice;
}

// 문이 열립니다, 닫힙니다, 올라갑니다, 내려갑니다.
unsigned char   GetVoice_OpenCloseUpDn(unsigned char tmpCurVoice)
{
    static unsigned char UpDnVoice = 0x0;
    static bit bopened = FALSE;
    static bit bupdned = FALSE;

    if (tmpCurVoice != 0xff)
        return tmpCurVoice;

    if (ELE_bPARKING_READY)
        return tmpCurVoice;

    if (ELE_bAUTO)   // 자동 !
    {
        // Up, Down 시, 음성 처리
        if (ELE_bOPEN && (UpDnVoiceTimer > 40) && bopened && (bupdned == FALSE))
        {
            if (ELE_bUP)
            {
                tmpCurVoice = UP_MENT; // 올라갑니다 !
                bupdned = TRUE;
            }
            else if (ELE_bDOWN)
            {
                tmpCurVoice = DOWN_MENT; // 내려 갑니다 !
                bupdned = TRUE;
            }
        }
        // Door Open 시, 음성 처리
        if (ELE_bCAR_MOVE == FALSE)
        {
            if ((ELE_mSYSSTATUS == msysDOOROPEN) && (bopened == FALSE) && !bVoicePlaying)   //open
            {
                tmpCurVoice = OPEN_MENT; // 문이 열립니다 !
                bopened = TRUE;
                UpDnVoiceTimer = 0;
            }
            else if ((ELE_mSYSSTATUS == msysDOORCLOSE) && bopened)   //close
            {
                tmpCurVoice = CLOSE_MENT; // 문이 닫힙니다 !
                bopened = FALSE;
            }
        }
        else
        {
            UpDnVoiceTimer = 0;
            bupdned = FALSE;
        }
    }
    else   // 자동이 아닐 때 !
    {
        if (ELE_bCLOSE)   // 문이 닫혔을 때 !
        {
            if (bupdned == FALSE)
            {
                if (ELE_bUP && (UpDnVoice != UP_MENT))
                {
                    tmpCurVoice = UpDnVoice = UP_MENT;
                    bupdned = TRUE;
                }
                else if (ELE_bDOWN && (UpDnVoice != DOWN_MENT))
                {
                    tmpCurVoice = UpDnVoice = DOWN_MENT;
                    bupdned = TRUE;
                }
            }
        }
        else
        {
            UpDnVoice = 0;
            bupdned = FALSE;
        }
    }

    return(tmpCurVoice);
}


unsigned char   GetVoice_Song(unsigned char befVoice)
{
    unsigned char tmCurVoice;
    static bit bSong = FALSE;

    if (befVoice != 0xff)
        return befVoice;

    if (ELE_bCAR_MOVE && ELE_bAUTO)
    {
        if (ELE_bFLOW) bSong = FALSE;
        if (!VoiceBusy() && bSong && ELE_bUP)
        {
            tmCurVoice = SONG_MENT;
            return tmCurVoice;
        }
        else if (!VoiceBusy() && bSong && ELE_bDOWN)
        {
            tmCurVoice = SONG_MENT;
            return tmCurVoice;
        }
    }
    else
    {
        bSong = TRUE;
    }
    return befVoice;
}

unsigned char   GetVoice_Beep(unsigned char tmpCurVoice)
{
    unsigned char tmCurVoice;

    if (tmpCurVoice != 0xff) // 이미 다른 음성이 등록되어 있다면 !
        return tmpCurVoice;

    if (ELE_IN_AT && ELE_bCAR_MOVE)
    {
        if (!VoiceBusy() && ((ELE_IN_UB == 0) || (ELE_IN_DB == 0)))
        {
            tmpCurVoice = BEEP_MENT;
        }
    }
    return tmpCurVoice;
}


unsigned char    GetVoice_State(UCHAR befVoice, UCHAR curVoice)
{
    unsigned char tmMent;
    static unsigned char EmergencyVoiceCnt = 0;

    if (befVoice != 0xff)
        return befVoice;

    tmMent = befVoice;
    // 파킹
    if (ELE_bPARKING_READY  && (curVoice != PARKING_MENT))
    {
        tmMent = PARKING_MENT;
    }
    if (ELE_bPARKING  && (curVoice == PARKING_MENT))
    {
        if (bVoicePlaying)
        {
            SPI_Stop_Play();
            bVoicePlaying = FALSE;
        }
    }

    // 오버로드
    if ((ELE_bOPEN || ELE_bOPEN_SUB) && ELE_bOVERLOAD && (curVoice != OVERLOAD_MENT))
    {
        tmMent = OVERLOAD_MENT;
    }

    // 화재
    if (ELE_bFIRE && (curVoice != HWAJAE_MENT))
    {
        tmMent = HWAJAE_MENT;
    }

    // 비상
    // [151006] 자동시에만 EMG MENT 출력 되도록 수정
    if (ELE_bEMG  && (curVoice != EMERGENCY_MENT) && (ELE_IN_AT == 0))
    {
        if (EmergencyVoiceCnt < 10)	EmergencyVoiceCnt++;
        if (EmergencyVoiceCnt < 6)
            tmMent = EMERGENCY_MENT;
    }
    if (ELE_bEMG == FALSE)
        EmergencyVoiceCnt = 0;

    // 밧데리
    if (ELE_bBAT  && (curVoice != POWER_DOWN_MENT))
    {
        tmMent = POWER_DOWN_MENT;
    }

    return tmMent;

}


//카버튼 음성 처리
unsigned char   GetVoice_CarCall(UCHAR tmpCurVoice, UCHAR *curkey, UCHAR *befkey)
{
    unsigned char j;
    unsigned char iFloor; // 0~31
    unsigned char bitKey;

    if (tmpCurVoice != 0xff)
        return tmpCurVoice;
    if (!ELE_bAUTO || ELE_bFLOW)
        return tmpCurVoice;
    if (!ELE_bUP && !ELE_bDOWN)
        return tmpCurVoice;
    if (CurVoice != 0xff)
        return tmpCurVoice;

    bitKey = 0x01;
    j = 0;
    for (iFloor = 0; iFloor < 32; iFloor++)
    {
        if (curkey[j] != befkey[j])   //8개의 카키 상태 비교
        {
            // 한 개의 카키 상태 비교
            if ((curkey[j] & bitKey) &&  !(befkey[j] & bitKey)) // 카콜 등록이면? (참 && !거짓)
            {
                if (iFloor != (ELE_nCURFLOOR - 1)) // 카콜 등록 층이 현재 층과 같지 않을 때 ! (즉, 같을 땐 무시)
                {
                    befkey[j] = (befkey[j] | bitKey);
                    tmpCurVoice = GetCarCallMent(iFloor);
                }
                break;
            }
            else if (!(curkey[j] & bitKey) && (befkey[j] & bitKey)) //카콜 취소이면? (!거짓 && 참)
            {
                befkey[j] = (befkey[j] & ~bitKey);

                if (bSetAfterCancel)
                {
                    bAfterCancel = TRUE;
                    tmpCurVoice = GetCarCallMent(iFloor);
                }
                else
                {
                    tmpCurVoice = CANCLE_MENT;
                }
                break;
            }

            bitKey = (bitKey << 1);
            if (bitKey == 0)
            {
                j++;
                bitKey = 0x01;
            }
        }
        else
        {
            j++;
            bitKey = 0x01;
            iFloor = (iFloor + 7);
        }
    }
    return tmpCurVoice;
}



// 카콜 키 상태 값을 CurVoide에 저장한다.
unsigned char    GetCarCallMent(unsigned char Call_Floor)
{
    unsigned char   cDotDsp, i, bValid;
    UCHAR tmMent;

    bValid = TRUE;
    // Dot1
    i = (Call_Floor * 2);
    cDotDsp = FloorChar[i + 0];
    if (cDotDsp == 'B')
    {
        tmMent = CARBTN_F1;
    }
    else if (cDotDsp == '0')
    {
        tmMent = CARBTN_B1;
    }
    else if (cDotDsp == '1')
    {
        tmMent = 10 + CARBTN_B1;
    }
    else if (cDotDsp == '2')
    {
        tmMent = 20 + CARBTN_B1;
    }
    else if (cDotDsp == '3')
    {
        tmMent = 30 + CARBTN_B1;
    }
    else
    {
        bValid = FALSE;
        tmMent = 0xff;
    }
    // Dot2
    if (bValid)
    {
        cDotDsp = FloorChar[i + 1];
        if (cDotDsp == '0')
        {
            if (tmMent < (10 + CARBTN_B1))
                tmMent = 0xff;
        }
        else if (cDotDsp == 'F')
        {
            tmMent = (tmMent + 4);
        }
        else if ((cDotDsp >= '1') && (cDotDsp <= '9'))
        {
            if (tmMent == CARBTN_F1) // 지하층이면?
                tmMent = tmMent - (cDotDsp - '0');
            else // 지상층이면?
                tmMent = tmMent + (cDotDsp - '0');
        }
        else
        {
            tmMent = 0xff;
        }
    }
    return tmMent;
}



void    SetCarKeyCancel(void)
{
    unsigned char bBefBtnClr;
    unsigned char i, j, k;

    bBefBtnClr = OFF;

    if (!ELE_bUP && !ELE_bDOWN)
    {
        bBefBtnClr = ON;
    }
    if (ELE_bEXT_BUT_CLR || ELE_bCAR_BUT_CLR)
    {
        bBefBtnClr = ON;
    }

    if (bBefBtnClr == ON)
    {
        CurCarKey[0] = Elevator0.CarKey[0] = Elevator1.CarKey[0]
                                             = Elevator2.CarKey[0] = Elevator3.CarKey[0] = BefCarKey[0] = 0;
        CurCarKey[1] = Elevator0.CarKey[1] = Elevator1.CarKey[1]
                                             = Elevator2.CarKey[1] = Elevator3.CarKey[1] = BefCarKey[1] = 0;
        CurCarKey[2] = Elevator0.CarKey[2] = Elevator1.CarKey[2]
                                             = Elevator2.CarKey[2] = Elevator3.CarKey[2] = BefCarKey[2] = 0;
        CurCarKey[3] = Elevator0.CarKey[3] = Elevator1.CarKey[3]
                                             = Elevator2.CarKey[3] = Elevator3.CarKey[3] = BefCarKey[3] = 0;
    }

    if (ELE_bOPEN || ELE_bOPEN_SUB)
    {
        k = (ELE_nCURFLOOR - 1);
        i = (k / 8);
        j = (k % 8);
        k = 0x01;
        k = (k << j);

        BefCarKey[i] = (BefCarKey[i] & ~k);
        CurCarKey[i] = (CurCarKey[i]  & ~k);
        Elevator0.CarKey[i] = (Elevator0.CarKey[i] & ~k);
        Elevator1.CarKey[i] = (Elevator1.CarKey[i] & ~k);
        Elevator2.CarKey[i] = (Elevator2.CarKey[i] & ~k);
        Elevator3.CarKey[i] = (Elevator3.CarKey[i] & ~k);
    }
}


// 음성 다운로드
void	WaitDownLoader(void)
{

    SSPEN = 0;

    SSPCON1 = 0;

    TRISC3 = 1; //sck
    TRISC4 = 1; //sdi
    TRISC5 = 1; //sdo
    TRISA5 = 1; //ss

    do
    {
        CLRWDT();
    }
    while (_VOICE_DOWNLOAD_PIN);


    while (1);

}


void    SetupDisplayES15(unsigned char mdata, unsigned char mode)
{
}

void  SetupDisplay(unsigned char ft, unsigned char sd)
{
}


unsigned char SyncButtonCheck(unsigned char src)
{
    unsigned char i;

    if (RxEidBuffer & HOST_BOARD)   // Host !
    {
        if (SrcAddress  == LocalNumber)	return(1);
        else							return(0);
    }
    else   // Slave !
    {
        if (SrcAddress  == LocalNumber)
        {
            i = (unsigned char)RxEidBuffer;
            if ((i == 0x80) || (i == 0x81) || (i == 0x82) || (i == 0x83))   // CAR Board
            {
                return(1);
            }
            else
            {
                return(0);
            }
        }
        else	return(0);
    }
}


// CarKey 등록
void    MyLampCheck(void)
{
    unsigned int i, j;
    i = 0;
    j = 0;

    i = (unsigned char)RxEidBuffer;

    switch (i)   // Car Address
    {
    case    0x80:
        YourDoor0 = EqualDataBuf[2]; // mCarOpCl
        Elevator0.CarKey[0] = EqualDataBuf[3];
        Elevator0.CarKey[1] = EqualDataBuf[4];
        Elevator0.CarKey[2] = EqualDataBuf[5];
        Elevator0.CarKey[3] = EqualDataBuf[6];
        j = 1;
        break;
    case    0x81:
        YourDoor1 = EqualDataBuf[2];
        Elevator1.CarKey[0] = EqualDataBuf[3];
        Elevator1.CarKey[1] = EqualDataBuf[4];
        Elevator1.CarKey[2] = EqualDataBuf[5];
        Elevator1.CarKey[3] = EqualDataBuf[6];
        j = 1;
        break;
    case    0x82:
        YourDoor2 = EqualDataBuf[2];
        Elevator2.CarKey[0] = EqualDataBuf[3];
        Elevator2.CarKey[1] = EqualDataBuf[4];
        Elevator2.CarKey[2] = EqualDataBuf[5];
        Elevator2.CarKey[3] = EqualDataBuf[6];
        j = 1;
        break;
    case    0x83:
        YourDoor3 = EqualDataBuf[2];
        Elevator3.CarKey[0] = EqualDataBuf[3];
        Elevator3.CarKey[1] = EqualDataBuf[4];
        Elevator3.CarKey[2] = EqualDataBuf[5];
        Elevator3.CarKey[3] = EqualDataBuf[6];
        j = 1;
        break;
    }

    if (j == 1)
    {
        YourDoor  = YourDoor0   | YourDoor1   | YourDoor2   | YourDoor3;
        CurCarKey[0] = Elevator0.CarKey[0] | Elevator1.CarKey[0] |
                       Elevator2.CarKey[0] | Elevator3.CarKey[0];
        CurCarKey[1] = Elevator0.CarKey[1] | Elevator1.CarKey[1] |
                       Elevator2.CarKey[1] | Elevator3.CarKey[1];
        CurCarKey[2] = Elevator0.CarKey[2] | Elevator1.CarKey[2] |
                       Elevator2.CarKey[2] | Elevator3.CarKey[2];
        CurCarKey[3] = Elevator0.CarKey[3] | Elevator1.CarKey[3] |
                       Elevator2.CarKey[3] | Elevator3.CarKey[3];
    }
}


// CAR CALL 음성을 위한 엘리베이터 각층 디스플레이 값 저장
unsigned char DspCharRdWr(void)
{
    unsigned char   CurFlrNum;

    if (ELE_nCURFLOOR > 32)	return(0);
    if (ELE_nCURFLOOR < 1)	return(0);

    if (nBefFlr == ELE_nCURFLOOR)
    {
        nBefFlrTime = 0;
    }
    else
    {
        if (nBefFlrTime > 3)
        {
            nBefFlrTime = 0;
            nBefFlr = ELE_nCURFLOOR;
            CurFlrNum = ELE_nCURFLOOR - 1;
            CurFlrNum = (CurFlrNum * 2);
            if ((ELE_DSP1 != FloorChar[CurFlrNum]) || (ELE_DSP2 != FloorChar[CurFlrNum + 1]))
            {
                new_buf[CurFlrNum + 0] = ELE_DSP1;
                new_buf[CurFlrNum + 1] = ELE_DSP2;
                flash_write(source_ptr_1, sizex, dest_ptr_1);
            }
        }
    }
    return(0);
}




void    HextoASCIIByte(void)
{
    unsigned char   i;

    i = (src & 0xf0) >> 4;
    if (i < 0x0a)   i = i + '0';
    else         i = i + '7';
    firstdata = i;

    i = (src & 0x0f);
    if (i < 0x0a)   i = i + '0';
    else         i = i + '7';
    seconddata = i;
}



void    TestVoicePlay(void)
{
    unsigned bBusy;

    TmpCurVoice = 0;
    TestMentDelayTimer = 0;
    _VOICE_ACT = VOICE_ON;


    for (; 1;)
    {
        CLRWDT();

        if (_VOICE_DOWNLOAD_PIN)
            WaitDownLoader();

        bBusy = VoiceBusy();

        CLRWDT();

        if (bBusy == FALSE)
        {
            if (TestMentDelayTimer > 200)
            {
                SPI_Play(TmpCurVoice);
                TmpCurVoice++;
                if (TmpCurVoice > 100)
                    TmpCurVoice = 0;
                TestMentDelayTimer = 0;
            }
        }
        else
        {
            TestMentDelayTimer = 0;
        }
    }

}



/*******************************************************
        manual play and record
*******************************************************/

void    PortInit(void)
{
    TRISE2 = 1;	  // port E data direction...(output)
    TRISE1 = 1;
    TRISE0 = 1;

// TRISD Register
    TRISD7 = 1;	// port D data direction....(output)
    TRISD6 = 1;
    TRISD5 = 1;
    TRISD4 = 1;
    TRISD3 = 1;
    TRISD2 = 1;
    TRISD1 = 1;
    TRISD0 = 1;

// TRISC Register
    TRISC7 = 1;	// port C data direction
    TRISC6 = 1;
    TRISC5 = 1;
    TRISC4 = 1;
    TRISC3 = 1;
    TRISC2 = 1;
    TRISC1 = 1;
    TRISC0 = 1;

// TRISB Register
    TRISB7 = 1;	// port B data direction
    TRISB6 = 1;
    TRISB5 = 1;
    TRISB4 = 1;
    TRISB3 = 1; //can rx
    TRISB2 = 1; //can tx
    TRISB1 = 1; //in
    TRISB0 = 1; //in

// TRISA Register
    TRISA7 = 1;	// port A data direction
    TRISA6 = 1;
    TRISA5 = 1;

    TRISA3 = 1;
    TRISA2 = 1;
    TRISA1 = 1;
    TRISA0 = 1;

    TRISC0 = 0;

// LATE Register
    LATE2 = 1;	// port E data latch
    LATE1 = 1;
    LATE0 = 1;

// LATD Register
    LATD7 = 1;	// port D data latch
    LATD6 = 1;
    LATD5 = 1;
    LATD4 = 1;
    LATD3 = 1;
    LATD2 = 1;
    LATD1 = 1;
    LATD0 = 1;


// LATC Register
    LATC7 = 1;	// port C data latch
    LATC6 = 1;
    LATC5 = 1;
    LATC4 = 1;
    LATC3 = 1;
    LATC2 = 1;
    LATC1 = 1;
    LATC0 = 1;

// LATB Register
    LATB7 = 1;	// port B data latch
    LATB6 = 1;
    LATB5 = 1;
    LATB4 = 1;
    LATB3 = 1;
    LATB2 = 1;
    LATB1 = 1;
    LATB0 = 1;

// LATA Register
    LATA7 = 1;	// port A data latch
    LATA6 = 1;
    LATA5 = 1;
    LATA3 = 1;
    LATA2 = 1;
    LATA1 = 1;
    LATA0 = 1;

#ifndef		CPU45K80
    TRISA4 = 0;
    LATA4 = 1;
#else
    TRISE0 = 0;
    LATE0 = 1;
#endif
}


void SetDipSW()
{
    if (_DIPSW3 && _DIPSW4)         LocalNumber = 0;
    else if (!_DIPSW3 && _DIPSW4)   LocalNumber = 1;
    else if (_DIPSW3 && !_DIPSW4)  LocalNumber = 2;
    else if (!_DIPSW3 && !_DIPSW4)  LocalNumber = 3;

    IdPt = (LocalNumber * HOST_DATA_RECOD) + RCV_DATA;
    RcvBuf[IdPt+S0_FLOOR] = 0x0;

    if (!_DIPSW2)
    {
        bSetCarBtnVoice = TRUE;
    }
    else
    {
        bSetCarBtnVoice = FALSE;
    }
    if (!_DIPSW1)
    {
        TestVoicePlay();
    }
}


unsigned char VoiceBusy(void)
{
    if (SPI_Play_Status_Chk()) // 음성멘트 방송중이면 OUT1 LED에 불이 들어온다.
        return TRUE;
    else
        return FALSE;
}


void InitVoice(void)
{
    unsigned char i;

    FloorXCnt = 0;
    for (; FloorXCnt < 10;)
    {
        CLRWDT();
    }
    FloorXCnt = 0;

    WriteSPI_ADDR(ADD00_SYS_CON, 0x08);
    WriteSPI_ADDR(ADD00_SBC_CON, 0x0);
    WriteSPI_ADDR(ADD00_AUDIO_CON, 0x02);
    WriteSPI_ADDR(ADD00_LED_CON, 0xff);
    WriteSPI_ADDR(ADD00_SYS_CON, 0x0);

    _VOICE_ACT = VOICE_OFF;
    SPI_Stop_Play();

    _BATTERY = ON;
    while (!_POWER_DOWN)
    {
        _BATTERY = ON;
    }
    _BATTERY = OFF;
    BatteryRun = 0;

    MyAddress = VOICE_ADR;
    RunPgm = 0x55;
    CanDatacnt0 = 2;
    CanDatacnt1 = 2;
    CanCmd = 0;

    for (i = 0; i < 64; i++)
    {
        new_buf[i] = FloorChar[i];
        nBefFlr = 0;
        nBefFlrTime = 0;
    }

    RunPgm = 0x0;
    valid_key = 0;
    active_key = 0;
    BatteryRun = 0;
    Flow_Active = 0;
    CurVoice = 0xff;
    PlaySeq = Default_SEQ;
    bVoicePlaying = 0;
    TmpCurVoice = 0xff;
    HwajaeVoiceCnt = 0;
    OverLoadVoiceCnt = 0;
    bAfterCancel = FALSE;
}

void SetVoice(void)
{
    bSetAfterCancel = TRUE;
    bSetSong = FALSE;
}






