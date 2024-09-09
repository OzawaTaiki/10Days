#include "camera.h"
#include "Input.h"
#include "ImGuiManager.h"
#include "RandomGenerator.h"

void Camera::Initialize()
{
	kWindowWidth_ = 1280;
	kWindowHeight_ = 720;

	//pos_ = { kWindowWidth_ / 2,kWindowHeight_ / 2 };
	pos_ = { 0,0 };
	size_ = { kWindowWidth_,kWindowHeight_ };
	scale_ = { 1,1 };

	rotate_ = 0;

	moveSpeed_ = 8.0f;
	
	Vector2 rectSize = { 360,640 };
	screenRect_.SetValue(pos_, rectSize);

	isShake_ = false;
	baseShakeCount_ = 30;
	currentShakeCount_ = baseShakeCount_;

	rendering_.worldMatrix = MakeAffineMatrix(scale_, rotate_, pos_);
	rendering_.viewMatrix = Inverse(rendering_.worldMatrix);
	rendering_.orthoMatrix = MakeOrthographicMatrix(-kWindowWidth_ / 2, -kWindowHeight_ / 2, kWindowWidth_ / 2, kWindowHeight_ / 2);
	rendering_.viewportMatrix = MakeViewportMatrix(0, 0, size_.x, size_.y);
}

void Camera::Update(bool _isFalling, bool _isReturning,bool _endFall)
{
#ifdef _DEBUG
	ShowImgui();


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
#endif // _DEBUG


	Vector2 move = { 0,0 };

	if (_isFalling)
	{
		if (Input::GetInstance()->PushKey(DIK_W))

		{
			move.y -= moveSpeed_;
		}
		if (Input::GetInstance()->PushKey(DIK_S))
		{
			move.y += moveSpeed_;
		}

		if (move.y != 0)
		{
			screenRect_.pos += move;

			downLine_.sPos += move;
			downLine_.ePos += move;
		}
	}
	// 落下してないとき
	else
	{
		if (_isReturning)
		{
			screenRect_.pos = lerp(screenRect_.pos, *parent_, 0.1f);
		}
		else
		{
			screenRect_.pos = lerp(screenRect_.pos, *parent_, 0.1f);
			//screenRect_.pos = pos_ + *parent_;
			//returnPos_ = screenRect_.pos;

			downLine_.sPos = screenRect_.worldVerties[2];
			downLine_.ePos = screenRect_.worldVerties[3];
		}
	}

	if (_endFall)
		isShake_ = true;

	Shaking();

	if (isShake_)
		rendering_.worldMatrix = MakeAffineMatrix(scale_, rotate_, screenRect_.pos + shake_);
	else
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

void Camera::Shaking()
{
	if (!isShake_)
		return;

	if (currentShakeCount_ <= 0)
	{
		currentShakeCount_ = baseShakeCount_;
		isShake_ = false;
	}

	--currentShakeCount_;
	shake_ = RandomGenerator::GetInstance()->GetUniformVec2(-5.0f, 5.0f);
}

void Camera::ShowImgui()
{
	ImGui::Begin("Camera");
	ImGui::DragFloat2("position", &pos_.x, 1.0f);
	ImGui::BeginDisabled(true);
	ImGui::DragFloat2("WorldPos", &screenRect_.pos.x, 1.0f);
	ImGui::EndDisabled();
	if (ImGui::DragFloat2("rectSize", &screenRect_.size.x, 1.0f))
		screenRect_.SetValue(pos_, screenRect_.size);
	ImGui::DragFloat("MoveSpeed", &moveSpeed_, 1.0f);
	ImGui::InputInt("shakeTime", &baseShakeCount_);
	ImGui::End();
}


