#include "tft_display.h"
#include "esp_log.h"
#include "driver/spi_master.h"
#include <cstdlib>
#include <cstring>

static const char* TAG = "TFT";

TftDisplay::~TftDisplay() {
    if (panel_) {
        esp_lcd_panel_del(panel_);
    }
    if (io_) {
        esp_lcd_panel_io_del(io_);
    }
    free(fillLineBuf_);
}

bool TftDisplay::begin() {
    // 1. SPI 总线初始化
    spi_bus_config_t busCfg = {};
    busCfg.mosi_io_num     = PIN_TFT_MOSI;
    busCfg.miso_io_num     = GPIO_NUM_NC;
    busCfg.sclk_io_num     = PIN_TFT_SCK;
    busCfg.quadwp_io_num   = -1;
    busCfg.quadhd_io_num   = -1;
    busCfg.max_transfer_sz = TFT_WIDTH * TFT_HEIGHT * 2;

    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &busCfg, SPI_DMA_CH_AUTO));

    // 2. LCD panel IO (SPI)
    esp_lcd_panel_io_spi_config_t ioCfg = {};
    ioCfg.cs_gpio_num       = PIN_TFT_CS;
    ioCfg.dc_gpio_num       = PIN_TFT_DC;
    ioCfg.spi_mode          = 0;
    ioCfg.pclk_hz           = 40 * 1000 * 1000;
    ioCfg.trans_queue_depth = 7;
    ioCfg.lcd_cmd_bits      = 8;
    ioCfg.lcd_param_bits    = 8;

    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(
        reinterpret_cast<esp_lcd_spi_bus_handle_t>(SPI2_HOST), &ioCfg, &io_));

    // 3. ST7789 panel
    esp_lcd_panel_dev_config_t panelCfg = {};
    panelCfg.reset_gpio_num = PIN_TFT_RST;
    panelCfg.rgb_ele_order  = LCD_RGB_ELEMENT_ORDER_RGB;
    panelCfg.bits_per_pixel = 16;

    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_, &panelCfg, &panel_));

    // 4. 初始化序列
    esp_lcd_panel_reset(panel_);
    esp_lcd_panel_init(panel_);
    esp_lcd_panel_invert_color(panel_, true);
    esp_lcd_panel_swap_xy(panel_, false);
    esp_lcd_panel_mirror(panel_, true, false);

    // 5. 打开显示
    esp_lcd_panel_disp_on_off(panel_, true);

    // 6. 分配填充行缓冲
    fillLineBuf_ = static_cast<uint16_t*>(malloc(TFT_WIDTH * sizeof(uint16_t)));

    ESP_LOGI(TAG, "Display initialized (%dx%d)", TFT_WIDTH, TFT_HEIGHT);
    return true;
}

void TftDisplay::fillScreen(uint16_t color) {
    fillRect(0, 0, TFT_WIDTH, TFT_HEIGHT, color);
}

void TftDisplay::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    if (w == 0 || h == 0 || !fillLineBuf_) return;

    for (uint16_t i = 0; i < w; i++) fillLineBuf_[i] = color;

    for (uint16_t row = 0; row < h; row++) {
        esp_lcd_panel_draw_bitmap(panel_, x, y + row, x + w, y + row + 1, fillLineBuf_);
    }
}

void TftDisplay::drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    drawFastHLine(x, y, w, color);
    drawFastHLine(x, y + h - 1, w, color);
    drawFastVLine(x, y, h, color);
    drawFastVLine(x + w - 1, y, h, color);
}

void TftDisplay::drawBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* bitmap) {
    esp_lcd_panel_draw_bitmap(panel_, x, y, x + w, y + h, bitmap);
}
