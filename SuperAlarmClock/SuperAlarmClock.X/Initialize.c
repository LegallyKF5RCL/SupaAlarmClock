/*
 * arbitrarly assigning functions to gpios without regard to circuit design
 *
 * snooze button    -   RB15    -   I
 * Set time button  -   RB14    -   I
 * Set alarm button -   RB13    -   I
 * Alarm On/Off     -   RB12    -   I
 * Increment button -   RB11    -   I
 * decrement button -   RB10    -   I
 *
 * SPIDAT           -   RB9     -   O
 * SPICLK           -   RB8     -   O
 * SPIMOSI          -   RB7     -   O
 * SPIMISO          -   RB6     -   I
 */

#include <p24HJ128GP202.h>
#include <Generic.h>
#include <rtcc.h>

void Initialize(void)
{  
    /*
    TRISBbits.TRISB15   = 1;
    TRISBbits.TRISB14   = 1;
    TRISBbits.TRISB13   = 1;
    TRISBbits.TRISB12   = 1;
    TRISBbits.TRISB11   = 1;
    TRISBbits.TRISB10   = 1;
    TRISBbits.TRISB9    = 0;
    TRISBbits.TRISB8    = 0;
    TRISBbits.TRISB7    = 0;
    TRISBbits.TRISB6    = 1;
    */
    
    TRISB = 0xFC40;      //hex value replaces individual TRISB above
    TRISA = 0x0000;     //Default until PORTA is used
    AD1PCFGL = 0xFFFF;   //all digital please

    return;
}
