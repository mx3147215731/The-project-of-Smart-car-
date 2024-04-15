#include "reg52.h"
#include "hc04.h"
#include "delay.h"
#include "sg90.h"
 
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
		
		 if(disMiddle>35){
			closeStatusLight();
     //前进
    }
		else{
			 openStatusLight();
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
		   
    }

	}
} 






