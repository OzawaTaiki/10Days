#include "EnemyManager.h"
#include "StacksEnemy.h"
#include "FragileEnemy.h"
#include "Thwomp.h"
#include "ImGuiManager.h"
#include "utils.h"
#include <TankEnemy.h>

void EnemyManager::Initialize(Thwomp* _thwompPtr)
{
	enemis_.clear(); 
	stacksChildren_.clear();
	thwompPtr_ = _thwompPtr;

	textureHandle_Fraglie_ = Novice::LoadTexture("./Resources/Images/enemy_Fraglie.png");
	textureHandle_Tank_ = Novice::LoadTexture("./Resources/Images/enemy_Tank.png");
	textureHandle_Stacks_ = Novice::LoadTexture("./Resources/Images/enemy_Stacks.png");
}

void EnemyManager::Update()
{
#ifdef _DEBUG
	ImGui::Begin("enemy");
#endif // _DEBUG
	int c = 0;
	for (auto it = enemis_.begin(); it != enemis_.end();)
	{
		if (!(*it)->IsAlive())
		{
			it = enemis_.erase(it);
		}
		else
		{
			(*it)->Update();
			(*it)->ShowImgui(c);
			it++;
			c++;
		}
	}
#ifdef _DEBUG
	ImGui::End();
#endif // _DEBUG
}

void EnemyManager::Draw(const sRendering& _rendring)
{
	for (auto& enemy : enemis_)
	{
		enemy->Draw(_rendring);
	}
}

void EnemyManager::AddEnemy(const Vector2& _position, uint32_t _type)
{
	EnemyType type = static_cast<EnemyType>(_type);


	switch (type)
	{
	case EnemyType::Fraglie:
		enemis_.push_back(std::make_unique<FragileEnemy>());
		dynamic_cast<FragileEnemy*>(enemis_.back().get())->Initialize(_position, thwompPtr_, textureHandle_Fraglie_);
		break;
	case EnemyType::Tank:
		enemis_.push_back(std::make_unique<TankEnemy>());
		enemis_.back()->Initialize(_position, thwompPtr_, textureHandle_Tank_);
		break;
	case EnemyType::Stacks_Parent:
		{
			enemis_.push_back(std::make_unique<StacksEnemy>());
			dynamic_cast<StacksEnemy*>(enemis_.back().get())->Initialize(_position, thwompPtr_, textureHandle_Stacks_, true);
			auto parentPtr = enemis_.back().get();

			std::reverse(stacksChildren_[_position.x].begin(), stacksChildren_[_position.x].end());
			for (size_t i = 0; i < stacksChildren_[_position.x].size(); ++i)
			{
				Vector2 offset = { 0,-64 };
				Vector2 pos = { 0,-64 };
				pos += offset * static_cast<float> (i);
				enemis_.push_back(std::make_unique<StacksEnemy>());
				dynamic_cast<StacksEnemy*>(enemis_.back().get())->SetParent(parentPtr);
				dynamic_cast<StacksEnemy*>(enemis_.back().get())->Initialize(pos, thwompPtr_, textureHandle_Stacks_);
			}
			break;
		}
	case EnemyType::Stacks_Child:
		stacksChildren_[_position.x].push_back(_position.y);
		break;
	default:
		break;
	}
}

void EnemyManager::PositionUpdate()
{
	for (auto& enemy : enemis_)
		enemy->PositionUpdate();
}
