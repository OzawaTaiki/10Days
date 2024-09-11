#pragma once

#include "Scene.h"
#include "utils.h"

#include <cstdint>

class Result :public Scene
{
public:
	Result(uint32_t _score) :score_(_score) {};

	void Initialize() override;
	void Update() override;
	void Draw() override;

	int GetNextValue_(){ return hitValue_; };
private:

	float sinValue_[2];
	float count_[2];

	uint32_t score_;

	int hitValue_;

	int Button_toTitle_;
	int Button_continue_;

	float defaultScale_;
	float scale_[2];
	
	Vector2 defaultSize_;
	Vector2 pos_[2];


	int back_;



};