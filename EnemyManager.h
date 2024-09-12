#pragma once
#include "Enemy.h"
#include "utils.h"
#include <list>
#include <memory>
#include <unordered_map>

class Thwomp;

enum class EnemyType
{
	Fraglie			= 10,			//柔い敵
	Tank			= 20,			//固い敵
	Stacks_Parent	= 30,			//重なってる敵
	Stacks_Child	= 31			//重なってる敵
};

class EnemyManager
{
public:
	static EnemyManager* GetInstance() { static EnemyManager instance; return &instance; };

	void Initialize(Thwomp* _thwompPtr);
	void Update();
	void Draw(const sRendering& _rendring);

	void AddEnemy(const Vector2& _position,uint32_t _type);
	void PositionUpdate();

	std::list< std::unique_ptr<Enemy>>& GetEnemyList() { return enemis_; }

private:

	EnemyManager() = default;

	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;

	int textureHandle_Fraglie_;
	int textureHandle_Tank_;
	int textureHandle_Stacks_;

	std::list< std::unique_ptr<Enemy>> enemis_;
	std::unordered_map<float, std::vector<float>> stacksChildren_;

	Thwomp* thwompPtr_;
};
