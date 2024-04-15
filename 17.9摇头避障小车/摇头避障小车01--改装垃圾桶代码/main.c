#include "reg52.h"
#include "hc04.h"
#include "delay.h"
#include "sg90.h"
 





void main()
{
	
	double dis;
	
	Time0Init();
	Time1Init();
	//舵机的初始位置
	initSG90_0();
	
	while(1){
    
		//超声波测距
		dis = get_distance();
		if(dis < 10){//如果小于10厘米
				//开盖，灯状态，D5亮
				openStatusLight();
				openDusbin();
		}else{
				//关盖，灯状态，D5灭
				closeStatusLight();
				closeDusbin();
		}
	}
} 






