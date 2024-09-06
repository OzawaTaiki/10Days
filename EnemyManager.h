#pragma once
#include "Enemy.h"
#include "utils.h"
#include <list>
#include <memory>

class EnemyManager
{
public:
	static EnemyManager* GetInstance();

	void Initialize();
	void Update();
	void Draw(const sRendering& _rendring);

	void AddEnemy(const Vector2& _position);
	void PositionUpdate();

	std::list< std::unique_ptr<Enemy>>& GetEnemyList() { return enemis_; }

private:

	std::list< std::unique_ptr<Enemy>> enemis_;

};
