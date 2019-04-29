#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "btn_for_motor_send.h"
#include "stdint.h"

void SystemInit(void){
	PLL_Init();
	UART5_init ();
    PORT_F_INIT();
}

int main(void){
 uint32_t pf0_pf4;
 uint8_t status_char;   
while(1){
pf0_pf4= (GPIO_PORTF_DATA_R & 0X11);
status_char=render_switchs_value (pf0_pf4);
void UART5_Tx(status_char);
    }
}