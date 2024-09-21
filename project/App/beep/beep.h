#ifndef __BEEP_H__
#define __BEEP_H__
#include "public.h" 
#include "intrins.h"
sbit BEEP=P1^5; 
sbit sound=P1^5;

void beepVoice_us(u16 i);
void t1int();
void delay(unsigned char t);
void song(unsigned char gyz[]);
void dzl_song();
#endif