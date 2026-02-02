#include <stdio.h>
#include "sdkconfig.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led.h"

void app_main(void)
{
    uint32_t flash_size;
    esp_chip_info_t chip_info;

    esp_flash_get_size(NULL, &flash_size);
    esp_chip_info(&chip_info);

    printf("This is ESP32 chip with %d CPU cores  \n", chip_info.cores);

    printf("flash size of %ud MB\n", flash_size/(1024*1024));

    // 初始化LED (GPIO 5, 1个LED)
    if (led_init(5, 1) != ESP_OK) {
        printf("Failed to initialize LED\n");
        return;
    }

    printf("LED initialized successfully on GPIO 5\n");

    // 循环演示不同颜色
    while(1) {
        printf("Hello World!\n");
         // 遍历色相创建彩虹效果
        for(int hue = 0; hue < 360; hue += 10) {
            led_set_all_pixels_hsv(hue, 100, 50);  // 饱和度100%，明度50%
            led_refresh();
            vTaskDelay(100 / portTICK_PERIOD_MS);  // 更快的变化效果
        }
        
        vTaskDelay(500 / portTICK_PERIOD_MS);  // 短暂暂停
    }
    
}