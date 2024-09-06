#include "EnemyManager.h"

EnemyManager* EnemyManager::GetInstance()
{
	static std::unique_ptr<EnemyManager>enemyManager = std::make_unique< EnemyManager>();
	return enemyManager.get();
}

void EnemyManager::Initialize()
{
	enemis_.clear();
}

void EnemyManager::Update()
{
	for (auto it = enemis_.begin(); it != enemis_.end();)
	{
		if (!(*it)->IsAlive())
		{
			it = enemis_.erase(it);
		}
		else
		{
			(*it)->Update();
			it++;
		}
	}
}

void EnemyManager::Draw(const sRendering& _rendring)
{
	for (auto& enemy : enemis_)
	{
		enemy->Draw(_rendring);
	}
}

void EnemyManager::AddEnemy(const Vector2& _position)
{
	enemis_.push_back(std::make_unique<Enemy>());
	enemis_.back()->Initialize(_position);
}

void EnemyManager::PositionUpdate()
{
	for (auto& enemy : enemis_)
		enemy->PositionUpdate();
}
