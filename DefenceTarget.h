#pragma once
#include "utils.h"
#include "CollisionAtrribute.h"
class Thwomp;

class DefenceTarget
{
public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rendring);

	void OnCollision(CollisoinAttribute _attribute);


	Vector2& GetMove() { return move_; }
	Vector2& GetVelo() { return velocity_; }
	Vector2 GetPos() { return rect_.pos; }
	bool Isalive() { return isAlive_; }
	bool StopInCliff() { return stopInCliff_; }
	bool WalkOnThwomp_() { return walkOnThwomp_; }
	Rect GetRect() const { return rect_; };
	CollisoinAttribute GetCollisoinAttribute() { return CollisoinAttribute::DefenceTarget; }

	void SetWalkOnThwomp(bool _walk) { walkOnThwomp_ = _walk; }
	void SetStopInCliff(bool _stop) { stopInCliff_ = _stop; }
	void SetThwompPtr(Thwomp* _thwompPtr);
	void PositionUpdate();

private:

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
	bool				stopInCliff_;				//段差で止まる
	bool				walkOnThwomp_;

	int					hp_;
	const int			kMaxHp_					= 3;
	bool				isAlive_;


	uint32_t			damageCoolTime_;			//無敵時間（フレーム
	uint32_t			currentCoolTime_;			//無敵時間カウント用
	bool				isInvincible_;

	int					textureIndex_ = 0;				//何枚目を表示するか
	int					currentAnimationCount_ = 0;		//カウント用
	int					animationFrame_ = 10;			//何フレームで切り替えるか

	int					textureHandle_;
	unsigned int		color_;
	

	Thwomp*				thwompPtr_;

	bool Im_isMove_;

	void ShowImgui();


};