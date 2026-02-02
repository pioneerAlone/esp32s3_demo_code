#include "led.h"
#include "led_strip.h"
//#include "led_strip_rmt.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_check.h"  // 包含ESP_RETURN_ON_ERROR宏

static const char *TAG = "led";

// LED控制句柄
static led_strip_handle_t led_strip = NULL;
static int g_led_count = 0;  // 保存LED数量

esp_err_t led_init(int gpio_num, int led_num)
{
    // RMT驱动的LED配置
    led_strip_config_t strip_config = {
        .strip_gpio_num = gpio_num,                    // GPIO number
        .max_leds = led_num,                           // 最大LED数量
        .led_model = LED_MODEL_WS2812,                 // LED模型
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // 颜色格式：绿色、红色、蓝色
        .flags.invert_out = false,                     // 不反转输出信号
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,        // 使用默认时钟源
        .resolution_hz = 10 * 1000 * 1000,    // 分辨率：10MHz
        .flags.with_dma = false,               // 不使用DMA
    };

    // 保存LED数量
    g_led_count = led_num;
    
    // 创建LED控制器
    ESP_RETURN_ON_ERROR(
        led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip),
        TAG,
        "create new strip failed"
    );

    ESP_LOGI(TAG, "LED strip initialized successfully with GPIO %d and %d LEDs", gpio_num, led_num);
    return ESP_OK;
}

esp_err_t led_set_pixel(uint32_t index, uint32_t red, uint32_t green, uint32_t blue)
{
    if (!led_strip) {
        ESP_LOGE(TAG, "LED strip is not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    ESP_RETURN_ON_ERROR(
        led_strip_set_pixel(led_strip, index, red, green, blue),
        TAG,
        "set pixel failed"
    );
    
    return ESP_OK;
}

esp_err_t led_set_all_pixels(uint32_t red, uint32_t green, uint32_t blue)
{
    if (!led_strip) {
        ESP_LOGE(TAG, "LED strip is not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t ret = ESP_OK;
    // 获取LED的数量，需要通过配置传入或保存到全局变量
    // 我们需要保存LED数量
    for (int i = 0; i < g_led_count; i++) {
        ret = led_strip_set_pixel(led_strip, i, red, green, blue);
        if (ret != ESP_OK) {
            break;
        }
    }
    
    return ret;
}

esp_err_t led_set_pixel_hsv(uint32_t index, uint16_t hue, uint8_t saturation, uint8_t value)
{
    if (!led_strip) {
        ESP_LOGE(TAG, "LED strip is not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    ESP_RETURN_ON_ERROR(
        led_strip_set_pixel_hsv(led_strip, index, hue, saturation, value),
        TAG,
        "set pixel hsv failed"
    );
    
    return ESP_OK;
}

esp_err_t led_set_all_pixels_hsv(uint16_t hue, uint8_t saturation, uint8_t value)
{
    if (!led_strip) {
        ESP_LOGE(TAG, "LED strip is not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    esp_err_t ret = ESP_OK;
    for (int i = 0; i < g_led_count; i++) {
        ret = led_strip_set_pixel_hsv(led_strip, i, hue, saturation, value);
        if (ret != ESP_OK) {
            break;
        }
    }
    
    return ret;
}

esp_err_t led_refresh(void)
{
    if (!led_strip) {
        ESP_LOGE(TAG, "LED strip is not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    ESP_RETURN_ON_ERROR(
        led_strip_refresh(led_strip),
        TAG,
        "refresh strip failed"
    );

    return ESP_OK;
}

esp_err_t led_clear(void)
{
    if (!led_strip) {
        ESP_LOGE(TAG, "LED strip is not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    ESP_RETURN_ON_ERROR(
        led_strip_clear(led_strip),
        TAG,
        "clear strip failed"
    );

    return ESP_OK;
}

esp_err_t led_deinit(void)
{
    if (!led_strip) {
        ESP_LOGE(TAG, "LED strip is not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    ESP_RETURN_ON_ERROR(
        led_strip_del(led_strip),
        TAG,
        "delete strip failed"
    );
    
    led_strip = NULL;
    g_led_count = 0;
    return ESP_OK;
}