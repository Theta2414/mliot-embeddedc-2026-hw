#define STM32F103xB
#include "stm32f1xx_hal.h"

// Cấu hình thời gian chống dội cơ khí (đơn vị: mili-giây)
#define DEBOUNCE_DELAY 50

// Khai báo hàm ngắt SysTick (Bắt buộc để bộ đếm thời gian của HAL hoạt động)
void SysTick_Handler(void) {
    HAL_IncTick(); 
}

// Hàm phục vụ cơ chế tự kiểm tra lỗi của HAL (nếu có kích hoạt USE_FULL_ASSERT)
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
    while (1) {
    }
}
#endif

int main(void) {
    HAL_Init();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE(); 

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_13;               
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;      
    GPIO_InitStruct.Pull = GPIO_NOPULL;              
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;     
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);          

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;          
    GPIO_InitStruct.Pull = GPIO_PULLUP; 
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_PinState current_reading;
    GPIO_PinState last_reading = GPIO_PIN_SET; // Mặc định ở chế độ Pull-up là mức 1 (SET)
    GPIO_PinState button_state = GPIO_PIN_SET; // Trạng thái phím đã qua bộ lọc
    uint32_t last_debounce_time = 0;

    while (1) {
        current_reading = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

        if (current_reading != last_reading) {
            last_debounce_time = HAL_GetTick();
        }

        if ((HAL_GetTick() - last_debounce_time) > DEBOUNCE_DELAY) {
            
            if (current_reading != button_state) {
                button_state = current_reading;

                if (button_state == GPIO_PIN_SET) {
                    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                }
            }
        }

        last_reading = current_reading;
    }
}