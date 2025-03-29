#include "soft_i2c.h"

static GPIO_InitTypeDef g_GPIO_CONFIG = {
	.Pull = GPIO_NOPULL,
	.Speed = GPIO_SPEED_FREQ_HIGH,
};

/******************************************************************************/
/*-----------------------------------���ò�-----------------------------------*/
/******************************************************************************/

static inline void iic_scl_1(RRD_DRIVER_IIC *driver) {
	HAL_GPIO_WritePin(driver->params.__scl_port,driver->params.__scl_pin,GPIO_PIN_SET);
}

static inline void iic_scl_0(RRD_DRIVER_IIC *driver) {
		HAL_GPIO_WritePin(driver->params.__scl_port,driver->params.__scl_pin,GPIO_PIN_RESET);
}

static inline void iic_sda_1(RRD_DRIVER_IIC *driver) {
		HAL_GPIO_WritePin(driver->params.__sda_port,driver->params.__sda_pin,GPIO_PIN_SET);
}

static inline void iic_sda_0(RRD_DRIVER_IIC *driver) {
		HAL_GPIO_WritePin(driver->params.__sda_port,driver->params.__sda_pin,GPIO_PIN_RESET);
}

static inline uint8_t iic_sda_read(RRD_DRIVER_IIC *driver) {
	return HAL_GPIO_ReadPin(driver->params.__sda_port,driver->params.__sda_pin);
}

static void iic_to_write_mode(RRD_DRIVER_IIC *self)
{
	iic_scl_0(self);	// ��ֹ���л���дģʽ��ʱ�򣬳��ֲ�ȷ����ƽ
	g_GPIO_CONFIG.Pin = self->params.__sda_pin;
	g_GPIO_CONFIG.Mode = GPIO_MODE_OUTPUT_OD;
	HAL_GPIO_Init(self->params.__sda_port, &g_GPIO_CONFIG);
}

static void iic_to_read_mode(RRD_DRIVER_IIC *self)
{
	iic_scl_0(self);	// ��ֹ���л���дģʽ��ʱ�򣬳��ֲ�ȷ����ƽ
	g_GPIO_CONFIG.Pin = self->params.__sda_pin;
	g_GPIO_CONFIG.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(self->params.__sda_port, &g_GPIO_CONFIG);
}

/******************************************************************************/
/*----------------------------------�ڲ��궨��--------------------------------*/
/******************************************************************************/
#define I2C_WR	0		/* д����bit */
#define I2C_RD	1		/* ������bit */


/******************************************************************************/
/*-----------------------------------�ڲ�����---------------------------------*/
/******************************************************************************/
/**
 * @brief  			I2C����λ�ӳ٣����400KHz
 * @note			 �����ʱ����ͨ��������AX-Pro�߼������ǲ��Եõ��ġ�
							  CPU��Ƶ72MHzʱ�����ڲ�Flash����, MDK���̲��Ż�
							 ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
							 ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
							 ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
							 IAR���̱���Ч�ʸߣ���������Ϊ7
 * @param[in]   
 * @return      
 */
static inline void iic_delay(void)
{
	uint8_t i;
	for (i = 0; i < 20; i++);
}

/******************************************************************************/
/*-----------------------------------�ӿ�ʵ��---------------------------------*/
/******************************************************************************/
/**
 * @brief  			CPU����I2C���������ź�
 * @note				��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź�
 * @param[in]   
 * @return
 */
static void i2c_start(RRD_DRIVER_IIC *driver)
{
	iic_to_write_mode(driver);
	
	iic_sda_1(driver);
	iic_scl_1(driver);
	iic_delay();
	
	iic_sda_0(driver);
	iic_delay();
	
	iic_scl_0(driver);
	iic_delay();
}

/**
 * @brief  			CPU����I2C����ֹͣ�ź�
 * @note				��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź�
 * @param[in]   
 * @return
 */
static void i2c_stop(RRD_DRIVER_IIC *driver)
{
	iic_to_write_mode(driver);
	
	iic_sda_0(driver);
	iic_scl_1(driver);
	iic_delay();
	
	iic_scl_1(driver);
	iic_delay();
	
	iic_sda_1(driver);
	iic_delay();
}

/**
 * @brief  			CPU����һ��ACK�ź�
 * @param[in]   
 * @return
 */
static void i2c_ack(RRD_DRIVER_IIC *driver)
{
	iic_to_write_mode(driver);
	
	iic_sda_0(driver);
	iic_delay();
	iic_scl_1(driver);
	iic_delay();
	iic_scl_0(driver);
}

/**
 * @brief  			CPU����1��NACK�ź�
 * @param[in]   
 * @return
 */
static void i2c_nack(RRD_DRIVER_IIC *driver)
{	
	iic_to_write_mode(driver);
	
	iic_sda_1(driver);
	iic_delay();
	iic_scl_1(driver);
	iic_delay();
	iic_scl_0(driver);
}

/**
 * @brief  			CPU��I2C�����豸����8bit����
 * @param[in]   _ucByte  �ȴ����͵��ֽ�
 * @note				�ȷ����ֽڵĸ�λbit7
 * @return
 */
static void i2c_send_byte(RRD_DRIVER_IIC *driver, uint8_t byte)
{
	iic_to_write_mode(driver);
	
	for (uint8_t i = 0; i < 8; i++)
	{		
		(byte & 0x80)? iic_sda_1(driver) 
								 : iic_sda_0(driver);
		iic_delay();
		iic_scl_1(driver);
		iic_delay();	
		iic_scl_0(driver);
		iic_delay();
		byte <<= 1;
	}
	iic_sda_1(driver); // �ͷ�����,�ôӻ������ź�
}


/**
 * @brief  			CPU��I2C�����豸��ȡ8bit����	
 * @param[in]   
 * @return			����������
 */
