#pragma once
#include "utils.h"

class BackGround
{
public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rend);
private:
	Vector2				pos_;
	Vector2				size_;
	Vector2				scale_;

	int					textureHandle_[2];
};