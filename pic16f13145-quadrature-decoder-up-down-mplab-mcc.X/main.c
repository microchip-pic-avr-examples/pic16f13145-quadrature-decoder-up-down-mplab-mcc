 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

volatile uint16_t overflow_count = 0, underflow_count = 0;

void Overflow_Handler(void);
void Underflow_Handler(void);

int main(void)
{
    uint8_t value, old_value;
    int32_t result;
    
    SYSTEM_Initialize(); 
    
    /* Enable the Global Interrupts */
    INTERRUPT_GlobalInterruptEnable(); 

    /* Enable the Peripheral Interrupts */
    INTERRUPT_PeripheralInterruptEnable(); 


    /* Reset the UP/DOWN counter */
    CLBSWIN0 = 1;
    __delay_ms(20);
    CLBSWIN0 = 0;
    
    /* Setting the callbacks for the overflow and underflow events */
    CLB1_CLB1I0_SetInterruptHandler(Overflow_Handler);
    CLB1_CLB1I1_SetInterruptHandler(Underflow_Handler);
    
    while(1)
    {
        /* Storing the old value read on the UP/DOWN counter output */
        old_value = value;
        /* Reading the output of the UP/DOWN counter (RC0, RC1, RC2, RC3) */
        value = PORTC & (0x0F);       
        /* The result gets printed only if a change occurred */
        if(old_value != value)
        {
            /* Computing the current result */
            result = (int32_t)overflow_count * 16 - (int32_t)underflow_count * 16 + (int32_t)value;
            printf("%ld ticks\r\n", result);
        }   
    }    
}

void Overflow_Handler(void)
{
    overflow_count++;
}

void Underflow_Handler(void)
{
    underflow_count++;
}