#include "ChangeSceneFromTitle.h"

void FromTitle::Initialize()
{
	backGround_ = Novice::LoadTexture("./Resources/Images/backGround_title.png");
	title_ = Novice::LoadTexture("./Resources/Images/title.png");

	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
	camera_->SetMovableRange({ 0,-720 }, { 1280 ,720 });

	thwomp_ = std::make_unique<Thwomp>();
	thwomp_->Initialize({ 640,-360 }, true);

	stage_ = std::make_unique<Stage>();
	stage_->Initialize();

	Vector2 enemyPopPos = thwomp_->GetPos();
	enemyPopPos.y = 700;

	enemyManager_ = EnemyManager::GetInstance();
	enemyManager_->Initialize(thwomp_.get());
	enemyManager_->AddEnemy(enemyPopPos, static_cast<uint32_t>(EnemyType::Fraglie));

	camera_->SetParent(thwomp_->GetPositoinPtr());
}

void FromTitle::Update()
{
 	thwomp_->StartStagingFromTitle();
	camera_->StartStagingFromTitle(thwomp_->EndFalling());

	ChackCollision();

	thwomp_->PositionUpdate();
	//defenceTarget_->PositionUpdate();
	enemyManager_->PositionUpdate();

	if (thwomp_->isReady())
		isChange_ = true;
}

void FromTitle::Draw()
{
	sRendering re = camera_->GetRenderringMatrix();


	Matrix3x3 vpvpmat = re.GetvpVpMat();
	Vector2  drawpos = Transform({ 0,-720 }, vpvpmat);

	Novice::DrawSprite((int)drawpos.x, (int)drawpos.y, backGround_, 1, 1, 0, WHITE);
	Novice::DrawSprite((int)drawpos.x, (int)drawpos.y, title_, 1, 1, 0, WHITE);

	stage_->Draw(re);
	camera_->Draw(re);
	thwomp_->Draw(re);
	enemyManager_->Draw(re);
}

void FromTitle::ChackCollision()
{
	Rect enemyRect;
	Rect cameraRect = camera_->GetRect();
	Rect thwompRect = thwomp_->GetRect();
	for (auto& enemy : enemyManager_->GetEnemyList())
	{
		enemyRect = enemy->GetRect();

		if (IsCollision(thwompRect, enemyRect))
		{
			thwomp_->OnCollision(CollisoinAttribute::Enemy);
			enemy->Dead();
			camera_->SetMovableRange({ 0,0 }, { 1280,720 });
		}
	}

	if (stage_->CollisionCheck(thwompRect, thwomp_->GetMove()))
	{
		thwomp_->OnCollision(CollisoinAttribute::Stage);
	}
}
