/****************************任务调度函数********************************/
#include "main.h"
#include "interval_task_scheduler.h"
#include "usart.h"

/** 模拟时间戳函数
 * @brief  每次调用，timestamp 增加 5
 * @param  
 * @return timestamp：时间戳
 */
static uint32_t get_mock_time_stamp_ms(void) {
    static uint32_t timestamp = 0;
    timestamp += 1;
    return timestamp;
}


/** 任务函数
 * @brief 根据要求创建不同任务
 * @param  
 * @return
 */
static void task1(void) {
		// 具体任务
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		printf("task1\n");
}

static void task2(void) {
    // 具体任务
}

/** 调度执行函数
 * @brief 根据不同时间分配来执行任务
 * @param  
 * @return
 */
void Task_scheduling_start(void) {
    TASK_RRD tasks[] = {// 定义任务列表
        {task_enable ,3000, 0, task1},  // 任务1
        {task_enable , 300, 0, task2}   // 任务2
    };

    // 创建任务调度器
    INTERVAL_TASK_SCHEDULER *scheduler = interval_task_scheduler_new(tasks, 2);
    if (scheduler == NULL) {
        printf("Scheduler creation failed\n");
        return;
    }

    // 设置调度器的时间戳获取函数
    scheduler->get_time_stamp_ms = get_mock_time_stamp_ms;

    // 模拟调度任务
    for (int i = 0; i < 2000; i++) {  // 模拟200次调度周期
        printf("Cycle %d:\n", i + 1);
        scheduler->schedule_task(scheduler);
    }
	
    // 释放调度器
    scheduler->del((void**)&scheduler);
}