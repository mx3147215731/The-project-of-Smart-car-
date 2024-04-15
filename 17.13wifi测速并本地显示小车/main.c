#include "reg52.h"
#include "motor.h"
#include "delay.h"
#include "uart.h"
#include "time.h"
#include "stdio.h"
#include "oled.h"
#include "ESP8266.h"


sbit speedIO =P3^2; //外部中断0
unsigned int speedCnt=0;
extern unsigned int speed;
extern char signal;
char speedMes[30];
//发送数据
char FSSJ[]="AT+CIPSEND=0,5\r\n";

void EX0Init()
{
EX0=1; //允许中断
//EA=1; //初始化串口的时候已经打开
IT0=1; //配置为下降沿触发



}

void main()
{

	Time0Init();//定时器0的初始化 -- 先写 -- 他的TMOD 是直接复制的，为了不影响后面的操作
	UartInit();//初始化 串口
	Delay1000ms(); // 给wifi模块上电时间
	initWifI_AP(); // wifi初始化, 工作在工作模式
	waitConnect();
	
	EX0Init(); //外部中断初始化
	Oled_Init();
	Oled_Clear();
	while(1){
	if(signal){ //1s发送一次，发完记得复位
		sendString(FSSJ);
    Delay1000ms();
		sprintf(speedMes,"%d cm/s ",speed);//组件字符串
		sendString(speedMes);
	  signal=0;
    }
		
		Oled_Show_Str(2,2,speedMes);
	}

} 
// 以下的外部中断我们设置为下降沿触发
void speedHandler() interrupt 0 
{
 speedCnt++;
}