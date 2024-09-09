#pragma once
#include "Thwomp.h"
#include "DefenceTarget.h"
#include "CrushingWall.h"
#include "Camera.h"
#include "Stage.h"
#include "EnemyManager.h"
#include "utils.h"
#include "Scene.h"
#include <memory>
#include <vector>

class InGame : public Scene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	void CheckCollisions();

	sRendering										rendering_;


	EnemyManager*									enemyManager_;

	std::unique_ptr<Stage>							stage_;
	std::unique_ptr<Camera>							camera_;
	std::unique_ptr<Thwomp>							thwomp_;
	std::unique_ptr<CrushingWall>					crushingWall_;
	std::unique_ptr<DefenceTarget>					defenceTarget_;
};