#include "motor.h"




void  goBack() // 前进
{
	RightConA=0;
	RightConB=1;	

	LeftConA=0;
	LeftConB=1;	

}



void goForward() // 后退
{
	RightConA=1;
	RightConB=0;	
		
	LeftConA=1;
	LeftConB=0;	

}

void goLeft() // 左转 -- 轮子左边不动，右边前进， 右边的速到大于左边的时候，就实现了左转
{
	RightConA=1;
	RightConB=0;	
		
	LeftConA=0;
	LeftConB=0;	

}


void goRight() // 右转 --轮子右边不动，左边前进
{

	RightConA=0;
	RightConB=0;	
		
	LeftConA=1;
	LeftConB=0;	

}
