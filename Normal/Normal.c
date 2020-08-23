/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 8/30/2018
Author  : 
Company : 
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega8.h>
#define LED PORTB.6
unsigned long LoadA=0 ;
unsigned long LoadB=0;
unsigned long Duty=0;
// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Reinitialize Timer1 value
TCNT1H=0xE0C0 >> 8;
TCNT1L=0xE0C0 & 0xff;
PORTB ^= (1<<PORTB7);
}

// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void){
    PORTB|=0x40;
}

// Timer1 output compare B interrupt service routine
interrupt [TIM1_COMPB] void timer1_compb_isr(void){
    PORTB&=~0x40;
}

void main(void)
{
unsigned long temp=0;
Duty=50;
temp=Duty*8000/(2*100);     //Warning about overload 
LoadA=61535-temp;           //61535 center of 1ms, /2 cuz B will do half
LoadB=61535+temp;

// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=Out Bit1=Out Bit0=In 
DDRB=(1<<DDB7) | (1<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (1<<DDB2) | (1<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=0 Bit1=0 Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);
// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Toggle on compare match
// OC1B output: Toggle on compare match
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 1 ms
// Output Pulse(s):
// OC1A Period: 2 ms Width: 1 ms// OC1B Period: 2 ms Width: 1 ms
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: On
TCCR1A=(0<<COM1A1) | (1<<COM1A0) | (0<<COM1B1) | (1<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0xE0;
TCNT1L=0xC0;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=LoadA>> 8;
OCR1AL=LoadA& 0xff;
OCR1BH=LoadB>> 8;
OCR1BL=LoadB& 0xff;


// Timer(s)/Counter(s) Interrupt(s) initialization
//TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (1<<OCIE1A) | (1<<OCIE1B) | (1<<TOIE1) | (0<<TOIE0);
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (1<<OCIE1A) | (1<<OCIE1B) | (1<<TOIE1) | (0<<TOIE0);
// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here

      }
}
