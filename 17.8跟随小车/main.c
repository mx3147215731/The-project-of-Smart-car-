#include "reg52.h"

#include "motor.h"
#include "delay.h"

//sbit leftSensor = P2^7;
//sbit rightSensor = P2^6;

sbit leftSensor= P2^5;
sbit rightSensor = P2^4;

void main()
{
	

 //左边跟随模块能返回红外，输出低电平，右边不能返回，输出高电平，说明物体在左边需要左转，右边同理
	while(1){
		
	if(!leftSensor && !rightSensor){ //两个低电平，两个模块都能反射回来红外线 -- 亮灯 -- 向前
  goForward(); 
  }
  if(leftSensor && !rightSensor){//左边模块被黑线吸收，无法返回红外线 -- 高电平--灭灯 --左转
  goRight();
  }	
	if(!leftSensor && rightSensor){//右边模块被黑线吸收，无法返回红外线 -- 高电平--灭灯 -- 右转
  goLeft(); 
  }	
	if(leftSensor && rightSensor){
   //左右模块都没反射回来 -- 停
		stop();
  }
	

	}

}