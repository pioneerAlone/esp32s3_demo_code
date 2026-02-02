#ifndef _LED_H_
#define _LED_H_

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 初始化LED灯控制
 * 
 * @param gpio_num 要使用的GPIO引脚号
 * @param led_num 要控制的LED数量
 * @return esp_err_t 
 */
esp_err_t led_init(int gpio_num, int led_num);

/**
 * @brief 设置指定位置LED的颜色
 * 
 * @param index LED索引
 * @param red 红色值 (0-255)
 * @param green 绿色值 (0-255)
 * @param blue 蓝色值 (0-255)
 * @return esp_err_t 
 */
esp_err_t led_set_pixel(uint32_t index, uint32_t red, uint32_t green, uint32_t blue);

/**
 * @brief 设置所有LED为相同颜色
 * 
 * @param red 红色值 (0-255)
 * @param green 绿色值 (0-255)
 * @param blue 蓝色值 (0-255)
 * @return esp_err_t 
 */
esp_err_t led_set_all_pixels(uint32_t red, uint32_t green, uint32_t blue);


/**
 * @brief 设置指定位置LED的HSV颜色
 * 
 * @param index LED索引
 * @param hue 色相 (0-360)
 * @param saturation 饱和度 (0-100)
 * @param value 明度 (0-100)
 * @return esp_err_t 
 */
esp_err_t led_set_pixel_hsv(uint32_t index, uint16_t hue, uint8_t saturation, uint8_t value);

/**
 * @brief 设置所有LED为相同的HSV颜色
 * 
 * @param hue 色相 (0-360)
 * @param saturation 饱和度 (0-100)
 * @param value 明度 (0-100)
 * @return esp_err_t 
 */
esp_err_t led_set_all_pixels_hsv(uint16_t hue, uint8_t saturation, uint8_t value);

/**
 * @brief 刷新LED显示
 * 
 * @return esp_err_t 
 */
esp_err_t led_refresh(void);

/**
 * @brief 关闭所有LED
 * 
 * @return esp_err_t 
 */
esp_err_t led_clear(void);

/**
 * @brief 删除LED控制句柄，释放资源
 * 
 * @return esp_err_t 
 */
esp_err_t led_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* _LED_H_ */