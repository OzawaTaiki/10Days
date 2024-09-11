#pragma once
#include "utils.h"
#include "Scene.h"
#include "Thwomp.h"
#include "EnemyManager.h"
#include "Stage.h"
#include "Camera.h"

#include <memory>

class FromTitle : public Scene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	void ChackCollision();

	std::unique_ptr<Camera>				camera_;
	std::unique_ptr<Thwomp>				thwomp_;
	std::unique_ptr<Stage>				stage_;
	EnemyManager*						enemyManager_;


	int									backGround_;
	int									title_;		
};