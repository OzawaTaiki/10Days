#include "RandomGenerator.h"

RandomGenerator::RandomGenerator() : engine(std::random_device{}()) {
    std::random_device rd;
    engine.seed(rd());
}

int RandomGenerator::GetUniformInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(engine);
}

double RandomGenerator::GetUniformDouble() {
    std::uniform_real_distribution<> dist(0.0, 1.0);
    return dist(engine);
}
