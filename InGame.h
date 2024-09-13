#pragma once
#include "Thwomp.h"
#include "DefenceTarget.h"
#include "CrushingWall.h"
#include "Camera.h"
#include "Stage.h"
#include "EnemyManager.h"
#include "utils.h"
#include "Scene.h"
#include "BackGround.h"
#include <memory>
#include <vector>

class InGame : public Scene
{
public:
	~InGame();

	void Initialize() override;
	void Update() override;
	void Draw() override;

	uint32_t GetScore() { return score_; }

private:
	void CheckCollisions();

	void DrawScore();
	void DrawHp();

	float score_Scale_ = 0.6f;
	Vector2 score_pos_ = { 20,20 };

	Vector2 HP_Size_ = { 64,64 };
	Vector2 HP_pos_ = { 32,640 };

	sRendering										rendering_;


	EnemyManager*									enemyManager_;

	std::unique_ptr<Stage>							stage_;
	std::unique_ptr<Camera>							camera_;
	std::unique_ptr<Thwomp>							thwomp_;
	std::unique_ptr<CrushingWall>					crushingWall_;
	std::unique_ptr<DefenceTarget>					defenceTarget_;
	std::unique_ptr<BackGround>						backGround_;

	int textureHadle_;

	uint32_t score_;
};