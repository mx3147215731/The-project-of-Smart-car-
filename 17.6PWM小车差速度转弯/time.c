#include "reg52.h"

#include "motor.h"

char speedLeft;
char cntLeft=0;

char speedRight;
char cntRight=0;


void Time0Init()
{
	//1. 配置定时器0工作模式位16位计时
	TMOD = 0x01; //先调用无所谓
	//2. 给初值，定一个0.5出来
	TL0=0x33;
	TH0=0xFE;
	//3. 开始计时
	TR0 = 1;
	TF0 = 0;
	//4. 打开定时器0中断
	ET0 = 1;
	//5. 打开总中断EA
	EA = 1;
}


void Time1Init()
{
	//1. 配置定时器0工作模式位16位计时
	//TMOD = 0x01; // 后调用不能直接赋值
	TMOD &= 0x0F;
	TMOD |= 0x1 << 4;
	//2. 给初值，定一个0.5出来
	TL1=0x33;
	TH1=0xFE;
	//3. 开始计时
	TR1 = 1;
	TF1 = 0;
	//4. 打开定时器1中断
	ET1 = 1;
	//5. 打开总中断EA
	EA = 1;
}

//定时器 0 对应的是中断1
void Time0Handler() interrupt 1
{
	cntLeft++;  //统计爆表的次数. cnt=1的时候，报表了1
	//重新给初值
	TL0=0x33;
	TH0=0xFE;
	
	//控制PWM波
	if(cntLeft < speedLeft){//  前进  -- 占空比越高越快
		goForwardLeft();
	}else{//停止
		stopLeft();
	}
	
	if(cntLeft == 40){//爆表40次，经过了20ms
		cntLeft = 0;  //当100次表示1s，重新让cnt从0开始，计算下一次的1s
	}
		
}
//定时器 1 对应的是中断3 -- 控制右轮
void Time1Handler() interrupt 3
{
	cntRight++;  //统计爆表的次数. cnt=1的时候，报表了1
	//重新给初值
	TL1=0x33;
	TH1=0xFE;
	
	//控制PWM波
	if(cntLeft < speedRight){//  前进  -- 占空比越高越快
		goForwardRight();
	}else{//停止
		stopRight();
	}
	
	if(cntRight == 40){//爆表40次，经过了20ms
		cntRight = 0;  //当100次表示1s，重新让cnt从0开始，计算下一次的1s
	}
		
}