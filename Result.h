#pragma once

#include "Scene.h"

#include <cstdint>

class Result :public Scene
{
public:
	Result(uint32_t _score) :score_(_score) {};

	void Initialize() override;
	void Update() override;
	void Draw() override;



private:
	uint32_t score_;

};