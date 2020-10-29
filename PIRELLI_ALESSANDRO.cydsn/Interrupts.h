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
    
    #define BYTE_TO_SEND 4                  //2 bytes for the photoresistor value, 2 bytes for the potentiometer's one
    #define DATA_SIZE 1+BYTE_TO_SEND+1      //total size of the data including head and tail bytes
    #define THRESHOLD 30000                 //threshold value choosen experimentally      
    
    #define PHR 0                   //photoresistor's Amux channel
    #define PTM 1                   //potentiometer's Amux channel
    
    CY_ISR_PROTO (Sampling);
    CY_ISR_PROTO (Rx);
        
    uint8 Data[DATA_SIZE];          
    
    int32 value_PHR;                //light intensity sampled from the photoresistor 
    int32 value_PTM;                //voltage intensity sampled from the potentiometer
    uint8 PWMFlag;                  //flag used to allow the device to update the intensity of the bulb's light through PWM 
    
    volatile uint8 PacketFlag;      //flag used to know that data is available
    
#endif


/* [] END OF FILE */
