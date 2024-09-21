#include "public.h"
#include "ds1302.h"
#include "lcd1602.h"
#include "ds18b20.h"
#include "beep.h"
/*******************************************************************************
 * 函 数 名       : main
 * 函数功能		 : 主函数
 * 输    入       : 无
 * 输    出    	 : 无
 *******************************************************************************/

u8 id[5];
u8 bs[5],bf[5],wt[5];
u8 next[10];
u8 next1[6];
u8 next2[6];

bus_init()
{
	id[1]=0x01;
	bs[1]=0X06;
	bf[1]=0X30;
	wt[1]=0X20;
	
	id[2]=0x02;
	bs[2]=0X06;
	bf[2]=0X40;
	wt[2]=0X40;
	
	id[3]=0x03;
	bs[3]=0X07;
	bf[3]=0X30;
	wt[3]=0X30;
	
	id[4]=0x04;
	bs[4]=0X08;
	bf[4]=0X00;
	wt[4]=0X30;
}

void js()
{
	int i=1;
	u8 did=id[i];
	int min=bs[i]/16*1000+bs[i]%16*100+bf[i]/16*10+bf[i]%16;
	next[0]=id[i]%16+'0';
	next[1]=' ';
	next[2]=bs[i]/16+'0';
	next[3]=bs[i]%16+'0';
	next[4]=':';
	next[5]=bf[i]/16+'0';
	next[6]=bf[i]%16+'0';
	next[7]='\0';
	
	for(i=2;i<=4;i++)
	{
		if(min>bs[i]/16*1000+bs[i]%16*100+bf[i]/16*10+bf[i]%16)
		{
			min=bs[i]/16*1000+bs[i]%16*100+bf[i]/16*10+bf[i]%16;
			next[0]=id[i]%16+'0';
			next[1]=' ';
			next[2]=bs[i]/16+'0';
			next[3]=bs[i]%16+'0';
			next[4]=':';
			next[5]=bf[i]/16+'0';
			next[6]=bf[i]%16+'0';
			next[7]='\0';
		}
	}
}

