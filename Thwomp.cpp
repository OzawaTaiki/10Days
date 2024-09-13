#include "Thwomp.h"
#include "Rendering.h"
#include "Novice.h"
#include "input.h"
#include "RandomGenerator.h"
#include "ImGuiManager.h"
#include "SoundManager.h"

void Thwomp::Initialize(const Vector2& _pos, bool _playStaging)
{
	Vector2 pos = _pos;
	Vector2 size = { 96,128 };
	rect_.SetValue(pos, size);

	Vector2 margin = { 128,0 };
	knockbackSize_[0] = size + margin;
	knockbackSize_[1] = size + margin * 2;
	knockbackSize_[2] = size + margin * 3;

	knockbackRect_.SetValue(pos, knockbackSize_[0]);
	charge_ = 0;
	frameCountForCharge_ = 0;

	//溜め時間
	chargeThreshold_[0] = 120;
	chargeThreshold_[1] = 180;
	chargeThreshold_[2] = 65535;

	chargeScale_[0] = { 1.05f,1.05f };
	chargeScale_[1] = { 1.08f,1.08f };
	chargeScale_[2] = { 1.1f ,1.1f };

	scale_ = { 1,1 };
	rotate_ = 0;

	moveSpeed_ = 5.0f;
	move_ = { 0, 0 };

	isReady_ = true;
	isCharging_ = false;
	isFalling_ = false;
	endFalling_ = false;
	isReturning_ = false;

	fallSpeed_ = 15.0f;

	color_ = 0xffffffff;
	textureHandle_ = Novice::LoadTexture("./Resources/Images/guardon10.png");

	//impacttextureHandle_ = Novice::LoadTexture("./Resources/Images/impact.png");

	input_ = Input::GetInstance();

	fromTitle_ = _playStaging;
	if (fromTitle_)
	{
		StartCharging();
		currentState_ = std::bind(&Thwomp::ChargingState, this);
	}
	else
		currentState_ = std::bind(&Thwomp::ReadyState, this);

}

void Thwomp::Update()
{
	currentState_();

	rect_.Calculate(); 
	knockbackRect_.SetValue(rect_.pos, knockbackSize_[charge_]);

	if (endFalling_) {
		textureIndex_ = 0;
		
	}
	/*if (canKnockBack_) {
		impact = rect_;
		if(impactcount == -1)
		impactcount = 0;
	}
	if (impactcount >= 0) {
		Impact();
	}*/

#ifdef _DEBUG
	ShowImgui();
#endif // _DEBUG
}

void Thwomp::Draw(const sRendering& _rendring)
{
	Matrix3x3 wMat = MakeAffineMatrix(scale_, rotate_, rect_.pos);
	Matrix3x3 wvpvpMat = _rendring.GetwvpVpMat(wMat);

	for (size_t index = 0; index < 4; ++index)
	{
		rect_.screenVerties[index] = Transform(rect_.localVertices[index], wvpvpMat);
		knockbackRect_.screenVerties[index] = Transform(knockbackRect_.localVertices[index], wvpvpMat);
	}

	Novice::DrawQuad((int)rect_.screenVerties[0].x, (int)rect_.screenVerties[0].y,
					 (int)rect_.screenVerties[1].x , (int)rect_.screenVerties[1].y,
					 (int)rect_.screenVerties[2].x , (int)rect_.screenVerties[2].y,
					 (int)rect_.screenVerties[3].x , (int)rect_.screenVerties[3].y,
					 textureIndex_* (int)rect_.size.x, 0, (int)rect_.size.x, (int)rect_.size.y,
					 textureHandle_, color_);

#ifdef _DEBUG
	Novice::DrawBox((int)knockbackRect_.screenVerties[0].x, (int)knockbackRect_.screenVerties[0].y,
					(int)knockbackSize_[charge_].x, (int)knockbackSize_[charge_].y, 0, 0xff, kFillModeWireFrame);
#endif // _DEBUG


}

void Thwomp::OnCollision(CollisoinAttribute _attribute)
{
	switch (_attribute)
	{
	case CollisoinAttribute::Stage:
		canKnockBack_ = true;
	case CollisoinAttribute::ScreenRect:
		if (isFalling_)
			endFalling_ = true;
		break;
	case CollisoinAttribute::DefenceTarget:
	case CollisoinAttribute::Enemy:
	default:
		break;
	}

}

void Thwomp::OnCollisionToLine(const sLine& _line)
{
	move_.y = _line.sPos.y - rect_.pos.y - rect_.size.y / 2.0f;
}

void Thwomp::PositionUpdate()
{
	rect_.pos += move_;
	move_ = { 0,0 };
	rect_.Calculate();
}


std::optional<Rect> Thwomp::GetKnokbackRect() const
{
	if (endFalling_&& isFalling_)
		return knockbackRect_;
	else
		return std::nullopt;
}

Vector2 Thwomp::GetKnockbackPositoin(const Vector2& _posision)
{
	Vector2 result = { 0,rect_.pos.y };
	Vector2 dir = GetDirectionToTarget(rect_.pos, _posision);

	int rand = RandomGenerator::GetInstance()->GetUniformInt(-5, 5);

	// thwompに対して左にいる
	if (dir.x < 0)
	{
		result.x = rect_.pos.x - knockbackSize_[charge_].x / 2.0f + rand;
	}
	else
	{
		result.x = rect_.pos.x + knockbackSize_[charge_].x / 2.0f + rand;
	}

	return result;
}

