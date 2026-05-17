#include "st7789v_stm32_interface.h"
#include "main.h" // Include main header for SPI handle and GPIO definitions
#include "stm32f0xx_hal.h"

SPI_HandleTypeDef *spi_handle;
GPIO_TypeDef *dc_port;
uint16_t dc_pin;
GPIO_TypeDef *resx_port;
uint16_t resx_pin;
GPIO_TypeDef *cs_port;
uint16_t cs_pin;



#define CS_IDLE()    HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_SET)   // Set CS pin HIGH
#define CS_ACTIVE()  HAL_GPIO_WritePin(cs_port, cs_pin, GPIO_PIN_RESET) // Set CS pin LOW

#define RESX_IDLE()    HAL_GPIO_WritePin(resx_port, resx_pin, GPIO_PIN_SET)   // Set RESX pin HIGH
#define RESX_ACTIVE()  HAL_GPIO_WritePin(resx_port, resx_pin, GPIO_PIN_RESET) // Set RESX pin LOW

#define DC_COMMAND()  HAL_GPIO_WritePin(dc_port, dc_pin, GPIO_PIN_RESET) // Set D/CX pin LOW for Command
#define DC_DATA()     HAL_GPIO_WritePin(dc_port, dc_pin, GPIO_PIN_SET)   // Set D/CX pin HIGH for Data

/**
 * @brief Setup SPI handle for display communication
 * 
 */
void LCD_IO_setup_spi(SPI_HandleTypeDef *hspi)
{
    spi_handle = hspi;
} 

/**
 * @brief Setup GPIO pins for display control
 * 
 */
void LCD_IO_setup_gpio(GPIO_TypeDef *DC_port, 
                            uint16_t DC_pin, 
                            GPIO_TypeDef *RESX_port, 
                            uint16_t RESX_pin, 
                            GPIO_TypeDef *CS_port, 
                            uint16_t CS_pin)
{
    dc_port = DC_port;
    dc_pin = DC_pin;
    resx_port = RESX_port;
    resx_pin = RESX_pin;
    cs_port = CS_port;
    cs_pin = CS_pin;
}

/**
 * @brief Initializes display SPI bus and toggles RESX for hardware reset.
 * 
 */
void LCD_IO_Init(void) {
  //* CSX pin  toggle
  CS_IDLE();         // Set CS pin HIGH
  LCD_IO_Delay(20);  // Reset pulse time
  CS_ACTIVE();       // Set CS pin LOW
  LCD_IO_Delay(20);  // Reset pulse time

  //* RESX pin routine
  RESX_IDLE();      // Set RESX pin HIGH
  LCD_IO_Delay(50); // Reset pulse time
  RESX_ACTIVE();    // Set RESX pin LOW
  LCD_IO_Delay(50); // Reset pulse time
  RESX_IDLE();      // Set RESX pin HIGH
  LCD_IO_Delay(50); // Reset pulse time
}

/**
  * @brief  Writes to the display using D/CX pin, selecting Command option.
  */
void LCD_IO_WriteCommand(uint8_t command) {
  DC_COMMAND();   // Set WRX pin LOW to indicate Command
  CS_ACTIVE();    // Set CS pin LOW
  
  // SPI 1-byte transmission example, change this to your SPI transmit function
  HAL_SPI_Transmit(spi_handle, &command, 1, 500);
  
  CS_IDLE();      // Set CS pin HIGH
}

/**
  * @brief  Writes to the display using D/CX pin, selecting Data option.
  * 
  */
void LCD_IO_WriteData(uint8_t *data, uint8_t length) {
  if (length > 0) {
    DC_DATA();      // Set WRX pin HIGH to indicate Data
    CS_ACTIVE();    // Set CS pin LOW
    
    // SPI 1-byte transmission example, change this to your SPI transmit function
    HAL_SPI_Transmit(spi_handle, data, length, 500);
  }

  CS_IDLE();        // Set CS pin HIGH
}

/**
  * @brief  Simple MCU delay in ms.
  * @param  Delay in ms.
  */
void LCD_IO_Delay(uint32_t Delay) {
  HAL_Delay(Delay);  // MCU Delay function
}