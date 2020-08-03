#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "PLL.h"
#include "SysTick.h"
#include <stdio.h>
#include "uart.h"
#include "math.h"

#include <stdio.h>
#include <stdlib.h>

//Justin Chan
//400177650
//chanj89
//Used 96MHz or 4
//LED pins N0 and L1

#define NVIC_ST_CTRL_R          (*((volatile uint32_t *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile uint32_t *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile uint32_t *)0xE000E018))
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Counter load value

// Initialize SysTick with busy wait running at bus clock.
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}
// Time delay using busy wait.
// The delay parameter is in units of the core clock. (units of 8.333 nsec for 120 MHz clock)


void PortN_Init(void){
	//Use PortN onboard LED	
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R12;				// activate clock for Port N
	while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R12) == 0){};	// allow time for clock to stabilize
	GPIO_PORTN_DIR_R |= 0b11101;        								// make PN0 out (PN0 built-in LED1)
  GPIO_PORTN_AFSEL_R &= ~0b11101;     								// disable alt funct on PN0
  GPIO_PORTN_DEN_R |= 0b11101;        								// enable digital I/O on PN0
																									// configure PN1 as GPIO
  //GPIO_PORTN_PCTL_R = (GPIO_PORTN_PCTL_R&0xFFFFFF0F)+0x00000000;
								// disable analog functionality on PN0		
	

	return;
}

void PortL_Init(void){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R10;	
	while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R10) == 0){};	
	GPIO_PORTL_DIR_R |= 0b1111;        								
  GPIO_PORTL_AFSEL_R &= ~0b1111;     								
  GPIO_PORTL_DEN_R |= 0b1111;        								    									
	

	return;
}

void PortM_Init(void){
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R11;				
	while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R11) == 0){};	
	GPIO_PORTM_DIR_R |= 0xFF; 
  GPIO_PORTM_AFSEL_R &= ~0xFF;     							
  GPIO_PORTM_DEN_R |= 0xFF;        							
	return;
}

void SysTick_Wait(uint32_t delay){
  volatile uint32_t elapsedTime;
  uint32_t startTime = NVIC_ST_CURRENT_R;
  do{
    elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(elapsedTime <= delay);
}

void motorForward1(){
	for(int i = 1; i <= 2; i++){		//512 is one full rotation
		int delay = 90000;
		GPIO_PORTM_DATA_R &= 0b11110000;
		GPIO_PORTM_DATA_R |= 0b00001001;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b11110000;
		GPIO_PORTM_DATA_R |= 0b00001100;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b11110000;
		GPIO_PORTM_DATA_R |= 0b00000110;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b11110000;
		GPIO_PORTM_DATA_R |= 0b00000011;
		SysTick_Wait(delay);
		
	}
}

void motorForward2(){
	for(int i = 1; i <= 2; i++){		//512 is one full rotation
		int delay = 90000;
		GPIO_PORTM_DATA_R &= 0b00001111;
		GPIO_PORTM_DATA_R |= 0b10010000;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b00001111;
		GPIO_PORTM_DATA_R |= 0b11000000;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b00001111;
		GPIO_PORTM_DATA_R |= 0b01100000;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b00001111;
		GPIO_PORTM_DATA_R |= 0b00110000;
		SysTick_Wait(delay);
				
	}
}
void motorForward3(){
	for(int i = 1; i <= 2; i++){		//512 is one full rotation
		int delay = 90000;
		GPIO_PORTL_DATA_R &= 0b00000000;
		GPIO_PORTL_DATA_R |= 0b00001001;
		SysTick_Wait(delay);
		GPIO_PORTL_DATA_R &= 0b00000000;
		GPIO_PORTL_DATA_R |= 0b00001100;
		SysTick_Wait(delay);
		GPIO_PORTL_DATA_R &= 0b00000000;
		GPIO_PORTL_DATA_R |= 0b00000110;
		SysTick_Wait(delay);
		GPIO_PORTL_DATA_R &= 0b00000000;
		GPIO_PORTL_DATA_R |= 0b00000011;
		SysTick_Wait(delay);
		
	}
}

void motorBackward1(){
	for(int i = 1; i <= 2; i++){		//512 is one full rotation
		int delay = 90000;
		
		GPIO_PORTM_DATA_R &= 0b11110000;
		GPIO_PORTM_DATA_R |= 0b00000011;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b11110000;
		GPIO_PORTM_DATA_R |= 0b00000110;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b11110000;
		GPIO_PORTM_DATA_R |= 0b00001100;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b11110000;
		GPIO_PORTM_DATA_R |= 0b00001001;
		SysTick_Wait(delay);
		
		GPIO_PORTN_DATA_R = 0b0000;
	}
}

void motorBackward2(){
	for(int i = 1; i <= 2; i++){		//512 is one full rotation
		int delay = 90000;
		
		GPIO_PORTM_DATA_R &= 0b00001111;
		GPIO_PORTM_DATA_R |= 0b00110000;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b00001111;
		GPIO_PORTM_DATA_R |= 0b01100000;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b00001111;
		GPIO_PORTM_DATA_R |= 0b11000000;
		SysTick_Wait(delay);
		GPIO_PORTM_DATA_R &= 0b00001111;
		GPIO_PORTM_DATA_R |= 0b10010000;
		SysTick_Wait(delay);
		
		GPIO_PORTN_DATA_R = 0b0000;
	}
}

void motorBackward3(){
	for(int i = 1; i <= 2; i++){		//512 is one full rotation
		int delay = 90000;
		
		GPIO_PORTL_DATA_R &= 0b00000000;
		GPIO_PORTL_DATA_R |= 0b00000011;
		SysTick_Wait(delay);
		GPIO_PORTL_DATA_R &= 0b00000000;
		GPIO_PORTL_DATA_R |= 0b00000110;
		SysTick_Wait(delay);
		GPIO_PORTL_DATA_R &= 0b00000000;
		GPIO_PORTL_DATA_R |= 0b00001100;
		SysTick_Wait(delay);
		GPIO_PORTL_DATA_R &= 0b00000000;
		GPIO_PORTL_DATA_R |= 0b00001001;
		SysTick_Wait(delay);
		
		GPIO_PORTN_DATA_R = 0b0000;
	}
}

void pwm(int perc, int motor)
{

	int dcWait = 16000 + 16000 * perc / 100.0;
	GPIO_PORTN_DATA_R |= motor;
	SysTick_Wait(dcWait);
	GPIO_PORTN_DATA_R &= 0b00000000;
	SysTick_Wait(320000 - dcWait);
	
}


#define I2C_MCS_ACK             0x00000008  // Data Acknowledge Enable
#define I2C_MCS_DATACK          0x00000008  // Acknowledge Data
#define I2C_MCS_ADRACK          0x00000004  // Acknowledge Address
#define I2C_MCS_STOP            0x00000004  // Generate STOP
#define I2C_MCS_START           0x00000002  // Generate START
#define I2C_MCS_ERROR           0x00000002  // Error
#define I2C_MCS_RUN             0x00000001  // I2C Master Enable
#define I2C_MCS_BUSY            0x00000001  // I2C Busy
#define I2C_MCR_MFE             0x00000010  // I2C Master Function Enable

#define MAXRETRIES              5           // number of receive attempts before giving up
void I2C_Init(void){
  SYSCTL_RCGCI2C_R |= SYSCTL_RCGCI2C_R0;           // activate I2C0
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;          // activate port B
  while((SYSCTL_PRGPIO_R&0x0002) == 0){};// ready?

    GPIO_PORTB_AFSEL_R |= 0x0C;           // 3) enable alt funct on PB2,3       0b00001100
    GPIO_PORTB_ODR_R |= 0x08;             // 4) enable open drain on PB3 only

    GPIO_PORTB_DEN_R |= 0x0C;             // 5) enable digital I/O on PB2,3
//    GPIO_PORTB_AMSEL_R &= ~0x0C;          // 7) disable analog functionality on PB2,3

                                                                                // 6) configure PB2,3 as I2C
//  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFF00FF)+0x00003300;
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFF00FF)+0x00002200;    //TED
    I2C0_MCR_R = I2C_MCR_MFE;                      // 9) master function enable
    I2C0_MTPR_R = 0b0000000000000101000000000111011;                                        // 8) configure for 100 kbps clock (added 8 clocks of glitch suppression ~50ns)
    
}

