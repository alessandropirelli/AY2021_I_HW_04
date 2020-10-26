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

#ifndef __INTERRUPTS_H
    #define __INTERRUPTS_H
    
    #include "cytypes.h"
    #include "stdio.h"
    
    #define BYTE_TO_SEND 4
    #define DATA_SIZE 1+BYTE_TO_SEND+1
    #define THRESHOLD 30000                 
    
    #define PHR 0
    #define PTM 1
    
    CY_ISR_PROTO (Sampling);
    CY_ISR_PROTO (Rx);
    CY_ISR_PROTO (ChangeChannel);
    
    uint8 Data[DATA_SIZE];
    
    int32 value_PHR;            //light intensity sampled from the photoresistor 
    int32 value_PTM;            //voltage intensity sampled from the potentiometer
    uint8 PWMFlag;              //flag used to allow the device to update the intensity of the bulb's light through PWM 
    
    volatile uint8 PacketFlag;
    
#endif


/* [] END OF FILE */
