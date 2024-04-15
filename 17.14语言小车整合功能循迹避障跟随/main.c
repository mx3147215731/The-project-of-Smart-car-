#include "reg52.h"
#include "hc04.h"
#include "delay.h"
#include "sg90.h"
#include "motor.h"
#include "oled.h"
 
 
#define MIDDLE 0
#define LEFT   1
#define RIGHT  2


#define BZ   1
#define XJ   2
#define GS   3

//语音识别接口
sbit A25=P1^5;
sbit A26=P1^6;
sbit A27=P1^7;


//循迹的传感器
sbit leftSensorX = P2^7;
sbit rightSensorX = P2^6; 
//跟随的传感器
sbit leftSensorG= P2^5;
sbit rightSensorG = P2^4;

  char dir;
	double disMiddle;
	double disLeft;
	double disRight;
	
	
void xunJiMode()
{
  if(!leftSensorX && !rightSensorX){ //两个低电平，两个模块都能反射回来红外线 -- 亮灯 -- 向前
//  speedLeft=18;
//	speedRight=18;
		goForward();
  }
  if(leftSensorX && !rightSensorX){//左边模块被黑线吸收，无法返回红外线 -- 高电平--灭灯 --左转
//  speedLeft=5;
//	speedRight=18;
		goLeft();
  }	
	if(!leftSensorX && rightSensorX){//右边模块被黑线吸收，无法返回红外线 -- 高电平--灭灯 -- 右转
//  speedLeft=18;
//	speedRight=5;
		goRight();
  }	
	 if(leftSensorX && rightSensorX){
   //左右模块都没反射回来 -- 停
//	speedLeft=0;
//	speedRight=0;
		 stop();
  }
	




}
	
void genSuiMode()
{

	if(!leftSensorG && !rightSensorG){ //两个低电平，两个模块都能反射回来红外线 -- 亮灯 -- 向前
  goForward(); 
  }
  if(leftSensorG && !rightSensorG){//左边模块被黑线吸收，无法返回红外线 -- 高电平--灭灯 --左转
  goRight();
  }	
	if(!leftSensorG && rightSensorG){//右边模块被黑线吸收，无法返回红外线 -- 高电平--灭灯 -- 右转
  goLeft(); 
  }	
	if(leftSensorG && rightSensorG){
   //左右模块都没反射回来 -- 停
		stop();
  }
	



}
	
void biZhangMode()
{

	 Delay200ms();
    if(dir != MIDDLE){ 	  
		sgMiddle();
		dir = MIDDLE;
		Delay450ms();
		}
		 disMiddle=get_distance();
		
		 if(disMiddle>35){
			 goForward();
			 //closeStatusLight();
     //前进
    }
		
		else if(disMiddle<10){ //离得太近得后退
      goBack();
      //Delay200ms();
			//stop();
    }
		else{
			 //openStatusLight();
			 stop();
    //停止 --测距
				sgLeft();
	      Delay450ms();
			  disLeft=get_distance();
		   
			  
			  sgMiddle();

		    Delay450ms();
			 
				sgRight();
			  dir=RIGHT;
			  Delay450ms();
			
			  disRight=get_distance();
		   if(disLeft<disRight){
           goRight();
				   Delay200ms();
				   stop();
       }
			  if(disLeft>disRight){
           goLeft();
					 Delay200ms();
					 stop();
       }
			
    }


}


void main()
{
	int mark=0;

	Time0Init();
	Time1Init();
	//刚上电让摄像头保持在中间
   sgMiddle();
	 dir = MIDDLE;
	 Delay450ms();
	 
	
	//EX0Init(); //外部中断初始化
	Oled_Init(); //初始化OLED
	Oled_Clear();
	Oled_Show_Str(2,2,"------Ready------");
	while(1){
		//循迹模式
   if(A25==0 && A26==1 && A27==1){
		 if(mark != XJ){
     Oled_Show_Str(2,2,"----XunJi----");
		 Oled_Clear();
		 }
		 mark=XJ;
     xunJiMode();
    }
		//避障模式
		  if(A25==1 && A26==0 && A27==1){
				if(mark!=BZ){// 判断当前模式是否相同，防止重复刷新导致的闪屏
        Oled_Show_Str(2,2,"---BiZhang---");
				Oled_Clear();
        }
				mark = BZ;
				biZhangMode();
    }
		//跟随模式  
      if(A25==1 && A26==1 && A27==0){
				if(mark != GS){
				Oled_Show_Str(2,2,"---GenSui---");
				Oled_Clear();
        }
				mark=GS;
     genSuiMode();
    }
		// 停下
		if(A25==0 && A26==0 && A27==0){
     stop();
    }
		
		
	}
} 






