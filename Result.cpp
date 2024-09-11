#include "Result.h"
#include "Novice.h"
#include "Input.h"
#include "utils.h"
#include "ImGuiManager.h"

void Result::Initialize()
{
	back_ = Novice::LoadTexture("./Resources/Images/result.png");
	Button_continue_= Novice::LoadTexture("./Resources/Images/Button_Continue.png");
	Button_toTitle_= Novice::LoadTexture("./Resources/Images/Button_ToTitle.png");
	
	defaultSize_ = { 256,128 };
	defaultScale_ = 1.0f;

	scale_[0] = defaultScale_;
	scale_[1] = defaultScale_;

	pos_[0] = { 800,400 };
	pos_[1] = { 1088,400 };

	sinValue_[0] = 0.0f;
	sinValue_[0] = 0.0f;

	count_[0] = 0;
	count_[1] = 0;

	scoreDrawPos_ = { 864,64 };
}

void Result::Update()
{

#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_SPACE) ||
#endif // _DEBUG
		Input::GetInstance()->IsTriggerMouse(0) && hitValue_ != -1)
			isChange_ = true;
		else
			hitValue_ = -1;
	for (int i = 0; i < 2; i++)
	{
		if (IsCollisionWithMouse(pos_[i], defaultSize_))
		{
			count_[i] += 0.1f;
			sinValue_[i] = std::sinf(count_[i]);
			scale_[i] = Lerp(sinValue_[i], 1.05f, 0.95f);
			hitValue_ = i;
		}
		else
		{
			count_[i] = 0;
			sinValue_[i] = 0;
			scale_[i] = Lerp(0.1f, defaultScale_, scale_[i]);
		}

	}
}

void Result::Draw()
{
#ifdef _DEBUG
	Novice::ScreenPrintf(0, 0, "ResultScene");
	ImGui::Begin("result");
	ImGui::DragFloat2("continue", &pos_[0].x, 1.0f);
	ImGui::DragFloat("continue_scale", &scale_[0], 0.1f);
	ImGui::DragFloat2("toTitle", &pos_[1].x, 1.0f);
	ImGui::DragFloat("toTitle_scale", &scale_[1], 0.1f);
	ImGui::DragFloat2("score_pos", &scoreDrawPos_.x, 1.0f);
	ImGui::DragFloat("score_scale", &scoreDrawScale_, 0.1f);
	ImGui::End();

#endif // _DEBUG

	Novice::DrawSprite(0, 0, back_, 1, 1, 0, WHITE);
	
	Vector2 drawpos[2];
	drawpos[0] = pos_[0] - defaultSize_ / 2.0f * scale_[0];
	drawpos[1] = pos_[1] - defaultSize_ / 2.0f * scale_[1];

	Novice::DrawSprite((int)drawpos[0].x, (int)drawpos[0].y, Button_continue_, scale_[0], scale_[0], 0, WHITE);
	Novice::DrawSprite((int)drawpos[1].x, (int)drawpos[1].y, Button_toTitle_, scale_[1], scale_[1], 0, WHITE);
	DrawDigit(score_, scoreDrawPos_, 255, scoreDrawScale_);
}
