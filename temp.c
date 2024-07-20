#include "temp.h"
#include "OLED.h"

GPIO_InitTypeDef struct1;
extern TIM_HandleTypeDef htim1;
void test_pin()
{
DQ(1);
}
void gpio_uodate_init()
{
  struct1.Pin = DQ_Pin;
  struct1.Mode = GPIO_MODE_OUTPUT_PP;
  struct1.Pull = GPIO_PULLUP;
  struct1.Speed = GPIO_SPEED_FREQ_LOW;
}
void  mx_delay(uint8_t j)
{
	for(uint8_t i=j;i>0;i--);
}
//微秒延时
void Delay_us(uint16_t us)
{     
	uint16_t differ = 0xffff-us-5;				
	__HAL_TIM_SET_COUNTER(&htim1,differ);	//设定TIM1计数器起始值
	HAL_TIM_Base_Start(&htim1);		//启动定时器	
	
	while(differ < 0xffff-5)//判断
	{	
		differ = __HAL_TIM_GET_COUNTER(&htim1);		//查询计数器的计数值
	}
	HAL_TIM_Base_Stop(&htim1);//关闭定时器
}

void Temp_init()
{
	uint8_t x=0;
	DQ(1);
	Delay_us(100);
	DQ(0);
	Delay_us(500);
	DQ(1);
	//mx_delay(5);
	Delay_us(60);
	if(R_DQ==0)
		//OLED_ShowString(3,1,"OPEN");
	Delay_us(200);
}
uint8_t ReadOneChar(void)
{
	//struct1.Mode=GPIO_MODE_INPUT;
	//HAL_GPIO_Init(io_port,&struct1);
	uint8_t i =0;
	uint8_t dat =0;
	for (i=8;i>0;i--) 	
	{
//		DQ(1);
//		Delay_us(10);
		DQ(0);
		Delay_us(2);
		dat>>=1;
		DQ(1);
		Delay_us(12);
		if(R_DQ)
			dat|=0x80; 
		Delay_us(50);
		
	}
	return dat;
}
void WriteOneChar(uint8_t dat)
{
    //struct1.Mode=GPIO_MODE_OUTPUT_PP;
	//HAL_GPIO_Init(io_port,&struct1);
	for(uint8_t i =8;i>0;i--)
	{
		DQ(0);
		Delay_us(2);
		DQ(dat&0x01); 
		Delay_us(60);
		DQ(1);
		dat>>=1;
		Delay_us(5);
	}
	Delay_us(4);
	
}

uint32_t ReadTemp(void)
{
	
	
	uint8_t fg=1;
	uint32_t sdata=0;
	Temp_init();
	WriteOneChar(0xcc);
	WriteOneChar(0x44);
	Delay_us(1250);
	Temp_init();
	WriteOneChar(0xcc);
	WriteOneChar(0xbe);
	uint8_t tempL=ReadOneChar();
	uint8_t tempH=ReadOneChar();
	if(tempH>0x7f)
	{
		tempL=~tempL;
		tempH=~tempH+1;
		fg=0;
	}
	sdata = tempL/16+tempH*16;  
	OLED_ShowNum(1,1,sdata,3);
	OLED_ShowNum(4,1,tempH,5);
	OLED_ShowNum(3,1,tempL,5);
	return sdata;
	
}	