#include "reg52.h"
#include "hc04.h"
#include "delay.h"
#include "sg90.h"
 





void main()
{
	
	Time0Init();
	Time1Init();
	//刚上电让摄像头保持在中间
  sgMiddle();
	Delay2000ms();
	
	while(1){


				sgLeft();
		    Delay450ms();
			  sgMiddle();
		    Delay450ms();
				sgRight();
		    Delay450ms();
      	sgMiddle();
		    Delay450ms();
	}
} 






