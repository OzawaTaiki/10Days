#include "Enemy.h"
#include "ImGuiManager.h"

void Enemy::Initialize(const Vector2& _position)
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

	knockbackVelocity_ = { 7.0f,-5.0f };
	isKnockback_ = false;
	moveSpeed_ = -0.5f;

	canMoving_ = false;

	hp_ = kMaxHp_;
	isAlive_ = true;

	textureHandle_ = 0;
	color_ = 0xffffffff;

	Im_isMove_ = true;
}

void Enemy::Update()
{
#ifdef _DEBUG
	ShowImgui();
#endif // _DEBUG

	Move();

	rect_.Calculate();
	canMoving_ = false;

}

void Enemy::Draw(const sRendering& _rendring)
{
	Matrix3x3 wMat = MakeAffineMatrix(scale_, rotate_, rect_.pos);
	Matrix3x3 wvpvpMat = _rendring.GetwvpVpMat(wMat);

	for (size_t index = 0; index < 4; ++index)
	{
		rect_.worldVertices[index] = Transform(rect_.localVertices[index], wvpvpMat);
	}

	Novice::DrawQuad((int)rect_.worldVertices[0].x, (int)rect_.worldVertices[0].y,
					 (int)rect_.worldVertices[1].x, (int)rect_.worldVertices[1].y,
					 (int)rect_.worldVertices[2].x, (int)rect_.worldVertices[2].y,
					 (int)rect_.worldVertices[3].x, (int)rect_.worldVertices[3].y,
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
	default:
		break;
	}
}

void Enemy::Move()
{
	if (isKnockback_)
	{
		velocity_ += accelelation_;

		rect_.pos += velocity_;
		if (rect_.pos.y >= 500 - 32)
		{
			rect_.pos.y = 500 - 32;
			isKnockback_ = false;
		}
		return;
	}

	if (!canMoving_ || !Im_isMove_)
		return;

	rect_.pos.x += moveSpeed_;
}

void Enemy::Damage()
{
	hp_--;
	if (hp_ <= 0)
	{
		isAlive_ = false;
	}
}

void Enemy::Knockback()
{
	isKnockback_ = true;
	velocity_ = knockbackVelocity_;
}

void Enemy::ShowImgui()
{
	ImGui::Begin("Enemy");
	ImGui::DragFloat2("position", &rect_.pos.x, 1.0f);
	ImGui::DragFloat("speed", &moveSpeed_, 0.1f);
	ImGui::Text("Moving : %s", canMoving_ ? "true" : "false");
	ImGui::Text("HP : %d", hp_);
	ImGui::Text("isAlive : %s", isAlive_ ? "true" : "false");
	ImGui::Checkbox("isMove", &Im_isMove_);
	ImGui::End();
}
