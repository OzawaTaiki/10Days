#include "EnemyManager.h"
#include "Thwomp.h"
#include "ImGuiManager.h"

void EnemyManager::Initialize(Thwomp* _thwompPtr)
{
	enemis_.clear(); 
	thwompPtr_ = _thwompPtr;

	textureHandle_ = Novice::LoadTexture("./Resources/Images/enemy.png");
}

void EnemyManager::Update()
{
	ImGui::Begin("enemy");
	int c = 0;
	for (auto it = enemis_.begin(); it != enemis_.end();)
	{
		if (!(*it)->IsAlive())
		{
			it = enemis_.erase(it);
		}
		else
		{
			(*it)->ShowImgui(c);
			(*it)->Update();
			it++;
			c++;
		}
	}
	ImGui::End();
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
	enemis_.back()->Initialize(_position, thwompPtr_,textureHandle_);
}

void EnemyManager::PositionUpdate()
{
	for (auto& enemy : enemis_)
		enemy->PositionUpdate();
}
