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

#include "Interrupts.h"
#include "project.h"

int32 value_PHR;
int32 value_PTM;
int32 value;
uint8 ch_received;
uint8 RxFlag=0;
uint8 CCFlag=0;
uint8 count=0;
uint8 channel=PHR;

CY_ISR(Sampling){
    Timer_ReadStatusRegister();
    if(RxFlag==1){
        
        if(channel==PHR){
            value_PHR = ADC_DelSig_Read32();
            if(value_PHR<0) value_PHR=0;
            if(value_PHR>65535) value_PHR=65535;
            
            value=value_PHR;
            
            if(value_PHR>THRESHOLD){
            CCFlag = 1;
            }else{
            CCFlag = 0;
            }
            
        }else{
            value_PTM = ADC_DelSig_Read32();
            if(value_PTM<0) value_PTM=0;
            if(value_PTM>65535) value_PTM=65535;
            
            value=value_PTM;
        }
        
        
        
        Data[1]=value>>8;
        Data[2]=value & 0xFF;
        
        PacketFlag=1;
    }
}

CY_ISR(ChangeChannel){
    Timer_ReadStatusRegister();
    count++;
    AMux_FastSelect(channel);
    if(CCFlag == 1){
        if(count<6){
            channel=PTM;
        }else if(count==10){
           channel=PHR;
           count=0;
        }
    }else{
        channel=PHR;
        CCFlag=0;
    }
}

CY_ISR(Rx){
    ch_received=UART_GetChar();
    switch(ch_received){
        case 'B':
        case 'b':
            RxFlag=1;
            Pin_LED_Write(1);
            Timer_Start();
            break;
        case 'S':
        case 's':
            RxFlag=0;
            Pin_LED_Write(0);
            Timer_Stop();
            break;
        default:
            break;
    }
}



/* [] END OF FILE */
