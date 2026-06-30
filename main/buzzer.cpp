#include "buzzer.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

static constexpr ledc_timer_t   TIMER   = LEDC_TIMER_0;
static constexpr ledc_channel_t CHANNEL = LEDC_CHANNEL_0;
static constexpr ledc_mode_t    MODE    = LEDC_LOW_SPEED_MODE;

void Buzzer::begin() {
    ledc_timer_config_t timerCfg = {};
    timerCfg.speed_mode      = MODE;
    timerCfg.timer_num       = TIMER;
    timerCfg.duty_resolution = LEDC_TIMER_10_BIT;
    timerCfg.freq_hz         = 1000;
    timerCfg.clk_cfg         = LEDC_AUTO_CLK;
    ledc_timer_config(&timerCfg);

    ledc_channel_config_t chCfg = {};
    chCfg.speed_mode = MODE;
    chCfg.channel    = CHANNEL;
    chCfg.timer_sel  = TIMER;
    chCfg.intr_type  = LEDC_INTR_DISABLE;
    chCfg.gpio_num   = BUZZER_PIN;
    chCfg.duty       = 0;
    chCfg.hpoint     = 0;
    ledc_channel_config(&chCfg);
}

void Buzzer::tone(uint32_t freqHz, uint32_t durationMs) {
    ledc_set_freq(MODE, TIMER, freqHz);
    ledc_set_duty(MODE, CHANNEL, 512);  // 50% 占空比
    ledc_update_duty(MODE, CHANNEL);
    playing_ = true;

    if (durationMs > 0) {
        vTaskDelay(pdMS_TO_TICKS(durationMs));
        noTone();
    }
}

void Buzzer::noTone() {
    ledc_set_duty(MODE, CHANNEL, 0);
    ledc_update_duty(MODE, CHANNEL);
    playing_ = false;
}

void Buzzer::playJump() {
    tone(600, 80);
}

void Buzzer::playDie() {
    tone(200, 300);
}

void Buzzer::playPoint() {
    tone(800, 50);
    vTaskDelay(pdMS_TO_TICKS(50));
    tone(1200, 50);
}
