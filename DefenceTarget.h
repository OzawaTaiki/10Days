#pragma once
#include "utils.h"
#include "CollisionAtrribute.h"


class DefenceTarget
{
public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rendring);

	void OnCollision(CollisoinAttribute _attribute);


	Vector2& GetMove() { return move_; }
	bool Isalive() { return isAlive_; }
	Rect GetRect() const { return rect_; };
	CollisoinAttribute GetCollisoinAttribute() { return CollisoinAttribute::DefenceTarget; }

	void PositionUpdate();

private:

	void Move();
	void Damage();
	void Knockback(const Vector2& _velocity);
	void UpdateInvincible();


	Rect				rect_;
	Vector2				scale_;
	float				rotate_;
	Vector2				move_;

	Vector2				velocity_;
	Vector2				accelelation_;
	Vector2				baseKnockbackVelocity_;
	Vector2				knockbackVelocity_;
	bool				isKnockback_;

	float				moveSpeed_;
	bool				canMoving_;

	int					hp_;
	const int			kMaxHp_					= 3;
	bool				isAlive_;

	uint32_t			damageCoolTime_;			//無敵時間（フレーム
	uint32_t			currentCoolTime_;			//無敵時間カウント用
	bool				isInvincible_;

	int					textureHandle_;
	unsigned int		color_;


	bool Im_isMove_;

#ifdef _DEBUG
	void ShowImgui();
#endif // _DEBUG


};