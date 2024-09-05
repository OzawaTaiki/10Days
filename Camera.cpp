#include "camera.h"
#include "Input.h"
#include "ImGuiManager.h"

void Camera::Initialize()
{
	kWindowWidth_ = 1280;
	kWindowHeight_ = 720;

	//pos_ = { kWindowWidth_ / 2,kWindowHeight_ / 2 };
	pos_ = { 0,0 };
	size_ = { kWindowWidth_,kWindowHeight_ };
	scale_ = { 1,1 };

	rotate_ = 0;

	moveSpeed_ = 5.0f;
	
	screenRect_.SetValue(pos_, size_ / 2.0f);

	rendering_.worldMatrix = MakeAffineMatrix(scale_, rotate_, pos_);
	rendering_.viewMatrix = Inverse(rendering_.worldMatrix);
	rendering_.orthoMatrix = MakeOrthographicMatrix(-kWindowWidth_ / 2, -kWindowHeight_ / 2, kWindowWidth_ / 2, kWindowHeight_ / 2);
	rendering_.viewportMatrix = MakeViewportMatrix(0, 0, size_.x, size_.y);
}

void Camera::Update()
{
#ifdef _DEBUG
	ShowImgui();
#endif // _DEBUG


	if (Input::GetInstance()->PushKey(DIK_LEFT))
	{
		pos_.x -= moveSpeed_;
	}
	if (Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		pos_.x += moveSpeed_;
	}
	if (Input::GetInstance()->PushKey(DIK_UP))
	{
		pos_.y -= moveSpeed_;
	}
	if (Input::GetInstance()->PushKey(DIK_DOWN))
	{
		pos_.y += moveSpeed_;
	}

	screenRect_.pos = pos_;
	if (parent_)
		screenRect_.pos = pos_ + *parent_;

	rendering_.worldMatrix = MakeAffineMatrix(scale_, rotate_, screenRect_.pos);
	rendering_.viewMatrix = Inverse(rendering_.worldMatrix);
	rendering_.orthoMatrix = MakeOrthographicMatrix(-kWindowWidth_ / 2, -kWindowHeight_ / 2, kWindowWidth_ / 2, kWindowHeight_ / 2);
	rendering_.viewportMatrix = MakeViewportMatrix(0, 0, size_.x, size_.y);

	screenRect_.Calculate();

}

void Camera::Draw(const sRendering& _rendring)
{
	_rendring;
	Vector2 drawpos = pos_ - screenRect_.size / 2.0f;
	Matrix3x3 wMat = MakeAffineMatrix(scale_, rotate_, drawpos);
	Matrix3x3 wvpvpMat = _rendring.GetwvpVpMat(wMat);

	drawpos = Transform(screenRect_.pos, wvpvpMat);

	Novice::DrawBox((int)drawpos.x, (int)drawpos.y, (int)screenRect_.size.x, (int)screenRect_.size.y, 0, 0x000000ff, kFillModeWireFrame);
}

void Camera::ShowImgui()
{
	ImGui::Begin("Camera");
	ImGui::DragFloat2("position", &pos_.x, 1.0f);
	ImGui::BeginDisabled(true);
	ImGui::DragFloat2("WorldPos", &screenRect_.pos.x, 1.0f);
	ImGui::EndDisabled();
	if (ImGui::DragFloat2("WorldPos", &screenRect_.size.x, 1.0f))
		screenRect_.SetValue(pos_, screenRect_.size);
	ImGui::DragFloat("MoveSpeed", &moveSpeed_, 1.0f);
	ImGui::End();
}


