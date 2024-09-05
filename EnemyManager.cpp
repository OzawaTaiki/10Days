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
	for (auto& enemy : enemis_)
		enemy->Update();
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
