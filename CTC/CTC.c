/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : TEST Timer1 CTC Mode
         *Resullt- Timer1 Overflow Interrupt only happen when count from MAX(0xFFFF to 0)
         When timer reach TOP there is no interrupt (When testing) 
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
unsigned long LoadA=0 ;
unsigned long LoadB=0;
unsigned long Duty=0;
// Declare your global variables here
interrupt [TIM1_CAPT] void timer1_capt_isr(void){
  PORTB ^= (1<<PORTB7);

}
// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
PORTB ^= (1<<PORTB7);
}

// Timer1 output compare A interrupt service routine
interrupt [TIM1_COMPA] void timer1_compa_isr(void)
{
  PORTB^=(1<<PORTB6);
}
// Timer1 output compare B interrupt service routine
interrupt [TIM1_COMPB] void timer1_compb_isr(void)
{
   PORTB^=(1<<PORTB6);
}

void main(void)
{
long temp;
Duty=20;
temp=Duty*10000/(2*100);     //Warning about overload 
LoadA=5000-temp;           //61535 center of 1ms, /2 cuz B will do half
LoadB=5000+temp;
// Declare your local variables here

// Input/Output Ports initialization
// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=Out Bit1=Out Bit0=In 
DDRB=(1<<DDB7) | (1<<DDB6) | (1<<DDB5) | (1<<DDB4) | (0<<DDB3) | (1<<DDB2) | (1<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=0 Bit1=0 Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);
// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 1000.000 kHz
// Mode: CTC top=ICR1
// OC1A output: Toggle on compare match
// OC1B output: Toggle on compare match
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 10 ms
// Output Pulse(s):
// OC1A Period: 20 ms Width: 10 ms// OC1B Period: 20 ms Width: 10 ms
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: On
TCCR1A=(0<<COM1A1) | (1<<COM1A0) | (0<<COM1B1) | (1<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (1<<WGM13) | (1<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x27;
ICR1L=0x0F;
OCR1AH=LoadA>> 8;
OCR1AL=LoadA& 0xff;
OCR1BH=LoadB>> 8;
OCR1BL=LoadB& 0xff;
// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (1<<TICIE1) | (1<<OCIE1A) | (1<<OCIE1B) | (1<<TOIE1) | (0<<TOIE0);

// Global enable interrupts
#asm("sei")

while (1)
      {

      }
}
