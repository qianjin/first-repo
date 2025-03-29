/********************************机械臂********************************/

#include "stm32f10x.h"                  // Device header
#include "math.h"
#include "Delay.h"
#include "mechanical_arm.h"

/********************************************************************/
/*------------------------------驱动层------------------------------*/
/********************************************************************/

void Arm_Init(void)
{

}


/********************************************************************/
/*-----------------------平滑改变舵机角度---------------------------*/
/********************************************************************/
void PWM_SetCompare1(unsigned int Compare)
{
	TIM_SetCompare1(TIM3, Compare);
}

void PWM_SetCompare2(unsigned int Compare)
{
	TIM_SetCompare1(TIM3, Compare);
}

void PWM_SetCompare3(unsigned int Compare)
{
	TIM_SetCompare1(TIM3, Compare);
}

void Set_Angle(float targetangle1,float targetangle2,float targetangle3,float step,unsigned int delay)
{
	// 定义静态变量
	static float currentangle1 = 0;
	static float currentangle2 = 0;
	static float currentangle3 = 0;
	
	// 步进调整
	while(fabs(targetangle1 - currentangle1) > step ||
				fabs(targetangle2 - currentangle2) > step ||
				fabs(targetangle3 - currentangle2) > step){
				
				if(fabs(targetangle1 - currentangle1) > step)// 当前目标角度和当前角度差值超过步进值
						currentangle1 += (targetangle1 > currentangle1) ? step : -step;// 调整角度1，增加或减少步进值
        else
            currentangle1 = targetangle1;// 如果差值不超过步进值，直接将角度1设置为目标角度

				if(fabs(targetangle2 - currentangle2) > step)
						currentangle2 += (targetangle2 > currentangle2) ? step : -step;
        else
            currentangle2 = targetangle2;
	
				if(fabs(targetangle3 - currentangle3) > step)
						currentangle3 += (targetangle3 > currentangle3) ? step : -step;
        else
            currentangle3= targetangle3;
				
				PWM_SetCompare1(currentangle1 / 180 * 2000 + 500);
				PWM_SetCompare2(currentangle2 / 180 * 2000 + 500);
				PWM_SetCompare3(currentangle3 / 180 * 2000 + 500);
				
				delay_us(delay);
				}
}