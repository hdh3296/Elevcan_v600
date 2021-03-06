
#include  "iodef.h"


unsigned int    __attribute__((section(".usercode"))) CurSelPortIn(unsigned int port_sel)
{
	unsigned int retval=1;
	unsigned int NcNo=1;

    if(port_sel & 0x80)     NcNo=1;      //N_Open
    else                    NcNo=0;      //N_Close

    port_sel=(port_sel & 0x7f);
	
	switch(port_sel){
		case	SILK_EMG:
				if(IN_EMG_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_PRK:
				if(IN_PRK_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_AUTO:
				if(IN_AUTO_PORT)	retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_U_B:
				if(IN_U_B_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_D_B:
				if(IN_D_B_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_OLS:
				if(IN_OP_E_PORT)	retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_GS:
				if(IN_CL_E_PORT)	retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_DS:
				if(IN_HL_D_PORT)	retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_SU1:
				if(IN_SU1_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_SD1:
				if(IN_SD1_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_SFT:
				if(IN_SFT_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_OVL:
				if(IN_OVL_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_ULS:
				if(IN_ULS_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_DLS:
				if(IN_DLS_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_LU:
				if(IN_LU_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_LD:
				if(IN_LD_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_GR:
				if(IN_GR_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_BAT:
				if(IN_BAT_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_PASS:
				if(IN_PASS_PORT)	retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FIRE:
				if(IN_FIRE_PORT)	retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_WATER:
				if(IN_WATER_PORT)	retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FULL:
				if(IN_FULL_PORT)	retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_MM:
				if(IN_MM_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FHM:
				if(IN_FHM_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FR1:
				if(IN_FR1_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FR2:
				if(IN_FR2_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_GS2:
				if(IN_GS2_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_DS2:
				if(IN_DS2_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_SU2:
				if(IN_SU2_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_SD2:
				if(IN_SD2_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_BM:
				if(IN_BM_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_INV:
				if(IN_INV_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_X0:
				if(IN_X0_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_X1:
				if(IN_X1_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_X2:
				if(IN_X2_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_X3:
				if(IN_X3_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_X4:
				if(IN_X4_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_X5:
				if(IN_X5_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_X6:
				if(IN_X6_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_X7:
				if(IN_X7_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FS0:
				if(IN_FS0_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FS1:
				if(IN_FS1_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FS2:
				if(IN_FS2_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FS3:
				if(IN_FS3_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FS4:
				if(IN_FS4_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_DER:
				if(IN_DER_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_FID:
				if(IN_FID_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
		case	SILK_UND:
				if(IN_UND_PORT)	    retval=1;		
				else		        retval=0;
                if(!NcNo)           retval=!retval;               
				break;
/////////////////////////////////////////////////
		case	SILK_DOOR_HOLD:
				if(IN_DOOR_HOLD_PORT)	    retval=1;		
				else		        		retval=0;
                if(!NcNo)           		retval=!retval;               
				break;
		case	SILK_VIRTUAL_X1:
				if(IN_VIRTUAL_X1_PORT)	    retval=1;		
				else		        		retval=0;
                if(!NcNo)           		retval=!retval;               
				break;
		case	SILK_VIRTUAL_X2:
				if(IN_VIRTUAL_X2_PORT)	    retval=1;		
				else		        		retval=0;
                if(!NcNo)           		retval=!retval;               
				break;
		case	SILK_VIRTUAL_X3:
				if(IN_VIRTUAL_X3_PORT)	    retval=1;		
				else		        		retval=0;
                if(!NcNo)           		retval=!retval;               
				break;
		case	SILK_VIRTUAL_X4:
				if(IN_VIRTUAL_X4_PORT)	    retval=1;		
				else		        		retval=0;
                if(!NcNo)           		retval=!retval;               
				break;
		case	SILK_VIRTUAL_X5:
				if(IN_VIRTUAL_X5_PORT)	    retval=1;		
				else		        		retval=0;
                if(!NcNo)           		retval=!retval;               
				break;
		case	SILK_VIRTUAL_X6:
				if(IN_VIRTUAL_X6_PORT)	    retval=1;		
				else		        		retval=0;
                if(!NcNo)           		retval=!retval;               
				break;
		case	SILK_VIRTUAL_X7:
				if(IN_VIRTUAL_X7_PORT)	    retval=1;		
				else		        		retval=0;
                if(!NcNo)           		retval=!retval;               
				break;
///////////////////////////////////
		case	EXT_EX0:
				if(sRamDArry[mExtIN0] & 0x01)	    retval=1;		
				else		        				retval=0;
                if(!NcNo)           				retval=!retval;               
				break;
		case	EXT_EX1:
				if(sRamDArry[mExtIN0] & 0x02)	    retval=1;		
				else		        				retval=0;
                if(!NcNo)           				retval=!retval;               
				break;
		case	EXT_EX2:
				if(sRamDArry[mExtIN0] & 0x04)	    retval=1;		
				else		        				retval=0;
                if(!NcNo)           				retval=!retval;               
				break;
		case	EXT_EX3:
				if(sRamDArry[mExtIN0] & 0x08)	    retval=1;		
				else		        				retval=0;
                if(!NcNo)           				retval=!retval;               
				break;
		case	EXT_EX4:
				if(sRamDArry[mExtIN0] & 0x10)	    retval=1;		
				else		        				retval=0;
                if(!NcNo)           				retval=!retval;               
				break;
		case	EXT_EX5:
				if(sRamDArry[mExtIN0] & 0x20)	    retval=1;		
				else		        				retval=0;
                if(!NcNo)           				retval=!retval;               
				break;
		case	EXT_EX6:
				if(sRamDArry[mExtIN0] & 0x40)	    retval=1;		
				else		        				retval=0;
                if(!NcNo)           				retval=!retval;               
				break;
		case	EXT_EX7:
				if(sRamDArry[mExtIN0] & 0x80)	    retval=1;		
				else		        				retval=0;
                if(!NcNo)           				retval=!retval;               
				break;


		default:
				retval=1;
				break;
    }

    return(retval);
}



/*

unsigned int    __attribute__((section(".usercode"))) CurSelPortInSetClr(unsigned int port_sel,unsigned int port_val)
{
	unsigned int retval=1;
	unsigned int NcNo=1;

    if(port_sel & 0x80)     NcNo=1;      //N_Open
    else                    NcNo=0;      //N_Close

    port_sel=(port_sel & 0x7f);
	                                
	switch(port_sel){
		case	SILK_EMG:
                if(!NcNo)  port_val=!port_val;               
				IN_EMG_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_PRK:
                if(!NcNo)  port_val=!port_val;               
				IN_PRK_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_AUTO:
                if(!NcNo)  port_val=!port_val;               
				IN_AUTO_PORT	    =port_val;		
                retval=0;
				break;
		case	SILK_U_B:
                if(!NcNo)  port_val=!port_val;               
				IN_U_B_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_D_B:
                if(!NcNo)  port_val=!port_val;               
				IN_D_B_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_OLS:
                if(!NcNo)  port_val=!port_val;               
				IN_OP_E_PORT	    =port_val;		
                retval=0;
				break;
		case	SILK_GS:
                if(!NcNo)  port_val=!port_val;               
				IN_CL_E_PORT	    =port_val;		
                retval=0;
				break;
		case	SILK_DS:
                if(!NcNo)  port_val=!port_val;               
				IN_HL_D_PORT	    =port_val;		
                retval=0;
				break;
		case	SILK_SU1:
                if(!NcNo)  port_val=!port_val;               
				IN_SU1_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_SD1:
                if(!NcNo)  port_val=!port_val;               
				IN_SD1_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_SFT:
                if(!NcNo)  port_val=!port_val;               
				IN_SFT_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_OVL:
                if(!NcNo)  port_val=!port_val;               
				IN_OVL_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_ULS:
                if(!NcNo)  port_val=!port_val;               
				IN_ULS_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_DLS:
                if(!NcNo)  port_val=!port_val;               
				IN_DLS_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_LU:
                if(!NcNo)  port_val=!port_val;               
				IN_LU_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_LD:
                if(!NcNo)  port_val=!port_val;               
				IN_LD_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_GR:
                if(!NcNo)  port_val=!port_val;               
				IN_GR_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_BAT:
                if(!NcNo)  port_val=!port_val;               
				IN_BAT_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_PASS:
                if(!NcNo)  port_val=!port_val;               
				IN_PASS_PORT	    =port_val;		
                retval=0;
				break;
		case	SILK_FIRE:
                if(!NcNo)  port_val=!port_val;               
				IN_FIRE_PORT	    =port_val;		
                retval=0;
				break;
		case	SILK_WATER:
                if(!NcNo)  port_val=!port_val;               
				IN_WATER_PORT	    =port_val;		
                retval=0;
				break;
		case	SILK_FULL:
                if(!NcNo)  port_val=!port_val;               
				IN_FULL_PORT	    =port_val;		
                retval=0;
				break;
		case	SILK_EX1:
                if(!NcNo)  port_val=!port_val;               
				IN_EX1_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_FHM:
                if(!NcNo)  port_val=!port_val;               
				IN_FHM_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_FR1:
                if(!NcNo)  port_val=!port_val;               
				IN_FR1_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_FR2:
                if(!NcNo)  port_val=!port_val;               
				IN_FR2_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_GS2:
                if(!NcNo)  port_val=!port_val;               
				IN_GS2_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_DS2:
                if(!NcNo)  port_val=!port_val;               
				IN_DS2_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_SU2:
                if(!NcNo)  port_val=!port_val;               
				IN_SU2_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_SD2:
                if(!NcNo)  port_val=!port_val;               
				IN_SD2_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_SU3:
                if(!NcNo)  port_val=!port_val;               
				IN_SU3_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_SD3:
                if(!NcNo)  port_val=!port_val;               
				IN_SD3_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_X0:
                if(!NcNo)  port_val=!port_val;               
				IN_X0_PORT	        =port_val;	
                retval=0;
				break;
		case	SILK_X1:
                if(!NcNo)  port_val=!port_val;               
				IN_X1_PORT	        =port_val;	
                retval=0;
				break;
		case	SILK_X2:
                if(!NcNo)  port_val=!port_val;               
				IN_X2_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_X3:
                if(!NcNo)  port_val=!port_val;               
				IN_X3_PORT	        =port_val;	
                retval=0;
				break;
		case	SILK_X4:
                if(!NcNo)  port_val=!port_val;               
				IN_X4_PORT	        =port_val;	
                retval=0;
				break;
		case	SILK_X5:
                if(!NcNo)  port_val=!port_val;               
				IN_X5_PORT	        =port_val;	
                retval=0;
				break;
		case	SILK_X6:
                if(!NcNo)  port_val=!port_val;               
				IN_X6_PORT	        =port_val;	
                retval=0;
				break;
		case	SILK_X7:
                if(!NcNo)  port_val=!port_val;               
				IN_X7_PORT	        =port_val;	
                retval=0;
				break;
		case	SILK_FS0:
                if(!NcNo)  port_val=!port_val;               
				IN_FS0_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_FS1:
                if(!NcNo)  port_val=!port_val;               
				IN_FS1_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_FS2:
                if(!NcNo)  port_val=!port_val;               
				IN_FS2_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_FS3:
                if(!NcNo)  port_val=!port_val;               
				IN_FS3_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_FS4:
                if(!NcNo)  port_val=!port_val;               
				IN_FS4_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_DER:
                if(!NcNo)  port_val=!port_val;               
				IN_DER_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_FID:
                if(!NcNo)  port_val=!port_val;               
				IN_FID_PORT	        =port_val;		
                retval=0;
				break;
		case	SILK_UND:
                if(!NcNo)  port_val=!port_val;               
				IN_UND_PORT	        =port_val;		
                retval=0;
				break;
		default:
                retval=1;
				break;
    }

    return(retval);
}
*/


unsigned int       __attribute__((section(".usercode"))) CurSelOutPort(unsigned int port_sel,unsigned int port_val)
{
	unsigned int retval=1;
	unsigned int NcNo=1;

    if(port_sel & 0x80)     NcNo=1;      //N_Open
    else                    NcNo=0;      //N_Close

    port_sel=(port_sel & 0x7f);

    switch(port_sel){
        case    SILK_OP:
            if(!NcNo)  port_val=!port_val;               
			OUT_OP_PORT=port_val;
            retval=0;
            break;
        case    SILK_CL:
            if(!NcNo)  port_val=!port_val;               
			OUT_CL_PORT=port_val;
            retval=0;
            break;
        case    SILK_OP_S:
            if(!NcNo)  port_val=!port_val;               
			OUT_OP_S_PORT=port_val;
            retval=0;
            break;
        case    SILK_CL_S:
            if(!NcNo)  port_val=!port_val;               
			OUT_CL_S_PORT=port_val;
            retval=0;
            break;
        case    SILK_BK2:
            if(!NcNo)  port_val=!port_val;               
			OUT_BK2_PORT=port_val;
            retval=0;
            break;
        case    SILK_D_S:
            if(!NcNo)  port_val=!port_val;               
			OUT_D_S_PORT=port_val;
            retval=0;
            break;
        case    SILK_GBR:
            if(!NcNo)  port_val=!port_val;               
			OUT_GBR_PORT=port_val;
            retval=0;
            break;
        case    SILK_BK1:
            if(!NcNo)  port_val=!port_val;               
			OUT_BK1_PORT=port_val;
            retval=0;
            break;
        case    SILK_FAN:
            if(!NcNo)  port_val=!port_val;               
			OUT_FAN_PORT=port_val;
            retval=0;
            break;
        case    SILK_LIT:
            if(!NcNo)  port_val=!port_val;               
			OUT_LIT_PORT=port_val;
            retval=0;
            break;
        case    SILK_BUZ:
            if(!NcNo)  port_val=!port_val;               
			OUT_BUZ_PORT=port_val;
            retval=0;
            break;
        case    SILK_BELL:
            if(!NcNo)  port_val=!port_val;               
			OUT_BELL_PORT=port_val;
            retval=0;
            break;
        case    SILK_RST:
            if(!NcNo)  port_val=!port_val;               
			OUT_RST_PORT=port_val;
            retval=0;
            break;
        case    SILK_ERR:
            if(!NcNo)  port_val=!port_val;               
			OUT_ERR_PORT=port_val;
            retval=0;
            break;
        case    SILK_HOP:
            if(!NcNo)  port_val=!port_val;               
			OUT_HOP_PORT=port_val;
            retval=0;
            break;
        case    SILK_HCL:
            if(!NcNo)  port_val=!port_val;               
			OUT_HCL_PORT=port_val;
            retval=0;
            break;
        case    SILK_UP:
            if(!NcNo)  port_val=!port_val;               
			OUT_U_W_PORT=port_val;		
            break;
        case    SILK_DN:
            if(!NcNo)  port_val=!port_val;               
			OUT_D_W_PORT=port_val;		
            break;
        case    SILK_P1:
            if(!NcNo)  port_val=!port_val;               
			OUT_P1_PORT=port_val;		
            break;
        case    SILK_P2:
            if(!NcNo)  port_val=!port_val;               
			OUT_P2_PORT=port_val;		
            break;
        case    SILK_P3:
            if(!NcNo)  port_val=!port_val;               
			OUT_P3_PORT=port_val;		
            break;
        case    SILK_P4:
            if(!NcNo)  port_val=!port_val;               
			OUT_P4_PORT=port_val;		
            break;
        case    SILK_DAC:
            if(!NcNo)  port_val=!port_val;               
			OUT_DAC_PORT=port_val;		
            break;

        case    SILK_SLOW_DOOR:
            if(!NcNo)  port_val=!port_val;               
			OUT_SLOW_DOOR_PORT=port_val;		
            break;
        case    SILK_VIRTUAL_Y1:
            if(!NcNo)  port_val=!port_val;               
			OUT_VIRTUAL_Y1_PORT=port_val;		
            break;
        case    SILK_VIRTUAL_Y2:
            if(!NcNo)  port_val=!port_val;               
			OUT_VIRTUAL_Y2_PORT=port_val;		
            break;
        case    SILK_VIRTUAL_Y3:
            if(!NcNo)  port_val=!port_val;               
			OUT_VIRTUAL_Y3_PORT=port_val;		
            break;
        case    SILK_VIRTUAL_Y4:
            if(!NcNo)  port_val=!port_val;               
			OUT_VIRTUAL_Y4_PORT=port_val;		
            break;
        case    SILK_VIRTUAL_Y5:
            if(!NcNo)  port_val=!port_val;               
			OUT_VIRTUAL_Y5_PORT=port_val;		
            break;
        case    SILK_VIRTUAL_Y6:
            if(!NcNo)  port_val=!port_val;               
			OUT_VIRTUAL_Y6_PORT=port_val;		
            break;
        case    SILK_VIRTUAL_Y7:
            if(!NcNo)  port_val=!port_val;               
			OUT_VIRTUAL_Y7_PORT=port_val;		
            break;
        case    SILK_EXT_Y0:
            if(!NcNo)  port_val=!port_val;   
			OUT_EXT_Y0_PORT=port_val;		
            break;
        case    SILK_EXT_Y1:
            if(!NcNo)  port_val=!port_val;               
			OUT_EXT_Y1_PORT=port_val;		
            break;
        case    SILK_EXT_Y2:
            if(!NcNo)  port_val=!port_val;               
			OUT_EXT_Y2_PORT=port_val;		
            break;
        case    SILK_EXT_Y3:
            if(!NcNo)  port_val=!port_val;               
			OUT_EXT_Y3_PORT=port_val;		
            break;
        case    SILK_EXT_Y4:
            if(!NcNo)  port_val=!port_val;               
			OUT_EXT_Y4_PORT=port_val;		
            break;
        case    SILK_EXT_Y5:
            if(!NcNo)  port_val=!port_val;               
			OUT_EXT_Y5_PORT=port_val;		
            break;
        case    SILK_EXT_Y6:
            if(!NcNo)  port_val=!port_val;               
			OUT_EXT_Y6_PORT=port_val;		
            break;
        case    SILK_EXT_Y7:
            if(!NcNo)  port_val=!port_val;               
			OUT_EXT_Y7_PORT=port_val;		
            break;
        default:
            retval=0;
            break;
    }

    return(retval);
}




unsigned int       __attribute__((section(".usercode"))) CurSelOutPortChk(unsigned int port_sel)
{
    unsigned int retval=1;
	unsigned int NcNo=1;

    if(port_sel & 0x80)     NcNo=1;      //N_Open
    else                    NcNo=0;      //N_Close

    port_sel=(port_sel & 0x7f);

    switch(port_sel){
        case    SILK_FAN:
			if(OUT_FAN_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_LIT:
			if(OUT_LIT_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_BUZ:
			if(OUT_BUZ_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_BELL:
			if(OUT_BELL_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_RST:
			if(OUT_RST_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_ERR:
			if(OUT_ERR_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_HOP:
			if(OUT_HOP_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_HCL:
			if(OUT_HCL_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_OP:
			if(OUT_OP_PORT)	    retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_CL:
			if(OUT_CL_PORT)	    retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_OP_S:
			if(OUT_OP_S_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_CL_S:
			if(OUT_CL_S_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_BK2:
			if(OUT_BK2_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_D_S:
			if(OUT_D_S_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_GBR:
			if(OUT_GBR_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_BK1:
			if(OUT_BK1_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_UP:
			if(OUT_U_W_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_DN:
			if(OUT_D_W_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_P1:
			if(OUT_P1_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_P2:
			if(OUT_P2_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_P3:
			if(OUT_P3_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_P4:
			if(OUT_P4_PORT)	    retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;
        case    SILK_DAC:
			if(OUT_DAC_PORT)	retval=1;		
			else		        retval=0;
            if(!NcNo)           retval=!retval;               
            break;

        case    SILK_SLOW_DOOR:
			if(OUT_SLOW_DOOR_PORT)	retval=1;		
			else		        	retval=0;
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_VIRTUAL_Y1:
			if(OUT_VIRTUAL_Y1_PORT)	retval=1;		
			else		        	retval=0;
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_VIRTUAL_Y2:
			if(OUT_VIRTUAL_Y2_PORT)	retval=1;		
			else		        	retval=0;
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_VIRTUAL_Y3:
			if(OUT_VIRTUAL_Y3_PORT)	retval=1;		
			else		        	retval=0;
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_VIRTUAL_Y4:
			if(OUT_VIRTUAL_Y4_PORT)	retval=1;		
			else		        	retval=0;
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_VIRTUAL_Y5:
			if(OUT_VIRTUAL_Y5_PORT)	retval=1;		
			else		        	retval=0;
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_VIRTUAL_Y6:
			if(OUT_VIRTUAL_Y6_PORT)	retval=1;		
			else		        	retval=0;
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_VIRTUAL_Y7:
			if(OUT_VIRTUAL_Y7_PORT)	retval=1;		
			else		        	retval=0;
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_EXT_Y0:
			if(OUT_EXT_Y0_PORT)		retval=1;		
			else					retval=0;	
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_EXT_Y1:
			if(OUT_EXT_Y1_PORT)		retval=1;		
			else					retval=0;	
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_EXT_Y2:
			if(OUT_EXT_Y2_PORT)		retval=1;		
			else					retval=0;	
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_EXT_Y3:
			if(OUT_EXT_Y3_PORT)		retval=1;		
			else					retval=0;	
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_EXT_Y4:
			if(OUT_EXT_Y4_PORT)		retval=1;		
			else					retval=0;	
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_EXT_Y5:
			if(OUT_EXT_Y5_PORT)		retval=1;		
			else					retval=0;	
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_EXT_Y6:
			if(OUT_EXT_Y6_PORT)		retval=1;		
			else					retval=0;	
            if(!NcNo)           	retval=!retval;               
            break;
        case    SILK_EXT_Y7:
			if(OUT_EXT_Y7_PORT)		retval=1;		
			else					retval=0;	
            if(!NcNo)           	retval=!retval;               
            break;

        default:
           retval=0;
           break;
    }
    return(retval);
}



unsigned int       __attribute__((section(".usercode"))) CurSelPortIDRead(unsigned int port_sel)
{
	unsigned int cur_port_val;

    switch(port_sel){
        case    SILK_FAN:
			cur_port_val=cF_FAN;
            break;
        case    SILK_LIT:
			cur_port_val=cF_LIT;
            break;
        case    SILK_BUZ:
			cur_port_val=cF_BUZ;
            break;
        case    SILK_BELL:
			cur_port_val=cF_BELL;
            break;
        case    SILK_RST:
			cur_port_val=cF_RST;
            break;
        case    SILK_ERR:
			cur_port_val=cF_ERR;
            break;
        case    SILK_HOP:
			cur_port_val=cF_HOP;
            break;
        case    SILK_HCL:
			cur_port_val=cF_HCL;
            break;
        case    SILK_OP:
			cur_port_val=cF_OP;
            break;
        case    SILK_CL:
			cur_port_val=cF_CL;
            break;
        case    SILK_OP_S:
			cur_port_val=cF_OP_S;
            break;
        case    SILK_CL_S:
			cur_port_val=cF_CL_S;
            break;
        case    SILK_BK2:
			cur_port_val=cF_BK2;
            break;
        case    SILK_D_S:
			cur_port_val=cF_D_S;
            break;
        case    SILK_GBR:
			cur_port_val=cF_GBR;
            break;
        case    SILK_BK1:
			cur_port_val=cF_BK1;
            break;
        case    SILK_UP:
			cur_port_val=cF_UP;
            break;
        case    SILK_DN:
			cur_port_val=cF_DN;
            break;
        case    SILK_P1:
			cur_port_val=cF_P1;
            break;
        case    SILK_P2:
			cur_port_val=cF_P2;
            break;
        case    SILK_P3:
			cur_port_val=cF_P3;
            break;
        case    SILK_P4:
			cur_port_val=cF_P4;
            break;
        case    SILK_DAC:
			cur_port_val=cF_DAC;
            break;
        case    SILK_SLOW_DOOR:
			cur_port_val=cF_SLOW_DOOR;
            break;
        case    SILK_VIRTUAL_Y1:
			cur_port_val=cF_VIRTUAL_Y1;
            break;
        case    SILK_VIRTUAL_Y2:
			cur_port_val=cF_VIRTUAL_Y2;
            break;
        case    SILK_VIRTUAL_Y3:
			cur_port_val=cF_VIRTUAL_Y3;
            break;
        case    SILK_VIRTUAL_Y4:
			cur_port_val=cF_VIRTUAL_Y4;
            break;
        case    SILK_VIRTUAL_Y5:
			cur_port_val=cF_VIRTUAL_Y5;
            break;
        case    SILK_VIRTUAL_Y6:
			cur_port_val=cF_VIRTUAL_Y6;
            break;
        case    SILK_VIRTUAL_Y7:
			cur_port_val=cF_VIRTUAL_Y7;
            break;
/*
///////////////////////////////////
        case    SILK_EXT_Y0:
			cur_port_val=cF_EXT_Y0;
            break;
        case    SILK_EXT_Y1:
			cur_port_val=cF_EXT_Y1;
            break;
        case    SILK_EXT_Y2:
			cur_port_val=cF_EXT_Y2;
            break;
        case    SILK_EXT_Y3:
			cur_port_val=cF_EXT_Y3;
            break;
        case    SILK_EXT_Y4:
			cur_port_val=cF_EXT_Y4;
            break;
        case    SILK_EXT_Y5:
			cur_port_val=cF_EXT_Y5;
            break;
        case    SILK_EXT_Y6:
			cur_port_val=cF_EXT_Y6;
            break;
        case    SILK_EXT_Y7:
			cur_port_val=cF_EXT_Y7;
            break;
*/
        default:
			cur_port_val=0xff;
           break;
    }

    return(cur_port_val);
}




