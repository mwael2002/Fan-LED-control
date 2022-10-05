#include "STD_Types.h"
#include "MAP_interface.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
#include "ADC_interface.h"
#include "Timer_interface.h"
#include "LCD_interface.h"

U8 flag;
ADC_Chain ch;
U16 value[2];

void notify(void);

void main(void){
   
 DIO_set_pin_direction(Group_B,DIO_Pin_3,OUTPUT);  
 DIO_set_pin_direction(Group_D,DIO_Pin_5,OUTPUT);  

	U8 channels[2]={ADC_CH_3,ADC_CH_4};

	ch.Chain_Channel=channels;
	ch.Chain_Size=2;
	ch.Chain_Notification_Func=notify;
	ch.Chain_Result=value;
	ADC_init();
	Global_Int_En_Dis(Global_Int_Enable);
  
  
  
  
  LCD_init();

 Timer0_init();
 Timer1_init();
	
 ADC_Start_Chain_Conversion_Asynch(&ch); 
	
while(1){
   


     
 
   }
}

void notify(void){

   /* temp_reading after ADC is the digital value
   maximum digital value is 1024 (10 bit resolution)
   maximum voltage is 5 V
    temp_reading -> 1023
    current volt   -> 5
    current volt= temp_reading*5/1023
   
    output of LM35 is 10 mV/ degree Celisus
    
    1 degree        -> 0.01 V
    current  temp -> current volt    
    
    current temp = current volt*100/1
    current temp = temp_reading*5*100/1023
    */
   
    U16 temp_reading=value[0];
    temp_reading= temp_reading*5*100.0/1023.0;
    
    set_comparematch_value(TIMER0_ID,MAP_Get_Input_Value(0,50,0,255,temp_reading));
    Timer1_set_comparematch_value(CMPA,value[1]);
    
    LCD_write_string_pos("Temprature:",0,0);
    LCD_write_no_pos(temp_reading,0,11);
    
    LCD_write_string_pos("Light:",1,0);
    LCD_write_no_pos(value[1],1,6);
    
 ADC_Start_Chain_Conversion_Asynch(&ch); 
   
   
   }
