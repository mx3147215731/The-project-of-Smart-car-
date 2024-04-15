#include "reg52.h"

#include "motor.h"
#include "delay.h"




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