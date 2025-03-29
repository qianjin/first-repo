/************************************ͨ��Э����ش���********************************/
/*
���ܣ�����Ӵ��ڽ��յ�����λ�����͵����ݲ�ִ������������λ������ROV����
*/


#include "usart1.h"
#include "command.h"
#include "JY901.h"
#include "MS5837.h"
#include "control.h"
#include "PID.h"

//#include "servo.h"

/*************************������ݴ�����*****************************/
/*
���ܣ������յ��ĵ���������������õ��ת��
������RX_Engine_Control_Buff_Union rx_data
*/
void Engine_DataHandler(RX_Engine_Control_Buff_Union rx_data)
{
		Motor.motor1_speed=rx_data.engine.engine1;
		Motor.motor2_speed=rx_data.engine.engine2;
		Motor.motor3_speed=rx_data.engine.engine3;
		Motor.motor4_speed=rx_data.engine.engine4;
		Motor.motor5_speed=rx_data.engine.engine5;
		Motor.motor6_speed=rx_data.engine.engine6;
//		Motor.motor7_speed=rx_data.engine.engine7;
//		Motor.motor8_speed=rx_data.engine.engine8;
}

 
/*************************PID�������ݴ�����*****************************/
/*
���ܣ������յ���PID��������������PID����
������PID_Buff_Union PID_Data
*/
 void PID_DataHandler(PID_Buff_Union PID_Data)
{			
//			SendDataFlag_PID=1;	//��PID���ݷ��ͱ�־λ��һ���Ӷ���ʱ��Ƭѭ���з���PID���ݸ���λ����
													//��ΪPID�������ݹ��෢��ʱ��ϳ������ڴ˴�ֱ�ӷ��ͣ��п�������ķ��ա�
			
			pidData_pitch.kP=PID_Data.piddata.pitch_P;
			pidData_pitch.kI=PID_Data.piddata.pitch_I;
			pidData_pitch.kD=PID_Data.piddata.pitch_D;
			
			pidData_pitch_w.kP=PID_Data.piddata.pitch_w_P;
			pidData_pitch_w.kI=PID_Data.piddata.pitch_w_I;
			pidData_pitch_w.kD=PID_Data.piddata.pitch_w_D;
	        
			pidData_depth.kP=PID_Data.piddata.depth_P;
			pidData_depth.kI=PID_Data.piddata.depth_I;
			pidData_depth.kD=PID_Data.piddata.depth_D;
	        
			pidData_yaw_w.kP=PID_Data.piddata.yaw_w_P;
			pidData_yaw_w.kI=PID_Data.piddata.yaw_w_I;
			pidData_yaw_w.kD=PID_Data.piddata.yaw_w_D;

}
/*************************PID�趨Ŀ��ֵ���ݴ�����*****************************/
/*
���ܣ������յ���PID�趨Ŀ��ֵ����������PID����
������Motion_Contorl_Buff_Union setpara_data
*/
void Setpara_Handler(Motion_Contorl_Buff_Union setpara_data)
{
	pidData_depth.set = setpara_data.setpara.depth_set;
	pidData_pitch.set = setpara_data.setpara.pitch_set;
	pidData_yaw_w.set = setpara_data.setpara.yaw_w_set;
}

/*************************�ֱ�ֵ���ݴ�����*****************************/
/*
���ܣ������ֱ�����
������Handle_Buff_Union setpara_data
*/
void Handle_Handler(Handle_Buff_Union setpara_data)
{
	handle.left_x=setpara_data.handle.left_x;
	handle.left_y=setpara_data.handle.left_y;
	handle.right_x=setpara_data.handle.right_x;
	handle.right_y=setpara_data.handle.right_y;	
	handle.Key = setpara_data.handle.Key;
}

/*************************ģʽѡ����*****************************/
/*
���ܣ�������λ��ģʽ
������Handle_Buff_Union setpara_data
*/
void Mode_Handler(RX_Mode_Buff_Union setpara_data)
{
	control_mode=setpara_data.mode;
}


/*-----------------�����ʼλ----------------*/
uint8_t Is_Startbit(uint8_t data){
	if (data!= Startbit_Engine_Control&&
			data!=Startbit_Mode&&
			data!=Startbit_PIDData&&
			data!=Startbit_Motion_Control&&
			data!=Startbit_Handle&&
			data!=Startbit_Servo){
			return 0;
		}
			return 1;
}

