#include "reg52.h"
#include "motor.h"
#include "string.h"


#define SIZE 12
sfr AUXR = 0x8E;
char buffer[SIZE];

extern char AT_OK_Flag; 
extern char Client_Connect_Flag;

void UartInit(void)		//9600bps@11.0592MHz
{
	AUXR=0x01; //减少定时器辐射 -- 抗干扰
	SCON =0x50; //配置 串口口工作方式1，REN 使能接收
	//不配 PCON  -- 不设置倍数关系
	//配置定时器1为 8位自动重装
	TMOD &=0xF0; //高位清零
  TMOD |=0x20;  //00 10  -- 配置为定时器1为: 1 0 模式 -- 8位自动重装
  
	//定义初值
  TL1=0xFD;
	TH1=0xFD; // 9600 波特率的初值
  TR1= 1; // 定时器 -- 启动
	
	EA =1; // 开启总中断
	ES=1;  // 开启串口中断
	
}


void sendByte(char mydata)
{
  SBUF=mydata;
  while(!TI); //TI用来记录是否发送成功， 0 -- 没发送成功， 1 -- 发送成功
	TI=0;

}


void sendString(char *str)
{
 while(*str != '\0'){
   sendByte(*str);
	 str++;
  }

}


void uartHandler() interrupt 4
{
	static int  i = 0;
	char tmp;
 if(RI) // 中断处理函数中，对于接收中断的响应
 {
    RI=0; //清楚接收中断标志位
	  tmp = SBUF;
	  if(tmp == 'M' || tmp == 'O'|| tmp == '0' )
			 i=0;
		buffer[i++]=tmp;

		  if(buffer[0]=='0' && buffer[2]=='C'){//0,Connect
     Client_Connect_Flag=1;
		 memset(buffer,'\0',SIZE);
    }

	    if(buffer[0]=='O' && buffer[1]=='K'){//联网成功 WIFI GOT 
     AT_OK_Flag=1;
		 memset(buffer,'\0',SIZE);
    }
		
	  if(buffer[0] == 'M'){
			switch(buffer[1]){
			case '1':
					goForward();
					break;
		
			case '2':
					goBack();
					break;
			
			case '3':
					goLeft();
					break;
		
			case '4':
					goRight();
					break;
			default://前提是M开关，但不是上面4跳到额指令不然就进不来了
				stop();
			  break;
			
			}
		
    }
	 if(i == SIZE) {
		 i = 0;
     memset(buffer,'\0',SIZE);
    }
 }
  
	
}

