#include "beep.h"
#include "intrins.h"
sbit speaker=P1^5; 
unsigned char timer0h,timer0l,time=1;

code unsigned char dzl[]={
	111,112,111,113,112,111,114,113,125,
	0
};

code unsigned char wait1[]={
	143,
	0 
};

unsigned int  code FreTab[28]  = {
	3517,3134,2792,2633,2351,2094,1865,
	1758,1566,1395,1319,1175,1046,932 ,
	880 ,785 ,699 ,660 ,587 ,523 ,466 ,
	440 ,392 ,349 ,329 ,293 ,261 ,233 ,  
};

void t0int() interrupt 1
{
	speaker=!speaker;
	TH0=timer0h;
	TL0=timer0l;
}

//  ����Ŀ����������ǰ�����ĵ�ʱ��
void delay(unsigned char t)
{
	unsigned long t2;
	for(;t>0;t--)
	{
		for(t2=0;t2<5000;t2++){;}
	}
	TR0=0;// ֹͣ����	������ε�������������Ĳ���������
}
/**/
void song(unsigned char gyz[])
{
	unsigned char k=0;
	unsigned long i=0;	//  ���ڸ�ʳ������⣬��Ҫ���ô�һ��ķ�Χ������û����һ�������¿�ʼ��
	// ������������ֻ��һ�飬Ѱ������0ֵʱ��ֹͣ��
	while(time)	
	{
		if(gyz[i]%10==0) 	 // ����Ϊ0ֵʱͣ�ٴ���
		{
			TR0=0;	  // ֹͣ����
		}
		else
		{
			k=gyz[i]%10+7*(gyz[i]/100+1)-1;
			timer0h=(65535-FreTab[k])/256;
			timer0l=(65535-FreTab[k])%256;
			TR0=1;	  // ����T0�������ȥ����
		}
		time=gyz[i]/10%10;
		i=i+1;
		
		delay(time);
	}
}

void dzl_song()
{
	time = 1;
	song(dzl);
}

void wait1_song()
{
	time = 1;
	song(wait1);
}
