#include "game.h"
#include "lvgl.h"
#include "font/fmt_txt/lv_font_fmt_txt.h"
#include <cstdio>
#include <cstring>

// Extern declare LVGL fonts (not in lvgl.h for unscii)
LV_FONT_DECLARE(lv_font_montserrat_14);

// ──────────── 恐龙像素图 20x24 (RGB565) ────────────
// 0 = 透明, else = 像素颜色
const uint16_t DinoGame::dinoImg[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0x8410,0x8410,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0xFFFF,0x8410,0x8410,0x8410,0x8410,0xFFFF,0x8410,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0x8410,0x8410,0x8410,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0x8410,0x8410,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0x8410,0x8410,0x8410,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0x8410,0x8410,0,0,0,0,0,0,0,0,0,0,0,
};

// ──────────── 仙人掌像素图 12x22 (RGB565) ────────────
const uint16_t DinoGame::cactusImg[] = {
    0,0,0,0,0,0,0,0x07E0,0x07E0,0,0,0,
    0,0,0,0,0,0,0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0,0,0,0,0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0,0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,0,
    0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,0,
    0,0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,0,0,
    0,0,0,0x07E0,0x07E0,0x07E0,0x07E0,0x07E0,0,0,0,0,
};

// ──────────── 鸟像素图 18x14 (RGB565) ────────────
const uint16_t DinoGame::birdImg[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0xF800,0xF800,0xF800,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0xF800,0xF800,0xF800,0xF800,0xF800,0,0,0,0,0,0,0,
    0,0,0,0,0,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0,0,0,0,0,0,0,
    0,0,0,0,0,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0xF800,0xF800,0xF800,0xF800,0xF800,0xF800,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0xF800,0xF800,0xF800,0xF800,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

// ──────────── 字体：使用 LVGL 内置 Montserrat 14 ────────────
static const lv_font_t* gameFont = &lv_font_montserrat_14;

// ──────────── 游戏实现 ────────────

void DinoGame::begin() {
    tft_.fillScreen(COLOR_WHITE);
    drawGround();
    drawDino();

    // 显示提示
    drawString(85, 60, "Press A", COLOR_GRAY);
}

void DinoGame::update() {
    uint8_t btn = input_.justPressed();

    switch (state_) {
    case GameState::READY: {
        if (btn & BTN_A_M) {
            state_ = GameState::PLAYING;
            tft_.fillScreen(COLOR_WHITE);
        }
        break;
    }

    case GameState::PLAYING: {
        // 全局刷新：先清屏，再画所有元素
        tft_.fillScreen(COLOR_WHITE);

        if (input_.read() & BTN_A_M) dino_.jump();
        dino_.ducking = (input_.read() & BTN_B_M) && !dino_.jumping;

        // 更新
        dino_.update();
        speed_ = 3.0f + score_ * 0.02f;

        // 移动障碍物
        for (auto& o : obs_) {
            if (!o.active) continue;
            o.x -= int16_t(speed_);
            if (o.x < -30) o.active = false;
        }

        // 生成障碍物
        if (spawnCD_ == 0) {
            spawnObstacle();
            spawnCD_ = 40 + (rand() % 50);
        } else {
            spawnCD_--;
        }

        // 计分
        score_++;
        frame_++;

        // 碰撞检测
        {
            int16_t dinoY = dino_.y;
            int16_t dinoH = dino_.ducking ? DINO_DUCK_H : DINO_H;
            bool hit = false;
            for (auto& o : obs_) {
                if (!o.active) continue;
                if (DINO_X < o.x + o.w && DINO_X + DINO_W > o.x &&
                    dinoY < o.y + o.h && dinoY + dinoH > o.y) {
                    hit = true;
                    break;
                }
            }
            if (hit) {
                state_ = GameState::GAMEOVER;
                tft_.fillScreen(COLOR_WHITE);
                drawString(70, 80, "GAME OVER", COLOR_RED);
                drawString(85, 100, "A:Restart", COLOR_GRAY);
                break;
            }
        }

        if (state_ == GameState::GAMEOVER) break;

        // 绘制所有元素
        drawGround();
        drawDino();
        drawObstacles();
        drawScore();
        break;
    }

    case GameState::GAMEOVER: {
        if (btn & BTN_A_M) {
            resetGame();
            state_ = GameState::PLAYING;
            tft_.fillScreen(COLOR_WHITE);
        }
        break;
    }
    }
}

void DinoGame::drawGround() {
    // 地面水平线
    tft_.fillRect(0, GROUND_Y, 240, 2, COLOR_GRAY);
    // 地面虚线装饰
    for (int x = frame_ % 8; x < 240; x += 8) {
        tft_.fillRect(x, GROUND_Y + 3, 4, 2, COLOR_DARKGRAY);
    }
}

void DinoGame::drawDino() {
    int16_t dinoY = dino_.y;
    int16_t dinoH = dino_.ducking ? DINO_DUCK_H : DINO_H;

    // 简化：矩形恐龙 + 眼睛
    uint16_t bodyColor = COLOR_GRAY;
    if (dino_.jumping) bodyColor = COLOR_DARKGRAY;

    tft_.fillRect(DINO_X, dinoY, DINO_W, dinoH, bodyColor);
    // 眼睛
    tft_.fillRect(DINO_X + 13, dinoY + 4, 4, 4, COLOR_WHITE);
    tft_.fillRect(DINO_X + 15, dinoY + 5, 2, 2, COLOR_BLACK);
    // 腿
    int legPhase = (frame_ / 4) % 2;
    if (!dino_.jumping) {
        tft_.fillRect(DINO_X + 2, dinoY + dinoH, 3, 4, bodyColor);
        tft_.fillRect(DINO_X + 10, dinoY + dinoH - legPhase * 2, 3, 4, bodyColor);
    } else {
        tft_.fillRect(DINO_X + 6, dinoY + dinoH, 8, 2, bodyColor);
    }
}

void DinoGame::drawObstacles() {
    for (auto& o : obs_) {
        if (!o.active) continue;
        tft_.fillRect(o.x, o.y, o.w, o.h, o.y < GROUND_Y - 20 ? COLOR_RED : COLOR_GREEN);
    }
}

void DinoGame::drawScore() {
    // 右上角显示分数 (LVGL 字体)
    char buf[16];
    snprintf(buf, sizeof(buf), "%lu", score_);
    drawString(2, 2, buf, COLOR_GRAY, gameFont);
}

void DinoGame::drawChar(uint16_t x, uint16_t y, char ch, uint16_t color, const lv_font_t* font) {
    if (!font) font = gameFont;
    if (ch == ' ') return;

    lv_font_glyph_dsc_t dsc;
    if (!lv_font_get_glyph_dsc(font, &dsc, ch, '\0')) return;
    if (dsc.format >= LV_FONT_GLYPH_FORMAT_VECTOR) return;
    if (dsc.box_w == 0 || dsc.box_h == 0) return;

    // Get raw bitmap by calling get_glyph_bitmap with req_raw_bitmap=1 and NULL draw_buf
    dsc.req_raw_bitmap = 1;
    const uint8_t* bitmap = (const uint8_t*)font->get_glyph_bitmap(&dsc, NULL);
    dsc.req_raw_bitmap = 0;
    if (!bitmap) return;

    // Get bpp from the font's internal descriptor
    lv_font_fmt_txt_dsc_t* fdsc = (lv_font_fmt_txt_dsc_t*)font->dsc;
    int bpp = fdsc->bpp;
    int w = dsc.box_w;
    int h = dsc.box_h;

    int16_t sx = x + dsc.ofs_x;
    int16_t sy = y + dsc.ofs_y;

    // Exact LVGL internal decoding algorithm (copied from lv_font_fmt_txt.c)
    static const uint8_t opa4_table[16] = {0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255};
    static const uint8_t opa2_table[4] = {0, 85, 170, 255};

    if (bpp == 1) {
        int i = 0;
        for (int row = 0; row < h; row++) {
            for (int col = 0; col < w; col++, i++) {
                i = i & 0x7;
                uint8_t val = 0;
                if (i == 0) val = (*bitmap) & 0x80 ? 0xFF : 0x00;
                else if (i == 1) val = (*bitmap) & 0x40 ? 0xFF : 0x00;
                else if (i == 2) val = (*bitmap) & 0x20 ? 0xFF : 0x00;
                else if (i == 3) val = (*bitmap) & 0x10 ? 0xFF : 0x00;
                else if (i == 4) val = (*bitmap) & 0x08 ? 0xFF : 0x00;
                else if (i == 5) val = (*bitmap) & 0x04 ? 0xFF : 0x00;
                else if (i == 6) val = (*bitmap) & 0x02 ? 0xFF : 0x00;
                else if (i == 7) { val = (*bitmap) & 0x01 ? 0xFF : 0x00; bitmap++; }
                if (val > 128) tft_.fillRect(sx + col, sy + row, 1, 1, color);
            }
        }
    } else if (bpp == 2) {
        int i = 0;
        for (int row = 0; row < h; row++) {
            for (int col = 0; col < w; col++, i++) {
                i = i & 0x3;
                uint8_t val = 0;
                if (i == 0) val = opa2_table[(*bitmap) >> 6];
                else if (i == 1) val = opa2_table[((*bitmap) >> 4) & 0x3];
                else if (i == 2) val = opa2_table[((*bitmap) >> 2) & 0x3];
                else if (i == 3) { val = opa2_table[(*bitmap) & 0x3]; bitmap++; }
                if (val > 128) tft_.fillRect(sx + col, sy + row, 1, 1, color);
            }
        }
    } else if (bpp == 4) {
        int i = 0;
        for (int row = 0; row < h; row++) {
            for (int col = 0; col < w; col++, i++) {
                i = i & 0x1;
                uint8_t val;
                if (i == 0) val = opa4_table[(*bitmap) >> 4];
                else { val = opa4_table[(*bitmap) & 0xF]; bitmap++; }
                if (val > 128) tft_.fillRect(sx + col, sy + row, 1, 1, color);
            }
        }
    } else if (bpp == 8) {
        for (int row = 0; row < h; row++) {
            for (int col = 0; col < w; col++) {
                if (*bitmap > 128) tft_.fillRect(sx + col, sy + row, 1, 1, color);
                bitmap++;
            }
        }
    }
}

void DinoGame::drawString(uint16_t x, uint16_t y, const char* str, uint16_t color, const lv_font_t* font) {
    if (!font) font = gameFont;
    while (*str) {
        drawChar(x, y, *str, color, font);
        lv_font_glyph_dsc_t dsc;
        if (lv_font_get_glyph_dsc(font, &dsc, *str, '\0')) {
            x += dsc.adv_w;  // advance horizontally
        }
        str++;
    }
}

void DinoGame::spawnObstacle() {
    for (auto& o : obs_) {
        if (o.active) continue;
        o.active = true;
        o.x = 240;
        // 随机选择仙人掌(低)或鸟(高)
        if (rand() % 3 == 0) {
            // 鸟 - 飞在空中
            o.y = GROUND_Y - 50;
            o.w = 18;
            o.h = 14;
        } else {
            // 仙人掌
            o.y = GROUND_Y - 22;
            o.w = 12;
            o.h = 22;
        }
        break;
    }
}

void DinoGame::resetGame() {
    dino_.reset();
    score_ = 0;
    speed_ = 3.0f;
    frame_ = 0;
    spawnCD_ = 0;
    for (auto& o : obs_) o.active = false;
}
