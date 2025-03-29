#ifndef __SCHEDULER_H
#define __SCHEDULER_H
#include "stdint.h"
#include "main.h"
struct ROVScheduler//时间片轮转结构体
{
	uint16_t cnt_5ms,cnt_10ms,cnt_20ms,cnt_50ms,cnt_100ms,cnt_1000ms;
};

extern struct ROVScheduler scheduler;

void Scheduler_Counter(void);
void ROV_Loop(void);
#endif
