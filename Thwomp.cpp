#include "Thwomp.h"
#include "Rendering.h"
#include "Novice.h"
#include "input.h"
#include "ImGuiManager.h"

void Thwomp::Initialize()
{
	Vector2 pos = { 0,0 };
	Vector2 size = { 128,128 };
	rect_.SetValue(pos, size);

	scale_ = { 1,1 };
	rotate_ = 0;

	moveSpeed_ = 5.0f;

	isCharging_ = false;
	isFalling_ = false;
	endFalling_ = true;
	fallSpeed_ = 15.0f;

	color_ = 0xffffffff;
	textureHandle_ = 0;

	input_= Input::GetInstance();
}

void Thwomp::Update()
{
#ifdef _DEBUG
	ShowImgui();
#endif // _DEBUG

	Move();
	Falling();

	if (input_->TriggerKey(DIK_SPACE))
		StartCharging();
	else if (isCharging_ && !input_->PushKey(DIK_SPACE))
		StartFalling();

	rect_.Calculate();
}

void Thwomp::Draw(const sRendering& _rendring)
{
	Matrix3x3 wMat = MakeAffineMatrix(scale_, rotate_, rect_.pos);
	Matrix3x3 wvpvpMat= _rendring.GetwvpVpMat(wMat);

	for (size_t index = 0; index < 4; ++index)
	{
		rect_.worldVertices[index] = Transform(rect_.localVertices[index], wvpvpMat);
	}

	Novice::DrawQuad((int)rect_.worldVertices[0].x, (int)rect_.worldVertices[0].y,
					 (int)rect_.worldVertices[1].x, (int)rect_.worldVertices[1].y,
					 (int)rect_.worldVertices[2].x, (int)rect_.worldVertices[2].y,
					 (int)rect_.worldVertices[3].x, (int)rect_.worldVertices[3].y,
					 0, 0, (int)rect_.size.x, (int)rect_.size.y,
					 textureHandle_, color_);
}

void Thwomp::OnCollision()
{
	endFalling_ = true;
}

void Thwomp::StartCharging()
{
	isCharging_ = true;
	color_ = 0xff0000ff;
}

void Thwomp::StartFalling()
{
	isFalling_ = true;
	isCharging_ = false;
	endFalling_ = false;

	prePos_= rect_.pos;

	color_ = 0x00ff00ff;
}

void Thwomp::Move()
{
	if (input_->PushKey(DIK_A))
	{
		rect_.pos.x -= moveSpeed_;
	}
	if (input_->PushKey(DIK_D))
	{
		rect_.pos.x += moveSpeed_;
	}
	if (input_->PushKey(DIK_W))
	{
		rect_.pos.y -= moveSpeed_;
	}
	if (input_->PushKey(DIK_S))
	{
		rect_.pos.y += moveSpeed_;
	}
}

void Thwomp::Falling()
{
	if (isFalling_)
	{
		if(!endFalling_)
		{
			rect_.pos.y += fallSpeed_;
			//仮判定
			if (rect_.pos.y >= 500)
			{
				endFalling_ = true;
			}
		}
		else
		{
			rect_.pos.y -= 3.0f;
			if (rect_.pos.y <= prePos_.y)
			{
				isFalling_ = false;
				color_ = 0xffffffff;
			}
		}
	}
}

void Thwomp::ShowImgui()
{
	ImGui::Begin("Thwomp");
	ImGui::DragFloat2("position", &rect_.pos.x, 1.0f);
	ImGui::DragFloat("moveSpeed", &moveSpeed_, 0.1f);
	ImGui::DragFloat("fallSpeed", &fallSpeed_, 0.1f);
	ImGui::Text("charging : %s", isCharging_? "true" : "false");
	ImGui::Text(" falling : %s", isFalling_ ? "true" : "false");
	ImGui::Text(" endFall : %s", endFalling_? "true" : "false");
	ImGui::End();
}
