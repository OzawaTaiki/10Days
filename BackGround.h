#pragma once
#include "utils.h"

class BackGround
{
public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rend);
private:
	Vector2				pos_[2];
	Vector2				size_[2];
	Vector2				scale_[2];
	float				moveSpeed_[2];

	int					textureHandle_[2];
};