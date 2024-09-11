#include "BackGround.h"
#include "utils.h"

void BackGround::Initialize()
{
	pos_[0] = {0.0f,0.0f};
	pos_[1] = {1280.0f,0.0f};

	size_[0] = { 1280.0f,720.0f };
	size_[1] = { 1280.0f,720.0f };
	scale_[0] = { 1.0f,1.0f };
	scale_[1] = { 1.0f,1.0f };

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

	Vector2 drawPosBack[2];
	Vector2 drawPosFront[2];

	drawPosFront[0] = Transform(pos_[0], wvpvpMatFront);
	drawPosFront[1] = Transform(pos_[1], wvpvpMatFront);

	drawPosBack[0] = drawPosFront[0];
	drawPosBack[1] = drawPosFront[1];
	drawPosBack[0].x = drawPosFront[0].x - drawPosBack[0].x / 4.0f;
	drawPosBack[1].x = pos_[1].x + drawPosBack[0].x;

	Novice::DrawSprite((int)drawPosBack[1].x, (int)drawPosBack[1].y, textureHandle_[0], scale_[0].x, scale_[0].y, 0, WHITE);
	Novice::DrawSprite((int)drawPosBack[0].x, (int)drawPosBack[0].y, textureHandle_[0], scale_[0].x, scale_[0].y, 0, WHITE);


	Novice::DrawSprite((int)drawPosFront[0].x, (int)drawPosFront[0].y, textureHandle_[1], scale_[0].x, scale_[0].y, 0, WHITE);
	Novice::DrawSprite((int)drawPosFront[1].x, (int)drawPosFront[1].y, textureHandle_[1], scale_[0].x, scale_[0].y, 0, WHITE);

}
