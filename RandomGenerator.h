#pragma once

#include <random>
#include <memory>
#include <mutex>

class RandomGenerator {
public:
    static RandomGenerator* GetInstance() { static RandomGenerator instance; return &instance; };

    int GetUniformInt(int min, int max);
    double GetUniformDouble();

private:
    RandomGenerator();

    RandomGenerator(const RandomGenerator&) = delete;
    RandomGenerator& operator=(const RandomGenerator&) = delete;

    // 乱数生成エンジン
    std::mt19937 engine;
};