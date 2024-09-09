#pragma once

#include "Vector2.h"
#include <random>

class RandomGenerator {
public:
    static RandomGenerator* GetInstance() { static RandomGenerator instance; return &instance; };

    int GetUniformInt(int min, int max);
    Vector2 GetUniformVec2(float _min, float _max);
    double GetUniformDouble();

private:
    RandomGenerator();

    RandomGenerator(const RandomGenerator&) = delete;
    RandomGenerator& operator=(const RandomGenerator&) = delete;

    // 乱数生成エンジン
    std::mt19937 engine;
};