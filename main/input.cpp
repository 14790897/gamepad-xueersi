#include "input.h"
#include "driver/gpio.h"

void ButtonInput::begin() {
    // GPIO34/35 是仅输入引脚，不能设置内部上下拉
    gpio_config_t cfgInOnly = {};
    cfgInOnly.pin_bit_mask = (1ULL << BTN_RIGHT) | (1ULL << BTN_A);
    cfgInOnly.mode         = GPIO_MODE_INPUT;
    cfgInOnly.pull_up_en   = GPIO_PULLUP_DISABLE;
    cfgInOnly.pull_down_en = GPIO_PULLDOWN_DISABLE;
    cfgInOnly.intr_type    = GPIO_INTR_DISABLE;
    gpio_config(&cfgInOnly);

    // 其他按键：输入 + 内部上拉
    gpio_config_t cfgPullUp = {};
    cfgPullUp.pin_bit_mask = (1ULL << BTN_UP) | (1ULL << BTN_DOWN) |
                             (1ULL << BTN_LEFT) | (1ULL << BTN_B);
    cfgPullUp.mode         = GPIO_MODE_INPUT;
    cfgPullUp.pull_up_en   = GPIO_PULLUP_ENABLE;
    cfgPullUp.pull_down_en = GPIO_PULLDOWN_DISABLE;
    cfgPullUp.intr_type    = GPIO_INTR_DISABLE;
    gpio_config(&cfgPullUp);
}

uint8_t ButtonInput::read() {
    return currState_;
}

uint8_t ButtonInput::justPressed() {
    return currState_ & ~prevState_;
}

uint8_t ButtonInput::justReleased() {
    return prevState_ & ~currState_;
}

void ButtonInput::update() {
    prevState_ = currState_;
    currState_ = 0;

    // 低电平 = 按下（因为上拉）
    auto readPin = [](gpio_num_t gpio, uint8_t mask) -> uint8_t {
        return (gpio_get_level(gpio) == 0) ? mask : 0;
    };

    currState_ |= readPin(BTN_UP,    BTN_UP_M);
    currState_ |= readPin(BTN_DOWN,  BTN_DOWN_M);
    currState_ |= readPin(BTN_LEFT,  BTN_LEFT_M);
    currState_ |= readPin(BTN_RIGHT, BTN_RIGHT_M);
    currState_ |= readPin(BTN_A,     BTN_A_M);
    currState_ |= readPin(BTN_B,     BTN_B_M);
}
