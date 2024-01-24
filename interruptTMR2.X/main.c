/*
 * File:   main.c
 * Author: Paul
 *
 * Created on January 13, 2024, 8:32 PM
 */


#include <xc.h>
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000  //4Mhz

#define led PORTCbits.RC4
#define led2 PORTDbits.RD2

char data[4] = {'U', 'P', 'S', ' '};
int count = 0;
int timeAux = 0;

__interrupt() void myInterrupt(void){
    
    //extern int timeAux;
    
   
    
    if(TMR2IF == 1 ){
         if(count == 1138)
        {
            count = 0;
        } 
        if (count == 0) {
            led = 1;
        }
        if (count ==  57 + timeAux){
            led = 0;
        }
        //led = 1;
        //led = 0;
        count++;
        TMR2IF = 0;
        //TMR2 = 0;
    }
    
}

void main(void) {
    TRISC4 = 0;         //LED
    TRISD2 = 0;
    
    T2CON = 0b00001000; //Postcaler , Prescaler, TMR2ON = 0;
    PR2 = 21;
    TMR2IE =1;          //
    PEIE = 1;           //Peripherical Interrupt Enable
    GIE = 1;            //Global Interrupt Enable
    
    TMR2ON =1;
    
    while (1){
        led2 = 0;
        if (timeAux > 57){
            timeAux = 0;
        }
        __delay_ms(100);
        led2 = 1;
        timeAux++;
    }
    return;
}
