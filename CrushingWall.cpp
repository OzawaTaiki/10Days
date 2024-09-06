#include "CrushingWall.h"
#include "ImGuiManager.h"

void CrushingWall::Initialize()
{
	Vector2 pos = { -300,0 };
	Vector2 size = { 100,1440 };
	rect_.SetValue(pos, size);
	
	moveSpeed_ = 0.5f;

	rotate_ = 0.0f;
	scale_ = { 1.0f,1.0f };

	textureHandle_ = 0;
	color_ = 0x808080f0;

	im_isMove_ = true;
}

void CrushingWall::Update()
{
	Move();

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

	Novice::DrawQuad((int)rect_.screenVerties[0].x, (int)rect_.screenVerties[0].y,
					 (int)rect_.screenVerties[1].x, (int)rect_.screenVerties[1].y,
					 (int)rect_.screenVerties[2].x, (int)rect_.screenVerties[2].y,
					 (int)rect_.screenVerties[3].x, (int)rect_.screenVerties[3].y,
					 0, 0, (int)rect_.size.x, (int)rect_.size.y,
					 textureHandle_, color_);
}

void CrushingWall::Move()
{

	rect_.pos.x += moveSpeed_;
}

void CrushingWall::ShowImgui()
{
	ImGui::Begin("CrushingWall");
	ImGui::Checkbox("isMove", &im_isMove_);
	ImGui::End();
}
