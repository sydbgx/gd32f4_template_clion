#include "adc.h"
#include "systick.h"
#include "gd32f4xx.h"
#include <stdio.h>

void adc_config()
{
        /* GPIO 配置 */
        rcu_periph_clock_enable(RCU_GPIOA);
        gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_0);


        /* ADC 配置 */
        rcu_periph_clock_enable(RCU_ADC0);
        adc_deinit();

        /* 主频 */
        adc_clock_config(ADC_ADCCK_PCLK2_DIV8);

        /* ADC 基本配置*/
        adc_resolution_config(ADC0, ADC_RESOLUTION_12B);        // 分辨率
        adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);        // 数据对齐方式，右对齐

        /* ADC 模式配置 */
        adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);        // 扫描模式
        adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, ENABLE);// 连续模式

        /* ADC 规则配置 */
        // 电位器
        adc_channel_length_config(ADC0, ADC_REGULAR_CHANNEL, 2);
        adc_regular_channel_config(ADC0, 0, ADC_CHANNEL_16, ADC_SAMPLETIME_15);        // 温度
        adc_regular_channel_config(ADC0, 1, ADC_CHANNEL_0, ADC_SAMPLETIME_15);        // 电位器
        adc_channel_16_to_18(ADC_TEMP_VREF_CHANNEL_SWITCH, ENABLE);

        /* ADC 需要开启 DMA */
        adc_dma_mode_enable(ADC0);
        adc_dma_request_after_last_enable(ADC0);

        /* 启动ADC */
        adc_enable(ADC0);
        delay_1ms(1);

        /* ADC 校准 */
        adc_calibration_enable(ADC0);
        // 触发ADC进行采样：外部触发/内部触发(软触发)
        adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);
}

void adc_get_vol()
{
        /* 触发ADC进行采样：外部中断（EXTI）触发，内部触发（软中断） */
        adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);

        /* 等待ADC采样完成，获取ADC状态值 */
        while (adc_flag_get(ADC0, ADC_FLAG_EOC) == RESET);

        adc_flag_clear(ADC0, ADC_FLAG_EOC);
        uint16_t value = adc_regular_data_read(ADC0);

        float v = 3.3 * value / 4096;
        printf("vol: %.2f & value: %d\r\n", v, value);
}

void adc_get_temperature()
{
        /* 触发ADC进行采样：外部中断（EXTI）触发，内部触发（软中断） */
        adc_software_trigger_enable(ADC0, ADC_REGULAR_CHANNEL);

        /* 等待ADC采样完成，获取ADC状态值 */
        while (adc_flag_get(ADC0, ADC_FLAG_EOC) == RESET);

        adc_flag_clear(ADC0, ADC_FLAG_EOC);
        uint16_t value = adc_regular_data_read(ADC0);
        float temperature = (1.4 - value) / 4.4 + 25;
        printf("value: %d & temp: %f \r\n", value, temperature);
}

#define BUFF_LENGTH 2
uint16_t buff[BUFF_LENGTH] = {0};

static void adc_dma_get()
{
        /* 温度 */
        uint16_t value = buff[0];
        float temperature = (1.4 - 3.3 * value / 4096) / 4.4 + 25;
        printf("\r\n");
        printf("value: %d & temp: %.2f \r\n", value, temperature);

        printf("==================================================");

        /* 电位器 */
        value = buff[1];
        float v = 3.3 * value / 4096;
        printf("\r\n");
        printf("vol: %.2f & value: %d\r\n", v, value);
}