/**
  ******************************************************************************
  * @file    main.c
  * @author  Adapted for Nucleo F411RE
  * @brief   Bare-metal LED blink for STM32F411RE
  ******************************************************************************
*/

#include<stdint.h>

int main(void)
{
    // Define pointers to necessary registers
    uint32_t *pClkCtrlReg   = (uint32_t*)0x40023830;  // RCC AHB1ENR (Clock control register)
    uint32_t *pPortAModeReg = (uint32_t*)0x40020000;  // GPIOA Mode register
    uint32_t *pPortAOutReg  = (uint32_t*)0x40020014;  // GPIOA Output data register

    // 1. Enable the clock for GPIOA peripheral in AHB1ENR (SET the 0th bit)
    *pClkCtrlReg |= (1 << 0);

    // 2. Configure PA5 as output
    // a. Clear bits 10 and 11 (PA5 corresponds to bits [11:10] in MODER)
    *pPortAModeReg &= ~(3 << 10);
    // b. Set bit 10 to 1 (PA5 = Output mode)
    *pPortAModeReg |= (1 << 10);

    while(1)
    {
        // 3. Set PA5 HIGH (turn ON LED)
        *pPortAOutReg |= (1 << 5);

        // Introduce delay
        for(uint32_t i = 0; i < 300000; i++);

        // 4. Set PA5 LOW (turn OFF LED)
        *pPortAOutReg &= ~(1 << 5);

        for(uint32_t i = 0; i < 300000; i++);
    }
}
