/**
 * LVGL v9 最小配置 — ESP32 + ST7789 240x240
 */
#ifndef LV_CONF_H
#define LV_CONF_H

#define LV_COLOR_DEPTH          16
#define LV_COLOR_16_SWAP        0

/* ── 内存 ── */
#define LV_MEM_SIZE             (48U * 1024U)   /* 48KB for LVGL */

/* ── 刷新周期 ── */
#define LV_DEF_REFR_PERIOD      33              /* ~30fps */

/* ── 绘制缓冲区对齐 ── */
#define LV_DRAW_BUF_STRIDE_ALIGN    1
#define LV_DRAW_BUF_ALIGN           4

/* ── Tick 源 ── */
#define LV_TICK_CUSTOM            0
#define LV_TICK_CUSTOM_INCLUDE    0

/* ── 日志 ── */
#define LV_USE_LOG                0

/* ── 功能开关 ── */
#define LV_USE_DRAW_SW            1
#define LV_USE_SYSMON             0
#define LV_USE_PERF_MONITOR       0
#define LV_USE_OBSERVER           0

/* ── 字体 ── */
#define LV_FONT_MONTSERRAT_14            1
#define LV_FONT_DEFAULT_MONTSERRAT_14    1

/* ── 禁用不需要的模块节省 flash ── */
#define LV_USE_ANIMATION          0
#define LV_USE_GRID               0
#define LV_USE_FLEX               0

/* Widgets — 全部禁用，仅用基础绘图 */
#define LV_USE_ARC                0
#define LV_USE_BAR                0
#define LV_USE_BUTTON             0
#define LV_USE_BUTTONMATRIX       0
#define LV_USE_CANVAS             0
#define LV_USE_CHECKBOX           0
#define LV_USE_DROPDOWN           0
#define LV_USE_IMAGE              0
#define LV_USE_LABEL              0
#define LV_USE_LINE               0
#define LV_USE_ROLLER             0
#define LV_USE_SCALE              0
#define LV_USE_SLIDER             0
#define LV_USE_SPAN               0
#define LV_USE_SPINBOX            0
#define LV_USE_SPINNER            0
#define LV_USE_SWITCH             0
#define LV_USE_TABLE              0
#define LV_USE_TEXTAREA           0
#define LV_USE_WIN                0

#endif /* LV_CONF_H */
