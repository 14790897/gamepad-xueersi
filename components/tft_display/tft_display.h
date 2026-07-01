#pragma once
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_types.h"
#include "hal/gpio_types.h"
#include <cstdint>

/**
 * TFT 显示屏封装（基于 esp_lcd 组件驱动 ST7789）
 *
 * 引脚（与 SD 卡共享 SPI2，通过 CS 分时复用）:
 *   SCK  = GPIO18
 *   MOSI = GPIO23
 *   CS   = GPIO5
 *   DC   = GPIO4
 *   RST  = GPIO19
 */

constexpr gpio_num_t PIN_TFT_SCK  = GPIO_NUM_18;
constexpr gpio_num_t PIN_TFT_MOSI = GPIO_NUM_23;
constexpr gpio_num_t PIN_TFT_CS   = GPIO_NUM_5;
constexpr gpio_num_t PIN_TFT_DC   = GPIO_NUM_4;
constexpr gpio_num_t PIN_TFT_RST  = GPIO_NUM_19;

constexpr uint16_t TFT_WIDTH  = 160;
constexpr uint16_t TFT_HEIGHT = 128;

// RGB565 常用颜色
constexpr uint16_t COLOR_BLACK     = 0x0000;
constexpr uint16_t COLOR_WHITE     = 0xFFFF;
constexpr uint16_t COLOR_RED       = 0xF800;
constexpr uint16_t COLOR_GREEN     = 0x07E0;
constexpr uint16_t COLOR_BLUE      = 0x001F;
constexpr uint16_t COLOR_YELLOW    = 0xFFE0;
constexpr uint16_t COLOR_CYAN      = 0x07FF;
constexpr uint16_t COLOR_MAGENTA   = 0xF81F;
constexpr uint16_t COLOR_GRAY      = 0x8410;
constexpr uint16_t COLOR_DARKGRAY  = 0x4208;
constexpr uint16_t COLOR_ORANGE    = 0xFD20;
constexpr uint16_t COLOR_BROWN     = 0xA145;

class TftDisplay {
public:
    TftDisplay() = default;
    ~TftDisplay();

    bool begin();
    void fillScreen(uint16_t color);
    void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
    void drawFastHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color) { fillRect(x, y, w, 1, color); }
    void drawFastVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color) { fillRect(x, y, 1, h, color); }
    void drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
    void drawBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* bitmap);

    uint16_t width()  const { return TFT_WIDTH; }
    uint16_t height() const { return TFT_HEIGHT; }

    esp_lcd_panel_handle_t panel() const { return panel_; }

private:
    esp_lcd_panel_io_handle_t io_     = nullptr;
    esp_lcd_panel_handle_t    panel_  = nullptr;
    uint16_t* fillLineBuf_ = nullptr;  // 用于 fillRect 的行缓冲
};
