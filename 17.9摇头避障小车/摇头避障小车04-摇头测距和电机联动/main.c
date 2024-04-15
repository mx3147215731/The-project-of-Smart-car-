#include "reg52.h"
#include "hc04.h"
#include "delay.h"
#include "sg90.h"
#include "motor.h"
 
 
#define MIDDLE 0
#define LEFT   1
#define RIGHT  2




void main()
{
	
  char dir;
	double disMiddle;
	double disLeft;
	double disRight;
	Time0Init();
	Time1Init();
	//刚上电让摄像头保持在中间
   sgMiddle();
	 dir = MIDDLE;
	 Delay450ms();
	 Delay450ms();
	while(1){
    Delay200ms();
    if(dir != MIDDLE){ 	  
		sgMiddle();
		dir = MIDDLE;
		Delay450ms();
		}
		 disMiddle=get_distance();
		
		 if(disMiddle>40){
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
} 






