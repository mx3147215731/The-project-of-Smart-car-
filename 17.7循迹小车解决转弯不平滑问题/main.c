#include "reg52.h"

#include "motor.h"
#include "delay.h"
#include "uart.h"
#include "time.h"

sbit leftSensor = P2^7;
sbit rightSensor = P2^6; 

extern char speedLeft; //去整个工程中的其他文件找
extern char speedRight;

void main()
{
	Time0Init();//定时器 初始化 
	Time1Init();
	// 注意 我们TOMD这里的初始化是直接开赋值的方式 -- 我们 应该调用在串口初始化之前，不然会把串口的TMOD给覆盖掉
	//UartInit();//初始化 串口
	while(1){
		
		
	if(!leftSensor && !rightSensor){ //两个低电平，两个模块都能反射回来红外线 -- 亮灯 -- 向前
  speedLeft=25;
	speedRight=25;
  }
  if(leftSensor && !rightSensor){//左边模块被黑线吸收，无法返回红外线 -- 高电平--灭灯 --左转
  speedLeft=5;
	speedRight=2;
  }	
	if(!leftSensor && rightSensor){//右边模块被黑线吸收，无法返回红外线 -- 高电平--灭灯 -- 右转
  speedLeft=20;
	speedRight=5;
  }	
	 if(leftSensor && rightSensor){
   //左右模块都没反射回来 -- 停
	speedLeft=0;
	speedRight=0;
  }
	

	}

}