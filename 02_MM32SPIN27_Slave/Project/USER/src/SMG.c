#include "SMG.h"

/*****************数码管控制开断*************************/
#define  Nixie_Tube1_ON          	gpio_set(B8 ,0)
#define  Nixie_Tube2_ON          	gpio_set(D6 ,0)
#define  Nixie_Tube3_ON          	gpio_set(C11,0)
#define  Nixie_Tube4_ON          	gpio_set(C10,0)

#define  Nixie_Tube1_OFF          gpio_set(B8 ,1) 
#define  Nixie_Tube2_OFF          gpio_set(D6 ,1) 
#define  Nixie_Tube3_OFF          gpio_set(C11,1) 
#define  Nixie_Tube4_OFF          gpio_set(C10,1) 
/******************************************************/
//Nixie_Tube1_ON
#define  Tube1_ON   	gpio_set(B6 ,0)//a             
#define  Tube2_ON   	gpio_set(A15,0)//b        
#define  Tube3_ON   	gpio_set(B3 ,0)//c       
#define  Tube4_ON   	gpio_set(B7 ,0)//d       
#define  Tube5_ON   	gpio_set(B9 ,0)//e      
#define  Tube6_ON   	gpio_set(B4 ,0)//f       
#define  Tube7_ON   	gpio_set(C12,0)//g       
#define  Tube8_ON   	gpio_set(B5 ,0)//点 
//Nixie_Tube1_OFF
#define  Tube1_OFF   	gpio_set(B6 ,1)//a             
#define  Tube2_OFF   	gpio_set(A15,1)//b        
#define  Tube3_OFF   	gpio_set(B3 ,1)//c       
#define  Tube4_OFF   	gpio_set(B7 ,1)//d       
#define  Tube5_OFF   	gpio_set(B9 ,1)//e      
#define  Tube6_OFF   	gpio_set(B4 ,1)//f       
#define  Tube7_OFF   	gpio_set(C12,1)//g       
#define  Tube8_OFF   	gpio_set(B5 ,1)//点


void show_1234(void)
{
	Tube2_ON;
	Tube3_ON;
	Nixie_Tube1_ON;
	systick_delay_ms(2);
	Tube2_OFF;
	Tube3_OFF;
	Nixie_Tube1_OFF;
	Tube1_ON;
	Tube2_ON;
	Tube7_ON;
	Tube4_ON;
	Tube5_ON;
	Nixie_Tube2_ON;
	systick_delay_ms(2);
	Tube1_OFF;
	Tube2_OFF;
	Tube7_OFF;
	Tube4_OFF;
	Tube5_OFF;
	Nixie_Tube2_OFF;
	Tube1_ON;
	Tube2_ON;
	Tube3_ON;
	Tube4_ON;
	Tube7_ON;
	Nixie_Tube3_ON;
	systick_delay_ms(2);
	Tube1_OFF;
	Tube2_OFF;
	Tube3_OFF;
	Tube4_OFF;
	Tube7_OFF;
	Nixie_Tube3_OFF;
	Tube2_ON;
	Tube3_ON;
	Tube6_ON;
	Tube7_ON;
	Nixie_Tube4_ON;
	systick_delay_ms(2);
	Tube3_OFF;
	Tube2_OFF;
	Tube6_OFF;
	Tube7_OFF;
	Nixie_Tube4_OFF;
}

