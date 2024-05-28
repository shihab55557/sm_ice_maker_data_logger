#include "stm32g030xx.h"
#include "uart.h"
#include "adc.h"
#include "timer.h"

long adctotemp(long adc){
    long T;
    if ( adc > 3979 )	{
        //uart_send("error    ");
        T=999;
    }
    else if ( adc > 3878 ){
        T= (-1024*adc + 3664896)>>10;
    }
    else if ( adc > 3714 )	{
        T= (-625*adc + 2114809)>>10;
    }
    else if ( adc > 3470 )	{
        T= (-420*adc + 1354281)>>10	;
    }
    else if ( adc >3136 )	{
        T= (-307*adc + 961762)>>10;	
    }	
    else if ( adc > 2726 )	{
        T= (-250*adc + 783484)>>10	;	
    }
    else if ( adc > 2274 )	{
        T= (-227*adc + 720198)>>10	;
    }	
    else if ( adc > 1825 )	{
        T= (-229*adc + 723641)>>10;
    }
    else if ( adc > 1420 )	{
        T= (-253*adc + 768884)>>10	;
    }	
    else if ( adc > 1080 )	{
        T= (-302*adc + 837571)>>10	;	
    }	
    else if ( adc > 811 )	{
        T= (-381*adc + 923503)>>10	;
    }	
    else{
        //uart_send("error    ");
        T=999;
    }
    return T;
}



void lever_stat(void){
		
}



void measurmnt(void){
	uint16_t lever=0;
	uint16_t rotation=0;
	uint16_t valve=0;
	
	lever = adc_read_filtered(3);
	rotation =  adc_read_filtered(4);
	
	valve = adc_read_filtered(5);
	
	
	
	if (lever <= 4000){
		lever = lever/10;
		uart_send_char("Lever: ");
		uart_send_num(lever);
		uart_send_char("\r\n");
	}
	if (rotation <= 4000){
		rotation = rotation/10;
		uart_send_char("Rotation: ");
		uart_send_num(rotation);
		uart_send_char("\r\n");
	}
	if (valve >= 3000){
		valve = valve/10;
		uart_send_char("Valve: ");
		uart_send_num(valve);
		uart_send_char("\r\n");
	}
}


volatile uint16_t updatedValue = 0;

void TIM1_BRK_UP_TRG_COM_IRQHandler(void) {
    if (TIM1->SR & TIM_SR_UIF) {
        TIM1->SR &= ~TIM_SR_UIF;
				uint16_t adc_value1=0;
				uint16_t temp=0;
				adc_value1 = adc_read_filtered(2);
				temp = adctotemp(adc_value1);
				uart_send_char("Temp: ");
				uart_send_num(temp);
				uart_send_char("\r\n");
    }
}


int main(void) {
    uart_Init(38400);    // Initialize UART with desired baud rate
	  uart_send_char("\r\nDebug Started\r\n");
	  for(uint32_t i=0;i<1000000;i++){
			 __NOP();
		}
		adc_init();
		timer_Init(0xFFF, 0x1E86);
		
		
		uint16_t temp=0;
    while (1) {
				measurmnt();
				for(uint32_t i=0;i<100000;i++){
					__NOP();
				}
    }
}

