#pragma once
#include "tft_display.h"
#include "input.h"
#include <cstdint>

/**
 * 谷歌小恐龙 Chrome Dino 游戏
 * 游戏区域: 240x240, 地面线 y=200
 * A键: 跳跃 / 开始    B键: 下蹲
 */

constexpr int16_t GROUND_Y   = 200;
constexpr int16_t DINO_X     = 30;
constexpr int16_t DINO_W     = 20;
constexpr int16_t DINO_H     = 24;
constexpr int16_t DINO_DUCK_H = 14;
constexpr float   GRAVITY    = 0.7f;
constexpr float   JUMP_VEL   = -9.0f;

struct Dino {
    int16_t y      = GROUND_Y - DINO_H;
    float   vy     = 0;
    bool    jumping = false;
    bool    ducking = false;

    void jump() {
        if (!jumping) { vy = JUMP_VEL; jumping = true; }
    }
    void update() {
        y  += int16_t(vy);
        vy += GRAVITY;
        if (y >= GROUND_Y - DINO_H) { y = GROUND_Y - DINO_H; vy = 0; jumping = false; }
    }
    void reset() { y = GROUND_Y - DINO_H; vy = 0; jumping = false; ducking = false; }
};

struct Obstacle {
    int16_t x, y, w, h;
    bool active = false;
};

enum class GameState { READY, PLAYING, GAMEOVER };

class DinoGame {
public:
    DinoGame(TftDisplay& tft, ButtonInput& input) : tft_(tft), input_(input) {}

    void begin();
    void update();

private:
    void drawGround();
    void drawDino();
    void drawObstacles();
    void drawScore();
    void spawnObstacle();
    void resetGame();

    TftDisplay& tft_;
    ButtonInput& input_;
    GameState state_ = GameState::READY;

    Dino dino_;
    Obstacle obs_[4] = {};
    uint32_t score_    = 0;
    float    speed_    = 3.0f;
    uint32_t frame_    = 0;
    uint32_t spawnCD_  = 0;

    // 恐龙像素图 20x24 RGB565
    static const uint16_t dinoImg[];
    // 仙人掌像素图 12x22 RGB565
    static const uint16_t cactusImg[];
    // 鸟像素图 18x14 RGB565
    static const uint16_t birdImg[];
};