void main()
{
	u8 time_buf[15];
	u8 flag1=1,flag2=1;
	
	int temp_value;
	u8 temp_buf[6];
	
	ds1302_init();//初始化DS1302
	lcd1602_init();//LCD1602初始化
	ds18b20_init();//初始化DS18B20
	bus_init();
	
	while(1)
	{
		ds1302_read_time();
		if(gDS1302_TIME[2]==0x23 && gDS1302_TIME[1]==0x59) bus_init();
		flag1=gDS1302_TIME[0]/16;
		if(flag1!=flag2)
		{
			flag2=flag1;
			lcd1602_clear();
		}
		
		if(bs[1]==gDS1302_TIME[2] && bf[1]==gDS1302_TIME[1]) //K1到站
		{
			lcd1602_clear();
			lcd1602_show_string(0,0,"K1 arrive soon!");
			lcd1602_show_string(0,1,"countdown:00:05");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			lcd1602_show_string(0,1,"countdown:00:04");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			lcd1602_show_string(0,1,"countdown:00:03");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			lcd1602_show_string(0,1,"countdown:00:02");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			lcd1602_show_string(0,1,"countdown:00:01");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_clear();
			lcd1602_show_string(0,0,"K1 arrive!");
			lcd1602_show_string(0,1,"K1 arrive!");
			delay_ms(1000);
			TMOD=1;		// 设置定时器0为16位计数模式 
			EA=1;ET0=1;
			dzl_song();
			if(bf[1]%16+wt[1]%16>=10) bf[1]+=6;
			bf[1]+=wt[1];
			if(bf[1]/16>=6)
			{
				bs[1]++;
				bf[1]-=0x60;
			}
		}
		else if(bs[2]==gDS1302_TIME[2] && bf[2]==gDS1302_TIME[1]) //K2到站
		{
			lcd1602_clear();
			lcd1602_show_string(0,0,"K2 arrive soon!");
			lcd1602_show_string(0,1,"countdown:00:05");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:04");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:03");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:02");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:01");
			
			TMOD=1;
			EA=1;ET0=1;
			wait2_song();
			
			lcd1602_clear();
			lcd1602_show_string(0,0,"K2 arrive!");
			lcd1602_show_string(0,1,"K2 arrive!");
			TMOD=1;		// 设置定时器0为16位计数模式
			EA=1;ET0=1;
			dzl_song();
			
			if(bf[2]%16+wt[2]%16>=10) bf[2]+=6;
			bf[2]+=wt[2];
			if(bf[2]/16>=6)
			{
				bs[2]++;
				bf[2]-=0x60;
			}
		}
		else if(bs[3]==gDS1302_TIME[2] && bf[3]==gDS1302_TIME[1]) //K3到站
		{
			lcd1602_clear();
			lcd1602_show_string(0,0,"K3 arrive soon!");
			lcd1602_show_string(0,1,"countdown:00:05");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:04");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:03");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:02");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:01");
			
			TMOD=1;
			EA=1;ET0=1;
			wait2_song();
			
			lcd1602_clear();
			lcd1602_show_string(0,0,"K3 arrive!");
			lcd1602_show_string(0,1,"K3 arrive!");
			TMOD=1;		// 设置定时器0为16位计数模式
			EA=1;ET0=1;
			dzl_song();
			
			if(bf[3]%16+wt[3]%16>=10) bf[3]+=6;
			bf[3]+=wt[3];
			if(bf[3]/16>=6)
			{
				bs[3]++;
				bf[3]-=0x60;
			}
		}
		else if(bs[4]==gDS1302_TIME[2] && bf[4]==gDS1302_TIME[1]) //K4到站
		{
			lcd1602_clear();
			lcd1602_show_string(0,0,"K4 arrive soon!");
			lcd1602_show_string(0,1,"countdown:00:05");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:04");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:03");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:02");
			
			TMOD=1;
			EA=1;ET0=1;
			wait1_song();
			
			lcd1602_show_string(0,1,"countdown:00:01");
			
			TMOD=1;
			EA=1;ET0=1;
			wait2_song();
			
			lcd1602_clear();
			lcd1602_show_string(0,0,"K4 arrive!");
			lcd1602_show_string(0,1,"K4 arrive!");
			TMOD=1;		// 设置定时器0为16位计数模式
			EA=1;ET0=1;
			dzl_song();
			
			if(bf[4]%16+wt[4]%16>=10) bf[4]+=6;
			bf[4]+=wt[4];
			if(bf[4]/16>=6)
			{
				bs[4]++;
				bf[4]-=0x60;
			}
		}
		if(flag1==0||flag1==4)
		{
			lcd1602_show_string(0,0,"Bus-Stop-Board");//第一行显示
			
			time_buf[0]=gDS1302_TIME[2]/16+'0';
			time_buf[1]=gDS1302_TIME[2]%16+'0';
			time_buf[2]=':';
			time_buf[3]=gDS1302_TIME[1]/16+'0';
			time_buf[4]=gDS1302_TIME[1]%16+'0';
			time_buf[5]=':';
			time_buf[6]=gDS1302_TIME[0]/16+'0';
			time_buf[7]=gDS1302_TIME[0]%16+'0';
			time_buf[8]='\0';
			lcd1602_show_string(0,1,time_buf);//第二行显示
			
			lcd1602_show_string(9,1,"T:");
			
			temp_value=ds18b20_read_temperture()*10;//保留温度值小数后一位
			if(temp_value<0)
			{
				temp_value=-temp_value;
				lcd1602_show_string(10,1,"-");
			}
			temp_buf[0]=temp_value%1000/100+'0';//十位
			temp_buf[1]=temp_value%1000%100/10+'0';//个位+小数点
			temp_buf[2]='.';
			temp_buf[3]=temp_value%1000%100%10+'0';//小数点后一位
			temp_buf[4]='C';
			temp_buf[5]='\0';
			lcd1602_show_string(11,1,temp_buf);
		}
		else if(flag1==1||flag1==5)
		{
			js();
			lcd1602_show_string(0,0,"NextBus:K");
			lcd1602_show_string(9,0,next);
			
		}
		else if(flag1==2)
		{
			lcd1602_show_string(0,0,"Next K1 : ");
			next1[0]=bs[1]/16+'0';
			next1[1]=bs[1]%16+'0';
			next1[2]=':';
			next1[3]=bf[1]/16+'0';
			next1[4]=bf[1]%16+'0';
			next1[5]='\0';
			lcd1602_show_string(10,0,next1);
			
			lcd1602_show_string(0,1,"Next K2 : ");
			next2[0]=bs[2]/16+'0';
			next2[1]=bs[2]%16+'0';
			next2[2]=':';
			next2[3]=bf[2]/16+'0';
			next2[4]=bf[2]%16+'0';
			next2[5]='\0';
			lcd1602_show_string(10,1,next2);
		}
		else if(flag1==3)
		{
			lcd1602_show_string(0,0,"Next K3 : ");
			next1[0]=bs[3]/16+'0';
			next1[1]=bs[3]%16+'0';
			next1[2]=':';
			next1[3]=bf[3]/16+'0';
			next1[4]=bf[3]%16+'0';
			next1[5]='\0';
			lcd1602_show_string(10,0,next1);
			
			lcd1602_show_string(0,1,"Next K4 : ");
			next2[0]=bs[4]/16+'0';
			next2[1]=bs[4]%16+'0';
			next2[2]=':';
			next2[3]=bf[4]/16+'0';
			next2[4]=bf[4]%16+'0';
			next2[5]='\0';
			lcd1602_show_string(10,1,next2);
		}
	}
}

