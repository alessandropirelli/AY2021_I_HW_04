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

#define PWM_OFF 0

#include "project.h"
#include "Interrupts.h"

int main(void)
{
    CyGlobalIntEnable; 
   
    AMux_Start();                   //start the Amux
    AMux_FastSelect(PHR);           //device starts from sampling tha photoresistor's channel
    ADC_DelSig_Start();             //start the ADC
    UART_Start();                   //start the UART
    PWM_Start();                    //start the PWM
    
    isr_Timer_StartEx(Sampling);    //"Sampling" function triggered by timer's counter overflow
    isr_Rx_StartEx(Rx);             //"RX" function trigger when UART receives data
         
    Data[0]= 0xA0;                  //head added to data
    Data[DATA_SIZE-1]= 0xC0;        //tail added to data  
    
    PacketFlag=0;
    PWMFlag=0;                      //flags initialization
       
    ADC_DelSig_StartConvert();
    
    for(;;)
    {
        if(PacketFlag==1){
            UART_PutArray(Data, DATA_SIZE);     //send data sampled
            PacketFlag=0;
        }
        
        if(PWMFlag==1){                         
            PWM_WriteCompare(value_PTM);        //program PWM with value set by potentiometer
        }else{
            PWM_WriteCompare(PWM_OFF);          //turn off bulb when either the surrounding light is high enough or the device is off
        }
        
    }
}

/* [] END OF FILE */
