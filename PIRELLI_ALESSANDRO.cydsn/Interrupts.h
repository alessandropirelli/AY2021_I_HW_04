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
    
    #define BYTE_TO_SEND 2
    #define DATA_SIZE 1+BYTE_TO_SEND+1
    #define THRESHOLD 32767
    
    #define PHR 0
    #define PTM 1
    
    CY_ISR_PROTO (Sampling);
    CY_ISR_PROTO (Rx);
    CY_ISR_PROTO (ChangeChannel);
    
    uint8 Data[DATA_SIZE];
    volatile uint8 PacketFlag;
    
#endif

/* [] END OF FILE */