static uint8_t i2c_read_byte(RRD_DRIVER_IIC *driver, uint8_t ack)
{
	iic_to_read_mode(driver);
	
	uint8_t value;

	for (uint8_t i = 0; i < 8; i++)
	{
		value <<= 1;
		iic_scl_1(driver);
		iic_delay();
		if (iic_sda_read(driver)){
			value++;
		}
		iic_scl_0(driver);
		iic_delay();
	}
	
	(ack)? i2c_ack(driver) 
			 : i2c_nack(driver);

	return value;
}

/**
 * @brief  			CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
 * @param[in]   
 * @return			0:��ȷӦ��1:��������Ӧ
 */
static uint8_t i2c_wait_ack(RRD_DRIVER_IIC *driver)
{
	iic_sda_1(driver);	// CPU�ͷ�SDA����,�ôӻ���������
	iic_delay();
	
	iic_to_read_mode(driver);
	
	iic_scl_1(driver);
	iic_delay();
	
	uint8_t re = iic_sda_read(driver);
	
	iic_scl_0(driver);
	iic_delay();
	return re;
}

/**
 * @brief  			���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
 * @param[in]   address �豸��I2C���ߵ�ַ
 * @return			0:��ȷ�� 1:δ̽�⵽
 */
static uint8_t i2c_check_device(RRD_DRIVER_IIC *driver,uint8_t address)
{
	i2c_start(driver);
	
	i2c_send_byte(driver,address|I2C_WR);		// �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ�
	uint8_t ack = i2c_wait_ack(driver);			// ����豸��ACKӦ��

	i2c_stop(driver);

	return ack;
}

/**
 * @brief   	 ������ȡ����
 * @param[in]  slave_add 	�ӻ���ַ
 * @param[in]  reg_add 		Ŀ��Ĵ�����ַ
 * @param[in]  data_list	��Ŷ�ȡ���ݵĻ�����
 * @param[in]  num 			Ҫ��ȡ�������ֽ���
 * @return  	 0 �ɹ�  1 ʧ��
 */
static uint8_t iic_read_buffer(RRD_DRIVER_IIC *driver,
								const uint8_t slave_add,
								const uint8_t reg_add,
								uint8_t* data_list,
								uint8_t num)
{
	i2c_start(driver);
	i2c_send_byte(driver,slave_add);
	i2c_wait_ack(driver);
	i2c_send_byte(driver,reg_add);
	i2c_wait_ack(driver);
	
	i2c_start(driver);
	i2c_send_byte(driver,slave_add+1);
	i2c_wait_ack(driver);
	
	while(num --){
		*data_list++ = i2c_read_byte(driver,num != 0);
	}
	
	i2c_stop(driver);
	return 0;
}

/**
 * @brief   	 ������������
 * @param[in]  reg_add 	Ŀ��Ĵ�����ַ
 * @param[in]  data_list	��Ŷ�ȡ���ݵĻ�����
 * @param[in]  num 			Ҫ��ȡ�������ֽ���
 * @return  
 */
static uint8_t iic_write_buffer(RRD_DRIVER_IIC *driver,
								const uint8_t slave_add,
								const uint8_t reg_add,
								uint8_t* data_list,
								uint8_t num)
{
	i2c_start(driver);
	i2c_send_byte(driver,slave_add);
	i2c_wait_ack(driver);
	i2c_send_byte(driver,reg_add);
	i2c_wait_ack(driver);
	
	while(num--){
		i2c_send_byte(driver,*data_list++);
		i2c_wait_ack(driver);
	}   
	i2c_stop(driver);
	return 0;
}

void iic_config_gpios(RRD_DRIVER_IIC *driver,
						GPIO_TypeDef* scl_port,
						uint16_t scl_pin,
						GPIO_TypeDef* sda_port,
						uint16_t sda_pin,
						uint16_t timeout)
{
	driver->params.__scl_port = scl_port;
	driver->params.__scl_pin = scl_pin;
	driver->params.__sda_port = sda_port;
	driver->params.__sda_pin = sda_pin;
	driver->params.__timeout = timeout;
}

/******************************************************************************/
/*----------------------------------�ӿڳ�ʼ��--------------------------------*/
/******************************************************************************/
SOFT_IIC_DRIVER_INTERFACE_RRD SOFT_IIC_DRIVER_INTERFACE = {
	.read_byte = (soft_iic_read_byte_fn_t)i2c_read_byte,
	.send_byte = (soft_iic_send_byte_fn_t)i2c_send_byte,
	.read_buffer = (soft_iic_read_buffer_fn_t)iic_read_buffer,
	.write_buffer = (soft_iic_write_buffer_fn_t)iic_write_buffer,
	.config_gpios = (soft_iic_config_gpios_fn_t)iic_config_gpios,
	.check_device = (soft_iic_check_device_fn_t)i2c_check_device
};

/**
 * @brief  			��ʼ��iic�豸
 * @param[in]   driver iic�豸ָ��
 * @return			0:��ʼ���ɹ�  -1:δ��ʼ���ɹ�
 */
RRD_DRIVER_IIC *iic_driver_new(void)
{
	RRD_DRIVER_IIC* driver;
	driver = malloc(sizeof(*driver));
	if(NULL == driver){
		// debug_log("RRD_USART_MANAGER malloc failed");
		return NULL;
	}

	/** \addtogroup Removed 
	 ** \{  */
	// driver->__ack = i2c_ack;
	// driver->__nack = i2c_nack;
	// driver->__stop = i2c_stop;
	// driver->__start = i2c_start;
	// driver->__wait_ack = i2c_wait_ack;
	/** \}  */
	driver->interface = &SOFT_IIC_DRIVER_INTERFACE;
	return driver;
}
