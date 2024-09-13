#include "BackGround.h"
#include "utils.h"

void BackGround::Initialize()
{
	pos_ = {0.0f,0.0f};

	size_ = { 1280.0f,720.0f };
	scale_ = { 1.2f,1.2f };

	textureHandle_[0]= Novice::LoadTexture("./Resources/Images/backGround1.png");
	textureHandle_[1]= Novice::LoadTexture("./Resources/Images/backGround2.png");
}

void BackGround::Update()
{
}

void BackGround::Draw(const sRendering& _rend)
{
	Matrix3x3 wvpvpMatFront = _rend.GetvpVpMat();
	Matrix3x3 wvpvpMatBack = _rend.GetvpVpMat(0.5f);

	Vector2 drawPosBack;
	Vector2 drawPosFront;

	drawPosFront = Transform(pos_, wvpvpMatFront);

	drawPosBack = drawPosFront;
	drawPosBack.x = drawPosFront.x - drawPosBack.x / 4.0f;

	for (int i = 0; i < 10; i++)
		Novice::DrawSprite((int)(drawPosBack.x + size_.x * i), (int)drawPosBack.y, textureHandle_[0], scale_.x, scale_.y, 0, WHITE);

	for (int i = 0; i < 10; i++)
		Novice::DrawSprite((int)(drawPosFront.x + size_.x * i), (int)drawPosFront.y, textureHandle_[1], scale_.x, scale_.y, 0, WHITE);


}
