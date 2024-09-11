#include "Title.h"
#include "Novice.h"
#include "Input.h"
#include "utils.h"
#include "ImGuiManager.h"

void Title::Initialize()
{
	backGround_ = Novice::LoadTexture("./Resources/Images/backGround_title.png");
	title_ = Novice::LoadTexture("./Resources/Images/title.png");

	thwomp_ = std::make_unique<Thwomp>();
	thwomp_->Initialize();

	pos_ = { 640,360 };
	scale_ = 1.0f;
	size_ = thwomp_->GetSize();
}

void Title::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
		isChange_ = true;
}

void Title::Draw()
{
#ifdef _DEBUG
	ImGui::Begin("title");
	ImGui::DragFloat("scale", &scale_, 0.01f);
	ImGui::DragFloat2("pos", &pos_.x, 1.0f);
	ImGui::End();
#endif // _DEBUG

	Novice::DrawSprite(0, 0, backGround_, 1, 1, 0, WHITE);
	Novice::DrawSprite(0, 0, title_, 1, 1, 0, WHITE);

	Vector2 drawpos = pos_ - size_ / 2.0f;
	Novice::DrawSpriteRect((int)drawpos.x, (int)drawpos.y,
						   0, 0, (int)size_.x, (int)size_.y, 
						   thwomp_->GetTextureHandle() , 0.25f, 1.0f, 
						   0, WHITE);

}