/*-----------------����Ԥ�����鳤��----------------*/
uint8_t Get_Expected_Lenth_Of_Array(uint8_t Startbit){
	switch (Startbit){
		case Startbit_Engine_Control:
			return Engine_Control_BUFF_LENTH;
		case Startbit_Mode:
			return Mode_BUFF_LENTH;	
		case Startbit_PIDData:
			return PID_BUFF_LENTH;
		case Startbit_Motion_Control:
			return Motion_Control_BUFF_LENTH;
		case Startbit_Handle:
			return Handle_BUFF_LENTH;
		case Startbit_Servo:
			return Servo_BUFF_LENTH;
		default:
			return 0;
	}
}

/*-----------------У���С----------------*/
uint8_t Check_Tail_Of_Data(uint8_t Size,uint8_t Data_Array[],uint8_t Startbit_R){
	uint8_t Index = 0;
	uint8_t Calcu_Size = Startbit_R;
	uint8_t Len_Of_Array = Get_Expected_Lenth_Of_Array(Startbit_R);

	for(Index = 0;Index < Len_Of_Array;Index++){
		Calcu_Size += Data_Array[Index];
	}
	if(Calcu_Size==Size){
		return 1;		
	}
	return 0;
}

/*-----------------��������----------------*/
static PID_Buff_Union pid_data;	
static Handle_Buff_Union handle_data;	
static RX_Mode_Buff_Union rx_mode_data;	
static RX_Engine_Control_Buff_Union engine_data;
static Motion_Contorl_Buff_Union motion_contorl_data;	

void Save_Data(uint8_t Startbit,uint8_t Index,uint8_t Data){
	switch (Startbit){
		case Startbit_Engine_Control:
			engine_data.RX_Buff[Index] = Data;
			break;
		case Startbit_PIDData:
			pid_data.Buff[Index] = Data;
			break;
		case Startbit_Motion_Control:
			motion_contorl_data.Buff[Index] = Data;
			break;
		case Startbit_Handle:
			handle_data.Buff[Index] = Data;
			break;
		case Startbit_Mode:
			rx_mode_data.RX_Buff[Index] = Data;
			break;
		case Startbit_Servo:
			break;
	}
}

/*-----------------ѡ�������----------------*/
void Select_Server_Func(uint8_t Startbit){
	switch (Startbit){
		case Startbit_Engine_Control:
				Engine_DataHandler(engine_data);
				break;
		case Startbit_PIDData:
				PID_DataHandler(pid_data);
				break;
		case Startbit_Motion_Control:
				Setpara_Handler(motion_contorl_data);
				break;
		case Startbit_Mode:
				Mode_Handler(rx_mode_data);
				break;
		case Startbit_Handle:
				Handle_Handler(handle_data);
				break;
		case Startbit_Servo:
				break;
	}
}

uint8_t SendDataFlag_PID=0;//PID���ݷ��ͱ�־λ
void Command_Handler_R(uint8_t Data){
	static uint8_t Rx_Array[100];
	static uint8_t Is_Endtbit = 0;
	static uint8_t Has_Startbit = 0;	
	static uint8_t Rx_Array_Index = 0;
	
	static uint8_t Startbit = 0;
	static uint8_t Expected_Lenth_Of_Array = 0;
	
	// ��һ�ν��յ������ݴ���
	if(!Has_Startbit){
		Has_Startbit = Is_Startbit(Data);
	}
	
	if(!Has_Startbit){

		return;
	}
	
	// ���û������ͷ������Ԥ�ڵ����鳤�Ȳ��ұ�������ͷ
	if(!Startbit){
		Startbit = Data;
		Expected_Lenth_Of_Array = Get_Expected_Lenth_Of_Array(Startbit);
		
		return;
	}
	
	// �����ݴ��뻺����
	if(Rx_Array_Index < Expected_Lenth_Of_Array){
		Rx_Array[Rx_Array_Index] = Data;
		Save_Data(Startbit,Rx_Array_Index,Data);
		Rx_Array_Index++;
		return;
	}
	
	// ���յ������ݸ���ΪԤ�ڳ���
	Is_Endtbit = Check_Tail_Of_Data(Data,Rx_Array,Startbit);
	if(!Is_Endtbit){
		Startbit = 0;
		Has_Startbit = 0;
		Rx_Array_Index = 0;
		Expected_Lenth_Of_Array = 0;
		return;
	}
	
	// ��������
	Select_Server_Func(Startbit);

	Startbit = 0;
	Has_Startbit = 0;
	Rx_Array_Index = 0;
	Expected_Lenth_Of_Array = 0;
	
	

}

