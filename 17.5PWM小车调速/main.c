#include "reg52.h"

#include "motor.h"
#include "delay.h"
#include "uart.h"
#include "time.h"

extern char speed; //去整个工程中的其他文件找

void main()
{
	Time0Init();//定时器 初始化 
	// 注意 我们TOMD这里的初始化是直接开赋值的方式 -- 我们 应该调用在串口初始化之前，不然会把串口的TMOD给覆盖掉
	//UartInit();//初始化 串口
	while(1){
	speed=20; // 20 ms -- 40 * 0.5 -- 全速运行 5ms -- 5/20= 20% 占空比 来控制他的速度
	Delay1000ms();
	Delay1000ms();
	speed=30;
	Delay1000ms();
	Delay1000ms();
	speed=40;
	Delay1000ms();
	Delay1000ms();
  
	}

}