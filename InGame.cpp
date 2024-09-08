#include "InGame.h"
#include "CollisionAtrribute.h"

void InGame::Initialize()
{
	camera_= std::make_unique<Camera>();
	camera_->Initialize();


	thwomp_ = std::make_unique<Thwomp>();
	thwomp_->Initialize();

	enemyManager_ = enemyManager_->GetInstance();
	enemyManager_->Initialize(thwomp_.get());

	stage_ = std::make_unique<Stage>();
	stage_->Initialize();

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
				カメラ内にいるとき移動
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

	camera_->Update(thwomp_->IsReady());
	//TODO: マップチップの読み込み，描画
	//TODO: マップチップとの衝突判定

	CheckCollisions();

	thwomp_->PositionUpdate();
	defenceTarget_->PositionUpdate();
	enemyManager_->PositionUpdate();

}

void InGame::Draw()
{
	sRendering re = camera_->GetRenderringMatrix();

	DrawAxis(re);
	DrawHorizontalLineAtY(500, re);

	stage_->Draw(re);
	camera_->Draw(re);
	thwomp_->Draw(re);
	enemyManager_->Draw(re);
	defenceTarget_->Draw(re);
	crushingWall_->Draw(re);
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
		// TODO : 張っているときは敵に対してノックバックしない（バグ
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
			thwomp_->OnCollision();
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
		thwomp_->OnCollision();
		defenceTarget_->OnCollision(CollisoinAttribute::Thwomp);
	}

	sLine cRectDownEdge = {
		.sPos = cameraRect.worldVerties[2],
		.ePos = cameraRect.worldVerties[3]
	};

	if (IsCollision(thwompRect, cRectDownEdge))
	{
		thwomp_->OnCollision(); 
		thwomp_->OnCollisionToLine(cRectDownEdge);
	}

	if (stage_->CollisionCheck(thwompRect, thwomp_->GetMove()))
	{
		thwomp_->OnCollision();
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
	}
	// TODO : 護衛対象，壁都も判定を 
}
