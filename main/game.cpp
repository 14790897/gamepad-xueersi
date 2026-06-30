#include "game.h"
#include <cstdio>
#include <cstring>

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

// ──────────── 数字 0-9 简单 5x7 像素图 ────────────
static const uint16_t digitW = 5, digitH = 7;
static const uint8_t digits[10][7] = {
    {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E},  // 0
    {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E},  // 1
    {0x0E,0x11,0x01,0x0E,0x10,0x10,0x1F},  // 2
    {0x0E,0x11,0x01,0x0E,0x01,0x11,0x0E},  // 3
    {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02},  // 4
    {0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E},  // 5
    {0x0E,0x10,0x10,0x1E,0x11,0x11,0x0E},  // 6
    {0x1F,0x01,0x02,0x04,0x08,0x08,0x08},  // 7
    {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E},  // 8
    {0x0E,0x11,0x11,0x0F,0x01,0x11,0x0E},  // 9
};

// ──────────── 游戏实现 ────────────

void DinoGame::begin() {
    tft_.fillScreen(COLOR_WHITE);
    drawGround();
    drawDino();

    // 显示提示
    const char* txt = "Press A";
    uint16_t x = 100;
    for (const char* p = txt; *p; p++) {
        tft_.fillRect(x, 60, 5, 7, COLOR_GRAY);
        x += 7;
    }
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
        // 清除上一帧
        {
            int16_t dinoY = dino_.y;
            int16_t dinoH = dino_.ducking ? DINO_DUCK_H : DINO_H;
            (void)dinoY; (void)dinoH;
            // 清除恐龙旧位置
            tft_.fillRect(DINO_X, 0, DINO_W, GROUND_Y, COLOR_WHITE);
        }

        // 输入处理
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
                // 显示 GAME OVER
                const char* go = "GAME OVER";
                uint16_t gx = 75;
                for (const char* p = go; *p; p++) {
                    if (*p != ' ') tft_.fillRect(gx, 80, 5, 7, COLOR_RED);
                    gx += 7;
                }
                const char* rs = "A:Restart";
                gx = 85;
                for (const char* p = rs; *p; p++) {
                    if (*p != ':') tft_.fillRect(gx, 100, 5, 7, COLOR_GRAY);
                    gx += 7;
                }
                break;
            }
        }

        if (state_ == GameState::GAMEOVER) break;

        // 清除障碍物旧区域
        for (auto& o : obs_) {
            if (!o.active) continue;
            tft_.fillRect(o.x + int16_t(speed_), o.y, int16_t(speed_) + 2, o.h, COLOR_WHITE);
        }

        // 绘制
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
    // 地面线
    tft_.drawFastHLine(0, GROUND_Y, 240, COLOR_GRAY);
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
        tft_.fillRect(DINO_X + 2,  dinoY + dinoH, 3, 4, bodyColor);
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
    // 右上角显示分数，用简单 5x7 字体
    char buf[16];
    snprintf(buf, sizeof(buf), "%lu", score_);
    uint16_t cx = 235;
    for (int i = strlen(buf) - 1; i >= 0; i--) {
        int d = buf[i] - '0';
        if (d < 0 || d > 9) continue;
        for (int y = 0; y < digitH; y++) {
            uint8_t row = digits[d][y];
            for (int x = 0; x < digitW; x++) {
                if (row & (1 << (digitW - 1 - x))) {
                    tft_.fillRect(cx + x, 5 + y, 1, 1, COLOR_GRAY);
                }
            }
        }
        cx -= (digitW + 1);
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
