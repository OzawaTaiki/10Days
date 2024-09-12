#include "FragileEnemy.h"


void FragileEnemy::Initialize(const Vector2& _position, Thwomp* _thwompPtr, int _textureHandle)
{
	Enemy::Initialize(_position, _thwompPtr, _textureHandle);

	hp_ = 1;
}

void FragileEnemy::Update()
{
	Enemy::Update();
}

void FragileEnemy::Draw(const sRendering& _rendring)
{
	Enemy::Draw(_rendring);
}
