#include "reg52.h"

#include "oled.h"




void main()
{

//1. oled 初始化
	Oled_Init(); 
	Oled_Clear();
  Oled_Show_Str(2,2,"speed: 35cm/s");

	

	
	while(1);
}