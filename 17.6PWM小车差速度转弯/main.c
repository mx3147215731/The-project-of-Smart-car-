#include "reg52.h"

#include "motor.h"
#include "delay.h"
#include "uart.h"
#include "time.h"

extern char speedLeft; //去整个工程中的其他文件找

extern char speedRight;

void main()
{
	Time0Init();//定时器 初始化 
	Time1Init();
	// 注意 我们TOMD这里的初始化是直接开赋值的方式 -- 我们 应该调用在串口初始化之前，不然会把串口的TMOD给覆盖掉
	//UartInit();//初始化 串口
	while(1){
  speedLeft=10;
	speedRight=40;
	Delay1000ms();
	Delay1000ms();

	speedLeft=40;
	speedRight=10;
	Delay1000ms();
  Delay1000ms();
	}

}