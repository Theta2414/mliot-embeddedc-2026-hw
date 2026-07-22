#define STM32F103xB
#include "stm32f1xx_hal.h" 

void SysTick_Handler(void) {
    HAL_IncTick(); 
}

int main(void) {
    HAL_Init();

    __HAL_RCC_GPIOC_CLK_ENABLE(); 

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    GPIO_InitStruct.Pin = GPIO_PIN_13;               
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;      
    GPIO_InitStruct.Pull = GPIO_NOPULL;              
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;     
    
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);          

    while (1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        
        HAL_Delay(200); 
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
    while (1) {
    }
}
#endif