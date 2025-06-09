/*****************************************************************************
 * @Author                : Omar Megahed<omarmegahed741@gmail.com>           *
 * @CreatedDate           : 2023-12-01 00:00:00                              *
 * @LastEditors           : Omar Megahed<omarmegahed741@gmail.com>           *
 * @LastEditDate          : 2025-06-09 03:51:52                              *
 * @FilePath              : CH32V003F4P6_Platform/CH32V003F4P6_Deployment/User/main.c*
 * @CopyRight             : MerBleueAviation                                 *
 ****************************************************************************/

/*
 * @Note
 * This example demonstrates SysTick timer configuration for 1ms interrupts
 * PC0 is toggled every 1ms using SysTick interrupt
 */

#include "debug.h"
#include "core_riscv.h"
#include "ch32v00x.h"

/* SysTick Control Register bit definitions */
#define SYSTICK_CTLR_ENABLE     (1 << 0)    // Counter enable
#define SYSTICK_CTLR_INT        (1 << 1)    // Interrupt enable
#define SYSTICK_CTLR_RELOAD     (1 << 3)    // Counter reload enable

/*********************************************************************
 * @fn      GPIO_Config
 *
 * @brief   Configure GPIO for debug pin (PC0)
 *
 * @return  none
 */
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    // Enable GPIOC clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    // Configure PC0 as push-pull output
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      SysTick_Init
 *
 * @brief   Initialize SysTick timer for 1ms interrupts
 *          Using HCLK/8 (3MHz) as clock source
 *
 * @return  none
 */
void SysTick_Init(void)
{
    // Calculate reload value for 1ms using HCLK/8
    // SystemCoreClock is 24MHz, so HCLK/8 = 3MHz
    // For 1ms: 3000000 / 1000 = 3000 cycles
    // Need to subtract 1 because counter counts down to 0
    SysTick->CMP = 2999;  // For 1ms timing (3000 - 1)
    SysTick->CNT = 0;     // Clear counter
    
    // Configure SysTick:
    // - Enable counter
    // - Enable interrupt
    // - Use HCLK/8 as clock source (bit 2 = 0)
    // - Enable auto-reload
    SysTick->CTLR = SYSTICK_CTLR_ENABLE |   // Enable counter
                    SYSTICK_CTLR_INT |      // Enable interrupt
                    SYSTICK_CTLR_RELOAD;    // Enable auto-reload
    
    // Enable SysTick interrupt in NVIC
    NVIC_EnableIRQ(SysTicK_IRQn);
}

/*********************************************************************
 * @fn      SysTick_Handler
 *
 * @brief   SysTick interrupt handler - called every 1ms
 *          Toggles PC0 to show the 1ms timing
 *
 * @return  none
 */
__attribute__((interrupt("machine"))) void SysTick_Handler(void)
{
    // Toggle PC0 to show the 1ms timing
    GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)!GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_0));
    
    // Clear SysTick status register to acknowledge interrupt
    SysTick->SR = 0;
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *          Initializes system and enters infinite loop
 *
 * @return  none
 */
int main(void)
{
    /* Clock Configuration */
    SystemCoreClockUpdate();                    // Update system core clock
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); // Configure NVIC priority grouping
    /* Peripheral Initialization */
    GPIO_Config();                              // Configure debug pin
    SysTick_Init();                             // Initialize SysTick for 1ms interrupts

    /* Main Loop */
    while(1)
    {
        // Main loop is empty as we're using SysTick for timing
    }
}
