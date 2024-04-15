#include "reg52.h"
#include "delay.h"
#include "motor.h"

sbit D5       = P3^7;//根据原理图（电路图），设备变量led1指向P3组IO口的第7口
sbit D6       = P3^6;//根据原理图（电路图），设备变量led2指向P3组IO口的第6口

sbit sg90_con = P1^1;
int speed;
int cntSpeed=0;

int jd;
int cnt = 0;


void Time0Init()
{
	//1. 配置定时器0工作模式位16位计时
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;
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

//void openStatusLight()
//{
//	D5 = 0;
//	D6 = 1;
//}
//void closeStatusLight()
//{
//	D5 = 1;
//	D6 = 0;
//}



void sgMiddle()
{
	
	jd = 3; //90度 1.5ms高电平
	cnt = 0;

}

void sgLeft() //135 度
{
	
	jd = 5;  //135 度 
	cnt = 0;

}


void sgRight()
{

	jd = 1; //0度
	cnt = 0;
	

}

void Time0Handler() interrupt 1
{
	cnt++;  //统计爆表的次数. cnt=3的时候，报表了1
	//重新给初值
	TL0=0x33;
	TH0=0xFE;
	
	//控制PWM波
	if( cnt < jd){
		sg90_con = 1;
	}else{
		sg90_con = 0;
	}
	
	if(cnt == 40){//爆表40次，经过了20ms
		cnt = 0;  //当100次表示1s，重新让cnt从0开始，计算下一次的1s
		sg90_con = 1;
	}
	
	
	if( cntSpeed < speed){
		goForward();
	}else{
		stop();
	}
	
	
		if(cntSpeed >= 40){//爆表40次，经过了20ms
		cntSpeed = 0;  //当100次表示1s，重新让cnt从0开始，计算下一次的1s
		
	}
		
}
