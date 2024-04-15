#include "reg52.h"

#include "motor.h"

char speed;
char cnt=0;

void Time0Init()
{
	//1. 配置定时器0工作模式位16位计时
	TMOD = 0x01;
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


void Time0Handler() interrupt 1
{
	cnt++;  //统计爆表的次数. cnt=1的时候，报表了1
	//重新给初值
	TL0=0x33;
	TH0=0xFE;
	
	//控制PWM波
	if(cnt < speed){//  前进  -- 占空比越高越快
		goForward();
	}else{//停止
		stop();
	}
	
	if(cnt == 40){//爆表40次，经过了20ms
		cnt = 0;  //当100次表示1s，重新让cnt从0开始，计算下一次的1s
	}
		
}