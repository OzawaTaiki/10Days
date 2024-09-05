#include "InGame.h"
#include "CollisionAtrribute.h"

void InGame::Initialize()
{
	camera_= std::make_unique<Camera>();
	camera_->Initialize();

	enemyManager_ = enemyManager_->GetInstance();
	enemyManager_->Initialize();

	stage_ = std::make_unique<Stage>();
	stage_->Initialize();

	thwomp_ = std::make_unique<Thwomp>();
	thwomp_->Initialize();

	defenceTarget_ = std::make_unique<DefenceTarget>();
	defenceTarget_->Initialize();

	crushingWall_ = std::make_unique<CrushingWall>();
	crushingWall_->Initialize();

	camera_->SetParent(thwomp_->GetPositoinPtr());
}

void InGame::Update()
{
	/*
	//TODO: 敵．護衛対象の実装
		敵
			カメラ内にいるとき移動（画面サイズの矩形を用意，それとの判定をとる
			ドッスンとの衝突判定
			ドッスンによるノックバック
		護衛対象
				カメラ内にいるとき移動
				壁との衝突判定
				壁によるノックバック
			敵によるノックバック
			ドッスンによるノックバック
			死の概念

	//TODO: 迫る壁の実装
				時間経過で浸食進行
				護衛対象との衝突判定

	*/

	thwomp_->Update();
	defenceTarget_->Update();
	enemyManager_->Update();
	crushingWall_->Update();

	camera_->Update();
	//TODO: マップチップの読み込み，描画，
	//TODO: マップチップとの衝突判定

	CheckCollisions();
}

void InGame::Draw()
{
	sRendering re = camera_->GetRenderringMatrix();

	DrawAxis(re);
	DrawHorizontalLineAtY(500, re);

	camera_->Draw(re);
	thwomp_->Draw(re);
	enemyManager_->Draw(re);
	defenceTarget_->Draw(re);
	crushingWall_->Draw(re);
}

void InGame::CheckCollisions()
{
	Rect cameraRect= camera_->GetRect();
	Rect targetRect= defenceTarget_->GetRect();

	if (IsCollision(cameraRect, targetRect))
	{
		defenceTarget_->OnCollision(CollisoinAttribute::ScreenRect);
	}

	for (auto& enemy : enemyManager_->GetEnemyList())
	{
		Rect enemyRect = enemy->GetRect();
		if (IsCollision(cameraRect, enemyRect))
		{
			enemy->OnCollision(CollisoinAttribute::ScreenRect);
		}

		if (IsCollision(targetRect, enemyRect))
		{
			defenceTarget_->OnCollision(CollisoinAttribute::Enemy);
			enemy->OnCollision(CollisoinAttribute::DefenceTarget);
		}

	}


	Rect wallRect = crushingWall_->GetRect();

	if (IsCollision(wallRect, targetRect))
	{
		defenceTarget_->OnCollision(CollisoinAttribute::CrushingWall);
	}

	Rect thwompRect = thwomp_->GetRect();

	if (IsCollision(thwompRect, targetRect))
	{
		thwomp_->OnCollision();
		defenceTarget_->OnCollision(CollisoinAttribute::Thwomp);
	}

	sLine cRectDownEdge = {
		.sPos = cameraRect.worldVertices[2],
		.ePos = cameraRect.worldVertices[3],
		.color = 0xffffffff
	};

	if (IsCollision(thwompRect, cameraRect))
	{
		thwomp_->OnCollision();
	}

}
