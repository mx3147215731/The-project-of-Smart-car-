#include "reg52.h"
#include "delay.h"
sbit Trig     = P2^3;
sbit Echo     = P2^2;

void Time1Init()
{	
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;
	TH1 = 0;
	TL1 = 0;
	//设置定时器0工作模式1，初始值设定0开始数数，不着急启动定时器
}

void startHC()
{
	Trig = 0;
	Trig = 1;
	Delay10us();
	Trig = 0;
}

double get_distance()
{
		double time;
		//定时器数据清零，以便下一次测距
		TH1 = 0;
		TL1 = 0;
	//1. Trig ，给Trig端口至少10us的高电平
		startHC();
		//2. echo由低电平跳转到高电平，表示开始发送波
		while(Echo == 0);
		//波发出去的那一下，开始启动定时器
		TR1 = 1;
		//3. 由高电平跳转回低电平，表示波回来了
		while(Echo == 1);
		//波回来的那一下，我们开始停止定时器
		TR1 = 0;
		//4. 计算出中间经过多少时间
		time = (TH1 * 256 + TL1)*1.085;//us为单位
		//5. 距离 = 速度 （340m/s）* 时间/2
		return  (time * 0.017);
}