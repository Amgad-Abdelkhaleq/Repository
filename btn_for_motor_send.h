#ifndef __btn_for_motor_send_h__
#define	__btn_for_motor_send_h__

#include "stdint.h"
void UART5_init(void);
void PORT_F_INIT(void);
void UART5_Tx(uint8_t c);
char render_switchs_value (uint32_t pf0_pf4);
#endif // __btn_for_motor_send_h__