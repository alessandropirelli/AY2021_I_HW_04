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
uint8 RxFlag=0;

uint8 count=0;


CY_ISR(Sampling){
    
    Timer_ReadStatusRegister();
        
    
    if(RxFlag==1){
               
            value_PHR = ADC_DelSig_Read32();                //sample the photoresistor channel 
            if(value_PHR<0) value_PHR=0;
            if(value_PHR>65535) value_PHR=65535;            //adjust eventual reading errors
                   
            if(value_PHR<THRESHOLD){                        //if light level low enough
                                               
                AMux_FastSelect(PTM);                       //change sampling channel to potentiometer's one
            
                PWMFlag = 1;                                
            
                value_PTM = ADC_DelSig_Read32();            //sample potentiometer channel
                if(value_PTM<0) value_PTM=0;
                if(value_PTM>65535) value_PTM=65535;        //same corrections as before
                
                AMux_FastSelect(PHR);                       //return to photorestitor's channel
                
            }else{                                          //if light level over threshold
                PWMFlag = 0;                                
                PWM_WriteCompare(LED_OFF);                  //turn off bulb
            }
        
        Data[1]=value_PHR>>8;
        Data[2]=value_PHR & 0xFF;
        Data[3]=value_PTM>>8;
        Data[4]=value_PTM & 0xFF;
               
        PacketFlag=1;
        }
    }




CY_ISR(Rx){
    ch_received=UART_GetChar();
    switch(ch_received){
        case 'B':
        case 'b':
            RxFlag=1;                       
            Pin_LED_Write(LED_ON);          
            Timer_Start();
            break;
        case 'S':
        case 's':
            RxFlag = 0;
            Pin_LED_Write(LED_OFF);
            if(PWM_ReadCompare()!=0){               //if bulb on when device gets turned off
                PWMFlag=0;                          
                PWM_WriteCompare(LED_OFF);          //turn bulb off
            }
            Timer_Stop();
            break;
        default:
            break;
    }
}



/* [] END OF FILE */
