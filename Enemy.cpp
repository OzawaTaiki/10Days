#include "Enemy.h"
#include "ImGuiManager.h"
#include "Thwomp.h"

void Enemy::Initialize(const Vector2& _position, Thwomp* _thwompPtr)
{
	Vector2 pos = _position;
	Vector2 size = { 64,64 };
	pos.y = 500 ;
	pos.x -= size.x / 2.0f;
	pos.y -= size.y / 2.0f;
	rect_.SetValue(pos, size);

	scale_ = { 1,1 };
	rotate_ = 0.0f;

	velocity_ = { 0,0 };
	accelelation_ = { 0,0.5f };

	move_ = { 0,0 };
	baseKnockbackVelocity_ = { 7.0f,-5.0f };
	knockbackVelocity_ = baseKnockbackVelocity_;
	isKnockback_ = false;
	moveSpeed_ = -0.5f;

	canMoving_ = false;

	hp_ = kMaxHp_;
	isAlive_ = true;

	damageCoolTime_ = 120;
	currentCoolTime_ = damageCoolTime_;
	isInvincible_ = false;

	textureHandle_ = 0;
	color_ = 0xffffffff;

	thwompPtr_ = _thwompPtr;

	Im_isMove_ = true;
}

void Enemy::Update()
{
#ifdef _DEBUG
	ShowImgui();
#endif // _DEBUG

	Move();
	UpdateInvincible();

	rect_.Calculate();
	canMoving_ = false;

}

void Enemy::Draw(const sRendering& _rendring)
{
	Matrix3x3 wMat = MakeAffineMatrix(scale_, rotate_, rect_.pos);
	Matrix3x3 wvpvpMat = _rendring.GetwvpVpMat(wMat);

	for (size_t index = 0; index < 4; ++index)
	{
		rect_.screenVerties[index] = Transform(rect_.localVertices[index], wvpvpMat);
	}

	

	Novice::DrawQuad((int)rect_.screenVerties[0].x-1, (int)rect_.screenVerties[0].y-1,
					 (int)rect_.screenVerties[1].x+1, (int)rect_.screenVerties[1].y-1,
					 (int)rect_.screenVerties[2].x-1, (int)rect_.screenVerties[2].y+1,
					 (int)rect_.screenVerties[3].x+1, (int)rect_.screenVerties[3].y+1,
					 0, 0, (int)rect_.size.x+2, (int)rect_.size.y+2,
					 textureHandle_, 0xff);
	Novice::DrawQuad((int)rect_.screenVerties[0].x, (int)rect_.screenVerties[0].y,
					 (int)rect_.screenVerties[1].x, (int)rect_.screenVerties[1].y,
					 (int)rect_.screenVerties[2].x, (int)rect_.screenVerties[2].y,
					 (int)rect_.screenVerties[3].x, (int)rect_.screenVerties[3].y,
					 0, 0, (int)rect_.size.x, (int)rect_.size.y,
					 textureHandle_, color_);

}

void Enemy::OnCollision(CollisoinAttribute _attribute)
{
	switch (_attribute)
	{
	case CollisoinAttribute::Thwomp:
		Damage();
		break;
	case CollisoinAttribute::DefenceTarget:
		break;
	case CollisoinAttribute::ScreenRect:
		canMoving_ = true;
		break;
	case CollisoinAttribute::CrushingWall:
		//Damage();
		//Knockback();
		break;
	case CollisoinAttribute::Enemy:
		break;
	case CollisoinAttribute::Stage:
		if (move_.x == 0)
			velocity_.x = 0;
		if (move_.y == 0)
		{
			velocity_.y = 0;
			isKnockback_ = false;
		}
		break;
	case CollisoinAttribute::KnockbacKRect:
		CalculateKnockbackVelocity(thwompPtr_->GetKnockbackPositoin(rect_.pos),thwompPtr_->GetPos());
		break;
	default:
		break;
	}
}

void Enemy::PositionUpdate()
{
	rect_.pos += move_;
	move_ = { 0,0 };
	rect_.Calculate();
}

void Enemy::Move()
{
	if (isKnockback_)
	{
		velocity_ += accelelation_;
		move_ += velocity_;

		return;
	}

	if (!canMoving_ || !Im_isMove_)
		return;

	velocity_.y += accelelation_.y;
	if (velocity_.y > 15.0f)
		velocity_.y = 15.0f;
	move_.x += moveSpeed_;
	move_.y += velocity_.y;
}

void Enemy::Damage()
{
	// 無敵時間中なら早期リターン
	if (isInvincible_)
		return;

	// ダメージ
	// ０以下なら死
	hp_--;
	if (hp_ <= 0)
	{
		isAlive_ = false;
	}

	// 無敵フラグをたてる
	isInvincible_ = true;
}

void Enemy::Knockback(const Vector2& _velocity)
{
	if (isKnockback_)
		return;

	isKnockback_ = true;
	velocity_ = _velocity;
}

void Enemy::UpdateInvincible()
{
	if (!isInvincible_)
		return;
	// 無敵時間のカウント
	if (--currentCoolTime_ <= 0)
	{
		isInvincible_ = false;
		currentCoolTime_ = damageCoolTime_;
	}
}

void Enemy::CalculateKnockbackVelocity(const Vector2& _targetPos, const Vector2& _thwompPos)
{
	isKnockback_ = true;

	Vector2 toTarget = _targetPos - rect_.pos;

	Vector2 dir = GetDirectionToTarget(_thwompPos, rect_.pos);


	const float kBaseDis = 64.0f;
	float magnification = toTarget.x / kBaseDis;
	magnification = magnification < 0 ? -magnification : magnification;

	velocity_.x = baseKnockbackVelocity_.x * magnification * dir.x;
	velocity_.y = baseKnockbackVelocity_.y;
}

void Enemy::ShowImgui()
{
	ImGui::Begin("Enemy");
	ImGui::DragFloat2("position", &rect_.pos.x, 1.0f);
	ImGui::DragFloat("speed", &moveSpeed_, 0.1f);
	ImGui::DragFloat2("move", &move_.x, 0.1f);
	ImGui::Text("Moving : %s", canMoving_ ? "true" : "false");
	ImGui::Text("HP : %d", hp_);
	ImGui::Text("isAlive : %s", isAlive_ ? "true" : "false");
	ImGui::Checkbox("isMove", &Im_isMove_);
	ImGui::End();
}
