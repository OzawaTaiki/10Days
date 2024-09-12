#include "StacksEnemy.h"
#include "Thwomp.h"

void StacksEnemy::Initialize(const Vector2& _position, Thwomp* _thwompPtr, int _textureHandle, bool _parent)
{
	pos_ = _position;
	Vector2 nPos;
	if (_parent)
		nPos = pos_;
	else
	{
		assert(parent_);
		nPos = pos_ + parent_->GetPos();
	}
	Enemy::Initialize(nPos, _thwompPtr, _textureHandle);

	hp_ = 1;
}

void StacksEnemy::Update()
{
	scale_ = { 1.0f,1.0f };
	if (!canMoving_ || !Im_isMove_)
		return;
	//Move();
	canMoving_ = false;
}

void StacksEnemy::Draw(const sRendering& _rendring)
{
	Enemy::Draw(_rendring);
}

void StacksEnemy::OnCollision(CollisoinAttribute _attribute)
{
	switch (_attribute)
	{
	case CollisoinAttribute::Thwomp:
		Damage();
		break;
	case CollisoinAttribute::DefenceTarget:
		break;
	case CollisoinAttribute::ScreenRect:
		if (!parent_)
			canMoving_ = true;
		Move();
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
		if (!parent_)
			CalculateKnockbackVelocity(thwompPtr_->GetKnockbackPositoin(rect_.pos), thwompPtr_->GetPos());
		break;
	default:
		break;
	}
}

void StacksEnemy::Move()
{
	if (!parent_)
		Enemy::Move();
	else
	{
		rect_.pos = pos_ + parent_->GetPos();
		if (parent_->CanMove())
			Animation();
	}
}
