#pragma once
#include "Enemy.h"
#include "utils.h"
#include <list>
#include <memory>
#include <mutex>

class Thwomp;

class EnemyManager
{
public:
	static EnemyManager* GetInstance() { static EnemyManager instance; return &instance; };

	void Initialize(Thwomp* _thwompPtr);
	void Update();
	void Draw(const sRendering& _rendring);

	void AddEnemy(const Vector2& _position);
	void PositionUpdate();

	std::list< std::unique_ptr<Enemy>>& GetEnemyList() { return enemis_; }

private:

	EnemyManager() = default;

	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;

	int textureHandle_;
	std::list< std::unique_ptr<Enemy>> enemis_;
	Thwomp* thwompPtr_;
};
