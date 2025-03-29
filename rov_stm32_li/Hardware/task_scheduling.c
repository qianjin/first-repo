/****************************������Ⱥ���********************************/
#include "main.h"
#include "interval_task_scheduler.h"
#include "usart.h"

/** ģ��ʱ�������
 * @brief  ÿ�ε��ã�timestamp ���� 5
 * @param  
 * @return timestamp��ʱ���
 */
static uint32_t get_mock_time_stamp_ms(void) {
    static uint32_t timestamp = 0;
    timestamp += 1;
    return timestamp;
}


/** ������
 * @brief ����Ҫ�󴴽���ͬ����
 * @param  
 * @return
 */
static void task1(void) {
		// ��������
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		printf("task1\n");
}

static void task2(void) {
    // ��������
}

/** ����ִ�к���
 * @brief ���ݲ�ͬʱ�������ִ������
 * @param  
 * @return
 */
void Task_scheduling_start(void) {
    TASK_RRD tasks[] = {// ���������б�
        {task_enable ,3000, 0, task1},  // ����1
        {task_enable , 300, 0, task2}   // ����2
    };

    // �������������
    INTERVAL_TASK_SCHEDULER *scheduler = interval_task_scheduler_new(tasks, 2);
    if (scheduler == NULL) {
        printf("Scheduler creation failed\n");
        return;
    }

    // ���õ�������ʱ�����ȡ����
    scheduler->get_time_stamp_ms = get_mock_time_stamp_ms;

    // ģ���������
    for (int i = 0; i < 2000; i++) {  // ģ��200�ε�������
        printf("Cycle %d:\n", i + 1);
        scheduler->schedule_task(scheduler);
    }
	
    // �ͷŵ�����
    scheduler->del((void**)&scheduler);
}