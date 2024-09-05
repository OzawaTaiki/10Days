#pragma once
#include "utils.h"
#include "CollisionAtrribute.h"

class Enemy
{
public:
	void Initialize(const Vector2& _position);
	void Update();
	void Draw(const sRendering& _rendring);

	void OnCollision(CollisoinAttribute _attribute);


	bool Isalive() { return isAlive_; }
	Rect GetRect() const { return rect_; };
	CollisoinAttribute GetCollisoinAttribute() { return CollisoinAttribute::DefenceTarget; }


private:

	void Move();
	void Damage();
	void Knockback();

	Rect				rect_;
	Vector2				scale_;
	float				rotate_;

	Vector2				velocity_;
	Vector2				accelelation_;
	Vector2				knockbackVelocity_;
	bool				isKnockback_;

	float				moveSpeed_;
	bool				canMoving_;

	int					hp_;
	const int			kMaxHp_ = 3;
	bool				isAlive_;

	uint32_t			damageCoolTime_;
	bool				damage;

	int					textureHandle_;
	unsigned int		color_;


	bool Im_isMove_;

#ifdef _DEBUG
	void ShowImgui();
#endif // _DEBUG



};