#pragma once
#include "hal/gpio_types.h"
#include <cstdint>

/**
 * 6 键输入模块
 *
 * 上   GPIO2
 * 下   GPIO13
 * 左   GPIO27
 * 右   GPIO35  (仅输入)
 * A    GPIO34  (仅输入)
 * B    GPIO12  (启动敏感，上电避免高电平)
 *
 * 注意：GPIO34/35 仅输入，无内部上下拉
 */

// 按键 GPIO
constexpr gpio_num_t BTN_UP    = GPIO_NUM_2;
constexpr gpio_num_t BTN_DOWN  = GPIO_NUM_13;
constexpr gpio_num_t BTN_LEFT  = GPIO_NUM_27;
constexpr gpio_num_t BTN_RIGHT = GPIO_NUM_35;
constexpr gpio_num_t BTN_A     = GPIO_NUM_34;
constexpr gpio_num_t BTN_B     = GPIO_NUM_12;

// 按键状态掩码（位标志）
enum ButtonMask : uint8_t {
    BTN_NONE  = 0,
    BTN_UP_M    = 1 << 0,
    BTN_DOWN_M  = 1 << 1,
    BTN_LEFT_M  = 1 << 2,
    BTN_RIGHT_M = 1 << 3,
    BTN_A_M     = 1 << 4,
    BTN_B_M     = 1 << 5,
};

class ButtonInput {
public:
    /// 初始化所有按键 GPIO（输入 + 上拉）
    void begin();

    /// 读取当前按键状态（返回掩码组合）
    uint8_t read();

    /// 返回最近一次读取中有按键从"未按下"变为"按下"
    uint8_t justPressed();

    /// 返回最近一次读取中有按键从"按下"变为"未按下"
    uint8_t justReleased();

    /// 更新按键状态（每帧调用一次）
    void update();

private:
    uint8_t prevState_ = 0;
    uint8_t currState_ = 0;
};
