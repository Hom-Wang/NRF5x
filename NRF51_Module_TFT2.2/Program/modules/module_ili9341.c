/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf51_system.h"
#include "drivers\nrf51_spi.h"
#include "algorithms\algorithm_string.h"

#include "module_ili9341.h"
#include "module_fontlib.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LCD_SPIx                    NRF_SPI0

#define LCD_LIG_PIN                 16
//#define BLIGHT_PWM
#ifdef BLIGHT_PWM
  #define LCD_LIG                   TIM2->CCR2
  #define BLIGHT_MAX                255
  #define BLIGHT_MIN                0
  #define BLIGHT_DEFAULT            200
#else
  #define LCD_LIG_H()               __GPIO_SET(LCD_LIG_PIN)
  #define LCD_LIG_L()               __GPIO_RST(LCD_LIG_PIN)
  #define BLIGHT_MAX                1
  #define BLIGHT_MIN                0
  #define BLIGHT_DEFAULT            1
#endif

#define LCD_DC_PIN                  28
#define LCD_DC_H()                  __GPIO_SET(LCD_DC_PIN)
#define LCD_DC_L()                  __GPIO_RST(LCD_DC_PIN)

#define LCD_RST_PIN                 29
#define LCD_RST_H()                 __GPIO_SET(LCD_RST_PIN)
#define LCD_RST_L()                 __GPIO_RST(LCD_RST_PIN)

