#include "reg52.h"
#include "intrins.h"

sbit RightConA=P3^2;
sbit RightConB=P3^3;

sbit LeftConA=P3^4;
sbit LeftConB=P3^5;


void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void goForward() // 前进
{
RightConA=0;
RightConB=1;	
	
LeftConA=0;
LeftConB=1;	

}



void goBack() // 后退
{
RightConA=1;
RightConB=0;	
	
LeftConA=1;
LeftConB=0;	

}

void goLeft() // 左转 -- 轮子左边不动，右边前进， 右边的速到大于左边的时候，就实现了左转
{
RightConA=0;
RightConB=1;	
	
LeftConA=0;
LeftConB=0;	

}


void goRight() // 右转 --轮子右边不动，左边前进
{

RightConA=0;
RightConB=0;	
	
LeftConA=0;
LeftConB=1;	

}



void main()
{
	while(1){
	//开始的时候设置为往前走2s -- 延迟两秒后就往后走
	goForward(); 
	Delay1000ms();
	Delay1000ms();	
	goBack();
	Delay1000ms();
	Delay1000ms();	
	goLeft();
	Delay1000ms();
	Delay1000ms();	
	goRight();
	Delay1000ms();
	Delay1000ms();	
	}

}