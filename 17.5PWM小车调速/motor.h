
#include "reg52.h"
sbit RightConA=P3^3;
sbit RightConB=P3^2;

sbit LeftConA=P3^4;
sbit LeftConB=P3^5;

void goForward(); // 前进


void goBack(); // 后退


void goLeft(); // 左转 -- 轮子左边不动，右边前进， 右边的速到大于左边的时候，就实现了左转


void goRight() ;// 右转 --轮子右边不动，左边前进

void stop(); // 停止