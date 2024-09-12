#pragma once
#include "Enemy.h"


class StacksEnemy : public Enemy
{
public:
	void Initialize(const Vector2& _position, Thwomp* _thwompPtr, int _textureHandle, bool _parent = false);
	void Update()override;
	void Draw(const sRendering& _rendring)override;
	void OnCollision(CollisoinAttribute _attribute)override;

	void SetParent(Enemy* _parent) { parent_ = _parent; }
private:
	void Move();

	Enemy* parent_;
	Vector2 pos_;
};

