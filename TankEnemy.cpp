#include "TankEnemy.h"

void TankEnemy::Initialize(const Vector2& _position, Thwomp* _thwompPtr, int _textureHandle)
{
	Enemy::Initialize(_position, _thwompPtr, _textureHandle);
	
	hp_ = 2;
	maxTextureIndex_ = 6;
}

void TankEnemy::Update()
{
	Enemy::Update();
}

void TankEnemy::Draw(const sRendering& _rendring)
{
	if (!isAlive_)
		return;

	Matrix3x3 wMat = MakeAffineMatrix(scale_, rotate_, rect_.pos);
	Matrix3x3 wvpvpMat = _rendring.GetwvpVpMat(wMat);

	for (size_t index = 0; index < 4; ++index)
	{
		rect_.screenVerties[index] = Transform(rect_.localVertices[index], wvpvpMat);
	}


	/*Novice::DrawQuad((int)rect_.screenVerties[0].x - 1, (int)rect_.screenVerties[0].y - 1,
					 (int)rect_.screenVerties[1].x + 1, (int)rect_.screenVerties[1].y - 1,
					 (int)rect_.screenVerties[2].x - 1, (int)rect_.screenVerties[2].y + 1,
					 (int)rect_.screenVerties[3].x + 1, (int)rect_.screenVerties[3].y + 1,
					 0, 0, (int)rect_.size.x + 2, (int)rect_.size.y + 2,
					 textureHandle_, 0xff);*/

	Novice::DrawQuad((int)rect_.screenVerties[0].x, (int)rect_.screenVerties[0].y,
					 (int)rect_.screenVerties[1].x, (int)rect_.screenVerties[1].y,
					 (int)rect_.screenVerties[2].x, (int)rect_.screenVerties[2].y,
					 (int)rect_.screenVerties[3].x, (int)rect_.screenVerties[3].y,
					 int(rect_.size.x * textureIndex_), int((2 - hp_) * rect_.size.y) , (int)rect_.size.x, (int)rect_.size.y,
					 textureHandle_, color_);
}