//System running at 16,000,000 MHz
int main(){
	//Init
	PortN_Init();
	PortM_Init();
	PortL_Init();
	SysTick_Init();
	I2C_Init();
	UART_Init();
	//pwm();
	UART_printf("Program Begins\r\n");
	sprintf(printf_buffer,"RoboticArm \r\n");
	UART_printf(printf_buffer);
	
	int angle1 = 50;
	int angle2 = 50;
	int angle3 = 50;
	
	while(1)
	{
		char data = UART_InChar();
		
		switch (data){
			//base rotation
			case 'a':
				GPIO_PORTN_DATA_R = 0b00001;
				motorForward3();
				break;
			case 'f':
				GPIO_PORTN_DATA_R = 0b0001;
				motorBackward3();
				break;
			//main arm
			case 'e':
				GPIO_PORTN_DATA_R = 0b00001;
				motorForward1();
				break;
			case 'd':
				GPIO_PORTN_DATA_R = 0b0001;
				motorBackward1();
				break;
			//fore arm
			case 'w':
				GPIO_PORTN_DATA_R = 0b00001;
				motorForward2();
				break;
			case 's':
				GPIO_PORTN_DATA_R = 0b0001;
				motorBackward2();
				break;
			//wrist turn
			case 'r':
				GPIO_PORTN_DATA_R = 0b0001;
				angle1+=5;
				if(angle1 >= 130)
				angle1 = 130;
				pwm(angle1, 0b00010000);
				break;
			case 'q':
				GPIO_PORTN_DATA_R = 0b0001;
				angle1-=5;
				if(angle1 <= 0)
				angle1 = 0;
				pwm(angle1, 0b00010000);
				break;
			//claw
			case 'z':
				GPIO_PORTN_DATA_R = 0b0001;
				angle2+=10;
				if(angle2 >= 100)
				angle2 = 100;
				pwm(angle2, 0b00000100);
				break;
			case 'x':
				GPIO_PORTN_DATA_R = 0b0001;
				angle2-=10;
				if(angle2 <= 0)
				angle2 = 0;
				pwm(angle2, 0b00000100);
				break;
			//hand tilt
			case 'c':
				GPIO_PORTN_DATA_R = 0b001;
				angle3+=10;
				if(angle3 >= 180)
				angle3 = 180;
				pwm(angle3, 0b00001000);
				break;
			case 'v':
				GPIO_PORTN_DATA_R = 0b0001;
				angle3-=10;
				if(angle3 <= 20)
				angle3 = 20;
				pwm(angle3, 0b00001000);
				break;
		}
		GPIO_PORTN_DATA_R = 0b0000;
	}
}
