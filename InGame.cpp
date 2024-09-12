#include "InGame.h"
#include "CollisionAtrribute.h"
#include "ImGuiManager.h"

#include "Input.h"

InGame::~InGame()
{
	// ゲームシーンのところでフェードし始めて
	// ここでBGMとか止めるといいと思う。ｼﾗﾝｹﾄﾞ
}

void InGame::Initialize()
{
	camera_= std::make_unique<Camera>();
	camera_->Initialize();

	thwomp_ = std::make_unique<Thwomp>();
	thwomp_->Initialize({ 640,100 });

	enemyManager_ = enemyManager_->GetInstance();
	enemyManager_->Initialize(thwomp_.get());

	stage_ = std::make_unique<Stage>();
	stage_->Initialize();

	defenceTarget_ = std::make_unique<DefenceTarget>();
	defenceTarget_->Initialize();

	backGround_ = std::make_unique < BackGround>();
	backGround_->Initialize();

	crushingWall_ = std::make_unique<CrushingWall>();
	crushingWall_->Initialize();

	Vector2 range = stage_->GetMapSize() * stage_->GetMapchipSize();
	camera_->SetMovableRange({ 0,0, },range);
	camera_->SetParent(thwomp_->GetPositoinPtr());
	defenceTarget_->SetThwompPtr(thwomp_.get());
}

void InGame::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_R))
		Initialize();

	//stage_->Update();


	thwomp_->Update();
	defenceTarget_->Update();
	enemyManager_->Update();
	crushingWall_->Update();

	camera_->Update(thwomp_->IsFalling(), thwomp_->isReturning(),thwomp_->EndFalling());

	CheckCollisions();

	thwomp_->PositionUpdate();
	defenceTarget_->PositionUpdate();
	enemyManager_->PositionUpdate();

	if (!defenceTarget_->Isalive() || Input::GetInstance()->TriggerKey(DIK_RETURN) || score_ >= 1000)
		isChange_ = true;
}

void InGame::Draw()
{
	sRendering re = camera_->GetRenderringMatrix();

#ifdef _DEBUG
	DrawAxis(re);
#endif // _DEBUG

	backGround_->Draw(re);
	stage_->Draw(re);
	thwomp_->Draw(re);
	enemyManager_->Draw(re);
	defenceTarget_->Draw(re);
	crushingWall_->Draw(re);
	camera_->Draw(re);

	DrawScore();
}

void InGame::CheckCollisions()
{
	Rect enemyRect;
	Rect cameraRect = camera_->GetRect();
	Rect thwompRect = thwomp_->GetRect();
	Rect wallRect = crushingWall_->GetRect();
	Rect targetRect = defenceTarget_->GetRect();

	if (IsCollision(cameraRect, targetRect))
	{
		defenceTarget_->OnCollision(CollisoinAttribute::ScreenRect);
		// TODO : 入っているときは敵に対してノックバックしない（バグ
	}

	for (auto& enemy : enemyManager_->GetEnemyList())
	{
		enemyRect = enemy->GetRect();

		if (IsCollision(cameraRect, enemyRect))
		{
			enemy->OnCollision(CollisoinAttribute::ScreenRect);
		}

		if (IsCollision(targetRect, enemyRect))
		{
			defenceTarget_->OnCollision(CollisoinAttribute::Enemy);
			enemy->OnCollision(CollisoinAttribute::DefenceTarget);
		}
		if (IsCollision(thwompRect, enemyRect))
		{
			thwomp_->OnCollision(CollisoinAttribute::Enemy);
			enemy->OnCollision(CollisoinAttribute::Thwomp);
		}

		if (stage_->CollisionCheck(enemyRect, enemy->GetMove()))
		{
			enemy->OnCollision(CollisoinAttribute::Stage);
		}
	}

	if (IsCollision(wallRect, targetRect))
	{
		defenceTarget_->OnCollision(CollisoinAttribute::CrushingWall);
	}

	if (IsCollision(thwompRect, targetRect))
	{
		thwomp_->OnCollision(CollisoinAttribute::DefenceTarget);
		defenceTarget_->OnCollision(CollisoinAttribute::Thwomp);
	}
	sLine cRectDownEdge = camera_->GetLine();
	if (IsCollision(thwompRect, cRectDownEdge))
	{
		thwomp_->OnCollision(CollisoinAttribute::ScreenRect);
		thwomp_->OnCollisionToLine(cRectDownEdge);
	}

	if (stage_->CollisionCheck(thwompRect, thwomp_->GetMove()))
	{
		thwomp_->OnCollision(CollisoinAttribute::Stage);
	}
	if (stage_->CollisionCheck(targetRect, defenceTarget_->GetMove()))
	{
		defenceTarget_->OnCollision(CollisoinAttribute::Stage);
	}

	auto result = thwomp_->GetKnokbackRect();
	if (result.has_value())
	{
		Rect knockBackRect = *result;
		for (auto& enemy : enemyManager_->GetEnemyList())
		{
			enemyRect = enemy->GetRect();

			if (IsCollision(knockBackRect, enemyRect))
			{
				enemy->OnCollision(CollisoinAttribute::KnockbacKRect);
			}
		}

		if (IsCollision(knockBackRect, targetRect))
		{
			defenceTarget_->OnCollision(CollisoinAttribute::KnockbacKRect);
		}

		if (IsCollision(knockBackRect, wallRect))
		{
			crushingWall_->OnCollision(thwomp_->GetCharge());
		}
	}
}

void InGame::DrawScore()
{
	float moveDis = defenceTarget_->GetPos().x;
	float mapchipSize = stage_->GetMapchipSize();

	score_ = static_cast<uint32_t>(moveDis / mapchipSize);
#ifdef _DEBUG
	ImGui::Begin("Score");
	ImGui::DragFloat2("pos", &score_pos_.x, 1.0f);
	ImGui::DragFloat("scale", &score_Scale_, 0.01f);
	ImGui::End();
#endif // _DEBUG

	DrawDigit(score_, score_pos_, 255, score_Scale_);

}
