#ifndef LCD_H_
#define LCD_H_


#include "fsl_spi.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

#include <math.h>

#define LCD_WIDTH  160
#define LCD_HEIGHT 128

#define LCD_RST_0 GPIO_PinWrite(LCD_RST_GPIO, LCD_RST_PORT, LCD_RST_PIN, 0)
#define LCD_RST_1 GPIO_PinWrite(LCD_RST_GPIO, LCD_RST_PORT, LCD_RST_PIN, 1)

#define LCD_DC_0 GPIO_PinWrite(LCD_DC_GPIO, LCD_DC_PORT, LCD_DC_PIN, 0)
#define LCD_DC_1 GPIO_PinWrite(LCD_DC_GPIO, LCD_DC_PORT, LCD_DC_PIN, 1)

#define rgb(r, g, b) ((r >> 3) << 11 ) | ((g >> 2) << 5) | (b >> 3)

#define _RED 	rgb(255, 0, 0)
#define _GREEN 	rgb(0, 255, 0)
#define _BLUE 	rgb(0,0, 255)


void LCD_Init(SPI_Type *base);
void LCD_GramRefresh (void);
void LCD_SetHome();

void LCD_Clear(uint16_t color);
void LCD_Set_Bitmap(uint16_t *data);

void LCD_Draw_Point(uint16_t x1, uint16_t y1, uint16_t color);
void LCD_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

void LCD_Draw_Circle2(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t color);
void LCD_Draw_Circle(uint8_t x0, uint8_t y0, uint8_t radius, uint16_t color);
void LCD_Draw_Dotline(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color);

void LCD_Puts(uint16_t x, uint16_t y, char *text, uint16_t color);
void LCD_7seg(uint16_t x, uint16_t y, int32_t value, int8_t digits, uint16_t color);

void LCD_Set_ImagePart(uint16_t *data, uint16_t xs, uint16_t ys, uint16_t x, uint16_t y);

#endif /* LCD_H_ */
