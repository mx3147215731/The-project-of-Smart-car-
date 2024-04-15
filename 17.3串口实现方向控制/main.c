#include "reg52.h"

#include "motor.h"
#include "delay.h"
#include "uart.h"



void main()
{
	
	UartInit();//初始化 串口
	Delay1000ms();
	while(1){
	//开始的时候设置为往前走2s -- 延迟两秒后就往后走

	}

}