/***************************************************************
��������UpdateStatus(void)
���ܣ�������ʼ��startbit������λ��������Ӧ��ROV������Ϣ
������startbit
���أ���
*********************************************************************/
void UpdateStatus(uint8_t startbit)
{
	uint8_t i;
	uint8_t endbit=startbit;
	TX_Motion_Buff_Union TX_Data;
//	PID_Buff_Union PID_Data;
//	Motion_Contorl_Buff_Union set_data;		//�趨ֵ
	switch(startbit)
	{

		case(Startbit_Motion)://�����ʼ�����˶���Ϣ
		{
			TX_Data.motiondata.engine1=Motor.motor1_speed;				//��������ݸ�ֵ������������Ӧ��Ա
			TX_Data.motiondata.engine2=Motor.motor2_speed;
			TX_Data.motiondata.engine3=Motor.motor3_speed;
			TX_Data.motiondata.engine4=Motor.motor4_speed;
			TX_Data.motiondata.engine5=Motor.motor5_speed;
			TX_Data.motiondata.engine6=Motor.motor6_speed;
//			TX_Data.motiondata.engine7=Motor.motor7_speed;
//			TX_Data.motiondata.engine8=Motor.motor8_speed;
			
			
			TX_Data.motiondata.angle_x=JY901_val.angle_x;
			TX_Data.motiondata.angle_y=JY901_val.angle_y;
			
			TX_Data.motiondata.gyro_x=JY901_val.gyro_x;
			TX_Data.motiondata.gyro_y=JY901_val.gyro_y;
			TX_Data.motiondata.gyro_z=JY901_val.gyro_z;
			
			TX_Data.motiondata.deapth=MS5837_Val.depth;
			
			TX_Data.motiondata.mode=control_mode;

			USART1_SendByte(startbit);
			
			for(i=0;i<TX_BUFF_LENTH;i++)
			{
				USART1_SendByte(TX_Data.TX_Buff[i]);//���ν���������ÿһ���ֽڷ���
				endbit+=TX_Data.TX_Buff[i];//ͬʱ��ÿ���ֽڼӵ�У������
			}		
			USART1_SendByte(endbit);	//�������֮���У����
			USART1_SendByte(0xff);
			break;
			}
//		case(Startbit_PIDData)://����ͬ��ʽ����ע��ͬ��
//		{
//			PID_Data.piddata.pitch_P=pidData_pitch.kP;
//			PID_Data.piddata.pitch_I=pidData_pitch.kI;
//			PID_Data.piddata.pitch_D=pidData_pitch.kD;
//			
//						
//			PID_Data.piddata.pitch_w_P=pidData_pitch_w.kP;
//			PID_Data.piddata.pitch_w_I=pidData_pitch_w.kI;
//			PID_Data.piddata.pitch_w_D=pidData_pitch_w.kD;
//							
//			PID_Data.piddata.depth_P=pidData_depth.kP;
//			PID_Data.piddata.depth_I=pidData_depth.kI;
//			PID_Data.piddata.depth_D=pidData_depth.kD;

//			PID_Data.piddata.yaw_w_P=pidData_yaw_w.kP;
//			PID_Data.piddata.yaw_w_I=pidData_yaw_w.kI;
//			PID_Data.piddata.yaw_w_D=pidData_yaw_w.kD;

//			
//			USART1_SendByte(startbit);		//������ʼ��
//			for(i=0;i<PID_BUFF_LENTH;i++)
//			{
//				USART1_SendByte(PID_Data.Buff[i]);
//				endbit+=PID_Data.Buff[i];
//			}		
//			USART1_SendByte(endbit);	
//			break;
//		}
//		case(Startbit_Motion_Control):		//������˶�����
//		{
//			set_data.setpara.depth_set=pidData_depth.set;
//			set_data.setpara.pitch_set=pidData_pitch.set;
//			set_data.setpara.yaw_w_set=pidData_yaw_w.set;
//			USART1_SendByte(startbit);
//			for(i=0;i<Motion_Control_BUFF_LENTH;i++)
//			{
//				USART1_SendByte(set_data.Buff[i]);
//				endbit+=set_data.Buff[i];
//			}		
//			USART1_SendByte(endbit);	
//			break;
//		}	
	}
}

