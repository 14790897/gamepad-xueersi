#include "tft_display.h"
#include "input.h"
#include "game.h"
#include "buzzer.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char* TAG = "MAIN";

extern "C" void app_main() {
    ESP_LOGI(TAG, "=== Chrome Dino Game Start ===");

    TftDisplay  tft;
    ButtonInput input;
    Buzzer      buzzer;

    // 初始化外设
    if (!tft.begin()) {
        ESP_LOGE(TAG, "Display init failed, halt.");
        return;
    }
    input.begin();
    buzzer.begin();

    DinoGame game(tft, input);

    game.begin();

    // 主循环 ~30fps
    constexpr TickType_t FRAME_MS = pdMS_TO_TICKS(33);

    while (true) {
        input.update();
        game.update();
        vTaskDelay(FRAME_MS);
    }
}
