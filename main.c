/*
 * PROJECT: Kargo Egilme Takip Sistemi
 * PLATFORM: STM32L031K6 Gokhan Beyaz Topkapi University Graduate Project
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stm32l0xx_hal.h"

/* Donanim Tanimlamalari */
#define MPU6050_ADDR 0xD0
#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIOA

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

/* Fonksiyon Prototipleri */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    char uart_msg[100];
    uint8_t wake_up = 0x00;

    // Sensörü Uyandır
    HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, 0x6B, 1, &wake_up, 1, 100);

    while (1) {
        uint8_t sensor_data[6];
        // Ivme verilerini oku
        if (HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, 0x3B, 1, sensor_data, 6, 100) == HAL_OK) {

            int16_t x = (int16_t)(sensor_data[0] << 8 | sensor_data[1]);
            int16_t y = (int16_t)(sensor_data[2] << 8 | sensor_data[3]);
            int16_t z = (int16_t)(sensor_data[4] << 8 | sensor_data[5]);

            float ax = x / 16384.0f;
            float ay = y / 16384.0f;
            float az = z / 16384.0f;

            // Derece cinsinden aci hesapla
            float pitch = atan2(ay, az) * 180.0f / 3.14159f;
            float roll = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0f / 3.14159f;

            // --- KRITIK EGIM KONTROLU (25 DERECE) ---
            if (fabs(pitch) > 25.0f || fabs(roll) > 25.0f) {
                HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET); // LED YANAR
                sprintf(uart_msg, "OTONOMMATIK: KRITIK EGIM! Pitch:%.1f Roll:%.1f\r\n", pitch, roll);
                HAL_UART_Transmit(&huart2, (uint8_t*)uart_msg, strlen(uart_msg), 100);
            } else {
                HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // LED SONER
            }
        }
        HAL_Delay(250);
    }
}

/* Donanim Yapilandirmalari */
static void MX_I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.Timing = 0x00300F38;
    HAL_I2C_Init(&hi2c1);
}

static void MX_USART2_UART_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&huart2);
}

static void MX_GPIO_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}

void SystemClock_Config(void) {} // CubeIDE tarafından üretilen standart ayarlar
