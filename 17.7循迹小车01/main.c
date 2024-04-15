#include "reg52.h"

#include "motor.h"
#include "delay.h"

sbit leftSensor = P2^7;
sbit rightSensor = P2^6;

void main()
{
	
	 // 当两边都返回低电平 的时候，表示黑线就在车底 (红外线没有被吸收)-- 一直前走
   // 当左边高电平，右边低电平的时候，表示黑线在左模块底下，即将偏离轨道，需要左转，右边同理
	while(1){
		
	if(!leftSensor && !rightSensor){ //两个低电平，两个模块都能反射回来红外线 -- 亮灯 -- 向前
  goForward(); 
  }
  if(leftSensor && !rightSensor){//左边模块被黑线吸收，无法返回红外线 -- 高电平--灭灯 --左转
  goLeft();
  }	
	if(!leftSensor && rightSensor){//右边模块被黑线吸收，无法返回红外线 -- 高电平--灭灯 -- 右转
  goRight();
  }	
	 if(leftSensor && rightSensor){
   //左右模块都没反射回来 -- 停
		stop();
  }
	

	}

}