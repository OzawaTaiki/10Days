#include "CrushingWall.h"
#include "ImGuiManager.h"

void CrushingWall::Initialize()
{
	Vector2 pos = { -1480,0 };
	Vector2 size = { 1280,720 };
	Vector2 center = { -840,360 };
	rect_.SetValue(center, size);
	
	moveSpeed_ = 0.5f;

	rotate_ = 0.0f;
	scale_ = { 1.0f,1.0f };

	spriteSize_ = { 1280 ,720 };

	returnValue_[0] = 60;
	returnValue_[1] = 90;
	returnValue_[2] = 150;

	textureHandle_ = Novice::LoadTexture("./Resources/Images/wall.png");
	color_ = 0x808080f0;

	im_isMove_ = true;
}

void CrushingWall::Update()
{
#ifdef _DEBUG
	ShowImgui();
#endif // _DEBUG

	Move();

	Animation();
	rect_.Calculate();
}

void CrushingWall::Draw(const sRendering& _rendring)
{
	Matrix3x3 wMat = MakeAffineMatrix(scale_, rotate_, rect_.pos);
	Matrix3x3 wvpvpMat = _rendring.GetwvpVpMat(wMat);

	for (size_t index = 0; index < 4; ++index)
	{
		rect_.screenVerties[index] = Transform(rect_.localVertices[index], wvpvpMat);
	}

	/*Novice::DrawQuad((int)rect_.screenVerties[0].x, (int)rect_.screenVerties[0].y,
					 (int)rect_.screenVerties[1].x, (int)rect_.screenVerties[1].y,
					 (int)rect_.screenVerties[2].x, (int)rect_.screenVerties[2].y,
					 (int)rect_.screenVerties[3].x, (int)rect_.screenVerties[3].y,
					 0, 0, (int)rect_.size.x, (int)rect_.size.y,
					 textureHandle_, color_);*/

	Novice::DrawQuad((int)rect_.screenVerties[0].x, (int)0,
					 (int)rect_.screenVerties[1].x, (int)0,
					 (int)rect_.screenVerties[2].x, (int)720,
					 (int)rect_.screenVerties[3].x, (int)720,
					 int(spriteSize_.x * textureIndex_), int(0), (int)spriteSize_.x, (int)spriteSize_.y, 
					 textureHandle_, color_);
}

void CrushingWall::OnCollision(size_t _charge)
{
	rect_.pos.x -= returnValue_[_charge] * moveSpeed_;
}

void CrushingWall::Move()
{
	if (im_isMove_)
		rect_.pos.x += moveSpeed_;
}

void CrushingWall::Animation()
{
	currentAnimationCount_++;
	if (currentAnimationCount_ % animationFrame_ == 0)
	{
		textureIndex_++;
		if (textureIndex_ > 5)
			textureIndex_ = 0;
	}
}

void CrushingWall::ShowImgui()
{
#ifdef _DEBUG
	ImGui::Begin("CrushingWall");
	ImGui::Checkbox("isMove", &im_isMove_);
	ImGui::InputInt("animationframe", &animationFrame_);
	ImGui::End();
#endif // _DEBUG
}
