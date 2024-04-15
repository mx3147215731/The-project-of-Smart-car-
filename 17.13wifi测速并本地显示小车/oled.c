#include "reg52.h"
#include "intrins.h"
#include "Oledfont.h"


sbit scl = P1^2;
sbit sda = P1^3;

void IIC_Start()
{
	scl = 0;
	sda = 1;
	scl = 1;
	_nop_();
	sda = 0;
	_nop_();
}

void IIC_Stop()
{
	scl = 0;
	sda = 0;
	scl = 1;
	_nop_();
	sda = 1;
	_nop_();
}

char IIC_ACK()
{
	char flag;
	sda = 1;//就在时钟脉冲9期间释放数据线
	_nop_();
	scl = 1;
	_nop_();
	flag = sda;
	_nop_();
	scl = 0;
	_nop_();
	
	return flag;
}

void IIC_Send_Byte(char dataSend)
{
	int i;
	
	for(i = 0;i<8;i++){
		scl = 0;//scl拉低，让sda做好数据准备
		sda = dataSend & 0x80;//1000 0000获得dataSend的最高位，给sda
		_nop_();//发送数据建立时间
		scl = 1;//scl拉高开始发送
		_nop_();//数据发送时间
		scl = 0;//发送完毕拉低
		_nop_();//
		dataSend = dataSend << 1;
	}
}

void Oled_Write_Cmd(char dataCmd)
{
	//	1. start()
	IIC_Start();
	//		
	//	2. 写入从机地址  b0111 1000 0x78
	IIC_Send_Byte(0x78);
	//	3. ACK
	IIC_ACK();
	//	4. cotrol byte: (0)(0)000000 写入命令   (0)(1)000000写入数据
	IIC_Send_Byte(0x00);
	//	5. ACK
	IIC_ACK();
	//6. 写入指令/数据
	IIC_Send_Byte(dataCmd);
	//7. ACK
	IIC_ACK();
	//8. STOP
	IIC_Stop();
}

void Oled_Write_Data(char dataData)
{
	//	1. start()
	IIC_Start();
	//		
	//	2. 写入从机地址  b0111 1000 0x78
	IIC_Send_Byte(0x78);
	//	3. ACK
	IIC_ACK();
	//	4. cotrol byte: (0)(0)000000 写入命令   (0)(1)000000写入数据
	IIC_Send_Byte(0x40);
	//	5. ACK
	IIC_ACK();
	///6. 写入指令/数据
	IIC_Send_Byte(dataData);
	//7. ACK
	IIC_ACK();
	//8. STOP
	IIC_Stop();
}


void Oled_Init(void){
	Oled_Write_Cmd(0xAE);//--display off
	Oled_Write_Cmd(0x00);//---set low column address
	Oled_Write_Cmd(0x10);//---set high column address
	Oled_Write_Cmd(0x40);//--set start line address  
	Oled_Write_Cmd(0xB0);//--set page address
	Oled_Write_Cmd(0x81); // contract control
	Oled_Write_Cmd(0xFF);//--128   
	Oled_Write_Cmd(0xA1);//set segment remap 
	Oled_Write_Cmd(0xA6);//--normal / reverse
	Oled_Write_Cmd(0xA8);//--set multiplex ratio(1 to 64)
	Oled_Write_Cmd(0x3F);//--1/32 duty
	Oled_Write_Cmd(0xC8);//Com scan direction
	Oled_Write_Cmd(0xD3);//-set display offset
	Oled_Write_Cmd(0x00);//
	
	Oled_Write_Cmd(0xD5);//set osc division
	Oled_Write_Cmd(0x80);//
	
	Oled_Write_Cmd(0xD8);//set area color mode off
	Oled_Write_Cmd(0x05);//
	
	Oled_Write_Cmd(0xD9);//Set Pre-Charge Period
	Oled_Write_Cmd(0xF1);//
	
	Oled_Write_Cmd(0xDA);//set com pin configuartion
	Oled_Write_Cmd(0x12);//
	
	Oled_Write_Cmd(0xDB);//set Vcomh
	Oled_Write_Cmd(0x30);//
	
	Oled_Write_Cmd(0x8D);//set charge pump enable
	Oled_Write_Cmd(0x14);//
	
	Oled_Write_Cmd(0xAF);//--turn on oled panel		
}

void Oled_Clear()
{
	unsigned char i,j; //-128 --- 127
	
	for(i=0;i<8;i++){
		Oled_Write_Cmd(0xB0 + i);//page0--page7
		//每个page从0列
		Oled_Write_Cmd(0x00);
		Oled_Write_Cmd(0x10);
		//0到127列，依次写入0，每写入数据，列地址自动偏移
		for(j = 0;j<128;j++){
			Oled_Write_Data(0);
		}
	}
}

void Oled_Show_Char(char row,char col,char oledChar){ //row*2-2
	unsigned int  i;
	Oled_Write_Cmd(0xb0+(row*2-2));                           //page 0
	Oled_Write_Cmd(0x00+(col&0x0f));                          //low
	Oled_Write_Cmd(0x10+(col>>4));                            //high	
	for(i=((oledChar-32)*16);i<((oledChar-32)*16+8);i++){
		Oled_Write_Data(F8X16[i]);                            //写数据oledTable1
	}

	Oled_Write_Cmd(0xb0+(row*2-1));                           //page 1
	Oled_Write_Cmd(0x00+(col&0x0f));                          //low
	Oled_Write_Cmd(0x10+(col>>4));                            //high
	for(i=((oledChar-32)*16+8);i<((oledChar-32)*16+8+8);i++){
		Oled_Write_Data(F8X16[i]);                            //写数据oledTable1
	}		
}


/******************************************************************************/
// 函数名称：Oled_Show_Char 
// 输入参数：oledChar 
// 输出参数：无 
// 函数功能：OLED显示单个字符
/******************************************************************************/
void Oled_Show_Str(char row,char col,char *str){
	while(*str!=0){
		Oled_Show_Char(row,col,*str);
		str++;
		col += 8;	
	}		
}
