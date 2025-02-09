#include <stdint.h>

// Define register addresses
#define RCC_AHB1ENR   (*(volatile uint32_t*)0x40023830)
#define GPIOA_MODER   (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR     (*(volatile uint32_t*)0x40020014)
#define GPIOC_MODER   (*(volatile uint32_t*)0x40020800)
#define GPIOC_IDR     (*(volatile uint32_t*)0x40020810)

// Macros for setting and clearing bits
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

int main(void)
{
    // Enable clock for GPIOA and GPIOC
    SET_BIT(RCC_AHB1ENR, (1 << 0));  // GPIOA
    SET_BIT(RCC_AHB1ENR, (1 << 2));  // GPIOC

    // Configure PA5 as output
    CLEAR_BIT(GPIOA_MODER, (3 << 10));  // Clear MODER5[1:0]
    SET_BIT(GPIOA_MODER, (1 << 10));    // Set MODER5[0] to 1 (Output mode)

    // Configure PC13 as input (default state is input, but ensure it's set)
    CLEAR_BIT(GPIOC_MODER, (3 << 26));  // Clear MODER13[1:0]

    while (1)
    {
        // Check if the user button (PC13) is pressed
        if (!(GPIOC_IDR & (1 << 13)))  // Button is pressed when PC13 is low
        {
            // Toggle the LED (PA5)
            GPIOA_ODR ^= (1 << 5);

            // Simple debounce delay
            for (volatile uint32_t i = 0; i < 500000; i++);
        }
    }
}
