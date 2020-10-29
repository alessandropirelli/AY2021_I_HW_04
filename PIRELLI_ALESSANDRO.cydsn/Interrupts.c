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

#define LED_ON 1
#define LED_OFF 0

#include "Interrupts.h"
#include "project.h"

int32 value;
uint8 ch_received;
uint8 RxFlag=0;                 //flag that gets high when the device gets started via terminal

CY_ISR(Sampling){
    
    Timer_ReadStatusRegister();
            
    if(RxFlag==1){                                          //only if the device has been started
               
            value_PHR = ADC_DelSig_Read32();                //sample the photoresistor channel 
            if(value_PHR<0) value_PHR=0;
            if(value_PHR>65535) value_PHR=65535;            //adjust possible reading errors
                   
            if(value_PHR<THRESHOLD){                        //if light level low enough
                                               
                AMux_FastSelect(PTM);                       //change sampling channel to potentiometer's one
            
                PWMFlag = 1;                                //allow PWM regulation                          
            
                value_PTM = ADC_DelSig_Read32();            //sample potentiometer channel
                if(value_PTM<0) value_PTM=0;
                if(value_PTM>65535) value_PTM=65535;        //same corrections as before
                
                AMux_FastSelect(PHR);                       //return to photorestitor's channel
                
            }else{                                          //if light level over threshold
                
                PWMFlag = 0;         //leads to turning off the LED  (see main.c)                     
                
            }
        
        Data[1]=value_PHR>>8;
        Data[2]=value_PHR & 0xFF;
        Data[3]=value_PTM>>8;
        Data[4]=value_PTM & 0xFF;   //build data to send back to terminal
               
        PacketFlag=1;
        }
    }




CY_ISR(Rx){
    ch_received=UART_GetChar();
    switch(ch_received){
        case 'B':
        case 'b':                                   //when "B" or "b" are sent via terminal (begin)
            RxFlag=1;                               //start the device
            Pin_LED_Write(LED_ON);                  //turn on "diagnostic" built-in LED    
            Timer_Start();                          //timer works only when the device has to actually sample signals
            break;
        case 'S':
        case 's':                                   //when "S" or "s" are sent via terminal (stop)
            RxFlag = 0;                             //stop the device
            Pin_LED_Write(LED_OFF);                 //turn off "diagnostic" built-in LED
            PWMFlag=0;                          
            Timer_Stop();                           //stop the timer
            break;
        default:
            break;
    }
}



/* [] END OF FILE */
