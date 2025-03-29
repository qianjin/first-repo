/********************************��е��********************************/

#include "stm32f10x.h"                  // Device header
#include "math.h"
#include "Delay.h"
#include "mechanical_arm.h"

/********************************************************************/
/*------------------------------������------------------------------*/
/********************************************************************/

void Arm_Init(void)
{

}


/********************************************************************/
/*-----------------------ƽ���ı����Ƕ�---------------------------*/
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
	// ���徲̬����
	static float currentangle1 = 0;
	static float currentangle2 = 0;
	static float currentangle3 = 0;
	
	// ��������
	while(fabs(targetangle1 - currentangle1) > step ||
				fabs(targetangle2 - currentangle2) > step ||
				fabs(targetangle3 - currentangle2) > step){
				
				if(fabs(targetangle1 - currentangle1) > step)// ��ǰĿ��ǶȺ͵�ǰ�ǶȲ�ֵ��������ֵ
						currentangle1 += (targetangle1 > currentangle1) ? step : -step;// �����Ƕ�1�����ӻ���ٲ���ֵ
        else
            currentangle1 = targetangle1;// �����ֵ����������ֵ��ֱ�ӽ��Ƕ�1����ΪĿ��Ƕ�

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