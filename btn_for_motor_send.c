#include "tm4c123gh6pm.h"
#include "stdint.h"

void UART5_init (void){
SYSCTL_RCGCUART_R |=0x20; //provide clock to UART5
SYSCTL_RCGCGPIO_R |=0x10; //enable clock to PORTE
	//UART5 initialaization 
UART5_CTL_R=0; //disable uart5
UART5_IBRD_R=520; // 80MHZ/16*9600     (	NOT SURE IF 80MHZ OR 16MHZ )
UART5_FBRD_R=53;
UART5_LCRH_R=	0x70; //no parity,enable FIFO,width=8bit,1-stop bit
UART5_CTL_R=0x301; //enable UART5,TXE and RXE
  //GPIO config
GPIO_PORTE_DEN_R=0x30;    // make PE5,PE4 as digital
GPIO_PORTE_AMSEL_R=0;    //disable analog function 
GPIO_PORTE_AFSEL_R=0x30; //use PE5 and PE4 alternate function 
GPIO_PORTE_PCTL_R=0x00110000; //configure PE%,PE4 fot UART5
}


void PORT_F_INIT(void){
SYSCTL_RCGCGPIO_R |= 0x00000020; //enable clk for portF
	while((SYSCTL_PRGPIO_R & 0x00000020)==0); //wait 
	GPIO_PORTF_LOCK_R=0x4C4F434B; //unlock value defined in datasheet 
	GPIO_PORTF_CR_R=0xff; //enable ability to write to PUR for PF0
	GPIO_PORTF_DIR_R &= ~0x11; //set PF0 and PF4 as inputs 
	GPIO_PORTF_PUR_R=0x11; //enable pull-up-resistors on PF0 and PF4
	GPIO_PORTF_DEN_R |=0x11; //set PF0 and PF1 as digital
}


void UART5_Tx(uint8_t c){
	while((UART5_FR_R & 0x020 ) != 0); //wait untill buffer not full
	UART5_DR_R = c; //put data in uart data reg
}

 /* --input must be (GPIOF->DATA & 0x11) which contains PF0(SW2) and PF4(SW1) value 
    --output is char A or B or C
       A: shifts motor 30 degree clockwise
       B:  shift  motor 30 degree anti-clockwise
       C: no shift 
    --depend on : using pull-up resistor for PF0 and PF1    
*/
    char render_switchs_value (uint32_t pf0_pf4) {
 switch (pf0_pf4)
  {  
     case 0x00: //both swithces are pressed
       return 'C';
         break;
     case 0x01: //PF4(SW1) is pressed while PF0 isn't 
         return 'A';
         break;
     case 0x10: //PF0(SW2) is pressed while PF4 isn't
          return 'B'; 
         break;      
 
     default:
        return 'C';
         break;
 }



    }
