#pragma once
#include "hal/gpio_types.h"
#include <cstdint>

/**
 * 无源蜂鸣器 —— 使用 LEDC PWM 驱动
 * 引脚: GPIO14
 */

constexpr gpio_num_t BUZZER_PIN = GPIO_NUM_14;

class Buzzer {
public:
    /// 初始化 LEDC 通道（PWM）
    void begin();

    /// 播放指定频率（Hz），durationMs = 0 表示持续
    void tone(uint32_t freqHz, uint32_t durationMs = 0);

    /// 停止播放
    void noTone();

    /// 播放跳跃音效
    void playJump();

    /// 播放死亡音效
    void playDie();

    /// 播放得分音效
    void playPoint();

private:
    bool playing_ = false;
};
