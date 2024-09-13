#pragma once
#include "utils.h"
#include "CollisionAtrribute.h"

class Thwomp;

class Enemy
{
public:
	virtual void Initialize(const Vector2& _position, Thwomp* _thwompPtr,int _textureHandle);
	virtual	void Update();
	virtual void Draw(const sRendering& _rendring);

	virtual void OnCollision(CollisoinAttribute _attribute);

	bool IsAlive() { return isAlive_; }
	bool CanMove() { return canMoving_; }
	Vector2& GetMove() { return move_; }
	Vector2 GetPos() { return rect_.pos; }
	Rect GetRect() const { return rect_; };
	CollisoinAttribute GetCollisoinAttribute() { return CollisoinAttribute::DefenceTarget; }

	void PositionUpdate();
	void Dead() { isAlive_ = false; }


	void ShowImgui(int _num);
protected:

	void Move();
	void Damage();
	void Knockback(const Vector2& _velocity);
	void UpdateInvincible();
	void CalculateKnockbackVelocity(const Vector2& _targetPos, const Vector2& _thwompPos);
	
	void Animation();


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
	const int			kMaxHp_ = 2;
	bool				isAlive_;

	Thwomp*				thwompPtr_;


	uint32_t			damageCoolTime_;			//無敵時間（フレーム
	uint32_t			currentCoolTime_;			//無敵時間カウント用
	bool				isInvincible_;

	int						textureIndex_ = 0;				//何枚目を表示するか
	int						currentAnimationCount_ = 0;		//カウント用
	int						animationFrame_ = 10;			//何フレームで切り替えるか
	int						maxTextureIndex_ = 3;

	int					textureHandle_;
	unsigned int		color_;


	bool Im_isMove_;




};