/*
 * File:   Main.c
 * Author: Brian
 *
 * Created on March 21, 2013, 11:05 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include <Generic.h>
#include <p24Hxxxx.h>
#include <timer.h>
#include <outcompare.h>

////all of this needs to go into a header
void Initialize(void);
void Chip_Go_Fast(void);
void StartUp(void);

////end of what should be the header

_FBS( BWRP_WRPROTECT_OFF )
_FSS( SWRP_WRPROTECT_OFF )
_FGS(GWRP_OFF & GCP_OFF )
_FOSCSEL( FNOSC_FRCPLL  & IESO_OFF )
_FOSC( POSCMD_HS & OSCIOFNC_OFF & IOL1WAY_OFF & FCKSM_CSDCMD )
_FWDT( WDTPOST_PS8192 & WDTPRE_PR32 & WINDIS_OFF & FWDTEN_OFF)
_FPOR( FPWRT_PWR128 & ALTI2C_ON )
_FICD( ICS_PGD1 & JTAGEN_OFF )

int main(void)
{
    Chip_Go_Fast();
    StartUp();
    Initialize();

    return 0;
}

inline void Chip_Go_Fast()      /*Maxs out the chip speed. Blocking*/
{
    // Configure PLL prescaler, PLL postscaler, PLL divisor
        PLLFBD = 41; // M = 43
        CLKDIVbits.PLLPOST = 0; // N2 = 2
        CLKDIVbits.PLLPRE = 0; // N1 = 2
    // Initiate Clock Switch to Internal FRC with PLL (NOSC = 0b001)
        __builtin_write_OSCCONH(0x01);
        __builtin_write_OSCCONL(0x01);
    // Wait for Clock switch to occur
        while (OSCCONbits.COSC != 0b001);
    // Wait for PLL to lock
        while(OSCCONbits.LOCK != 1) {};
    return;
}

//////////
//ISR/////
//////////

void __attribute__ ((auto_psv))     _ISR    _T1Interrupt(void)
{
    _T1IF = 0;          //clear interrupt flag

    LATA ^= 0xFFFF;     //XOR latch with HIGH
    LATB ^= 0xFFFF;     //XOR latch with HIGH
                    //*is this innacurate at high frequency due to reading the latch rather than the port
    return;
}