#define LCD_CST_PIN                 12
#define LCD_CST_H()                 __GPIO_SET(LCD_CST_PIN)
#define LCD_CST_L()                 __GPIO_RST(LCD_CST_PIN)
#define LCD_SCK_PIN                 13
#define LCD_SDO_PIN                 14
#define LCD_SDI_PIN                 15
/*====================================================================================================*/
/*====================================================================================================*/
static SPI_InitTypeDef LCD_InitStruct;
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_WriteCmd
**功能 : Write Command or Address
**輸入 : writeCmd
**輸出 : None
**使用 : LCD_WriteCmd(0xCB);
**====================================================================================================*/
/*====================================================================================================*/
static void LCD_WriteCmd( uint8_t writeCmd )
{
  LCD_CST_L();
  LCD_DC_L();
  SPI_RW(LCD_SPIx, writeCmd);
  LCD_CST_H();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_WriteData
**功能 : Write Data
**輸入 : writeData
**輸出 : None
**使用 : LCD_WriteData(Byte8H(Color));
**====================================================================================================*/
/*====================================================================================================*/
static void LCD_WriteData( uint16_t writeData )
{
  LCD_CST_L();
  LCD_DC_H();
  SPI_RW(LCD_SPIx, writeData);
  LCD_CST_H();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_WriteColor
**功能 : Write Color
**輸入 : color
**輸出 : None
**使用 : LCD_WriteColor(BLACK);
**====================================================================================================*/
/*====================================================================================================*/
static void LCD_WriteColor( uint16_t color )
{
  LCD_CST_L();
  LCD_DC_H();
  SPI_RW(LCD_SPIx, Byte8H(color));
  SPI_RW(LCD_SPIx, Byte8L(color));
  LCD_CST_H();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ILI9341_Config
**功能 : Config ILI9341
**輸入 : None
**輸出 : None
**使用 : ILI9341_Config();
**====================================================================================================*/
/*====================================================================================================*/
void ILI9341_Config( void )
{
  SPI_Cmd(LCD_SPIx, DISABLE);

  nrf_gpio_cfg_output(LCD_DC_PIN);
  nrf_gpio_cfg_output(LCD_RST_PIN);
  ILI9341_LigConfig();

  LCD_InitStruct.PinCS     = LCD_CST_PIN;
  LCD_InitStruct.PinSCK    = LCD_SCK_PIN;
  LCD_InitStruct.PinMISO   = LCD_SDO_PIN;
  LCD_InitStruct.PinMOSI   = LCD_SDI_PIN;
//  SPI_HandleStruct.Init.CLKPolarity       = SPI_POLARITY_HIGH;
//  SPI_HandleStruct.Init.CLKPhase          = SPI_PHASE_2EDGE;
  LCD_InitStruct.CPOL      = SPI_CONFIG_CPOL_ActiveHigh;  // SPI_CONFIG_CPOL_ActiveLow, SPI_CONFIG_CPOL_ActiveHigh
  LCD_InitStruct.CPHA      = SPI_CONFIG_CPHA_Leading;     // SPI_CONFIG_CPHA_Trailing, SPI_CONFIG_CPHA_Leading
  LCD_InitStruct.BitOrder  = SPI_CONFIG_ORDER_MsbFirst;
  LCD_InitStruct.Freguency = SPI_FREQUENCY_FREQUENCY_M8;
  SPI_Init(LCD_SPIx, &LCD_InitStruct);

  SPI_EvenClear(LCD_SPIx);
  SPI_Cmd(LCD_SPIx, ENABLE);

  SPI_RW(LCD_SPIx, 0x00); // Tx Buf
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ILI9341_LigConfig
**功能 : Light I/O Config
**輸入 : None
**輸出 : None
**使用 : ILI9341_LigConfig();
**====================================================================================================*/
/*====================================================================================================*/
static void ILI9341_LigConfig( void )
{
#ifdef BLIGHT_PWM

#else
  nrf_gpio_cfg_output(LCD_LIG_PIN);
  LCD_LIG_L();

#endif
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ILI9341_Init
**功能 : Init ILI9341
**輸入 : None
**輸出 : None
**使用 : ILI9341_Init();
**====================================================================================================*/
/*====================================================================================================*/
void ILI9341_Init( void )
{
  // Reset
  LCD_RST_L();
  Delay_100ms(1);
  LCD_RST_H();
  Delay_10ms(5);

  LCD_WriteCmd(0xCB);
  LCD_WriteData(0x39);
  LCD_WriteData(0x2C);
  LCD_WriteData(0x00);
  LCD_WriteData(0x34);
  LCD_WriteData(0x02);

  LCD_WriteCmd(0xCF);
  LCD_WriteData(0x00);
  LCD_WriteData(0XC1);
  LCD_WriteData(0X30);

  LCD_WriteCmd(0xE8);
  LCD_WriteData(0x85);
  LCD_WriteData(0x00);
  LCD_WriteData(0x78);

  LCD_WriteCmd(0xEA);
  LCD_WriteData(0x00);
  LCD_WriteData(0x00);

  LCD_WriteCmd(0xED);
  LCD_WriteData(0x64);
  LCD_WriteData(0x03);
  LCD_WriteData(0X12);
  LCD_WriteData(0X81);

  LCD_WriteCmd(0xF7);
  LCD_WriteData(0x20);

  LCD_WriteCmd(0xC0);   // Power control
  LCD_WriteData(0x23);  // VRH[5:0]

  LCD_WriteCmd(0xC1);   // Power control
  LCD_WriteData(0x10);  // SAP[2:0];BT[3:0]

  LCD_WriteCmd(0xC5);   // VCM control
  LCD_WriteData(0x3e);  // 對比度調節
  LCD_WriteData(0x28); 

  LCD_WriteCmd(0xC7);   // VCM control2
  LCD_WriteData(0x86);  // --

  LCD_WriteCmd(0x36);   // Memory Access Control
#ifdef H_VIEW
  LCD_WriteData(0x48);  // 豎屏
#else
  LCD_WriteData(0xE8);  // 橫屏
#endif

  LCD_WriteCmd(0x3A);
  LCD_WriteData(0x55);

  LCD_WriteCmd(0xB1);
  LCD_WriteData(0x00);
  LCD_WriteData(0x18);

  LCD_WriteCmd(0xB6);   // Display Function Control
  LCD_WriteData(0x08);
  LCD_WriteData(0x82);
  LCD_WriteData(0x27);

  LCD_WriteCmd(0xF2);   // 3Gamma Function Disable
  LCD_WriteData(0x00);

  LCD_WriteCmd(0x26);   // Gamma curve selected
  LCD_WriteData(0x01);

  LCD_WriteCmd(0xE0);   // Set Gamma
  LCD_WriteData(0x0F);
  LCD_WriteData(0x31);
  LCD_WriteData(0x2B);
  LCD_WriteData(0x0C);
  LCD_WriteData(0x0E);
  LCD_WriteData(0x08);
  LCD_WriteData(0x4E);
  LCD_WriteData(0xF1);
  LCD_WriteData(0x37);
  LCD_WriteData(0x07);
  LCD_WriteData(0x10);
  LCD_WriteData(0x03);
  LCD_WriteData(0x0E);
  LCD_WriteData(0x09);
  LCD_WriteData(0x00);

  LCD_WriteCmd(0XE1);   // Set Gamma
  LCD_WriteData(0x00);
  LCD_WriteData(0x0E);
  LCD_WriteData(0x14);
  LCD_WriteData(0x03);
  LCD_WriteData(0x11);
  LCD_WriteData(0x07);
  LCD_WriteData(0x31);
  LCD_WriteData(0xC1);
  LCD_WriteData(0x48);
  LCD_WriteData(0x08);
  LCD_WriteData(0x0F);
  LCD_WriteData(0x0C);
  LCD_WriteData(0x31);
  LCD_WriteData(0x36);
  LCD_WriteData(0x0F);

  LCD_WriteCmd(0x11);   // Exit Sleep
  Delay_10ms(12);

  LCD_WriteCmd(0x29);   // Display on
  LCD_WriteCmd(0x2C);

  LCD_Clear(BLACK);
  LCD_SetBackLight(BLIGHT_DEFAULT);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_Clear
**功能 : Clear Windows
**輸入 : color
**輸出 : None
**使用 : LCD_Clear(BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_Clear( uint16_t color )
{
  uint32_t point = LCD_W * LCD_H;

  LCD_SetWindow(0, 0, LCD_W-1, LCD_H-1);

  while(point--)
    LCD_WriteColor(color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_SetCursor
**功能 : Set Cursor
**輸入 : coordiX, coordiY
**輸出 : None
**使用 : LCD_SetCursor(StartX, StartY);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_SetCursor( uint16_t coordiX, uint16_t coordiY )
{
  LCD_WriteCmd(0x2A);
  LCD_WriteData(Byte8H(coordiX));
  LCD_WriteData(Byte8L(coordiX));
  LCD_WriteCmd(0x2B);
  LCD_WriteData(Byte8H(coordiY));
  LCD_WriteData(Byte8L(coordiY));
  LCD_WriteCmd(0x2C);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_SetWindow
**功能 : Set Window
**輸入 : startX, startY, endX, endY
**輸出 : None
**使用 : LCD_SetWindow(X0, Y0, X1, Y1);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_SetWindow( uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY )
{
  LCD_WriteCmd(0x2A);
  LCD_WriteData(Byte8H(startX));
  LCD_WriteData(Byte8L(startX));
  LCD_WriteData(Byte8H(endX));
  LCD_WriteData(Byte8L(endX));
  LCD_WriteCmd(0x2B);
  LCD_WriteData(Byte8H(startY));
  LCD_WriteData(Byte8L(startY));
  LCD_WriteData(Byte8H(endY));
  LCD_WriteData(Byte8L(endY));
  LCD_WriteCmd(0x2C);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_SetBackLight
**功能 : Set LCD BackLight
**輸入 : backLight
**輸出 : None
**使用 : LCD_SetBackLight(BLIGHT_DEFAULT);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_SetBackLight( uint16_t backLight )
{
#ifdef BLIGHT_PWM
  if(backLight <= 0)                LCD_LIG = BLIGHT_MIN;
  else if(backLight >= BLIGHT_MAX)  LCD_LIG = BLIGHT_MAX;
  else                              LCD_LIG = BackLight;

#else
  if(backLight == 0)  LCD_LIG_L();
  else                LCD_LIG_H();

#endif
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawPixel
**功能 : Draw a Pixel
**輸入 : coordiX, coordiY, color
**輸出 : None
**使用 : LCD_DrawPixel(coordiX, coordiY, color);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawPixel( uint16_t coordiX, uint16_t coordiY, uint16_t color )
{
  LCD_SetCursor(coordiX, coordiY);
  LCD_WriteColor(color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawLineX
**功能 : Draw X-Axis Line
**輸入 : coordiX, coordiY, length, color
**輸出 : None
**使用 : LCD_DrawLine(coordiX, coordiY, length, color)
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawLineX( uint16_t coordiX, uint16_t coordiY, uint16_t length, uint16_t color )
{
  for(uint16_t i = 0; i < length; i++)
    LCD_DrawPixel(coordiX + i, coordiY, color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawLineY
**功能 : Draw Y-Axis Line
**輸入 : coordiX, coordiY, length, color
**輸出 : None
**使用 : LCD_DrawLine(coordiX, coordiY, length, color)
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawLineY( uint16_t coordiX, uint16_t coordiY, uint16_t length, uint16_t color )
{
  for(uint16_t i = 0; i < length; i++)
    LCD_DrawPixel(coordiX, coordiY + i, color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawRectangle
**功能 : Draw Rectangle
**輸入 : coordiX, coordiY, width, height, color
**輸出 : None
**使用 : LCD_DrawRectangle(coordiX, coordiY, width, height, color)
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawRectangle( uint16_t coordiX, uint16_t coordiY, uint16_t width, uint16_t height, uint16_t color )
{
  for(uint16_t i = 0; i <= height; i++) {
    LCD_DrawPixel(coordiX + i, coordiY, color);
    LCD_DrawPixel(coordiX + i, coordiY + width, color);
  }
  for(uint16_t i = 1; i < width; i++) {
    LCD_DrawPixel(coordiX, coordiY + i, color);
    LCD_DrawPixel(coordiX + height, coordiY + i, color);
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawRectangleFill
**功能 : Draw Rectangle
**輸入 : coordiX, coordiY, width, height, color
**輸出 : None
**使用 : LCD_DrawRectangleFill(coordiX, coordiY, width, height, color)
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawRectangleFill( uint16_t coordiX, uint16_t coordiY, uint16_t width, uint16_t height, uint16_t color )
{
  for(uint16_t i = 0; i < width; i++)
    for(uint16_t j = 0; j < height; j++)
      LCD_DrawPixel(coordiX + j, coordiY + i, color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawCircle
**功能 : Draw Circle
**輸入 : coordiX, coordiY, radius, color
**輸出 : None
**使用 : LCD_DrawCircle(coordiX, coordiY, radius, color)
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawCircle( uint16_t coordiX, uint16_t coordiY, uint16_t radius, uint16_t color )
{
  int a, b;
  int di;

  a = 0;
  b = radius;
  di = 3 - (radius << 1);

  while(a <= b) {
    LCD_DrawPixel(coordiX-b, coordiY-a, color); //3
    LCD_DrawPixel(coordiX+b, coordiY-a, color); //0
    LCD_DrawPixel(coordiX-a, coordiY+b, color); //1
    LCD_DrawPixel(coordiX-b, coordiY-a, color); //7
    LCD_DrawPixel(coordiX-a, coordiY-b, color); //2
    LCD_DrawPixel(coordiX+b, coordiY+a, color); //4
    LCD_DrawPixel(coordiX+a, coordiY-b, color); //5
    LCD_DrawPixel(coordiX+a, coordiY+b, color); //6
    LCD_DrawPixel(coordiX-b, coordiY+a, color);
    a++;
    // 使用 Bresenham 畫圓
    if(di < 0)
      di += 4 * a + 6;
    else {
      di += 10 + 4* (a - b);
      b--;
    }
    LCD_DrawPixel(coordiX + a, coordiY+b, color);
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawPicture
**功能 : Draw Picture
**輸入 : coordiX, coordiY, width, height, Pic
**輸出 : None
**使用 : LCD_DrawPicture(coordiX, coordiY, width, height, Pic);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawPicture( uint16_t coordiX, uint16_t coordiY, uint16_t width, uint16_t height, const uint8_t *pic )
{
  uint16_t *readPixel = (uint16_t*)pic;
  uint32_t j = height * width;

  LCD_SetWindow(coordiX, coordiY, coordiX + width - 1, coordiY + height - 1);

  for(uint32_t i = 0; i < j; i++)
    LCD_WriteColor(readPixel[i]);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_PutChar
**功能 : Put Char
**輸入 : coordiX, coordiY, chWord, fontColor, backColor
**輸出 : None
**使用 : LCD_PutChar(x, y, 'C', WHITE, BLACK)
**====================================================================================================*/
/*====================================================================================================*/
void LCD_PutChar( uint16_t coordiX, uint16_t coordiY, char *chWord, uint16_t fontColor, uint16_t backColor )
{
  uint8_t tmpChar = 0;
  uint16_t i = 0, j = 0;

  for(i = 0; i < 16; i++) {
    tmpChar = ASCII_16x8[*chWord-32][i];
    for(j = 0; j < 8; j++) {
      if(((tmpChar >> (7 - j)) & 0x01) == 0x01)
        LCD_DrawPixel(coordiX + j, coordiY + i, fontColor); // 字符顏色
      else
        LCD_DrawPixel(coordiX + j, coordiY + i, backColor); // 背景顏色
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_PutStr
**功能 : Put String
**輸入 : coordiX, coordiY, chWord, FontStyle, fontColor, backColor
**輸出 : None
**使用 : LCD_PutStr(10, 10, (int8_t*)"TFT LCD TEST ... ", WHITE, BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_PutStr( uint16_t coordiX, uint16_t coordiY, char *chWord, uint16_t fontColor, uint16_t backColor )
{
  uint16_t offsetX = 0;

  while(*chWord) {
    LCD_PutChar(coordiX + offsetX, coordiY, chWord, fontColor, backColor);
    chWord++;
    offsetX += 8;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_PutNum
**功能 : Put Number
**輸入 : oordiX, coordiY, Type, length, numData, fontColor, backColor
**輸出 : None
**使用 : LCD_PutNum(coordiX, coordiY, Type_D, length, numData, WHITE, BLACK)
**====================================================================================================*/
/*====================================================================================================*/
void LCD_PutNum( uint16_t coordiX, uint16_t coordiY, StringType Type, uint8_t length, uint32_t numData, uint16_t fontColor, uint16_t backColor )
{
  char tmpNum[16] = {0};

  num2Str(Type, length, tmpNum, numData);
  LCD_PutStr(coordiX, coordiY, tmpNum, fontColor, backColor);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_TestColoBar
**功能 : Draw Color Bar
**輸入 : None
**輸出 : None
**使用 : LCD_TestColoBar();
**====================================================================================================*/
/*====================================================================================================*/
#define COLOR_TYPE 20
void LCD_TestColoBar( void )
{
  uint32_t i = 0, j = 0;
  uint16_t drawColor[COLOR_TYPE] = {
    WHITE,
    RED,
    GREEN,
    BLUE,
    MAGENTA,
    GRED,
    GBLUE,
    BRED,
    BROWN,
    BRRED,
    CYAN,
    GRAY,
    YELLOW,
    DARKBLUE,
    LIGHTBLUE,
    GRAYBLUE,
    LIGHTGREEN,
    LGRAY,
    LGRAYBLUE,
    LBBLUE
  };

  LCD_SetWindow(0, 0, LCD_W - 1, LCD_H - 1);

  for(i = 0; i < 20; i++) {
    j = (LCD_H / 20) * LCD_W;
    while(j--)
      LCD_WriteColor(drawColor[i]);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
