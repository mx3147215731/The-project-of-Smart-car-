#include "uart.h"

#define SIZE 12



char AT_OK_Flag; 
char AT_Connect_Net_Flag ;
char Client_Connect_Flag ;



//工作在路由模式
code char LYMS[]="AT+CWMODE=2\r\n";
//使能多连接
code char DLJ[]="AT+CIPMUX=1\r\n";
//建立服务: 默认端口 333
code char JLIWF[]="AT+CIPSERVER=1\r\n";



void initWifI_AP()
{
	 sendString(LYMS);//设置路由模式
	 while(!AT_OK_Flag);
	 AT_OK_Flag=0;
   
	 sendString(DLJ); //使能多连接
	 while(!AT_OK_Flag);
	 AT_OK_Flag=0;

}

void waitConnect()
{
	
	 sendString(JLIWF);//建立服务器
	 while(!Client_Connect_Flag);
	 AT_OK_Flag=0;
	


}

