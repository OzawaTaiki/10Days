#pragma once
#include "Enemy.h"

/// <summary>
/// HPの低い敵
/// </summary>
class FragileEnemy :public Enemy
{
public:
	void Initialize(const Vector2& _position, Thwomp* _thwompPtr, int _textureHandle)override;
	void Update()override;
	void Draw(const sRendering& _rendring)override;


private:

};
