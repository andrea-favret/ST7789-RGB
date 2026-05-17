#ifndef __ST7789V_STM32_INTERFACE_H
#define __ST7789V_STM32_INTERFACE_H

#include <stdint.h>
#include <stdlib.h>

#include "stm32f0xx_hal.h"

void     LCD_IO_setup_spi(SPI_HandleTypeDef *hspi);           // Setup SPI handle for display communication
void     LCD_IO_setup_gpio(GPIO_TypeDef *DC_port, 
                            uint16_t DC_pin, 
                            GPIO_TypeDef *RESX_port, 
                            uint16_t RESX_pin, 
                            GPIO_TypeDef *CS_port, 
                            uint16_t CS_pin);                // Setup GPIO pins for display control

void     LCD_IO_Init(void);                                  // SPI bus init and LCD RESX pin toggle
void     LCD_IO_WriteCommand(uint8_t command);               // SPI write command
void     LCD_IO_WriteData(uint8_t *data, uint8_t length);    // SPI write data
uint16_t LCD_IO_ReadData(void);                              // SPI read data
void     LCD_IO_Delay(uint32_t delay);                       // Basic MCU delay

#endif // __ST7789V_STM32_INTERFACE_H