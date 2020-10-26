/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#define LED_OFF 0
#define PWM_OFF 0
#define PHR 0
#define PTM 1

#include "project.h"
#include "Interrupts.h"

int main(void)
{
    CyGlobalIntEnable; 
   
    AMux_Start();
    AMux_FastSelect(PHR);
    ADC_DelSig_Start();
    UART_Start();
    
    isr_Timer_StartEx(Sampling);
    isr_Rx_StartEx(Rx);
    PWM_Start();
     
    Data[0]= 0xA0;
    Data[DATA_SIZE-1]= 0xC0;
    
    PacketFlag=0;
    PWMFlag=0;   
       
    ADC_DelSig_StartConvert();
    
    for(;;)
    {
        if(PacketFlag==1){
            UART_PutArray(Data, DATA_SIZE);
            PacketFlag=0;
        }
        
        if(PWMFlag==1){
            PWM_WriteCompare(value_PTM);        
        }
        
        
    }
}

/* [] END OF FILE */
