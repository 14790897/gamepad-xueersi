# 🦖 Chrome Dino Game — ESP32 版

> 学而思小喵游戏手柄上的谷歌小恐龙游戏，基于 ESP32 + ST7789 TFT。

## 🎮 硬件

| 模块 | 芯片 / 引脚 |
|------|------------|
| 主控 | ESP32-D0WD (240MHz, 4MB Flash) |
| 显示 | ST7789 SPI TFT 240×240 |
| 按键 | 6键：上/下/左/右/A/B |
| 蜂鸣器 | GPIO14 无源蜂鸣器 (PWM) |

## 🕹️ 操作

| 按键 | GPIO | 功能 |
|------|------|------|
| **A** | 34 | 跳跃 / 开始 / 重新开始 |
| **B** | 12 | 下蹲 |

## 🔨 构建

```bash
git clone https://github.com/14790897/gamepad-xueersi.git
cd gamepad-xueersi
idf.py set-target esp32
idf.py build
```

## 📤 烧录

```bash
idf.py -p COMx flash monitor
```

> 波特率默认 460800，按住 BOOT 再按 EN 进入下载模式。

## 📁 项目结构

```
├── main/
│   ├── main.cpp        # 入口 app_main()
│   ├── game.h/.cpp     # 游戏逻辑（恐龙/障碍物/碰撞/记分）
│   ├── input.h/.cpp    # 6 键 GPIO 输入
│   └── buzzer.h/.cpp   # LEDC PWM 蜂鸣器
├── components/tft_display/
│   └── tft_display.h/.cpp  # esp_lcd 封装
└── .github/workflows/
    └── build.yml       # CI: 自动编译固件
```

## 🧪 CI

推送 `main` 分支自动触发 [ESPressif esp-idf-ci-action](https://github.com/espressif/esp-idf-ci-action)，编译产物保留 30 天。

[![Build Firmware](https://github.com/14790897/gamepad-xueersi/actions/workflows/build.yml/badge.svg)](https://github.com/14790897/gamepad-xueersi/actions/workflows/build.yml)
