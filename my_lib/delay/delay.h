#ifndef __DELAY_H
#define __DELAY_H 			   

#include "gd32f4xx.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//使用SysTick的普通计数模式对延迟进行管理(支持OS)
//包括delay_us,delay_ms
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/7/8
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//********************************************************************************
//修改说明
//V1.1 20160708 
//移植自F429的例程,针对F7做了相应修改
////////////////////////////////////////////////////////////////////////////////// 

typedef unsigned          char u8;
typedef unsigned short     int u16;
typedef unsigned           int u32;

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