void Thwomp::StartCharging()
{
	isReady_ = false;
	isCharging_ = true;
	SoundManager::GetInstance()->EnableSound("SE_GuardonCharging");
	//color_ = 0xff0000ff;
	
}

void Thwomp::StartFalling()
{
	isCharging_ = false;
	isFalling_ = true;

	prePos_= rect_.pos;

	frameCountForCharge_ = 0;
	SoundManager::GetInstance()->StopSound("SE_GuardonCharging");
	SoundManager::GetInstance()->EnableSound("SE_GuardonFalling");

	//color_ = 0x00ff00ff;
}

void Thwomp::StartReturning()
{
	isFalling_ = false;
	isReturning_ = true;
	scale_ = { 1,1 };

	SoundManager::GetInstance()->StopSound("SE_GuardonFalling");
	SoundManager::GetInstance()->EnableSound("SE_GuardonLanding");
	if(canKnockBack_)
		SoundManager::GetInstance()->EnableSound("SE_Knockback");

	//color_ = 0x0000ffff;
}

void Thwomp::StartReadyState()
{
	isReady_ = true;
	isCharging_ = false;
	isFalling_ = false;
	endFalling_ = false;
	isReturning_ = false;

	rect_.pos = prePos_;
	SoundManager::GetInstance()->StopSound("SE_GuardonLanding");

	//color_ = 0xffffffff;
}

void Thwomp::StartStagingFromTitle()
{
	prePos_ = { 640,100 };
	currentState_();

	if (frameCountForCharge_ >= chargeThreshold_[1])
		currentState_ = std::bind(&Thwomp::FallingState, this);

	if (isReady_)
		fromTitle_ = false;

	rect_.Calculate(); 
}

void Thwomp::Move()
{
	move_ = { 0,0 };

	if (input_->PushKey(DIK_A))
	{
		move_.x -= moveSpeed_;
	}
	if (input_->PushKey(DIK_D))
	{
		move_.x += moveSpeed_;
	}
	if (input_->PushKey(DIK_W))
	{
		move_.y -= moveSpeed_;
	}
	if (input_->PushKey(DIK_S))
	{
		move_.y += moveSpeed_;
	}
}

void Thwomp::Falling()
{
	move_.y += fallSpeed_;
}

void Thwomp::Returning()
{
	endFalling_ = false;
	rect_.pos.y += -3.0f;
}

void Thwomp::ReadyState()
{
	Move();

	if (input_->TriggerKey(DIK_SPACE))
	{
		StartCharging();
		
		currentState_ = std::bind(&Thwomp::ChargingState, this);
	}
}

void Thwomp::ChargingState()
{
	frameCountForCharge_++;

	for (int i = 0; i < 3; i++)
	{
		if (frameCountForCharge_ >= chargeThreshold_[i])
			continue;

		charge_ = i;
		scale_= chargeScale_[charge_];
		break;
	}
	Animation(frameCountForCharge_);


	if (isCharging_ && !input_->PushKey(DIK_SPACE))
	{
		StartFalling();
		currentState_ = std::bind(&Thwomp::FallingState, this);
	}


}

void Thwomp::FallingState()
{
	Falling();

	if (endFalling_)
	{
		StartReturning();
		currentState_ = std::bind(&Thwomp::ReturningState, this);
	}
}

void Thwomp::ReturningState()
{
	Returning();

	if (prePos_.y >= rect_.pos.y)
	{
		StartReadyState();
		currentState_ = std::bind(&Thwomp::ReadyState, this);
	}
}

void Thwomp::Animation(int frameCountForCharge)
{
	if (frameCountForCharge % 30 == 0) {
		if (textureIndex_ < 7) {
			textureIndex_++;
		}
	}
	

}

//void Thwomp::Impact()
//{
//	if (impactcount < 60) {
//		Novice::DrawQuad((int)impact.screenVerties[0].x-36, (int)impact.screenVerties[0].y,
//			(int)impact.screenVerties[1].x + 36, (int)impact.screenVerties[1].y,
//			(int)impact.screenVerties[2].x - 36, (int)impact.screenVerties[2].y,
//			(int)impact.screenVerties[3].x + 36, (int)impact.screenVerties[3].y,
//			400* impacttextureIndex_, 0, 400, 200,
//			impacttextureHandle_, color_);
//		impactcount++;
//		if (impactcount % 5 == 0) {
//			impacttextureHandle_++;
//		}
//		
//	}
//	else{
//		impactcount = -1;
//		impacttextureHandle_ = 0;
//	}
//}

void Thwomp::ShowImgui()
{
#ifdef _DEBUG
	ImGui::Begin("Thwomp");
	ImGui::DragFloat2("position", &rect_.pos.x, 1.0f);
	ImGui::DragFloat("moveSpeed", &moveSpeed_, 0.1f);
	ImGui::DragFloat("fallSpeed", &fallSpeed_, 0.1f);
	ImGui::DragFloat2("move", &move_.x, 0.1f);
	ImGui::Text(" ready : %s", isReady_? "true" : "false");
	ImGui::Text("charging : %s", isCharging_? "true" : "false");
	ImGui::Text(" falling : %s", isFalling_ ? "true" : "false");
	ImGui::Text(" endFall : %s", endFalling_? "true" : "false");
	ImGui::Text(" Returning : %s", isReturning_? "true" : "false");
	ImGui::InputInt("charge", reinterpret_cast<int*>(&charge_));
	ImGui::End();
#endif // _DEBUG
}
